// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "MyGameMode.generated.h"

enum EBattleState;

enum EWorldState;

/**
 *
 */
UCLASS(BlueprintType)
class BATTLETESTERIII_API AMyGameMode : public AGameModeBase
{

public:
	UPROPERTY(BlueprintType, BlueprintReadWrite)
	TEnumAsByte<EWorldState> WorldState;

	UPROPERTY(BlueprintType, BlueprintReadWrite)
	TEnumAsByte<EBattleState> BattleState;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsInBattle();

	GENERATED_BODY()

	AMyGameMode();
};
