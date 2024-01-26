// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/BattleAIController.h"

#include "AI/NavigationSystemBase.h"
#include "Navigation/PathFollowingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "BattleManager.h"

#include "MyGameMode.h"
#include "Battle/Battlefield.h"
#include "Characters/CombatCharacter.h"

void ABattleAIController::BeginPlay()
{
  Super::BeginPlay();
}

void ABattleAIController::OnPossess(APawn *InPawn)
{
  Super::OnPossess(InPawn);

  ACombatCharacter *combatChar = Cast<ACombatCharacter>(InPawn);

  if (combatChar)
  {
    this->controlledPawn = combatChar;
  }
}

void ABattleAIController::OnReachedBattleSpot()
{
  if (!this->controlledPawn)
  {
    return;
  }

  this->controlledPawn->SetCharacterDirection(this->controlledPawn->battleSpot.Direction);

  if (this->controllingBattlefield)
  {
    this->controllingBattlefield->IncrementSucessBattleSpots();
  }
}