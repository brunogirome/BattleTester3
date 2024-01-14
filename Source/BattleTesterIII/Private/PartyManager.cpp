// Fill out your copyright notice in the Description page of Project Settings.

#include "PartyManager.h"

#include "MyGameMode.h"

#include "Characters/Hero.h"
#include "Characters/PartyLeader.h"

void UPartyManager::Initialize(APartyLeader *partyLeaderRef, AMyGameMode *gameMode)
{
  this->PartyLeader = partyLeaderRef;

  this->PartyMembers.Add(this->PartyLeader);

  this->worldRef = gameMode->GetWorld();
}