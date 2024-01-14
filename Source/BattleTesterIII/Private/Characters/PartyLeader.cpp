// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/PartyLeader.h"

#include "GameFramework/SpringArmComponent.h"

#include "Components/CapsuleComponent.h"

APartyLeader::APartyLeader()
{
  this->SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));

  this->SpringArm->SetupAttachment(this->GetCapsuleComponent());
}
