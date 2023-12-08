// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTTask_MonsterBase.h"
#include "BTTask_InvisibleMonster.generated.h"

/**
 * 
 */
UCLASS()
class TEAMUNREAL2023_2_API UBTTask_InvisibleMonster : public UBTTask_MonsterBase
{
	GENERATED_BODY()
	
public:
	explicit UBTTask_InvisibleMonster(FObjectInitializer const& ObjectInitializer); //객체 초기화
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override; //몬스터 소환 테스크
};
