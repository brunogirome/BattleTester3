// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "MyGameMode.generated.h"

class UBattleManager;

enum EBattleState;

enum EWorldState;

/**
 *
 */
UCLASS(BlueprintType)
class BATTLETESTERIII_API AMyGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintType, BlueprintReadWrite)
	TEnumAsByte<EWorldState> WorldState;

	UPROPERTY(BlueprintReadOnly)
	UBattleManager *BattleManager;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsInBattle();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	TEnumAsByte<EBattleState> GetBattleState();

	virtual void BeginPlay() override;

	AMyGameMode();
};
