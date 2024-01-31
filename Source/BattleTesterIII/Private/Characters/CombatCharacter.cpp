// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/CombatCharacter.h"

#include "Engine/DataTable.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "PaperFlipbookComponent.h"

#include "MyGameInstance.h"
#include "AI/BattleAIController.h"

#include "Enums/CombatStatus.h"

FDetachmentTransformRules defaultAttachRules = FDetachmentTransformRules(EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, EDetachmentRule::KeepRelative, true);

bool ACombatCharacter::IsDead()
{
  return this->CombatStatus[ECombatStatus::COMBAT_STATUS_CURRENT_HP] <= 0;
}

bool ACombatCharacter::IsInBurnout()
{
  return this->CombatStatus[ECombatStatus::COMBAT_STATUS_CURRENT_STAMINA] < 0;
}

void ACombatCharacter::ReciveDamage(int32 amount)
{
  int32 *currentHp = this->CombatStatus.Find(ECombatStatus::COMBAT_STATUS_CURRENT_HP);

  if (currentHp)
  {
    *currentHp -= FMath::Clamp(amount, 0, *currentHp);
  }
}

void ACombatCharacter::SetAsTarget(USpringArmComponent *springArm, ACombatCharacter *lastCharacter)
{
  if (lastCharacter)
  {
    lastCharacter->DisplayTarget->SetVisibility(false);
  }

  this->DisplayTarget->SetVisibility(true);

  if (springArm->GetAttachParent())
  {
    springArm->DetachFromComponent(defaultAttachRules);
  }

  springArm->SetWorldLocation(this->GetActorLocation());
}

void ACombatCharacter::SetBattleSpot(FBattleSpot newBattleSpot)
{
  this->battleSpot = newBattleSpot;
}

ABattleAIController *ACombatCharacter::GetBattleAIController()
{
  ABattleAIController *validController = Cast<ABattleAIController>(this->GetController());

  if (validController)
  {
    return validController;
  }

  return nullptr;
}

void ACombatCharacter::ConsumeStamina(int32 amount)
{
  int32 *currentStamina = this->CombatStatus.Find(ECombatStatus::COMBAT_STATUS_CURRENT_STAMINA);

  if (currentStamina)
  {
    *currentStamina -= amount;
  }
}

void ACombatCharacter::RemoveCursor()
{
  this->DisplayTarget->SetVisibility(false);
}

void ACombatCharacter::SetAsCameraFocus(USpringArmComponent *springArm)
{
  if (springArm->GetAttachParent())
  {
    springArm->DetachFromComponent(defaultAttachRules);
  }

  springArm->AttachToComponent(this->GetCapsuleComponent(), FAttachmentTransformRules::KeepWorldTransform);
  springArm->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
}

void ACombatCharacter::BeginPlay()
{
  Super::BeginPlay();

  UMyGameInstance *gameInstance = Cast<UMyGameInstance>(this->GetWorld()->GetGameInstance());

  if (!gameInstance)
  {
    return;
  }

  if (!gameInstance->DT_FakeStatus)
  {
    return;
  }

  FFakeStatus *findFakeStatus = gameInstance->DT_FakeStatus->FindRow<FFakeStatus>(this->FakeCharacterName, "", true);

  if (findFakeStatus)
  {
    this->CombatStatus.Add(ECombatStatus::COMBAT_STATUS_HP, findFakeStatus->Hp);
    this->CombatStatus.Add(ECombatStatus::COMBAT_STATUS_CURRENT_HP, findFakeStatus->Hp);
    this->CombatStatus.Add(ECombatStatus::COMBAT_STATUS_MANA, findFakeStatus->Mana);
    this->CombatStatus.Add(ECombatStatus::COMBAT_STATUS_CURRENT_MANA, findFakeStatus->Mana);
    this->CombatStatus.Add(ECombatStatus::COMBAT_STATUS_PHYSICAL_DAMAGE, findFakeStatus->PhysicalDamage);
    this->CombatStatus.Add(ECombatStatus::COMBAT_STATUS_PHYSICAL_DEFENSE, findFakeStatus->PhysicalDefense);
    this->CombatStatus.Add(ECombatStatus::COMBAT_STATUS_MAGIC_DAMAGE, findFakeStatus->MagicDamage);
    this->CombatStatus.Add(ECombatStatus::COMBAT_STATUS_MAGIC_DEFENSE, findFakeStatus->MagicDefense);
    this->CombatStatus.Add(ECombatStatus::COMBAT_STATUS_STAMINA, findFakeStatus->Stamina);
    this->CombatStatus.Add(ECombatStatus::COMBAT_STATUS_CURRENT_STAMINA, findFakeStatus->Stamina);
    this->CombatStatus.Add(ECombatStatus::COMBAT_STATUS_SPEED, findFakeStatus->Speed);
    this->CombatStatus.Add(ECombatStatus::COMBAT_STATUS_EVASION, findFakeStatus->Evasion);
  }
}

ACombatCharacter::ACombatCharacter()
{
  this->DisplayTarget = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("DisplayTarget"));
  this->DisplayTarget->SetupAttachment(this->GetCapsuleComponent());
  this->DisplayTarget->SetRelativeLocation(FVector(0.f, 0.f, 150.f));
  this->DisplayTarget->SetRelativeRotation(FRotator(0.f, 0.f, -90.f));
  this->DisplayTarget->SetVisibility(false);

  // this->AIControllerClass = ABattleAIController::StaticClass();
}
