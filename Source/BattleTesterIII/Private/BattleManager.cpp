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

#include "Battle/Battlefield.h"
#include "Battle/DamageDisplay.h"
#include "AI/BattleAIController.h"
#include "Characters/CameraPawn.h"
#include "Characters/Hero.h"
#include "Characters/Enemy.h"

#include "Enums/BattleState.h"
#include "Enums/WorldState.h"
#include "Enums/AttackStrength.h"
#include "Enums/CombatStatus.h"

void UBattleManager::Initialize(UPartyManager *partyManagerRef, AMyGameMode *gameModeRef)
{
    this->heroesRefs = &partyManagerRef->PartyMembers;

    this->gameMode = gameModeRef;

    this->playerController = Cast<AMyPlayerController>(this->gameMode->GetWorld()->GetFirstPlayerController());
}

void UBattleManager::Start(ABattlefield *currentBattlefield)
{
    if (!currentBattlefield)
    {
        return;
    }

    this->BattleState = EBattleState::BATTLE_STATE_WAIT_ACTION;
    this->BattlefieldInstance = currentBattlefield;
    this->EnemiesRefs = this->BattlefieldInstance->Enemies;

    this->characterRefs.Empty();
    this->characterRefs.Append(*this->heroesRefs);
    this->characterRefs.Append(this->EnemiesRefs);

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

    this->SelectActionWidget = setupWidget(this->gameMode->WBP_SelectActionClass);
    this->SpellSelectionWidget = setupWidget(this->gameMode->WBP_SelectSpellClass);
    this->InventoryListWidget = setupWidget(this->gameMode->WBP_BattleInventoryList);

    ACameraPawn *cameraPawn = Cast<ACameraPawn>(this->playerController->GetPawn());

    if (cameraPawn)
    {
        if (cameraPawn->CameraSpringArm)
        {
            this->springArmRef = cameraPawn->CameraSpringArm;
        }
    }

    if (OnBattleStarted.IsBound())
    {
        OnBattleStarted.Broadcast();
    }

    sortTurn();
}

void UBattleManager::EndPhase()
{
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "End Phase");

    this->playerController->GoBackToBattleLocation();
}

void UBattleManager::SetPlayerActionState(bool isAlreadyCameraTarget)
{
    if (!this->TurnCharacter && !this->springArmRef && !this->gameMode)
    {
        return;
    }

    if (!isAlreadyCameraTarget)
    {
        this->TurnCharacter->SetAsCameraFocus(this->springArmRef);
    }

    // I need this delay to prevent Widget not being rendered when the player cancels target selection
    FTimerHandle widgetDelay;
    float Delay = 0.1f;

    this->gameMode->GetWorld()->GetTimerManager().SetTimer(widgetDelay, this, &UBattleManager::delayedActionSelectionWidgetSettings, Delay);
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

void UBattleManager::CalculatePhysicialDamage(EAttackStrength attackStrength)
{
    const float LIGHT_ATTACK_SCALING = 1.f;
    const float MEDIUM_ATTACK_SCALING = 1.33f;
    const float HEAVY_ATTACK_SCALING = 1.66f;

    float damage = 0;
    int32 staminaCost = 1;

    auto calculateDamage = [&](float scaling) -> int32
    {
        int32 *turnCharacterPhysicalDamage = this->TurnCharacter->CombatStatus.Find(ECombatStatus::COMBAT_STATUS_PHYSICAL_DAMAGE);
        int32 *turnCharacterPhysicalDefense = this->TargetCharacter->CombatStatus.Find(ECombatStatus::COMBAT_STATUS_PHYSICAL_DEFENSE);

        if (!turnCharacterPhysicalDamage ||
            !turnCharacterPhysicalDefense)
        {
            return -1;
        }

        float scaledDamage = *turnCharacterPhysicalDamage * scaling;
        int32 damageDealt = scaledDamage - *turnCharacterPhysicalDefense;

        return damageDealt;
    };

    switch (attackStrength)
    {
    case EAttackStrength::LIGHT_ATTACK_STRENGTH:
        damage = calculateDamage(LIGHT_ATTACK_SCALING);

        staminaCost = 1;
        break;

    case EAttackStrength::MEDIUM_ATTACK_STRENGTH:
        damage = calculateDamage(MEDIUM_ATTACK_SCALING);

        staminaCost = 2;
        break;

    case EAttackStrength::HEAVY_ATTACK_STRENGTH:
        // damage = calculateDamage(HEAVY_ATTACK_SCALING);
        damage = 999;

        staminaCost = 3;
        break;
    default:
        break;
    }

    FVector damageDisplayLocation;
    FRotator damageDisplayRotation;

    if (this->TargetCharacter)
    {
        damageDisplayLocation = this->TargetCharacter->GetActorLocation();
        damageDisplayRotation = this->TargetCharacter->GetActorRotation();
    }

    FTransform transform = FTransform(damageDisplayRotation, damageDisplayLocation);

    if (this->gameMode->BP_DamageDisplay)
    {
        ADamageDisplay *DamageDisplay = this->gameMode->GetWorld()->SpawnActorDeferred<ADamageDisplay>(
            this->gameMode->BP_DamageDisplay,
            transform,
            nullptr,
            nullptr,
            ESpawnActorCollisionHandlingMethod::Undefined);

        if (DamageDisplay)
        {
            DamageDisplay->DamageAmount = damage;
            DamageDisplay->FinishSpawning(transform);
        }
    }

    this->TurnCharacter->ConsumeStamina(staminaCost);
    this->TargetCharacter->ReciveDamage(damage);

    int32 *turnCharacterStamina = this->TurnCharacter->CombatStatus.Find(ECombatStatus::COMBAT_STATUS_CURRENT_STAMINA);

    int32 *debugTotalStamina = this->TurnCharacter->CombatStatus.Find(ECombatStatus::COMBAT_STATUS_STAMINA);

    if (!turnCharacterStamina)
    {
        return;
    }

    FString debugStamina = FString::Printf(TEXT("Current stamina: %d/%d"), *turnCharacterStamina, *debugTotalStamina);
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, debugStamina);

    if (this->TargetCharacter->IsDead())
    {
        if (*turnCharacterStamina <= 0)
        {
            this->EndPhase();
        }
        else
        {
            if (this->TurnCharacter->TypeOfCharacter == ETypeOfCharacter::HERO_CHRACTER)
            {
                this->playerController->GoBackToBattleLocation();
            }
            else
            {
                GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Future Logic of Enemy IA killed hero");
            }
        }

        return;
    }

    if (*turnCharacterStamina <= 0)
    {
        this->EndPhase();

        return;
    }

    this->BattleState = EBattleState::BATTLE_STATE_PLAYER_SELECT_ATTACK;
}

