// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle/BattleSpotBillboardComponent.h"

#include "Components/TextRenderComponent.h"

#include "Battle/Battlefield.h"

#include "Enums/CharacterDirection.h"

int32 UBattleSpotBillboardComponent::ComponentCounter = 0;

FBattleSpot UBattleSpotBillboardComponent::GetBattleSpot()
{
    return FBattleSpot(this->GetComponentLocation(), this->BattleDirection);
}

void UBattleSpotBillboardComponent::AttachOwnText()
{
    this->IndexTextComponent->SetText(FText::FromString(FString::FromInt(UBattleSpotBillboardComponent::ComponentCounter)));
    this->IndexTextComponent->SetupAttachment(this);
}

UBattleSpotBillboardComponent::UBattleSpotBillboardComponent()
{
    FRotator textIndexRotation = FRotator(0, 90.f, 0);

    FVector textIndexHeigthAux = FVector(0, 0, ABattlefield::ICON_HEIGHT + 20.f);

    this->IndexTextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("SpotIndexDisplay"));
    this->IndexTextComponent->SetHorizontalAlignment(EHTA_Center);
    this->IndexTextComponent->SetHiddenInGame(true);
    this->IndexTextComponent->SetRelativeRotation(textIndexRotation);

    if (this->IndexTextComponent)
    {
        this->IndexTextComponent->SetRelativeLocation(this->IndexTextComponent->GetRelativeLocation() + textIndexHeigthAux);
    }
}
