// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BehaviorUI.generated.h"

/**
 * 음영준 - AI위에 행동UI를 띄우는 위젯
 */
UCLASS()
class TEAMUNREAL2023_2_API UBehaviorUI : public UUserWidget
{
	GENERATED_BODY()
	
private:
	// 음영준 - UI 아이콘
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	UTexture2D* behaviorIcon;

	// 음영준 - UI 텍스트
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	FText behaviorText;

public:
	/// <summary>
	/// 음영준 - AI행동이 바뀜에 따라 UI아이콘과 텍스트를 바꿔주는 함수
	/// </summary>
	/// <param name="할당할 새 아이콘 텍스쳐2D"></param>
	/// <param name="할당할 새 텍스트"></param>
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetIconAndText(UTexture2D* icon, FText text);
};
