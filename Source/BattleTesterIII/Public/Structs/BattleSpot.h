#pragma once

#include "CoreMinimal.h"

#include "Enums/CharacterDirection.h"

#include "BattleSpot.generated.h"

USTRUCT(BlueprintType)
struct FBattleSpot
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector Location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ECharacterDirection> Direction;

	FBattleSpot(){};

	FBattleSpot(FVector newLocation, TEnumAsByte<ECharacterDirection> directionWhenReached)
		: Location(newLocation),
		  Direction(directionWhenReached){};
};