// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PartyManager.generated.h"

class AMyGameMode;

class AHero;

class UMyGameInstance;

class AMyPlayerController;

DECLARE_DELEGATE(FOnGameSpawnedHeroes);

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
	FOnGameSpawnedHeroes OnGameSpawnedHeroes;

	UPROPERTY(BlueprintReadWrite)
	TArray<AHero *> PartyMembers;

	UPROPERTY(BlueprintReadWrite)
	AHero *PartyLeader;

	void SetupParty();

	void SpawnParty(FVector startLocation = FVector(0, 0, 0), FRotator startRotation = FRotator(0, 0, 0));

	void Initialize(UMyGameInstance *gameInstanceRef, AMyGameMode *gameModeRef);
};
