// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"

#include "Blueprint/UserWidget.h"

#include "Widgets/SelectAction.h"

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

bool AMyPlayerController::IsInBattleStateActionSelection()
{
  return this->checkBattleState(EBattleState::BATTLE_STATE_PLAYER_ACTION_SELECT);
}

int32 AMyPlayerController::GetCurrentSelectActionIndex()
{
  return this->BattleManager->SelectActionWidget->SelectActionIndex;
}

void AMyPlayerController::IncrementOrDecrementActionIndex(FVector2D input)
{
  this->BattleManager->SelectActionWidget->IncrementOrDecrementAction(input);
}

bool AMyPlayerController::IsInSelectEnemyTarget()
{
  return this->checkBattleState(EBattleState::BATTLE_STATE_PLAYER_SELECT_ENEMY_TARGET);
}

bool AMyPlayerController::IsInSelectAttack()
{
  return this->checkBattleState(EBattleState::BATTLE_STATE_PLAYER_SELECT_ATTACK);
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

bool AMyPlayerController::checkBattleState(EBattleState state)
{
  bool rightBattleState = this->BattleManager->BattleState == state;

  bool isActionWidGetValid = this->BattleManager->SelectActionWidget->IsValidLowLevelFast();

  return rightBattleState && isActionWidGetValid && this->IsInBattle();
}