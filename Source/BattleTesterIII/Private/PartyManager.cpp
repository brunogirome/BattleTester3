// Fill out your copyright notice in the Description page of Project Settings.

#include "PartyManager.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "MyGameInstance.h"
#include "MyGameMode.h"
#include "MyPlayerController.h"

#include "Characters/Hero.h"

void UPartyManager::SpawnParty(FVector startLocation, FRotator startRotation)
{
  TArray<AActor *> foundPlayerStarts;

  if (startLocation.Size() == 0 || startRotation.IsZero())
  {
    UGameplayStatics::GetAllActorsOfClass(this->gameMode->GetWorld(), APlayerStart::StaticClass(), foundPlayerStarts);

    if (foundPlayerStarts.Num() > 0)
    {
      APlayerStart *playerStart = Cast<APlayerStart>(foundPlayerStarts[0]);

      if (playerStart)
      {
        startLocation = startLocation.Size() == 0 ? playerStart->GetActorLocation() : startLocation;

        startRotation = startRotation.IsZero() ? playerStart->GetActorRotation() : startRotation;
      }
    }
  }

  for (int32 i = 0; i < this->gameInstance->PartyMemberNames.Num(); i++)
  {
    FName heroName = this->gameInstance->PartyMemberNames[i];

    TSubclassOf<AHero> heroClass = this->gameInstance->PartyMemberClasses.FindRef(heroName);

    if (!heroClass)
    {
      continue;
    }

    FActorSpawnParameters spawnParameters;

    spawnParameters.Owner = this->playerController;

    AHero *hero = this->gameMode->GetWorld()->SpawnActor<AHero>(heroClass, startLocation, startRotation);

    hero->SpawnDefaultController();

    this->PartyMembers.Add(hero);

    if (i != this->gameInstance->PartyMemberNames.Num() - 1 && this->PartyMembers[i])
    {
      this->PartyMembers[i]->DoSaveMovimentHistory = true;
    }

    if (this->PartyMembers.Num() == 1)
    {
      this->PartyLeader = this->PartyMembers[0];

      this->PartyLeader->IsThePartyLeader = true;
    }
    else if (this->PartyMembers[i] && this->PartyMembers[i - 1])
    {
      this->PartyMembers[i]->TargetFollowHero = this->PartyMembers[i - 1];
    }
  }
}

void UPartyManager::Initialize(UMyGameInstance *gameInstanceRef, AMyGameMode *gameModeRef)
{
  if (!(gameInstanceRef || gameModeRef))
  {
    return;
  }

  this->gameMode = gameModeRef;

  this->gameInstance = gameInstanceRef;

  this->playerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
}