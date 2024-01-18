// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/BattleInventoryListItem.h"

#include "MyGameMode.h"

#include "BattleManager.h"

#include "Widgets/BattleInventoryList.h"

bool UBattleInventoryListItem::IsInHoverPosition()
{
    if (this->gameMode && this->gameMode->BattleManager)
    {
        return gameMode->BattleManager->InventoryListWidget->SelectedCursorIndex == this->Index;
    }

    return false;
}

void UBattleInventoryListItem::NativeConstruct()
{
    Super::NativeConstruct();

    AMyGameMode *myGameMode = Cast<AMyGameMode>(this->GetWorld()->GetAuthGameMode());

    if (myGameMode && myGameMode->BattleManager)
    {
        this->gameMode = myGameMode;
    }
}
