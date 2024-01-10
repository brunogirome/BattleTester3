// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleManager.h"

#include "MyGameMode.h"

#include "Characters/CombatCharacter.h"
#include "Characters/Hero.h"
#include "Characters/Enemy.h"

#include "Enums/BattleState.h"

void UBattleManager::Start(TArray<AHero *> heroes, TArray<AEnemy *> enemies, AMyGameMode *gameMode)
{
    this->heroesRefs = heroes;

    this->enemiesRefs = enemies;

    this->worldRef = gameMode->GetWorld();

    characterRefs.Empty();

    characterRefs.Append(heroes);

    characterRefs.Append(enemies);

    sortTurn();
}

void UBattleManager::sortTurn()
{
    characterRefs.Sort([](const ACombatCharacter &a, const ACombatCharacter &b)
                       { return a.Speed > b.Speed; });

    turnCharacter = characterRefs[0];

    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, turnCharacter->GetName());
}

bool UBattleManager::isGameOver()
{
    for (AHero *hero : this->heroesRefs)
    {
        if (!hero->IsDead())
        {
            return false;
        }
    }

    return true;
}

bool UBattleManager::isVictory()
{
    for (AEnemy *enemy : this->enemiesRefs)
    {
        if (!enemy->IsDead())
        {
            return false;
        }
    }

    return true;
}

UBattleManager::UBattleManager()
{
    this->BattleState = BATTLE_STATE_GET_NEXT_PLAYER;
}