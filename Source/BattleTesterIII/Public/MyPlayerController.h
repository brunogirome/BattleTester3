// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "MyPlayerController.generated.h"

class USelectAction;

class UBattleManager;

class AMyGameMode;

class APartyLeader;

enum EBattleState : uint8;

/**
 *
 */
UCLASS()
class BATTLETESTERIII_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

	AMyGameMode *gameMode;

	bool checkBattleState(EBattleState state);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Overworld")
	APartyLeader *PartyLeader;

	UFUNCTION(BlueprintCallable, Category = "Overworld")
	void MovePartyLeader(FVector2D input);

	UPROPERTY(BlueprintReadOnly, Category = "Battle")
	UBattleManager *BattleManager;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Battle")
	bool IsInBattle();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Battle|Select Action")
	bool IsInBattleStateActionSelection();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Battle|Select Action")
	int32 GetCurrentSelectActionIndex();

	UFUNCTION(BlueprintCallable, Category = "Battle|Select Action")
	void IncrementOrDecrementActionIndex(FVector2D input);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Battle|Select Enemy Target")
	bool IsInSelectEnemyTarget();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Battle|Select Attack")
	bool IsInSelectAttack();

public:
	virtual void BeginPlay() override;
};