// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle/DamageDisplay.h"

#include "Camera/CameraComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "Characters/CameraPawn.h"

void ADamageDisplay::BeginPlay()
{
	Super::BeginPlay();

	ACameraPawn *cameraPawn = Cast<ACameraPawn>(this->GetWorld()->GetFirstPlayerController()->GetViewTarget());

	if (cameraPawn && cameraPawn->PlayerCamera)
	{
		this->playerCameraReferance = cameraPawn->PlayerCamera;
	}
}

void ADamageDisplay::OnConstruction(const FTransform &Transform)
{
	this->TextRenderComponent->SetText(FText::AsNumber(std::trunc(this->DamageAmount)));
}

void ADamageDisplay::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!this->playerCameraReferance)
	{
		return;
	}

	FVector cameraWorldLocation = this->playerCameraReferance->GetComponentLocation();
	FRotator damageRotator = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), cameraWorldLocation);
	this->SetActorRotation(damageRotator);
}

ADamageDisplay::ADamageDisplay()
{
	this->PrimaryActorTick.bCanEverTick = true;

	this->DamageAmount = 0;

	this->InitialLifeSpan = 2.5f;

	this->TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("DamageDisplay"));
	this->TextRenderComponent->SetupAttachment(this->RootComponent);
	this->TextRenderComponent->SetWorldScale3D(FVector(1.5f, 1.5f, 1.5f));
	this->TextRenderComponent->SetText(FText::AsNumber(std::trunc(this->DamageAmount)));

	this->ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	this->ProjectileMovementComponent->UpdatedComponent = this->RootComponent;
	this->ProjectileMovementComponent->InitialSpeed = 500.f;
	this->ProjectileMovementComponent->Velocity = FVector(0.5f, 0.5f, 1.f);
}
