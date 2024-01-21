// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle/Battlefield.h"

#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Components/BillboardComponent.h"
#include "Components/TextRenderComponent.h"

#include "MyGameInstance.h"
#include "PartyManager.h"
#include "Characters/Enemy.h"
#include "Characters/Hero.h"

void ABattlefield::BeginPlay()
{
	Super::BeginPlay();

	TArray<AHero *> *partyMembers = &Cast<UMyGameInstance>(this->GetGameInstance())->PartyManager->PartyMembers;

	for (int i = 0; i < this->MAX_NUMBER_OF_HEROES && (*partyMembers).Num(); i++)
	{
		AHero *hero = (*partyMembers)[i];

		if (hero && this->HeroesPositions[i])
		{
			hero->SetBattleSpot(this->HeroesPositions[i]->GetComponentLocation());
		}
	}
}

ABattlefield::ABattlefield()
{
	FVector iconHeightVectorAux = FVector(0, 0, ICON_HEIGHT);

	FVector textIndexHeigthAux = FVector(0, 0, ICON_HEIGHT + 20.f);

	FRotator textIndexRotation = FRotator(0, 90.f, 0);

	this->BattleBoundaries = CreateDefaultSubobject<UBoxComponent>(TEXT("RootBoxCollision"));
	this->RootComponent = this->BattleBoundaries;
	this->BattleBoundaries->InitBoxExtent(FVector(500.0f, 500.0f, 50.0f));

	this->HeroLine = CreateDefaultSubobject<USceneComponent>(TEXT("HeroLine"));
	this->HeroLine->SetupAttachment(this->RootComponent);

	this->EnemyLine = CreateDefaultSubobject<USceneComponent>(TEXT("EnemyLine"));
	this->EnemyLine->SetupAttachment(this->RootComponent);

	for (int i = 0; i < this->MAX_NUMBER_OF_HEROES; i++)
	{
		UBillboardComponent *NewBillboard = CreateDefaultSubobject<UBillboardComponent>(FName(*FString::Printf(TEXT("HeroPosition%d"), i)));
		NewBillboard->SetupAttachment(this->HeroLine);

		if (NewBillboard)
		{
			NewBillboard->SetRelativeLocation(NewBillboard->GetRelativeLocation() + iconHeightVectorAux);

			UTextRenderComponent *NewTextComponent = CreateDefaultSubobject<UTextRenderComponent>(FName(*FString::Printf(TEXT("HeroIndex%d"), i)));
			NewTextComponent->SetupAttachment(NewBillboard);
			NewTextComponent->SetText(FText::FromString(FString::FromInt(i)));
			NewTextComponent->SetHorizontalAlignment(EHTA_Center);
			NewTextComponent->SetHiddenInGame(true);

			if (NewTextComponent)
			{
				NewTextComponent->SetRelativeLocation(NewTextComponent->GetRelativeLocation() + textIndexHeigthAux);
				NewTextComponent->SetRelativeRotation(textIndexRotation);

				this->HeroesPositions.Add(NewBillboard);
			}
		}
	}

	for (int i = 0; i < this->MAX_NUMBER_OF_ENEMIES; i++)
	{
		UBillboardComponent *NewBillboard = CreateDefaultSubobject<UBillboardComponent>(FName(*FString::Printf(TEXT("EnemyPosition%d"), i)));
		NewBillboard->SetupAttachment(this->EnemyLine);

		if (NewBillboard)
		{
			NewBillboard->SetRelativeLocation(NewBillboard->GetRelativeLocation() + iconHeightVectorAux);

			UTextRenderComponent *NewTextComponent = CreateDefaultSubobject<UTextRenderComponent>(FName(*FString::Printf(TEXT("EnemyIndex%d"), i)));
			NewTextComponent->SetupAttachment(NewBillboard);
			NewTextComponent->SetText(FText::FromString(FString::FromInt(i)));
			NewTextComponent->SetHorizontalAlignment(EHTA_Center);
			NewTextComponent->SetHiddenInGame(true);

			if (NewTextComponent)
			{
				NewTextComponent->SetRelativeLocation(NewTextComponent->GetRelativeLocation() + textIndexHeigthAux);
				NewTextComponent->SetRelativeRotation(textIndexRotation);

				this->EnemiesPositions.Add(NewBillboard);
			}
		}
	}

	for (int i = 0; i < this->MAX_NUMBER_OF_ENEMIES && this->Enemies.Num(); i++)
	{
		if (this->Enemies[i] && this->EnemiesPositions[i])
		{
			this->Enemies[i]->SetBattleSpot(EnemiesPositions[i]->GetComponentLocation() - iconHeightVectorAux);
		}
	}
}
