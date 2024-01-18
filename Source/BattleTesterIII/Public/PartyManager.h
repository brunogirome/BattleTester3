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
	UPROPERTY(BlueprintReadOnly)
	TArray<AHero *> PartyMembers;

	UPROPERTY(BlueprintReadOnly)
	AHero *PartyLeader;

	void Initialize(UMyGameInstance *gameInstanceRef, AMyGameMode *gameModeRef);
};
