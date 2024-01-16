// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "BattleManager.generated.h"

class USpringArmComponent;

class AMyGameMode;

class AMyPlayerController;

class ACombatCharacter;

class AHero;

class AEnemy;

class UPartyManager;

class USelectAction;

enum EBattleState : uint8;
/**
 *
 */
UCLASS(BlueprintType)
class BATTLETESTERIII_API UBattleManager : public UObject
{
	GENERATED_BODY()

	TSubclassOf<USelectAction> WBP_SelectActionClass;

	TArray<AHero *> *heroesRefs;

	TArray<ACombatCharacter *> characterRefs;

	UPartyManager *partyManager;

	AMyPlayerController *playerController;

	UWorld *worldRef;

	USpringArmComponent *springArmRef;

	uint8 enemySelectionIndex;

	uint8 aliveEnemies();

	void sortTurn();

	bool isGameOver();

	bool isVictory();

public:
	void Initialize(UPartyManager *partyManagerRef, AMyGameMode *gameMode, TSubclassOf<USelectAction> actionSelectWidgetClass);

	UFUNCTION(BlueprintCallable, Category = "Initialization")
	void Start(TArray<AEnemy *> enemies);

	UPROPERTY(BlueprintReadWrite, Category = "State Management|Variable")
	TEnumAsByte<EBattleState> BattleState;

	UPROPERTY(BlueprintReadOnly, Category = "State Management|Variable")
	ACombatCharacter *TargetCharacter;

	UPROPERTY(BlueprintReadOnly, Category = "State Management|Variable")
	ACombatCharacter *TurnCharacter;

	UPROPERTY(BlueprintReadOnly, Category = "State Management|Variable")
	TArray<AEnemy *> EnemiesRefs;

	UFUNCTION(BlueprintCallable, Category = "State Management|Action State")
	void SetPlayerActionState();

	UPROPERTY(BlueprintReadOnly, Category = "State Management|Action State")
	USelectAction *SelectActionWidget;

	UFUNCTION(BlueprintCallable, Category = "Select Target")
	void SelectNextEnemyTarget(bool firstTarget, FVector2D input = FVector2D(0.f, 0.f));

	UFUNCTION(BlueprintCallable, Category = "Attack")
	FVector SetAttackLocation();

	UBattleManager();
};
