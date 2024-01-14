// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

class UPartyManager;

/**
 *
 */
UCLASS()
class BATTLETESTERIII_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	UPartyManager *PartyManager;

	UMyGameInstance(const FObjectInitializer &ObjectInitializer);

	UMyGameInstance();
};
