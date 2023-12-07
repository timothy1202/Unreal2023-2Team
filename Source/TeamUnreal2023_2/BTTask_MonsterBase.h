// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MonsterBehavior.h"
#include "BTTask_MonsterBase.generated.h"

/**
 * 음영준 - 행동을 포함시킬 BTTask노드의 Base
 */
UCLASS()
class TEAMUNREAL2023_2_API UBTTask_MonsterBase : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
private:
	// 음영준 - 새로 할당할 행동 -> BT내에서 이 값을 설정
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior", meta = (AllowPrivateAccess = "true"))
	EMonsterBehavior newBehavior;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	// Getter함수
	FORCEINLINE EMonsterBehavior GetNewBehavior() { return newBehavior; }

};
