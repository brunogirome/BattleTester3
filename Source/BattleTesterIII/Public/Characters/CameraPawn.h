// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CameraPawn.generated.h"

class USpringArmComponent;

class UCameraComponent;

class UCapsuleComponent;

UCLASS()
class BATTLETESTERIII_API ACameraPawn : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	UCapsuleComponent *CapsuleComponent;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	USpringArmComponent *CameraSpringArm;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	UCameraComponent *PlayerCamera;

	ACameraPawn();
};
