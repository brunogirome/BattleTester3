// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameMode.h"

#include "MyGameInstance.h"
#include "PartyManager.h"
#include "BattleManager.h"

#include "Enums/BattleState.h"
#include "Enums/WorldState.h"

bool AMyGameMode::IsInOverWorld()
{
    return this->WorldState == EWorldState::WORLD_STATE_OVERWORLD;
}

bool AMyGameMode::IsInBattle()
{
    return this->WorldState == EWorldState::WORLD_STATE_BATTLE;
}

TEnumAsByte<EBattleState> AMyGameMode::GetBattleState()
{
    return this->BattleManager->BattleState;
}

void AMyGameMode::BeginPlay()
{
    Super::BeginPlay();

    this->gameInstance = Cast<UMyGameInstance>(this->GetWorld()->GetGameInstance());

    this->gameInstance->PartyManager->Initialize(this->gameInstance, this);

    this->gameInstance->PartyManager->SpawnParty();

    this->BattleManager = NewObject<UBattleManager>(UBattleManager::StaticClass());

    this->BattleManager->Initialize(this->gameInstance->PartyManager, this);
}

AMyGameMode::AMyGameMode()
{
    this->WorldState = EWorldState::WORLD_STATE_OVERWORLD;
}