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
    this->BattleState = EBattleState::BATTLE_STATE_WAIT_ACTION;

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

    this->turnCharacter = (*heroesRefs)[0];

    this->worldRef = gameMode->GetWorld();
}

void UBattleManager::SingleTargetSelection(ACombatCharacter *target)
{
    target->SetAsTarget(this->springArmRef, turnCharacter);
}

FVector UBattleManager::SetAttackLocation()
{
    FVector targetLocation = this->targetCharacter->GetActorLocation();

    targetLocation.X -= 70;

    targetLocation.Y += 50;

    this->BattleState = EBattleState::BATTLE_STATE_WAIT_ACTION;

    this->targetCharacter->RemoveCursor();

    this->turnCharacter->SetAsCameraFocus(this->springArmRef);

    return targetLocation;
}

void UBattleManager::SelectNextEnemyTarget(bool firstTarget, FVector2D increment)
{
    auto nextIndex = [&](bool firstCheck = false)
    {
        int32 incrementAmount = firstCheck ? increment.X : 1;

        int32 newIndex = this->enemySelectionIndex + incrementAmount;

        if (newIndex < 0)
        {
            return this->EnemiesRefs.Num() - 1;
        }

        return newIndex < this->aliveEnemies() ? newIndex : 0;
    };

    if (firstTarget)
    {
        this->enemySelectionIndex = 0;
    }
    else
    {
        this->enemySelectionIndex = nextIndex(true);
    }

    AEnemy *target = this->EnemiesRefs[this->enemySelectionIndex];

    if (target->IsDead())
    {
        this->enemySelectionIndex = nextIndex();

        for (int32 i = this->enemySelectionIndex; i < this->EnemiesRefs.Num(); i++)
        {
            target = this->EnemiesRefs[this->enemySelectionIndex];

            if (!target->IsDead())
            {
                break;
            }
        }
    }

    target->SetAsTarget(this->springArmRef, this->targetCharacter);

    this->targetCharacter = target;

    this->BattleState = EBattleState::BATTLE_STATE_PLAYER_SELECT_ENEMY_TARGET;
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
    this->BattleState = EBattleState::BATTLE_STATE_WAIT_ACTION;

    this->turnCharacter = nullptr;

    this->enemySelectionIndex = 0;
}