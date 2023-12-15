// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTTask_MonsterBase.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SkillBase.h"
#include "BTTask_TeleportingMonster.generated.h"

/**
 * 
 */
UCLASS()
class TEAMUNREAL2023_2_API UBTTask_TeleportingMonster : public UBTTask_SkillBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	float triggerPercentage = 100.f;

public:
	UBTTask_TeleportingMonster();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	/* ������ - �θ� Ŭ������ UBTTask_SkillBase�κ��� ��ӹ��� ���� �Լ���*/

	virtual void UseSkill(UBehaviorTreeComponent& OwnerComp) override;
	virtual void CancleSkill(UBehaviorTreeComponent& OwnerComp) override;

	UFUNCTION()
	void TeleportSkill(ANPC* npc, bool isTeleport);
};
