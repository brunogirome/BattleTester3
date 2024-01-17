// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SpellCard.generated.h"

/**
 *
 */
UCLASS()
class BATTLETESTERIII_API USpellCard : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	bool IsCardHovered;
};
