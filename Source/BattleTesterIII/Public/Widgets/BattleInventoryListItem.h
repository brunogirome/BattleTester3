// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "BattleInventoryListItem.generated.h"

class AMyGameMode;

/**
 *
 */
UCLASS()
class BATTLETESTERIII_API UBattleInventoryListItem : public UUserWidget
{
	GENERATED_BODY()

	AMyGameMode *gameMode;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsInHoverPosition();

	UPROPERTY(BlueprintReadOnly)
	int32 Index;

	UPROPERTY(BlueprintReadOnly)
	bool HaveContent;

	UPROPERTY(BlueprintReadOnly)
	FString ItemName;

	virtual void NativeConstruct() override;
};
