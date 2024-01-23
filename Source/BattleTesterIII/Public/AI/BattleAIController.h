// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "BattleAIController.generated.h"

class ACombatCharacter;

class UBattleManager;

/**
 *
 */
UCLASS()
class BATTLETESTERIII_API ABattleAIController : public AAIController
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly)
	FAIRequestID requestMoveToSpotID;

	UPROPERTY(BlueprintReadWrite)
	ACombatCharacter *controlledPawn;

	UPROPERTY(BlueprintReadOnly)
	UBattleManager *battleManagerInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float battleWalkSpeed = 2000.f;

	virtual void OnPossess(APawn *InPawn) override;

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void MoveToBattleSpot();

	// void OnMoveComplete(FAIRequestID RequestID, const FPathFollowingResult &Result);

	UFUNCTION(BlueprintCallable)
	void OnReachedBattleSpot();

	virtual void BeginPlay() override;
};
