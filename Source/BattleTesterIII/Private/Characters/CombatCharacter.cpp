// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/CombatCharacter.h"

#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "PaperFlipbookComponent.h"

// #include "AI/BattleAIController.h"

#include "Enums/CombatStatus.h"

FDetachmentTransformRules defaultAttachRules = FDetachmentTransformRules(EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, EDetachmentRule::KeepRelative, true);

bool ACombatCharacter::IsDead()
{
  return this->CombatStatus[ECombatStatus::COMBAT_STATUS_CURRENT_HP] <= 0;
}

void ACombatCharacter::ReciveDamage(int32 amount)
{
  this->CombatStatus[ECombatStatus::COMBAT_STATUS_CURRENT_HP] -= FMath::Clamp(amount, 0, this->CombatStatus[ECombatStatus::COMBAT_STATUS_CURRENT_HP]);
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

  if (this->FakeStatus.IsValid())
  {
    this->CombatStatus.Add(ECombatStatus::COMBAT_STATUS_HP, this->FakeStatus.Hp);
    this->CombatStatus.Add(ECombatStatus::COMBAT_STATUS_CURRENT_HP, this->FakeStatus.Hp);
    this->CombatStatus.Add(ECombatStatus::COMBAT_STATUS_MANA, this->FakeStatus.Mana);
    this->CombatStatus.Add(ECombatStatus::COMBAT_STATUS_CURRENT_MANA, this->FakeStatus.Mana);
    this->CombatStatus.Add(ECombatStatus::COMBAT_STATUS_PHYSICAL_DAMAGE, this->FakeStatus.PhysicalDamage);
    this->CombatStatus.Add(ECombatStatus::COMBAT_STATUS_PHYSICAL_DEFENSE, this->FakeStatus.PhysicalDefense);
    this->CombatStatus.Add(ECombatStatus::COMBAT_STATUS_MAGIC_DAMAGE, this->FakeStatus.MagicDamage);
    this->CombatStatus.Add(ECombatStatus::COMBAT_STATUS_MAGIC_DEFENSE, this->FakeStatus.MagicDefense);
    this->CombatStatus.Add(ECombatStatus::COMBAT_STATUS_STAMINA, this->FakeStatus.Stamina);
    this->CombatStatus.Add(ECombatStatus::COMBAT_STATUS_SPEED, this->FakeStatus.Speed);
    this->CombatStatus.Add(ECombatStatus::COMBAT_STATUS_EVASION, this->FakeStatus.Evasion);
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
