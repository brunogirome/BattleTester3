// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnnableCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

#include "PaperFlipbookComponent.h"

FVector2D ASpawnnableCharacter::Get2DRotation()
{
  FVector velocity = this->GetCharacterMovement()->Velocity;

  if (!velocity.IsNearlyZero())
  {
    float rotationX = velocity.X;

    float rotationY = velocity.Y * -1;

    this->idleDirections = FVector2D(rotationX, rotationY);
  }

  return this->idleDirections;
}

bool ASpawnnableCharacter::IsMoving()
{
  return this->GetCharacterMovement()->Velocity.Length() > 0.f;
}

ASpawnnableCharacter::ASpawnnableCharacter()
{
  this->idleDirections = FVector2D(0.f, 0.f);

  this->GetCapsuleComponent()->SetCapsuleHalfHeight(66.f);

  UMaterialInterface *MaskedLitSpriteMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("MaterialInstanceConstant'/Paper2D/MaskedLitSpriteMaterial.MaskedLitSpriteMaterial'"));

  this->GetSprite()->OverrideMaterials.Empty();

  this->GetSprite()->OverrideMaterials.Emplace(MaskedLitSpriteMaterial);

  FVector spriteLocation = this->GetSprite()->GetRelativeLocation();

  spriteLocation.Z = -68.5f;

  this->GetSprite()->SetRelativeLocation(spriteLocation);

  this->GetSprite()->SetCastShadow(true);

  this->bUseControllerRotationYaw = false;
}