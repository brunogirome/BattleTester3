// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatCharacter.h"
#include "Hero.generated.h"

/**
 *
 */
UCLASS()
class BATTLETESTERIII_API AHero : public ACombatCharacter
{
	GENERATED_BODY()

	void followHero();

	float const DISTANCE_TO_KEEP = 100.f;

	TArray<FVector> MovementHistory;

	int HistorySize = 10;

	void UpdateMovementHistory();

	void FollowMovementHistory();

public:
	AHero *TargetFollowHero;

	bool IsLeader;

	bool IsPartyLeader;

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;
};
