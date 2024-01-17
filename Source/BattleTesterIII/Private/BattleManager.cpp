// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleManager.h"

#include "GameFramework/SpringArmComponent.h"
#include "UObject/ConstructorHelpers.h"

#include "MyGameMode.h"
#include "MyPlayerController.h"
#include "PartyManager.h"

#include "Widgets/SelectAction.h"
#include "Widgets/SpellSelection.h"

#include "Characters/CombatCharacter.h"
#include "Characters/Hero.h"
#include "Characters/PartyLeader.h"
#include "Characters/Enemy.h"

#include "Enums/BattleState.h"

void UBattleManager::Initialize(UPartyManager *partyManagerRef, AMyGameMode *gameModeRef)
{
    this->heroesRefs = &partyManagerRef->PartyMembers;

    this->springArmRef = partyManagerRef->PartyLeader->SpringArm;

    this->gameMode = gameModeRef;

    this->playerController = Cast<AMyPlayerController>(this->gameMode->GetWorld()->GetFirstPlayerController());
}

void UBattleManager::Start(TArray<AEnemy *> enemies)
{
    this->BattleState = EBattleState::BATTLE_STATE_WAIT_ACTION;

    this->EnemiesRefs = enemies;

    this->characterRefs.Empty();

    this->characterRefs.Append(*this->heroesRefs);

    this->characterRefs.Append(enemies);

    this->SelectActionWidget = CreateWidget<USelectAction>(this->playerController, this->gameMode->WBP_SelectActionClass);

    this->SelectActionWidget->SetVisibility(ESlateVisibility::Collapsed);

    this->SelectActionWidget->AddToViewport();

    this->SpellSelectionWidget = CreateWidget<USpellSelection>(this->playerController, this->gameMode->WBP_SelectSpellClass);

    this->SpellSelectionWidget->SetVisibility(ESlateVisibility::Collapsed);

    this->SpellSelectionWidget->AddToViewport();

    sortTurn();
}

void UBattleManager::SetPlayerActionState()
{
    this->TurnCharacter->SetAsCameraFocus(this->springArmRef);

    FTimerHandle widgetDelay;

    float DelayInSeconds = 0.1f;

    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, "SetPlayerActionState");

    this->gameMode->GetWorld()->GetTimerManager().SetTimer(widgetDelay, this, &UBattleManager::delayedActionSelectionWidgetSettings, DelayInSeconds);
}

void UBattleManager::delayedActionSelectionWidgetSettings()
{
    FVector2D SelectActionLocation;

    this->gameMode->GetWorld()->GetFirstPlayerController()->ProjectWorldLocationToScreen(this->TurnCharacter->GetActorLocation(), SelectActionLocation, false);

    SelectActionLocation.X += 60;

    SelectActionLocation.Y -= 45;

    this->SelectActionWidget->SetPositionInViewport(SelectActionLocation, true);

    this->SelectActionWidget->IncrementOrDecrementAction();

    this->SelectActionWidget->SetVisibility(ESlateVisibility::Visible);

    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::SanitizeFloat(SelectActionLocation.X) + ", " + FString::SanitizeFloat(SelectActionLocation.Y));

    this->BattleState = EBattleState::BATTLE_STATE_PLAYER_ACTION_SELECT;
}

FVector UBattleManager::SetAttackLocation()
{
    FVector targetLocation = this->TargetCharacter->GetActorLocation();

    targetLocation.X -= 70;

    targetLocation.Y += 50;

    this->BattleState = EBattleState::BATTLE_STATE_WAIT_ACTION;

    this->TargetCharacter->RemoveCursor();

    this->TurnCharacter->SetAsCameraFocus(this->springArmRef);

    return targetLocation;
}

void UBattleManager::SetPlayerSpellSelection()
{
    this->SelectActionWidget->SetVisibility(ESlateVisibility::Collapsed);

    this->SpellSelectionWidget->SetVisibility(ESlateVisibility::Visible);

    this->BattleState = EBattleState::BATTLE_STATE_PLAYER_SELECT_SPELL;
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

        this->SelectActionWidget->SetVisibility(ESlateVisibility::Collapsed);
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

    target->SetAsTarget(this->springArmRef, this->TargetCharacter);

    this->TargetCharacter = target;

    this->BattleState = EBattleState::BATTLE_STATE_PLAYER_SELECT_ENEMY_TARGET;
}

void UBattleManager::sortTurn()
{
    characterRefs.Sort([](const ACombatCharacter &a, const ACombatCharacter &b)
                       { return a.Speed > b.Speed; });

    this->TurnCharacter = (*this->heroesRefs)[0];

    this->SetPlayerActionState();

    // GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TurnCharacter->GetName());
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

    this->TurnCharacter = nullptr;

    this->enemySelectionIndex = 0;
}