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

#if WITH_EDITOR
void ABattlefield::PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	// Verifique se a propriedade alterada é uma de suas texturas
	if (PropertyChangedEvent.Property && (PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(ABattlefield, HeroSpotTexture) ||
										  PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(ABattlefield, EnemySpotTexture)))
	{
		// Método para atualizar as texturas dos billboards
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

	FVector battleSpotLocation;

	for (int i = 0; i < this->MAX_NUMBER_OF_HEROES && partyMembers.Num(); i++)
	{
		AHero *hero = partyMembers[i];

		if (hero && this->HeroesPositions[i])
		{
			battleSpotLocation = this->HeroesPositions[i]->GetComponentLocation() - this->iconHeightVectorAux;

			// hero->SetBattleSpot();
		}
	}

	for (int i = 0; i < this->MAX_NUMBER_OF_ENEMIES && this->Enemies.Num(); i++)
	{
		if (this->Enemies[i] && this->EnemiesPositions[i])
		{
			// this->Enemies[i]->SetupBattle(EnemiesPositions[i]->GetComponentLocation() - this->iconHeightVectorAux, this);
		}
	}

	this->amountOfBattleSpots = this->HeroesPositions.Num() + this->EnemiesPositions.Num();
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

		// actorIAController->Move
	};

	for (AHero *hero : this->partyMembers)
	{
		// BattleAIController hero->
	}
}

ABattlefield::ABattlefield()
{
	this->BattleBoundaries = CreateDefaultSubobject<UBoxComponent>(TEXT("RootBoxCollision"));
	this->RootComponent = this->BattleBoundaries;
	this->BattleBoundaries->InitBoxExtent(FVector(500.0f, 500.0f, 50.0f));

	auto createLine = [&](USceneComponent *&lineRef, FString lineName, int32 count, TArray<UBattleSpotBillboardComponent *> *billboardsRef, FString spotName) -> void
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

				(*billboardsRef).Add(NewBillboard);
			}
		}
	};

	createLine(this->HeroLine, TEXT("HeroLine"), this->MAX_NUMBER_OF_HEROES, &this->HeroesPositions, "HeroSpot");

	createLine(this->EnemyLine, TEXT("EnemyLine"), this->MAX_NUMBER_OF_ENEMIES, &this->EnemiesPositions, "EnemySpot");
}