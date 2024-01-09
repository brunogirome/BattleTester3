// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/MyGameMode.h"

#include "Enums/BattleState.h"

#include "Enums/WorldState.h"

AMyGameMode::AMyGameMode()
{
    this->WorldState = WORLD_STATE_OVERWORLD;

    this->BattleState = BATTLE_STATE_GET_NEXT_PLAYER;
}

bool AMyGameMode::IsInBattle()
{
    return this->WorldState == WORLD_STATE_BATTLE;
}