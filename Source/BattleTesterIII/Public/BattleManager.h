// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "BattleManager.generated.h"

class AMyGameMode;

class ACombatCharacter;

class AHero;

class AEnemy;

class UPartyManager;

class USpringArmComponent;

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

	ACombatCharacter *turnCharacter;

	ACombatCharacter *targetCharacter;

	UPartyManager *partyManager;

	UWorld *worldRef;

	USpringArmComponent *springArmRef;

	uint8 enemySelectionIndex;

	uint8 aliveEnemies();

	void sortTurn();

	bool isGameOver();

	bool isVictory();

public:
	UFUNCTION(BlueprintCallable)
	void Start(TArray<AEnemy *> enemies);

	UFUNCTION(BlueprintCallable, Category = "Select Target")
	void SelectNextEnemyTarget(bool firstTarget, FVector2D input = FVector2D(0.f, 0.f));

	UFUNCTION(BlueprintCallable, Category = "Select Target")
	void SingleTargetSelection(ACombatCharacter *target);

	UFUNCTION(BlueprintCallable, Category = "Attack")
	FVector SetAttackLocation();

	void Initialize(UPartyManager *partyManagerRef, AMyGameMode *gameMode);

	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<EBattleState> BattleState;

	UPROPERTY(BlueprintReadOnly)
	TArray<AEnemy *> EnemiesRefs;

	UBattleManager();
};
