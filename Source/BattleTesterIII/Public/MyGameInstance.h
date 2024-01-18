// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "MyGameInstance.generated.h"

class UPartyManager;

class UPaperFlipbook;

class AHero;

/**
 *
 */
UCLASS()
class BATTLETESTERIII_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

	friend class UPartyManager;

protected:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Party")
	TMap<FName, TSubclassOf<AHero>> PartyMemberClasses;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Party")
	TArray<FName> PartyMemberNames;

public:
	UPROPERTY(BlueprintReadOnly, Category = "Party")
	UPartyManager *PartyManager;

	virtual void Init() override;

	UMyGameInstance();
};
