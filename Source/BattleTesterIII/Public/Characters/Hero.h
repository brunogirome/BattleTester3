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
	
public:
	virtual void BeginPlay() override;
};
