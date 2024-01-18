// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "MyPlayerController.generated.h"

class USpringArmComponent;

class UCameraComponent;

class UBattleManager;

class AMyGameMode;

class AHero;

enum EBattleState : uint8;

/**
 *
 */
UCLASS()
class BATTLETESTERIII_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	USpringArmComponent *CameraSpringArm;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Overworld")
	AHero *partyLeader;

	UFUNCTION(BlueprintCallable, Category = "Overworld")
	void MovePartyLeader(FVector2D input);

	UPROPERTY(BlueprintReadOnly, Category = "Battle")
	UBattleManager *battleManager;

	UFUNCTION(BlueprintCallable, Category = "Battle|Select Action")
	void IncrementOrDecrementActionIndex(FVector2D input);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Battle|Select Action")
	int32 GetCurrentSelectActionIndex();

	UFUNCTION(BlueprintCallable, Category = "Battle|Select Enemy Target")
	void CancelAttack();

	UFUNCTION(BlueprintCallable, Category = "Battle|Select Spell")
	void MoveSpellCursor(FVector2D input);

	UFUNCTION(BlueprintCallable, Category = "Battle|Select Spell")
	void CancelSpellSelect();

	UFUNCTION(BlueprintCallable, Category = "Battle|Battle Inventory List")
	void MoveBattleInventoryCursor(FVector2D input);

	UFUNCTION(BlueprintCallable, Category = "Battle|Battle Inventory List")
	void CancelBattleInventoryList();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Check State|Overworld")
	bool IsInOverWorld();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Check State|Battle")
	bool IsInBattle();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Check State|Battle")
	bool IsInBattleStateActionSelection();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Check State|Battle")
	bool IsInSelectEnemyTarget();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Check State|Battle")
	bool IsInSelectAttack();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Check State|Battle")
	bool IsInSelectSpell();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Check State|Battle")
	bool IsInIventoryList();

private:
	AMyGameMode *gameMode;

	bool checkBattleState(EBattleState state);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent *playerCamera;

public:
	AMyPlayerController();
};
