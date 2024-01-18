// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "BattleInventoryList.generated.h"

class UBattleInventoryListItem;

/**
 *
 */
UCLASS()
class BATTLETESTERIII_API UBattleInventoryList : public UUserWidget
{
	GENERATED_BODY()

	TArray<FString> FakeInventory;

	void setupPage();

	TArray<UBattleInventoryListItem *> ItemSlotsRefs;

	const int32 ITEMS_PER_SCREEN = 5;

	int32 currentPage = 0;

protected:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UBattleInventoryListItem *ItemSlot0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UBattleInventoryListItem *ItemSlot1;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UBattleInventoryListItem *ItemSlot2;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UBattleInventoryListItem *ItemSlot3;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UBattleInventoryListItem *ItemSlot4;

public:
	UPROPERTY(BlueprintReadOnly)
	int32 SelectedCursorIndex = 0;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool HasLastPage();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool HasNextPage();

	UFUNCTION(BlueprintCallable)
	void MoveCursor(FVector2D input = FVector2D(0.f, 0.f));

	virtual void NativeConstruct() override;
};
