// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatCharacter.h"
#include "Hero.generated.h"

class AMyGameMode;

/**
 *
 */
UCLASS()
class BATTLETESTERIII_API AHero : public ACombatCharacter
{
	GENERATED_BODY()

	AMyGameMode *gameMode;

	float const ACCEPTANCE_RADIUS = 120.f;

	float const FOLLOW_DISTANCE = 3;

	TArray<FVector> movementHistory;

	int historySize = 10;

	void updateMovementHistory();

	void followMovementHistory();

public:
	AHero *TargetFollowHero;

	bool DoSaveMovimentHistory;

	bool IsThePartyLeader;

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;
};
