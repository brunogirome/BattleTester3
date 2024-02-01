// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Delegates/Delegate.h"

#include "BattleManager.generated.h"

class USpringArmComponent;
class UUserWidget;
class AMyGameMode;
class AMyPlayerController;

class ABattlefield;
class ACombatCharacter;
class AHero;
class AEnemy;

class UPartyManager;
class USelectAction;
class USpellSelection;
class UBattleInventoryList;

enum EBattleState : uint8;
enum EAttackStrength : uint8;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartedBattleDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFrontOfOponentDelegate);

/**
 *
 */
UCLASS(BlueprintType)
class BATTLETESTERIII_API UBattleManager : public UObject
{
	GENERATED_BODY()

	TArray<AHero *> *heroesRefs;

	TArray<ACombatCharacter *> characterRefs;

	TSet<ACombatCharacter *> playedThisRound;

	UPartyManager *partyManager;

	AMyPlayerController *playerController;

	AMyGameMode *gameMode;

	USpringArmComponent *springArmRef;

	uint8 enemySelectionIndex;

	void startPhase(bool firstExecution = false);

	void endPhase();

	void sortTurnCharacters();

	bool isGameOver();

	bool isVictory();

	void setWidgetLocationOnScreen(UUserWidget *widget, float x = 0, float y = 0, ACombatCharacter *targetCharacter = nullptr);

	void delayedActionSelectionWidgetSettings();

public:
	void Initialize(UPartyManager *partyManagerRef, AMyGameMode *gameModeRef);

	UFUNCTION(BlueprintCallable, Category = "Initialization")
	void Start(ABattlefield *currentBattlefield);

	UPROPERTY(BlueprintReadWrite, Category = "State Management|Variable")
	TEnumAsByte<EBattleState> BattleState;

	UPROPERTY(BlueprintReadWrite, Category = "State Management|Variable")
	TEnumAsByte<EBattleState> LastBattleState;

	UPROPERTY(BlueprintReadOnly, Category = "State Management|Variable")
	ACombatCharacter *TargetCharacter;

	UPROPERTY(BlueprintReadOnly, Category = "State Management|Variable")
	ACombatCharacter *TurnCharacter;

	UPROPERTY(BlueprintReadOnly, Category = "State Management|Variable")
	TArray<AEnemy *> EnemiesRefs;

	UPROPERTY(BlueprintReadOnly, Category = "State Management|Variable")
	ABattlefield *BattlefieldInstance;

	UPROPERTY(BlueprintAssignable, Category = "State Management|Event")
	FStartedBattleDelegate OnBattleStarted;

	UFUNCTION(BlueprintCallable, Category = "Select Action")
	void SetPlayerActionState(bool isAlreadyCameraTarget = false);

	UPROPERTY(BlueprintReadOnly, Category = "Select Action|Widgets")
	USelectAction *SelectActionWidget;

	UFUNCTION(BlueprintCallable, Category = "Spell Selection")
	void SetPlayerSpellSelection();

	UPROPERTY(BlueprintReadOnly, Category = "Spell Selection|Widgets")
	USpellSelection *SpellSelectionWidget;

	UFUNCTION(BlueprintCallable, Category = "Inventory List")
	void SetPlayerInInventoryList();

	UPROPERTY(BlueprintReadOnly, Category = "Inventory List|Widgets")
	UBattleInventoryList *InventoryListWidget;

	UFUNCTION(BlueprintCallable, Category = "Select Target")
	void SetSelectSingleEnemyTarget();

	UFUNCTION(BlueprintCallable, Category = "Select Target")
	void SelectNextEnemyTarget(FVector2D input = FVector2D(0.f, 0.f));

	UPROPERTY(BlueprintAssignable, Category = "Select Target|Event")
	FOnFrontOfOponentDelegate OnFrontOfOponent;

	UFUNCTION(BlueprintCallable, Category = "Select Target|Event")
	void OnFrontOfOponentBroadcast();

	UFUNCTION(BlueprintCallable, Category = "Attack")
	FVector SetAttackLocation();

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void CalculatePhysicialDamage(EAttackStrength attackStrength);

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void CheckEndOfAttackTurn();

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void EndOfAttackTurn();

	UBattleManager();
};
