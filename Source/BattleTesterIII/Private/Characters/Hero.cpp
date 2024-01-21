// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/Hero.h"

void AHero::BeginPlay()
{
  Super::BeginPlay();
}

void AHero::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

  if (this->DoSaveMovimentHistory)
  {
    this->updateMovementHistory();
  }

  if (!this->IsThePartyLeader)
  {
    this->followMovementHistory();
  }
}

void AHero::updateMovementHistory()
{
  this->movementHistory.Insert(GetActorLocation(), 0);

  if (this->movementHistory.Num() > historySize)
  {
    this->movementHistory.RemoveAt(historySize);
  }
}

void AHero::followMovementHistory()
{
  if (!this->TargetFollowHero || this->TargetFollowHero->movementHistory.Num() == 0)
  {
    return;
  }

  int historyIndex = FMath::Min(this->FOLLOW_DISTANCE, TargetFollowHero->movementHistory.Num() - 1);

  FVector targetPoint = TargetFollowHero->movementHistory[historyIndex];

  FVector direction = (targetPoint - GetActorLocation()).GetSafeNormal();

  float distance = FVector::Dist(targetPoint, GetActorLocation());

  if (distance > this->ACCEPTANCE_RADIUS)
  {
    AddMovementInput(direction, 1.0f, false);
  }
}