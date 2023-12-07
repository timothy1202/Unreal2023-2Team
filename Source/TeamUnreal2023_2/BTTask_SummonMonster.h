// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTTask_MonsterBase.h"
#include "BTTask_SummonMonster.generated.h"

/**
 * ��ȯ�ϴ� ���� ��ȯ �׽�ũ
 */
UCLASS()
class TEAMUNREAL2023_2_API UBTTask_SummonMonster : public UBTTask_MonsterBase
{
	GENERATED_BODY()

public:
	explicit UBTTask_SummonMonster(FObjectInitializer const& ObjectInitializer); //��ü �ʱ�ȭ
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override; //���� ��ȯ �׽�ũ

	// Blueprint ĳ���� Ŭ������ ���� ������ �����մϴ�.
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<class APawn> BP_PawnClass;
	
};
