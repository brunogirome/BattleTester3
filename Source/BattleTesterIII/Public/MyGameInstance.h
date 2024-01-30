// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "MyGameInstance.generated.h"

class UPaperFlipbook;

class ABattleAIController;
class UPartyManager;
class UDataTable;
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

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Party")
	TSubclassOf<ABattleAIController> AIC_BattleAIControllerClass;

public:
	UPROPERTY(BlueprintReadOnly, Category = "Party")
	UPartyManager *PartyManager;

	UPROPERTY(Editanywhere, Category = "Data Tables")
	UDataTable *DT_FakeStatus;

	virtual void Init() override;

	UMyGameInstance();
};
