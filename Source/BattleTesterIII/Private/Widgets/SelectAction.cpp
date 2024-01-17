// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/SelectAction.h"

#include "Components/Button.h"

void USelectAction::IncrementOrDecrementAction(FVector2D input)
{
  int32 newIndex = this->SelectActionIndex - input.Y;

  if (newIndex < 0)
  {
    newIndex = this->selectActionButtons.Num() - 1;
  }
  else if (newIndex >= this->selectActionButtons.Num())
  {
    newIndex = 0;
  }

  FButtonStyle newStyle = this->selectActionButtons[this->SelectActionIndex]->GetStyle();

  if (input.Y != 0)
  {
    newStyle.Normal = this->normalStyle;

    this->selectActionButtons[this->SelectActionIndex]->SetStyle(newStyle);
  }

  newStyle.Normal = this->hoverStytle;

  this->selectActionButtons[newIndex]->SetStyle(newStyle);

  this->SelectActionIndex = newIndex;
}

void USelectAction::NativeConstruct()
{
  Super::NativeConstruct();

  this->selectActionButtons.Empty();

  this->selectActionButtons.Add(this->Attack);

  this->selectActionButtons.Add(this->Spells);

  this->selectActionButtons.Add(this->Items);

  this->selectActionButtons.Add(this->Defend);
}
