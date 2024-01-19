// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleManager.h"

#include "GameFramework/SpringArmComponent.h"
#include "UObject/ConstructorHelpers.h"

#include "MyGameMode.h"
#include "MyPlayerController.h"
#include "PartyManager.h"

#include "Widgets/SelectAction.h"
#include "Widgets/SpellSelection.h"
#include "Widgets/BattleInventoryList.h"

#include "Characters/CombatCharacter.h"
#include "Characters/Hero.h"
#include "Characters/Enemy.h"

#include "Enums/BattleState.h"

void UBattleManager::Initialize(UPartyManager *partyManagerRef, AMyGameMode *gameModeRef)
{
    this->heroesRefs = &partyManagerRef->PartyMembers;

    this->gameMode = gameModeRef;

    this->playerController = Cast<AMyPlayerController>(this->gameMode->GetWorld()->GetFirstPlayerController());

    // this->springArmRef = this->playerController->CameraSpringArm;
}

void UBattleManager::Start(TArray<AEnemy *> enemies)
{
    auto setupWidget = [&]<typename WidgetClass>(TSubclassOf<WidgetClass> widgetClass) -> WidgetClass *
    {
        WidgetClass *widget = CreateWidget<WidgetClass>(this->playerController, widgetClass);

        if (widget)
        {
            widget->SetVisibility(ESlateVisibility::Collapsed);

            widget->AddToViewport();
        }

        return widget;
    };

    this->BattleState = EBattleState::BATTLE_STATE_WAIT_ACTION;

    this->EnemiesRefs = enemies;

    this->characterRefs.Empty();

    this->characterRefs.Append(*this->heroesRefs);

    this->characterRefs.Append(enemies);

    this->SelectActionWidget = setupWidget(this->gameMode->WBP_SelectActionClass);

    this->SpellSelectionWidget = setupWidget(this->gameMode->WBP_SelectSpellClass);

    this->InventoryListWidget = setupWidget(this->gameMode->WBP_BattleInventoryList);

    sortTurn();
}

void UBattleManager::SetPlayerActionState()
{
    this->TurnCharacter->SetAsCameraFocus(this->springArmRef);

    FTimerHandle widgetDelay;

    float DelayInSeconds = 0.1f;

    this->gameMode->GetWorld()->GetTimerManager().SetTimer(widgetDelay, this, &UBattleManager::delayedActionSelectionWidgetSettings, DelayInSeconds);
}

void UBattleManager::delayedActionSelectionWidgetSettings()
{
    this->setWidgetLocationOnScreen(this->SelectActionWidget, 70.f, -45.f);

    this->SelectActionWidget->IncrementOrDecrementAction();

    this->SelectActionWidget->SetVisibility(ESlateVisibility::Visible);

    this->BattleState = EBattleState::BATTLE_STATE_PLAYER_ACTION_SELECT;
}

FVector UBattleManager::SetAttackLocation()
{
    FVector targetLocation = this->TargetCharacter->GetActorLocation();

    targetLocation.X -= 70.f;

    targetLocation.Y += 50.f;

    this->BattleState = EBattleState::BATTLE_STATE_WAIT_ACTION;

    this->TargetCharacter->RemoveCursor();

    this->TurnCharacter->SetAsCameraFocus(this->springArmRef);

    return targetLocation;
}

void UBattleManager::SetPlayerSpellSelection()
{
    if (this->BattleState == EBattleState::BATTLE_STATE_PLAYER_ACTION_SELECT)
    {
        this->SelectActionWidget->SetVisibility(ESlateVisibility::Collapsed);
    }

    this->LastBattleState = this->BattleState;

    this->setWidgetLocationOnScreen(this->SpellSelectionWidget, 70.f, -240.f);

    this->SpellSelectionWidget->MoveSpellCursor();

    this->SpellSelectionWidget->SetVisibility(ESlateVisibility::Visible);

    this->BattleState = EBattleState::BATTLE_STATE_PLAYER_SELECT_SPELL;
}

void UBattleManager::SetPlayerInInventoryList()
{
    if (this->BattleState == EBattleState::BATTLE_STATE_PLAYER_ACTION_SELECT)
    {
        this->SelectActionWidget->SetVisibility(ESlateVisibility::Collapsed);
    }

    this->LastBattleState = this->BattleState;

    this->setWidgetLocationOnScreen(this->InventoryListWidget, 70.f, -75.f);

    this->InventoryListWidget->MoveCursor();

    this->InventoryListWidget->SetVisibility(ESlateVisibility::Visible);

    this->BattleState = EBattleState::BATTLE_STATE_PLAYER_SELECT_ITEM;
}

void UBattleManager::SetSelectSingleEnemyTarget()
{
    if (this->isVictory())
    {
        return;
    }

    this->BattleState = EBattleState::BATTLE_STATE_PLAYER_SELECT_ENEMY_TARGET;

    this->SelectActionWidget->SetVisibility(ESlateVisibility::Collapsed);

    this->SelectNextEnemyTarget();
}

void UBattleManager::SelectNextEnemyTarget(FVector2D increment)
{
    if (this->isVictory())
    {
        return;
    }

    int32 vectorIncrementer = increment.X;

    auto incrementIndex = [&](int32 startIndex) -> int32
    {
        int32 incrementedIndex = startIndex + vectorIncrementer;

        int32 lastEnemyPartyIndex = this->EnemiesRefs.Num() - 1;

        if (incrementedIndex < 0)
        {
            incrementedIndex = lastEnemyPartyIndex;
        }
        else if (incrementedIndex > lastEnemyPartyIndex)
        {
            incrementedIndex = 0;
        }

        return incrementedIndex;
    };

    int32 newIndex = incrementIndex(this->enemySelectionIndex);

    int32 initialIndex = newIndex;

    AEnemy *target = this->EnemiesRefs[newIndex];

    while (target->IsDead())
    {
        vectorIncrementer = increment.X != 0 ? increment.X : 1;

        newIndex = incrementIndex(newIndex);

        if (initialIndex == newIndex)
        {
            return;
        }

        target = this->EnemiesRefs[newIndex];
    }

    this->enemySelectionIndex = newIndex;

    target->SetAsTarget(this->springArmRef, this->TargetCharacter);

    this->TargetCharacter = target;
}

void UBattleManager::setWidgetLocationOnScreen(UUserWidget *widget, float x, float y, ACombatCharacter *targetCharacter)
{
    ACombatCharacter *refCharacter = !targetCharacter ? this->TurnCharacter : targetCharacter;

    FVector2D SelectActionLocation = refCharacter->GetLocationOnScreen();

    SelectActionLocation.X += x;

    SelectActionLocation.Y += y;

    widget->SetPositionInViewport(SelectActionLocation, true);
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