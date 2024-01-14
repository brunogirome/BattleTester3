// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "BattleManager.generated.h"

class AMyGameMode;

class ACombatCharacter;

class AHero;

class AEnemy;

enum EBattleState;
/**
 *
 */
UCLASS()
class BATTLETESTERIII_API UBattleManager : public UObject
{
	GENERATED_BODY()

	TArray<AHero *> heroesRefs;

	TArray<ACombatCharacter *> characterRefs;

	ACombatCharacter *turnCharacter;

	ACombatCharacter *targetCharacter;

	UWorld *worldRef;

	void sortTurn();

	bool isGameOver();

	bool isVictory();

public:
	UFUNCTION(BlueprintCallable)
	void Start(TArray<AHero *> heroes, TArray<AEnemy *> enemies, AMyGameMode *gameMode);

	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<EBattleState> BattleState;

	UPROPERTY(BlueprintReadOnly)
	TArray<AEnemy *> EnemiesRefs;

	UBattleManager();
};
