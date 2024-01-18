// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"

#include "Blueprint/UserWidget.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "MyGameMode.h"
#include "MyGameInstance.h"
#include "PartyManager.h"
#include "BattleManager.h"

#include "Characters/Hero.h"

#include "Widgets/SelectAction.h"
#include "Widgets/SpellSelection.h"
#include "Widgets/BattleInventoryList.h"

#include "Enums/BattleState.h"

void AMyPlayerController::BeginPlay()
{
  Super::BeginPlay();

  this->gameMode = this->GetWorld()->GetAuthGameMode<AMyGameMode>();

  this->battleManager = this->gameMode->BattleManager;

  this->partyLeader = Cast<UMyGameInstance>(this->GetGameInstance())->PartyManager->PartyLeader;
}

void AMyPlayerController::MovePartyLeader(FVector2D input)
{
  float x = input.X;

  FVector directionX = FVector(1.f, 0.f, 0.f);

  this->partyLeader->AddMovementInput(directionX, x, false);

  FVector directionY = FVector(0.f, -1.f, 0.f);

  float y = input.Y;

  this->partyLeader->AddMovementInput(directionY, y, false);
}

int32 AMyPlayerController::GetCurrentSelectActionIndex()
{
  return this->battleManager->SelectActionWidget->SelectActionIndex;
}

void AMyPlayerController::IncrementOrDecrementActionIndex(FVector2D input)
{
  this->battleManager->SelectActionWidget->IncrementOrDecrementAction(input);
}

void AMyPlayerController::CancelAttack()
{
  this->battleManager->TargetCharacter->RemoveCursor();

  this->battleManager->SetPlayerActionState();
}

void AMyPlayerController::CancelSpellSelect()
{
  this->battleManager->SpellSelectionWidget->SetVisibility(ESlateVisibility::Collapsed);

  if (this->battleManager->LastBattleState == EBattleState::BATTLE_STATE_PLAYER_ACTION_SELECT)
  {
    this->battleManager->SetPlayerActionState();
  }
  else
  {
    this->battleManager->BattleState = this->battleManager->LastBattleState;
  }
}

void AMyPlayerController::MoveSpellCursor(FVector2D input)
{
  this->battleManager->SpellSelectionWidget->MoveSpellCursor(input);
}

void AMyPlayerController::CancelBattleInventoryList()
{
  this->battleManager->InventoryListWidget->SetVisibility(ESlateVisibility::Collapsed);

  if (this->battleManager->LastBattleState == EBattleState::BATTLE_STATE_PLAYER_ACTION_SELECT)
  {
    this->battleManager->SetPlayerActionState();
  }
  else
  {
    this->battleManager->BattleState = this->battleManager->LastBattleState;
  }
}

void AMyPlayerController::MoveBattleInventoryCursor(FVector2D input)
{
  this->battleManager->InventoryListWidget->MoveCursor(input);
}

bool AMyPlayerController::IsInOverWorld()
{
  return this->gameMode->IsInOverWorld();
}

bool AMyPlayerController::IsInBattle()
{
  return this->gameMode->IsInBattle();
}

bool AMyPlayerController::IsInBattleStateActionSelection()
{
  bool isActionWidgetValid = this->battleManager->SelectActionWidget->IsValidLowLevelFast();

  return this->checkBattleState(EBattleState::BATTLE_STATE_PLAYER_ACTION_SELECT) && isActionWidgetValid;
}

bool AMyPlayerController::IsInSelectEnemyTarget()
{
  return this->checkBattleState(EBattleState::BATTLE_STATE_PLAYER_SELECT_ENEMY_TARGET);
}

bool AMyPlayerController::IsInSelectAttack()
{
  return this->checkBattleState(EBattleState::BATTLE_STATE_PLAYER_SELECT_ATTACK);
}

bool AMyPlayerController::IsInSelectSpell()
{
  bool isSpellWidgetValid = this->battleManager->SpellSelectionWidget->IsValidLowLevelFast();

  return this->checkBattleState(EBattleState::BATTLE_STATE_PLAYER_SELECT_SPELL) && isSpellWidgetValid;
}

bool AMyPlayerController::IsInIventoryList()
{
  bool isBattleInventoryListValid = this->battleManager->InventoryListWidget->IsValidLowLevelFast();

  return this->checkBattleState(EBattleState::BATTLE_STATE_PLAYER_SELECT_ITEM) && isBattleInventoryListValid;
}

bool AMyPlayerController::checkBattleState(EBattleState state)
{
  bool rightBattleState = this->battleManager->BattleState == state;

  return rightBattleState && this->IsInBattle();
}

AMyPlayerController::AMyPlayerController()
{
  this->CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));

  this->CameraSpringArm->SetupAttachment(this->RootComponent);

  this->playerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));

  this->playerCamera->SetupAttachment(this->CameraSpringArm, USpringArmComponent::SocketName);
}
