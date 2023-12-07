// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTTask_MonsterBase.h"
#include "BTTask_SummonMonster.generated.h"

/**
 * 소환하는 몬스터 소환 테스크
 */
UCLASS()
class TEAMUNREAL2023_2_API UBTTask_SummonMonster : public UBTTask_MonsterBase
{
	GENERATED_BODY()

public:
	explicit UBTTask_SummonMonster(FObjectInitializer const& ObjectInitializer); //객체 초기화
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override; //몬스터 소환 테스크

	// Blueprint 캐릭터 클래스에 대한 참조를 생성합니다.
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<class APawn> BP_PawnClass;
	
};
