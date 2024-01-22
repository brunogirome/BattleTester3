#pragma once

#include "CoreMinimal.h"

#include "Enums/CharacterDirection.h"

#include "BattleSpot.generated.h"

USTRUCT(BlueprintType)
struct FBattleSpot
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ECharacterDirection> direction;

	FBattleSpot(){};

	FBattleSpot(FVector newLocation, TEnumAsByte<ECharacterDirection> directionWhenReached)
		: location(newLocation),
		  direction(directionWhenReached){};
};