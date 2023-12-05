// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_WaitBehavior.h"
#include "BTFunction.h"
#include "AIController.h"
#include "NPC.h"

EBTNodeResult::Type UBTTask_WaitBehavior::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ANPC* controlledPawn = nullptr;

	if (ANPC* pawn = BTFunction::GetControlledNPC(OwnerComp))
		controlledPawn = pawn;
	else
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

	EMonsterBehavior pawnBehavior = controlledPawn->GetBehavior();
	if (pawnBehavior == EMonsterBehavior::CHASE)
	{
		OwnerComp.GetAIOwner()->StopMovement();
		BTFunction::SetMonsterBehavior(*controlledPawn, newBehavior);
	}
	else if (pawnBehavior == EMonsterBehavior::PATROL)
	{
		return EBTNodeResult::Succeeded;
	}

	const float RemainingWaitTime = FMath::FRandRange(FMath::Max(0.0f, WaitTime - RandomDeviation), (WaitTime + RandomDeviation));
	SetNextTickTime(NodeMemory, RemainingWaitTime);

	return EBTNodeResult::InProgress;
}