// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/Hero.h"

#include "AIController.h"

void AHero::BeginPlay()
{
  Super::BeginPlay();
}

void AHero::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

  // if (this->TargetFollowHero)
  // {
  //   this->followHero();
  // }

  if (IsLeader)
  {
    this->UpdateMovementHistory();
  }

  if (!IsPartyLeader)
  {
    this->FollowMovementHistory();
  }
}

void AHero::UpdateMovementHistory()
{
  MovementHistory.Insert(GetActorLocation(), 0);

  if (MovementHistory.Num() > HistorySize)
  {
    MovementHistory.RemoveAt(HistorySize);
  }
}

// Método para seguir o histórico de movimentos
void AHero::FollowMovementHistory()
{
  if (!this->TargetFollowHero || TargetFollowHero->MovementHistory.Num() == 0)
  {
    return;
  }

  float AcceptanceRadius = 120.f;

  int FollowDistance = 3;

  // Define qual ponto da história este herói deve seguir
  int historyIndex = FMath::Min(FollowDistance, TargetFollowHero->MovementHistory.Num() - 1);
  FVector targetPoint = TargetFollowHero->MovementHistory[historyIndex];

  FVector direction = (targetPoint - GetActorLocation()).GetSafeNormal();
  float distance = FVector::Dist(targetPoint, GetActorLocation());

  if (distance > AcceptanceRadius) // AcceptanceRadius definido previamente
  {
    // Adicionando movimento na direção do ponto histórico
    AddMovementInput(direction, 1.0f, false);
  }
}

void AHero::followHero()
{
  if (!this->TargetFollowHero)
  {
    return;
  }

  FVector FollowLocation = TargetFollowHero->GetActorLocation() - (TargetFollowHero->GetActorForwardVector());

  AAIController *AIController = Cast<AAIController>(GetController());

  if (AIController)
  {
    float AcceptanceRadius = 35.0f;

    AIController->MoveToLocation(FollowLocation, DISTANCE_TO_KEEP, false);
  }
}