void UBattleManager::CheckEndOfAttackTurn()
{
    int32 *turnCharacterStamina = this->TurnCharacter->CombatStatus.Find(ECombatStatus::COMBAT_STATUS_CURRENT_STAMINA);

    if (!turnCharacterStamina)
    {
        return;
    }

    if (this->TargetCharacter->IsDead())
    {
        if (*turnCharacterStamina <= 0)
        {
            if (this->TurnCharacter->TypeOfCharacter == ETypeOfCharacter::HERO_CHRACTER)
            {
                this->SetPlayerActionState();
            }
            else
            {
                GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Enemy IA Check Attack Turn");
            }
        }
    }

    if (*turnCharacterStamina <= 0)
    {
        this->EndPhase();
    }
}

void UBattleManager::EndOfAttackTurn()
{
}

void UBattleManager::OnFinishedAttackAnimBroadcast()
{
    // if (OnFinishedAttackAnim.IsBound())
    // {
    //     OnFinishedAttackAnim.Broadcast();
    // }

    // this->BattleState = EBattleState::BATTLE_STATE_PLAYER_SELECT_ATTACK;
}

void UBattleManager::OnFrontOfOponentBroadcast()
{
    if (OnFrontOfOponent.IsBound())
    {
        OnFrontOfOponent.Broadcast();
    }

    this->BattleState = EBattleState::BATTLE_STATE_PLAYER_SELECT_ATTACK;
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
    this->characterRefs.Sort([](const ACombatCharacter &a, const ACombatCharacter &b)
                             {
        const int32* speedA = a.CombatStatus.Find(ECombatStatus::COMBAT_STATUS_SPEED);
        const int32* speedB = b.CombatStatus.Find(ECombatStatus::COMBAT_STATUS_SPEED);

        if (speedA && speedB)
        {
            return *speedA > *speedB;
        }
        else if (speedA)
        {
            return true;
        }
        else if (speedB)
        {
            return false;
        }
        return false; });

    for (ACombatCharacter *character : this->characterRefs)
    {
        if (!character->IsDead())
        {
            this->TurnCharacter = character;
            break;
        }
    }

    if (this->TurnCharacter->TypeOfCharacter == ETypeOfCharacter::HERO_CHRACTER)
    {
        this->SetPlayerActionState();
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TurnCharacter->GetName());
    }
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