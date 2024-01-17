// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "PaperZDCharacter.h"

#include "SpawnnableCharacter.generated.h"

enum ECharacterDirection : uint8;

/**
 *
 */
UCLASS()
class BATTLETESTERIII_API ASpawnnableCharacter : public APaperZDCharacter
{
	GENERATED_BODY()

	FVector2D idleDirections;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Animation")
	FVector2D Get2DRotation();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Animation")
	bool IsMoving();
	UFUNCTION(BlueprintCallable, Category = "Animation")
	void SetCharacterDirection(ECharacterDirection characterDirection);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Interface")
	FVector2D GetLocationOnScreen();

	ASpawnnableCharacter();
};
