// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "MyGameMode.generated.h"

class UMyGameInstance;

class UBattleManager;

class USelectAction;

enum EBattleState : uint8;

enum EWorldState : uint8;

/**
 *
 */
UCLASS(BlueprintType)
class BATTLETESTERIII_API AMyGameMode : public AGameModeBase
{
	GENERATED_BODY()

	UMyGameInstance *gameInstance;

protected:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Battle|Widget Classes")
	TSubclassOf<USelectAction> actionSelectWidgetClass;

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
