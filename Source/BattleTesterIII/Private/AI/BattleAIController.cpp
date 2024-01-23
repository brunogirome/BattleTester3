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

  AMyGameMode *gameMode = Cast<AMyGameMode>(this->GetWorld()->GetAuthGameMode());

  if (gameMode)
  {
    this->battleManagerInstance = gameMode->BattleManager;
  }

  // this->GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &ABattleAIController::OnMoveComplete);
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

  if (!this->battleManagerInstance)
  {
    return;
  }

  if (this->battleManagerInstance->BattlefieldInstance)
  {
    this->battleManagerInstance->BattlefieldInstance->IncrementSucessBattleSpots();
  }
}

// void ABattleAIController::MoveToBattleSpot()
// {
//   if (!this->controlledPawn)
//   {
//     return;
//   }

//   GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Started MoveToBattleSpot");

//   this->controlledPawn->GetCharacterMovement()->MaxWalkSpeed = this->battleWalkSpeed;

//   FVector spotLocation = this->controlledPawn->battleSpot.Location;
//   float acceptanceRadius = 0.1f;
//   bool stopOnOverlap = false;

//   this->requestMoveToSpotID = this->MoveToLocation(spotLocation, acceptanceRadius, stopOnOverlap);
// }

// void ABattleAIController::OnMoveComplete(FAIRequestID RequestID, const FPathFollowingResult &Result)
// {

//   if (Result.IsSuccess())
//   {
//     if (requestMoveToSpotID == RequestID)
//     {
//       GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Ended");

//       FTimerHandle TimerHandle;
//       float Delay = 0.1f;

//       this->GetWorld()->GetTimerManager().SetTimer(
//           TimerHandle, [&]()
//           {

//               if (!this->controlledPawn)
//               {
//                 return;
//               }

//               this->controlledPawn->SetCharacterDirection(this->controlledPawn->battleSpot.Direction);

//               if (!this->battleManagerInstance)
//               {
//                 return;
//               }

//               if (this->battleManagerInstance->BattlefieldInstance)
//               {
//                 this->battleManagerInstance->BattlefieldInstance->IncrementSucessBattleSpots();
//               } },
//           Delay, false);
//     }
//   }
// }