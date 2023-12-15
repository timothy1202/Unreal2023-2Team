// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTTask_MonsterBase.h"
#include "NPC.h"
#include "TurretPawn.h"
#include "BTTask_SkillBase.h"
#include "BTTask_SummonMonster.generated.h"

/**
 * ��ȯ�ϴ� ���� ��ȯ �׽�ũ
 */
UCLASS()
class TEAMUNREAL2023_2_API UBTTask_SummonMonster : public UBTTask_SkillBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster", meta = (AllowPrivateAccess = "ture"))
	TSubclassOf<ATurretPawn> turret_BP;

public:
	explicit UBTTask_SummonMonster(FObjectInitializer const& ObjectInitializer); //��ü �ʱ�ȭ
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override; //���� ��ȯ �׽�ũ

	virtual void UseSkill(UBehaviorTreeComponent& OwnerComp) override;
	virtual void CancleSkill(UBehaviorTreeComponent& OwnerComp) override;

	UFUNCTION()
	void Summon(ANPC* npc, bool isRight);
};
