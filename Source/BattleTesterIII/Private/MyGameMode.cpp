// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameMode.h"

#include "BattleManager.h"

#include "Enums/BattleState.h"

#include "Enums/WorldState.h"

bool AMyGameMode::IsInBattle()
{
    return this->WorldState == WORLD_STATE_BATTLE;
}

TEnumAsByte<EBattleState> AMyGameMode::GetBattleState()
{
    return this->BattleManager->BattleState;
}

void AMyGameMode::BeginPlay()
{
    Super::BeginPlay();

    this->BattleManager = NewObject<UBattleManager>(UBattleManager::StaticClass());
}

AMyGameMode::AMyGameMode()
{
    this->WorldState = WORLD_STATE_OVERWORLD;
}