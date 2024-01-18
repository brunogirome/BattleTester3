// Fill out your copyright notice in the Description page of Project Settings.

#include "PartyManager.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"

#include "MyGameInstance.h"
#include "MyGameMode.h"
#include "MyPlayerController.h"

#include "Characters/Hero.h"

void UPartyManager::Initialize(UMyGameInstance *gameInstanceRef, AMyGameMode *gameModeRef)
{
  if (!(gameInstanceRef || gameModeRef))
  {
    return;
  }

  this->gameMode = gameModeRef;

  this->gameInstance = gameInstanceRef;

  this->playerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

  FVector location = FVector(0, 0, 0);

  FRotator rotation = FRotator(0, 0, 0);

  TArray<AActor *> foundPlayerStarts;

  UGameplayStatics::GetAllActorsOfClass(this->gameMode->GetWorld(), APlayerStart::StaticClass(), foundPlayerStarts);

  if (foundPlayerStarts.Num() > 0)
  {
    APlayerStart *playerStart = Cast<APlayerStart>(foundPlayerStarts[0]);

    if (playerStart)
    {
      location = playerStart->GetActorLocation();

      rotation = playerStart->GetActorRotation();
    }
  }

  for (FName heroName : this->gameInstance->PartyMemberNames)
  {
    TSubclassOf<AHero> heroClass = this->gameInstance->PartyMemberClasses.FindRef(heroName);

    if (!heroClass)
    {
      continue;
    }

    FActorSpawnParameters spawnParameters;

    spawnParameters.Owner = this->playerController;

    AHero *hero = this->gameMode->GetWorld()->SpawnActor<AHero>(heroClass, location, rotation, spawnParameters);
  }
}