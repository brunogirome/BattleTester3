// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "Components/Button.h"

#include "MyGameMode.h"
#include "MyGameInstance.h"
#include "PartyManager.h"
#include "BattleManager.h"
#include "Characters/PartyLeader.h"

#include "Enums/BattleState.h"

void AMyPlayerController::BeginPlay()
{
  Super::BeginPlay();

  this->gameMode = this->GetWorld()->GetAuthGameMode<AMyGameMode>();

  this->BattleManager = gameMode->BattleManager;

  this->PartyLeader = Cast<UMyGameInstance>(this->GetGameInstance())->PartyManager->PartyLeader;
}

bool AMyPlayerController::IsInBattle()
{
  return this->gameMode->IsInBattle();
}

bool AMyPlayerController::checkBattleState(EBattleState state)
{
  bool rightBattleState = this->BattleManager->BattleState == state;

  bool isActionWidGetValid = this->SelectActionWidget->IsValidLowLevelFast();

  return rightBattleState && isActionWidGetValid && this->IsInBattle();
}

bool AMyPlayerController::IsInBattleStateActionSelection()
{
  return this->checkBattleState(EBattleState::BATTLE_STATE_PLAYER_ACTION_SELECT);
}

UButton *AMyPlayerController::GetCurrentSelectActionButton()
{
  return this->SelectActionButtons[this->SelectActionIndex];
}

void AMyPlayerController::IncrementOrDecrementActionIndex(FVector2D input)
{
  int32 newIndex = this->SelectActionIndex - input.Y;

  if (newIndex < 0)
  {
    newIndex = this->SelectActionButtons.Num() - 1;
  }
  else if (newIndex >= this->SelectActionButtons.Num())
  {
    newIndex = 0;
  }

  this->SelectActionIndex = newIndex;
}

bool AMyPlayerController::IsInSelectEnemyTarget()
{
  return this->checkBattleState(EBattleState::BATTLE_STATE_PLAYER_SELECT_ENEMY_TARGET);
}

void AMyPlayerController::MovePartyLeader(FVector2D input)
{
  float x = input.X;

  FVector directionX = FVector(1.f, 0.f, 0.f);

  this->PartyLeader->AddMovementInput(directionX, x, false);

  FVector directionY = FVector(0.f, -1.f, 0.f);

  float y = input.Y;

  this->PartyLeader->AddMovementInput(directionY, y, false);
}

void AMyPlayerController::AddSelectActionButtonsRef(UButton *buttonAttack, UButton *buttonSpells, UButton *buttonItems, UButton *buttonDefend)
{
  this->SelectActionButtons.Empty();

  this->SelectActionButtons.Add(buttonAttack);

  this->SelectActionButtons.Add(buttonSpells);

  this->SelectActionButtons.Add(buttonItems);

  this->SelectActionButtons.Add(buttonDefend);
}

AMyPlayerController::AMyPlayerController()
{
  this->SelectActionIndex = 0;
}