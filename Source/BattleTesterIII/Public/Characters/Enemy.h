// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/CombatCharacter.h"

#include "Enemy.generated.h"

class ACombatCharacter;

class ABattlefield;

struct FBattleSpot;

/**
 *
 */
UCLASS()
class BATTLETESTERIII_API AEnemy : public ACombatCharacter
{
	GENERATED_BODY()

	ABattlefield *ownerBattlefield;

protected:
	UFUNCTION(BlueprintCallable, Category = "Battle|Aggro")
	void triggerBattleStart(AActor *otherActor);

public:
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle|Aggro")
	// bool IsFollowing;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle|Aggro")
	bool IsAggroActive;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle|Aggro")
	int32 BattleIndex;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Battle|Aggro")
	ACombatCharacter *HeroTarget;

	UFUNCTION(BlueprintCallable, Category = "Battle|Aggro")
	void SetAggro(bool newAggroStatus, ACombatCharacter *heroToFollow = nullptr);

	UFUNCTION(BlueprintCallable, Category = "Battle|Aggro")
	void SetupBattle(FBattleSpot position, ABattlefield *battlefieldInstance);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Battle|Aggro")
	void FollowHeroActor();

	virtual void Tick(float DeltaTime) override;
};