// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/SpellSelection.h"

#include "Components/ListView.h"

#include "Widgets/SpellCard.h"

void USpellSelection::MoveSpellCursor(FVector2D input)
{
    if (input.Size() == 0)
    {
        this->spellSlots[0]->IsCardHovered = true;

        return;
    }

    float x = input.X;

    float y = input.Y;

    float newIndex = 0;

    if (x != 0)
    {
        newIndex = this->selectSpellIndex + x;

        if (newIndex < 0)
        {
            newIndex = this->SPELLS_PER_PAGE - 1;
        }
        else if (newIndex >= this->SPELLS_PER_PAGE)
        {
            newIndex = 0;
        }
    }

    if (y != 0)
    {
        newIndex = this->selectSpellIndex + (y * SPELLS_PER_ROW);

        if (newIndex < 0)
        {
            newIndex += this->SPELLS_PER_PAGE;
        }
        else if (newIndex >= this->SPELLS_PER_PAGE)
        {
            newIndex -= this->SPELLS_PER_PAGE;
        }
    }

    this->spellSlots[this->selectSpellIndex]->IsCardHovered = false;

    this->selectSpellIndex = newIndex;

    this->spellSlots[selectSpellIndex]->IsCardHovered = true;
}

void USpellSelection::NativeConstruct()
{
    Super::NativeConstruct();

    this->spellSlots.Empty();

    this->spellSlots.Add(SpellSlot0);

    this->spellSlots.Add(SpellSlot1);

    this->spellSlots.Add(SpellSlot2);

    this->spellSlots.Add(SpellSlot3);

    this->spellSlots.Add(SpellSlot4);

    this->spellSlots.Add(SpellSlot5);

    this->spellSlots.Add(SpellSlot6);

    this->spellSlots.Add(SpellSlot7);
}
