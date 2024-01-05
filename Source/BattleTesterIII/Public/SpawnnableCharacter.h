// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "PaperZDCharacter.h"

#include "SpawnnableCharacter.generated.h"

/**
 *
 */
UCLASS()
class BATTLETESTERIII_API ASpawnnableCharacter : public APaperZDCharacter
{
	GENERATED_BODY()

	FVector2D idleDirections;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FVector2D Get2DRotation();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsMoving();

	ASpawnnableCharacter();
};
