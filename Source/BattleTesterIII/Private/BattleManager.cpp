// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleManager.h"

#include "GameFramework/SpringArmComponent.h"

#include "MyGameMode.h"
#include "PartyManager.h"

#include "Characters/CombatCharacter.h"
#include "Characters/Hero.h"
#include "Characters/PartyLeader.h"
#include "Characters/Enemy.h"

#include "Enums/BattleState.h"

void UBattleManager::Start(TArray<AEnemy *> enemies)
{
    this->EnemiesRefs = enemies;

    characterRefs.Empty();

    characterRefs.Append(*this->heroesRefs);

    characterRefs.Append(enemies);

    sortTurn();
}

void UBattleManager::Initialize(UPartyManager *partyManagerRef, AMyGameMode *gameMode)
{
    this->heroesRefs = &partyManagerRef->PartyMembers;

    this->springArmRef = partyManagerRef->PartyLeader->SpringArm;

    this->worldRef = gameMode->GetWorld();
}

void UBattleManager::SingleTargetSelection(ACombatCharacter *target)
{
    target->SetAsTarget(this->springArmRef, turnCharacter);
}

void UBattleManager::SelectNextEnemyTarget(bool firstTarget)
{
    auto nextIndex = [&]()
    {
        return (enemySelectionIndex + 1) < this->aliveEnemies() ? enemySelectionIndex++ : 0;
    };

    if (firstTarget)
    {
        enemySelectionIndex = 0;
    }
    else
    {
        enemySelectionIndex = nextIndex();
    }

    AEnemy *target = this->EnemiesRefs[enemySelectionIndex];

    if (target->IsDead())
    {
        enemySelectionIndex = nextIndex();

        for (int32 i = enemySelectionIndex; i < this->EnemiesRefs.Num(); i++)
        {
            target = this->EnemiesRefs[enemySelectionIndex];

            if (!target->IsDead())
            {
                break;
            }
        }
    }

    target->SetAsTarget(this->springArmRef, this->targetCharacter);

    this->targetCharacter = target;
}

void UBattleManager::sortTurn()
{
    characterRefs.Sort([](const ACombatCharacter &a, const ACombatCharacter &b)
                       { return a.Speed > b.Speed; });

    turnCharacter = characterRefs[0];

    // GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, turnCharacter->GetName());
}

uint8 UBattleManager::aliveEnemies()
{
    uint8 aliveEnemiesCount = 0;

    for (AEnemy *enemy : this->EnemiesRefs)
    {
        if (!enemy->IsDead())
        {
            aliveEnemiesCount++;
        }
    }

    return aliveEnemiesCount;
}

bool UBattleManager::isGameOver()
{
    for (AHero *hero : *this->heroesRefs)
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
    return this->aliveEnemies() == 0;
}

UBattleManager::UBattleManager()
{
    this->BattleState = BATTLE_STATE_POSITIONING;

    this->turnCharacter = nullptr;

    this->enemySelectionIndex = 0;
}