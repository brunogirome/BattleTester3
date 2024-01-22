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

	FAIRequestID requestMoveToSpotID;

	ACombatCharacter *controlledPawn;

	UBattleManager *battleManagerInstance;

public:
	void
	MoveToBattleSpot();

	void OnMoveComplete(FAIRequestID RequestID, const FPathFollowingResult &Result);

	virtual void BeginPlay() override;
};
