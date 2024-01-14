// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpawnnableCharacter.h"
#include "CombatCharacter.generated.h"

class USpringArmComponent;

class UPaperFlipbookComponent;

/**
 *
 */
UCLASS()
class BATTLETESTERIII_API ACombatCharacter : public ASpawnnableCharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	int32 Hp;

	UPROPERTY(BlueprintReadOnly)
	int32 CurrentHp;

	UPROPERTY(BlueprintReadOnly)
	int32 Speed;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UPaperFlipbookComponent *DisplayTarget;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsDead();

	UFUNCTION(BlueprintCallable)
	void ReciveDamage(int32 amount);

	UFUNCTION(BlueprintCallable)
	void SetAsTarget(USpringArmComponent *springArm, ACombatCharacter *lastCharacter = nullptr);

	ACombatCharacter();
};
