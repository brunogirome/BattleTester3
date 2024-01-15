// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "MyPlayerController.generated.h"

class UUserWidget;

class UButton;

class UBattleManager;

class AMyGameMode;

class APartyLeader;

enum EBattleState : uint8;

/**
 *
 */
UCLASS()
class BATTLETESTERIII_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

	AMyGameMode *gameMode;

	bool checkBattleState(EBattleState state);

public:
	UPROPERTY(BlueprintReadOnly, Category = "Overworld")
	APartyLeader *PartyLeader;

	UPROPERTY(BlueprintReadOnly, Category = "Battle")
	UBattleManager *BattleManager;

	UPROPERTY(BlueprintReadWrite, Category = "Battle|Select Action")
	UUserWidget *SelectActionWidget;

	UPROPERTY(BlueprintReadWrite, Category = "Battle|Select Action")
	int32 SelectActionIndex;

	UPROPERTY(BlueprintReadWrite, Category = "Battle|Select Action")
	TArray<UButton *> SelectActionButtons;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Battle")
	bool IsInBattle();

	UFUNCTION(BlueprintCallable, Category = "Overworld")
	void MovePartyLeader(FVector2D input);

	UFUNCTION(BlueprintCallable, Category = "Battle|Select Action")
	void AddSelectActionButtonsRef(UButton *buttonAttack, UButton *buttonSpells, UButton *buttonItems, UButton *buttonDefend);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Battle|Select Action")
	bool IsInBattleStateActionSelection();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Battle|Select Action")
	UButton *GetCurrentSelectActionButton();

	UFUNCTION(BlueprintCallable, Category = "Battle|Select Action")
	void IncrementOrDecrementActionIndex(FVector2D input);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Battle|Select Enemy Target")
	bool IsInSelectEnemyTarget();

	virtual void BeginPlay() override;

	AMyPlayerController();
};
