// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "BattleManager.generated.h"

class USpringArmComponent;

class UUserWidget;

class AMyGameMode;

class AMyPlayerController;

class ACombatCharacter;

class AHero;

class AEnemy;

class UPartyManager;

class USelectAction;

class USpellSelection;

enum EBattleState : uint8;
/**
 *
 */
UCLASS(BlueprintType)
class BATTLETESTERIII_API UBattleManager : public UObject
{
	GENERATED_BODY()

	TArray<AHero *> *heroesRefs;

	TArray<ACombatCharacter *> characterRefs;

	UPartyManager *partyManager;

	AMyPlayerController *playerController;

	AMyGameMode *gameMode;

	USpringArmComponent *springArmRef;

	uint8 enemySelectionIndex;

	uint8 aliveEnemies();

	void setWidgetLocationOnScreen(UUserWidget *widget, float x = 0, float y = 0, ACombatCharacter *targetCharacter = nullptr);

	void sortTurn();

	bool isGameOver();

	bool isVictory();

	void delayedActionSelectionWidgetSettings();

public:
	void Initialize(UPartyManager *partyManagerRef, AMyGameMode *gameModeRef);

	UFUNCTION(BlueprintCallable, Category = "Initialization")
	void Start(TArray<AEnemy *> enemies);

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

	UFUNCTION(BlueprintCallable, Category = "Select Action")
	void SetPlayerActionState();

	UPROPERTY(BlueprintReadOnly, Category = "Select Action|Widgets")
	USelectAction *SelectActionWidget;

	UFUNCTION(BlueprintCallable, Category = "Spell Selection")
	void SetPlayerSpellSelection();

	UPROPERTY(BlueprintReadOnly, Category = "Spell Selection|Widgets")
	USpellSelection *SpellSelectionWidget;

	UFUNCTION(BlueprintCallable, Category = "Select Target")
	void SetSelectSingleEnemyTarget();

	UFUNCTION(BlueprintCallable, Category = "Select Target")
	void SelectNextEnemyTarget(FVector2D input = FVector2D(0.f, 0.f));

	UFUNCTION(BlueprintCallable, Category = "Attack")
	FVector SetAttackLocation();

	UBattleManager();
};
