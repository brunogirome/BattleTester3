// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "BattleAIController.generated.h"

class ACombatCharacter;
class ABattlefield;
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

	UPROPERTY(BlueprintReadWrite)
	UBattleManager *battleManagerInstance;

	UPROPERTY(BlueprintReadWrite)
	ABattlefield *controllingBattlefield;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float battleWalkSpeed = 2000.f;

	virtual void OnPossess(APawn *InPawn) override;

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void MoveToBattleSpot(ABattlefield *controllingBattlefieldReferance);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void MoveToSelectedTarget();

	UFUNCTION(BlueprintCallable)
	void OnReachedBattleSpot();

	virtual void BeginPlay() override;
};
