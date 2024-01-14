// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"

#include "PartyManager.h"

UMyGameInstance::UMyGameInstance(const FObjectInitializer &ObjectInitializer)
    : Super(ObjectInitializer)
{
  this->PartyManager = ObjectInitializer.CreateDefaultSubobject<UPartyManager>(this, TEXT("PartyManager"));
}

UMyGameInstance::UMyGameInstance() {}