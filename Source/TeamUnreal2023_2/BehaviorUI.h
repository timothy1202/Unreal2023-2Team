// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BehaviorUI.generated.h"

/**
 * ������ - AI���� �ൿUI�� ���� ����
 */
UCLASS()
class TEAMUNREAL2023_2_API UBehaviorUI : public UUserWidget
{
	GENERATED_BODY()
	
private:
	// ������ - UI ������
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	UTexture2D* behaviorIcon;

	// ������ - UI �ؽ�Ʈ
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	FText behaviorText;

public:
	/// <summary>
	/// ������ - AI�ൿ�� �ٲ� ���� UI�����ܰ� �ؽ�Ʈ�� �ٲ��ִ� �Լ�
	/// </summary>
	/// <param name="�Ҵ��� �� ������ �ؽ���2D"></param>
	/// <param name="�Ҵ��� �� �ؽ�Ʈ"></param>
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetIconAndText(UTexture2D* icon, FText text);
};
