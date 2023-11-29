// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BehaviorUI.generated.h"

/**
 * 
 */
UCLASS()
class TEAMUNREAL2023_2_API UBehaviorUI : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	UTexture2D* behaviorIcon;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	FText behaviorText;

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetIconAndText(UTexture2D* icon, FText text);
};
