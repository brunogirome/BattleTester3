// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/CameraPawn.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ACameraPawn::ACameraPawn()
{
	PrimaryActorTick.bCanEverTick = false;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));

	RootComponent = CapsuleComponent;

	this->CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));

	this->CameraSpringArm->SetupAttachment(RootComponent);

	this->CameraSpringArm->TargetArmLength = 700.f;

	this->PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	this->PlayerCamera->SetupAttachment(this->CameraSpringArm, USpringArmComponent::SocketName);
}
