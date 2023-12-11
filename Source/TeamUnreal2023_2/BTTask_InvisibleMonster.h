// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTTask_MonsterBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Materials/MaterialInterface.h"
#include "BTTask_InvisibleMonster.generated.h"

/**
 *
 */
UCLASS()
class TEAMUNREAL2023_2_API UBTTask_InvisibleMonster : public UBTTask_MonsterBase
{
	GENERATED_BODY()

public:
	explicit UBTTask_InvisibleMonster(FObjectInitializer const& ObjectInitializer); // �ڱ��� - ��ü �ʱ�ȭ
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override; //�ڱ��� - ���� ��ȯ �׽�ũ

private:
	/// <summary>
	/// �ڱ��� - ����ȭ ��Ƽ����
	/// </summary>
	void ApplyInvisibleMaterial(UBehaviorTreeComponent& OwnerComp);

};