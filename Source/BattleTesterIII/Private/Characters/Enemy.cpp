// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/Enemy.h"

#include "Characters/Hero.h"
#include "Battle/Battlefield.h"

#include "Structs/BattleSpot.h"

void AEnemy::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

  if (!this->IsFollowing && this->IsAggroActive)
  {
    this->IsFollowing = true;

    if (this->HeroTarget)
    {
      this->FollowHeroActor();
    }
  }
}

void AEnemy::SetAggro(bool newAggroStatus, ACombatCharacter *hetoToFollow)
{
  this->IsAggroActive = newAggroStatus;

  this->HeroTarget = hetoToFollow;
}

void AEnemy::SetupBattle(FBattleSpot position, ABattlefield *battlefieldInstance)
{
  this->SetBattleSpot(position);

  this->ownerBattlefield = battlefieldInstance;
}

void AEnemy::triggerBattleStart(AActor *otherActor)
{
  if (!otherActor || !this->HeroTarget)
  {
    return;
  }

  if (otherActor != this->HeroTarget)
  {
    return;
  }

  this->ownerBattlefield->MoveActorsToBattleLocations();
}