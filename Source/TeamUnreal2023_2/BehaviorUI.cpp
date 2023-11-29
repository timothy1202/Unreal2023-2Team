// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorUI.h"

void UBehaviorUI::SetIconAndText(UTexture2D* icon, FText text)
{
	behaviorIcon = icon;
	behaviorText = text;
}