// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Battlefield.generated.h"

class UBoxComponent;
class USceneComponent;
class UBillboardComponent;
class UTextRenderComponent;

class AEnemy;

UCLASS()
class BATTLETESTERIII_API ABattlefield : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MAX_NUMBER_OF_HEROES = 4;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MAX_NUMBER_OF_ENEMIES = 10;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float ICON_HEIGHT = 55.f;

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
	TArray<UBillboardComponent *> HeroesPositions;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<UBillboardComponent *> EnemiesPositions;

	// UPROPERTY(BlueprintReadWrite, EditAnywhere)
	// TArray<UTextRenderComponent *> HeroesIndexDisplay;

	// UPROPERTY(BlueprintReadWrite, EditAnywhere)
	// TArray<UTextRenderComponent *> EnemiesIndexs;

	virtual void BeginPlay() override;

	ABattlefield();
};
