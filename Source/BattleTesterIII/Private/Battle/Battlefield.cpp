// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle/Battlefield.h"

#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/Texture2D.h"

#include "Battle/BattleSpotBillboardComponent.h"

#include "MyGameInstance.h"
#include "MyGameMode.h"
#include "PartyManager.h"
#include "BattleManager.h"
#include "AI/BattleAIController.h"
#include "Characters/Enemy.h"
#include "Characters/Hero.h"
#include "Enums/CharacterDirection.h"

#if WITH_EDITOR
void ABattlefield::PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.Property && (PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(ABattlefield, HeroSpotTexture) ||
										  PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(ABattlefield, EnemySpotTexture)))
	{
		this->updateBillboardTextures();
	}
}

void ABattlefield::updateBillboardTextures()
{
	for (UBattleSpotBillboardComponent *HeroSpot : HeroesPositions)
	{
		if (HeroSpot)
		{
			HeroSpot->SetSprite(this->HeroSpotTexture);
		}
	}

	for (UBattleSpotBillboardComponent *EnemySpot : EnemiesPositions)
	{
		if (EnemySpot)
		{
			EnemySpot->SetSprite(this->EnemySpotTexture);
		}
	}
}
#endif

void ABattlefield::BeginPlay()
{
	Super::BeginPlay();

	this->partyMembers = Cast<UMyGameInstance>(this->GetGameInstance())->PartyManager->PartyMembers;

	for (int i = 0; i < this->MAX_NUMBER_OF_HEROES && this->partyMembers.Num(); i++)
	{
		AHero *hero = this->partyMembers[i];

		if (hero && this->HeroesPositions[i])
		{
			hero->SetBattleSpot(this->HeroesPositions[i]->GetBattleSpot());

			this->amountOfBattleSpots++;
		}
	}

	for (int i = 0; i < this->MAX_NUMBER_OF_ENEMIES && this->Enemies.Num(); i++)
	{
		AEnemy *enemy = this->Enemies[i];

		if (this->Enemies[i] && this->EnemiesPositions[i])
		{
			enemy->SetBattleSpot(this->EnemiesPositions[i]->GetBattleSpot());

			this->amountOfBattleSpots++;
		}
	}
}

void ABattlefield::IncrementSucessBattleSpots()
{
	this->amountOfActorsReachedBattleSpot++;

	if (this->amountOfBattleSpots == this->amountOfActorsReachedBattleSpot && !BattleStarted)
	{
		this->BattleStarted = true;

		AMyGameMode *gameMode = Cast<AMyGameMode>(this->GetWorld()->GetAuthGameMode());

		if (gameMode)
		{
			if (gameMode->BattleManager)
			{
				gameMode->BattleManager->Start(this);
			}
		}
	}
}

void ABattlefield::MoveActorsToBattleLocations()
{
	auto executeMoveToActor = [&](ACombatCharacter *actor)
	{
		if (!actor)
		{
			return;
		}

		ABattleAIController *actorIAController = Cast<ABattleAIController>(actor->GetController());

		actorIAController->MoveToBattleSpot();
	};

	for (AHero *hero : this->partyMembers)
	{
		executeMoveToActor(hero);
	}

	for (AEnemy *enemy : this->Enemies)
	{
		executeMoveToActor(enemy);
	}
}

ABattlefield::ABattlefield()
{
	this->BattleBoundaries = CreateDefaultSubobject<UBoxComponent>(TEXT("RootBoxCollision"));
	this->RootComponent = this->BattleBoundaries;
	this->BattleBoundaries->InitBoxExtent(FVector(500.0f, 500.0f, 50.0f));

	auto createLine = [&](USceneComponent *&lineRef, FString lineName, int32 count, TArray<UBattleSpotBillboardComponent *> *billboardsRef, FString spotName, ECharacterDirection defaultDirection) -> void
	{
		lineRef = CreateDefaultSubobject<USceneComponent>(*FString::Printf(TEXT("%s"), *lineName));
		lineRef->SetupAttachment(this->RootComponent);

		for (int i = 0; i < count; i++)
		{
			UBattleSpotBillboardComponent::ComponentCounter = i;

			UBattleSpotBillboardComponent *NewBillboard = CreateDefaultSubobject<UBattleSpotBillboardComponent>(FName(*FString::Printf(TEXT("%s%d"), *spotName, i)));
			NewBillboard->SetupAttachment(lineRef);

			if (NewBillboard)
			{
				NewBillboard->SetRelativeLocation(NewBillboard->GetRelativeLocation() + this->iconHeightVectorAux);
				NewBillboard->AttachOwnText();
				NewBillboard->BattleDirection = defaultDirection;

				(*billboardsRef).Add(NewBillboard);
			}
		}
	};

	createLine(this->HeroLine, TEXT("HeroLine"), this->MAX_NUMBER_OF_HEROES, &this->HeroesPositions, "HeroSpot", ECharacterDirection::CHARACTER_DIRECTION_RIGHT);

	createLine(this->EnemyLine, TEXT("EnemyLine"), this->MAX_NUMBER_OF_ENEMIES, &this->EnemiesPositions, "EnemySpot", ECharacterDirection::CHARACTER_DIRECTION_LEFT);
}