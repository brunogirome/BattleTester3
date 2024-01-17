// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpawnnableCharacter.h"
#include "CombatCharacter.generated.h"

class USpringArmComponent;

class UPaperFlipbookComponent;

enum ECombatStatus : uint8;

USTRUCT(BlueprintType)
struct FFakeStatus
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Hp = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Mana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int PhysicalDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int PhysicalDefense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MagicDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MagicDefense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Evasion;

	FFakeStatus(){};

	bool IsValid() const
	{
		return Hp != 0;
	}
};

/**
 *
 */
UCLASS(BlueprintType)
class BATTLETESTERIII_API ACombatCharacter : public ASpawnnableCharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	int32 Hp;

	UPROPERTY(BlueprintReadOnly)
	int32 CurrentHp;

	UPROPERTY(BlueprintReadOnly)
	int32 Speed;

	UPROPERTY(BlueprintReadOnly)
	TMap<TEnumAsByte<ECombatStatus>, int32> CombatStatus;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FFakeStatus FakeStatus = FFakeStatus();

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UPaperFlipbookComponent *DisplayTarget;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsDead();

	UFUNCTION(BlueprintCallable)
	void ReciveDamage(int32 amount);

	UFUNCTION(BlueprintCallable)
	void SetAsTarget(USpringArmComponent *springArm, ACombatCharacter *lastCharacter = nullptr);

	void RemoveCursor();

	void SetAsCameraFocus(USpringArmComponent *springArm);

	virtual void BeginPlay() override;

	ACombatCharacter();
};
