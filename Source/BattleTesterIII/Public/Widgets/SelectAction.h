// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "SelectAction.generated.h"

class UButton;

struct FSlateBrush;

/**
 *
 */
UCLASS()
class BATTLETESTERIII_API USelectAction : public UUserWidget
{
	GENERATED_BODY()

	TArray<UButton *> selectActionButtons;

protected:
	UPROPERTY(BlueprintReadWrite)
	FSlateBrush normalStyle;

	UPROPERTY(BlueprintReadWrite)
	FSlateBrush hoverStytle;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UButton *Attack;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UButton *Spells;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UButton *Items;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UButton *Defend;

public:
	int32 SelectActionIndex = 0;

	UFUNCTION(BlueprintCallable)
	void IncrementOrDecrementAction(FVector2D input = FVector2D(0.f, 0.f));
};
