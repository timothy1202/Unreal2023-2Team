// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MonsterBehavior.h"
#include "BTTask_MonsterBase.generated.h"

/**
 * ������ - �ൿ�� ���Խ�ų BTTask����� Base
 */
UCLASS()
class TEAMUNREAL2023_2_API UBTTask_MonsterBase : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
private:
	// ������ - ���� �Ҵ��� �ൿ -> BT������ �� ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior", meta = (AllowPrivateAccess = "true"))
	EMonsterBehavior newBehavior;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	// Getter�Լ�
	FORCEINLINE EMonsterBehavior GetNewBehavior() { return newBehavior; }

};
