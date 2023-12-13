// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_RunSkillBT.h"
#include "BTFunction.h"
#include "NPCAIController.h"

UBTTask_RunSkillBT::UBTTask_RunSkillBT(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Run Skill BT";
}

EBTNodeResult::Type UBTTask_RunSkillBT::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (ANPCAIController* AIController = Cast<ANPCAIController>(OwnerComp.GetAIOwner()))
	{
		// 음영준 - AI의 상태를 Skill상태로 바꿈
		BTFunction::GetNPCAndSetBehavior(OwnerComp, GetNewBehavior());

		AIController->RunSkillBT();
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}