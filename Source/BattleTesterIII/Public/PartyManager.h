// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PartyManager.generated.h"

class AMyGameMode;

class AHero;

class APartyLeader;

/**
 *
 */
UCLASS()
class BATTLETESTERIII_API UPartyManager : public UObject
{
	GENERATED_BODY()

	UWorld *worldRef;

public:
	UPROPERTY(BlueprintReadOnly)
	TArray<AHero *> PartyMembers;

	UPROPERTY(BlueprintReadOnly)
	APartyLeader *PartyLeader;

	void Initialize(APartyLeader *partyLeaderRef, AMyGameMode *gameMode);
};
