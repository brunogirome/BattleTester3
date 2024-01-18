// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"

#include "PartyManager.h"

void UMyGameInstance::Init()
{
  this->PartyManager = NewObject<UPartyManager>(this, UPartyManager::StaticClass());
}

UMyGameInstance::UMyGameInstance() {}