// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "SpellSelection.generated.h"

class USpellCard;
/**
 *
 */
UCLASS()
class BATTLETESTERIII_API USpellSelection : public UUserWidget
{
	GENERATED_BODY()

	TArray<USpellCard *> spellSlots;

	const int32 SPELLS_PER_ROW = 4;

	const int32 SPELLS_PER_PAGE = 8;

	int32 selectSpellIndex = 0;

	int32 currentPage = 0;

protected:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	USpellCard *SpellSlot0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	USpellCard *SpellSlot1;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	USpellCard *SpellSlot2;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	USpellCard *SpellSlot3;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	USpellCard *SpellSlot4;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	USpellCard *SpellSlot5;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	USpellCard *SpellSlot6;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	USpellCard *SpellSlot7;

public:
	UFUNCTION(BlueprintCallable)
	void MoveSpellCursor(FVector2D input = FVector2D(0.f, 0.f));

	virtual void NativeConstruct() override;
};
