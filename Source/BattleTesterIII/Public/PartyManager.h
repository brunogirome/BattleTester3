// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PartyManager.generated.h"

class AMyGameMode;

class AHero;

class UMyGameInstance;

class AMyPlayerController;

/**
 *
 */
UCLASS()
class BATTLETESTERIII_API UPartyManager : public UObject
{
	GENERATED_BODY()

	AMyGameMode *gameMode;

	UMyGameInstance *gameInstance;

	AMyPlayerController *playerController;

public:
	UPROPERTY(BlueprintReadWrite)
	TArray<AHero *> PartyMembers;

	UPROPERTY(BlueprintReadWrite)
	AHero *PartyLeader;

	UFUNCTION(BlueprintCallable)
	void SpawnParty(FVector startLocation = FVector(0, 0, 0), FRotator startRotation = FRotator(0, 0, 0));

	void Initialize(UMyGameInstance *gameInstanceRef, AMyGameMode *gameModeRef);
};
