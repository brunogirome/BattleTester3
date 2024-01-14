// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hero.h"
#include "PartyLeader.generated.h"

class USpringArmComponent;

/**
 * 
 */
UCLASS()
class BATTLETESTERIII_API APartyLeader : public AHero
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USpringArmComponent *SpringArm;

	APartyLeader();
};
