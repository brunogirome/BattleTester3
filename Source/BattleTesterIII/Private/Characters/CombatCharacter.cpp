// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/CombatCharacter.h"

#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "PaperFlipbookComponent.h"

bool ACombatCharacter::IsDead()
{
  return this->CurrentHp <= 0.f;
}

void ACombatCharacter::ReciveDamage(int32 amount)
{
  this->CurrentHp -= FMath::Clamp(amount, 0, this->CurrentHp);
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
    springArm->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, EDetachmentRule::KeepRelative, true));
  }

  springArm->SetWorldLocation(this->GetActorLocation());
}

ACombatCharacter::ACombatCharacter()
{
  this->DisplayTarget = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("DisplayTarget"));

  this->DisplayTarget->SetupAttachment(this->GetCapsuleComponent());

  this->DisplayTarget->SetRelativeLocation(FVector(0.f, 0.f, 150.f));

  this->DisplayTarget->SetRelativeRotation(FRotator(0.f, 0.f, -90.f));

  this->DisplayTarget->SetVisibility(false);

  this->CurrentHp = 100.f;

  this->Hp = 100.f;

  this->Speed = 10.f;
}
