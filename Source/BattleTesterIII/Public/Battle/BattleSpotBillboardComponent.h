// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BillboardComponent.h"

#include "Structs/BattleSpot.h"

#include "BattleSpotBillboardComponent.generated.h"

class UTextRenderComponent;

enum ECharacterDirection : uint8;

/**
 *
 */
UCLASS()
class BATTLETESTERIII_API UBattleSpotBillboardComponent : public UBillboardComponent
{
	GENERATED_BODY()

	FText IndexLabel;

public:
	static int32 ComponentCounter;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<ECharacterDirection> BattleDirection;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTextRenderComponent *IndexTextComponent;

	void AttachOwnText();

	FBattleSpot GetBattleSpot();

	UBattleSpotBillboardComponent();
};
