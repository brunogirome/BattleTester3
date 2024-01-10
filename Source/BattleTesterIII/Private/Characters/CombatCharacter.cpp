// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/CombatCharacter.h"

bool ACombatCharacter::IsDead()
{
  return this->CurrentHp <= 0.f;
}

void ACombatCharacter::TakeDamage(int32 amount)
{
  this->CurrentHp -= FMath::Clamp(amount, 0, this->CurrentHp);
}

ACombatCharacter::ACombatCharacter()
{
  this->CurrentHp = 100.f;

  this->Hp = 100.f;

  this->Speed = 10.f;
}
