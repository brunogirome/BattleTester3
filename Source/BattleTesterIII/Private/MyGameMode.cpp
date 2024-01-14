// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameMode.h"

#include "MyGameInstance.h"
#include "PartyManager.h"
#include "BattleManager.h"
#include "Characters/PartyLeader.h"

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

    UWorld *world = this->GetWorld();

    this->gameInstance = Cast<UMyGameInstance>(world->GetGameInstance());

    APartyLeader *partyLeader = Cast<APartyLeader>(world->GetFirstPlayerController()->GetPawn());

    this->gameInstance->PartyManager->Initialize(partyLeader, this);

    this->BattleManager = NewObject<UBattleManager>(UBattleManager::StaticClass());

    this->BattleManager->Initialize(this->gameInstance->PartyManager, this);
}

AMyGameMode::AMyGameMode()
{
    this->WorldState = WORLD_STATE_OVERWORLD;
}