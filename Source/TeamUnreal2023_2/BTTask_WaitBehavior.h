// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_Wait.h"
#include "MonsterBehavior.h"
#include "BTTask_WaitBehavior.generated.h"

/**
 * ������ - �÷��̾ ��ġ�� BT���� ������ �ð���ŭ ������ �ְ� �ϴ� Task
 */
UCLASS()
class TEAMUNREAL2023_2_API UBTTask_WaitBehavior : public UBTTask_Wait
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior", meta = (AllowPrivateAccess = "true"))
	EMonsterBehavior newBehavior;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
