// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpawnnableCharacter.h"

#include "Structs/BattleSpot.h"

#include "CombatCharacter.generated.h"

class USpringArmComponent;
class UPaperFlipbookComponent;
// class UMyGameInstance;
class ABattleAIController;

enum ECombatStatus : uint8;

USTRUCT(BlueprintType)
struct FFakeStatus : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

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

	friend class ABattleAIController;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Battle Control")
	FBattleSpot battleSpot;

public:
	UPROPERTY(EditAnywhere, Category = "Fake Data")
	FName FakeCharacterName;

	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	// FFakeStatus FakeStatus = FFakeStatus();

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Status")
	TMap<TEnumAsByte<ECombatStatus>, int32> CombatStatus;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Status|Getter")
	bool IsDead();

	UFUNCTION(BlueprintCallable, Category = "Status|Setter")
	void ReciveDamage(int32 amount);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Battle Control|Components")
	USpringArmComponent *CameraSpringArm;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Battle Control|Components")
	UPaperFlipbookComponent *DisplayTarget;

	UFUNCTION(BlueprintCallable, Category = "Battle Control|Components")
	void SetBattleSpot(FBattleSpot newBattleSpot);

	UFUNCTION(BlueprintCallable, Category = "Battle Control")
	void SetAsTarget(USpringArmComponent *springArm, ACombatCharacter *lastCharacter = nullptr);

	UFUNCTION(BlueprintCallable, Blueprintpure, Category = "Battle Control")
	ABattleAIController *GetBattleAIController();

	void RemoveCursor();

	void SetAsCameraFocus(USpringArmComponent *springArm);

	virtual void BeginPlay() override;

	ACombatCharacter();
};
