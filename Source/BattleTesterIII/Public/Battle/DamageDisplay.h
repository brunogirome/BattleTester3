// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "DamageDisplay.generated.h"

class UCameraComponent;
class UTextRenderComponent;
class UProjectileMovementComponent;

UCLASS()
class BATTLETESTERIII_API ADamageDisplay : public AActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform &Transform);

	UPROPERTY(BlueprintReadOnly, Category = "Components")
	UCameraComponent *playerCameraReferance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UTextRenderComponent *TextRenderComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UProjectileMovementComponent *ProjectileMovementComponent;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageAmount;

	ADamageDisplay();
};
