// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_RunMainBT.h"
#include "NPCAIController.h"

UBTTask_RunMainBT::UBTTask_RunMainBT(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Run Main BT";
}

EBTNodeResult::Type UBTTask_RunMainBT::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (ANPCAIController* AIController = Cast<ANPCAIController>(OwnerComp.GetAIOwner()))
	{
		AIController->RunMainBT();
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}