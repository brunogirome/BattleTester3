// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/BattleInventoryList.h"

#include "Widgets/BattleInventoryListItem.h"

bool UBattleInventoryList::HasLastPage()
{
    return currentPage > 0;
}

bool UBattleInventoryList::HasNextPage()
{
    int32 inventorySize = this->FakeInventory.Num();

    int32 totalOfPages = FMath::CeilToInt(static_cast<float>(inventorySize) / static_cast<float>(this->ITEMS_PER_SCREEN));

    return currentPage < (totalOfPages - 1);
}

void UBattleInventoryList::MoveCursor(FVector2D input)
{
    if (this->FakeInventory.Num() == 0)
    {

        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Is empty");

        return;
    }

    bool isSwitchingPage = false;

    if (input.X < 0 && this->HasLastPage())
    {
        currentPage--;

        isSwitchingPage = true;
    }

    if (input.X > 0 && this->HasNextPage())
    {
        currentPage++;

        isSwitchingPage = true;
    }

    if (isSwitchingPage || input.Size() == 0)
    {
        setupPage();

        return;
    }

    int32 newIndex = this->SelectedCursorIndex - input.Y;

    int32 maxIndex = -1;

    for (UBattleInventoryListItem *item : this->ItemSlotsRefs)
    {
        if (item->HaveContent)
        {
            maxIndex++;
        }
    }

    if (newIndex < 0)
    {
        newIndex = maxIndex;
    }

    if (newIndex > maxIndex)
    {
        newIndex = 0;
    }

    this->SelectedCursorIndex = newIndex;
}

void UBattleInventoryList::setupPage()
{
    int32 start = this->currentPage * ITEMS_PER_SCREEN;

    int32 end = FMath::Min(start + ITEMS_PER_SCREEN, this->FakeInventory.Num());

    for (UBattleInventoryListItem *itemSlot : this->ItemSlotsRefs)
    {
        if (itemSlot)
        {
            itemSlot->HaveContent = false;
        }
    }

    int32 itemSlotIndex = 0;

    for (int32 i = start; i < end && itemSlotIndex < this->ItemSlotsRefs.Num(); ++i)
    {
        if (this->ItemSlotsRefs[itemSlotIndex])
        {
            this->ItemSlotsRefs[itemSlotIndex]->HaveContent = true;

            this->ItemSlotsRefs[itemSlotIndex]->ItemName = this->FakeInventory[i];
        }

        itemSlotIndex++;
    }

    if (this->SelectedCursorIndex >= itemSlotIndex)
    {
        this->SelectedCursorIndex = (itemSlotIndex - 1);
    }
}

void UBattleInventoryList::NativeConstruct()
{
    Super::NativeConstruct();

    this->ItemSlotsRefs.Empty();

    this->ItemSlotsRefs.Add(this->ItemSlot0);

    this->ItemSlotsRefs.Add(this->ItemSlot1);

    this->ItemSlotsRefs.Add(this->ItemSlot2);

    this->ItemSlotsRefs.Add(this->ItemSlot3);

    this->ItemSlotsRefs.Add(this->ItemSlot4);

    this->FakeInventory.Empty();

    this->FakeInventory.Add("Item 0");
    this->FakeInventory.Add("Item 1");
    this->FakeInventory.Add("Item 2");
    this->FakeInventory.Add("Item 3");
    this->FakeInventory.Add("Item 4");
    this->FakeInventory.Add("Item 5");
    this->FakeInventory.Add("Item 6");
    this->FakeInventory.Add("Item 7");
    this->FakeInventory.Add("Item 8");
    this->FakeInventory.Add("Item 9");
    this->FakeInventory.Add("Item 10");
    this->FakeInventory.Add("Item 11");
    this->FakeInventory.Add("Item 12");
}