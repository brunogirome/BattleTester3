// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Battlefield.generated.h"

class UBoxComponent;
class USceneComponent;
class UBattleSpotBillboardComponent;
class UTextRenderComponent;
class UTexture2D;

class AMyGameMode;
class UPartyManager;
class AHero;
class AEnemy;

UCLASS()
class BATTLETESTERIII_API ABattlefield : public AActor
{
	GENERATED_BODY()

	FVector iconHeightVectorAux = FVector(0, 0, this->ICON_HEIGHT);

	int32 amountOfBattleSpots;

	int32 amountOfActorsReachedBattleSpot = 0;

	AMyGameMode *gameMode;

	UPartyManager *partyManager;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battlefield Textures")
	UTexture2D *HeroSpotTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battlefield Textures")
	UTexture2D *EnemySpotTexture;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent) override;

	void updateBillboardTextures();
#endif

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MAX_NUMBER_OF_HEROES = 4;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MAX_NUMBER_OF_ENEMIES = 10;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<AEnemy *> Enemies;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBoxComponent *BattleBoundaries;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USceneComponent *HeroLine;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USceneComponent *EnemyLine;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<UBattleSpotBillboardComponent *> HeroesPositions;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<UBattleSpotBillboardComponent *> EnemiesPositions;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool BattleStarted;

	UFUNCTION(BlueprintCallable)
	void ActivateEnemyAggros(AActor *otherActor);

	UFUNCTION(BlueprintCallable)
	void DeactivateEnemyAggros();

	void LoadHeroesReferances();

	const static int32 ICON_HEIGHT = 55;

	void MoveActorsToBattleLocations();

	void IncrementSucessBattleSpots();

	virtual void BeginPlay() override;

	ABattlefield();
};
