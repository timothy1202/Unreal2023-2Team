// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_WaitBehavior.h"
#include "AIController.h"
#include "NPC.h"

EBTNodeResult::Type UBTTask_WaitBehavior::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ANPC* controlledPawn = nullptr;

	if (bool result = OwnerComp.GetAIOwner()->GetPawn()->IsA(ANPC::StaticClass()))
		controlledPawn = Cast<ANPC>(OwnerComp.GetAIOwner()->GetPawn());
	else
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

	EMonsterBehavior pawnBehavior = controlledPawn->GetBehavior();
	if (pawnBehavior == EMonsterBehavior::CHASE)
	{
		UE_LOG(LogTemp, Warning, TEXT("Set"));
		OwnerComp.GetAIOwner()->StopMovement();
		controlledPawn->SetBehavior(newBehavior);
	}
	else if (pawnBehavior == EMonsterBehavior::PATROL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Set"));
		return EBTNodeResult::Succeeded;
	}

	const float RemainingWaitTime = FMath::FRandRange(FMath::Max(0.0f, WaitTime - RandomDeviation), (WaitTime + RandomDeviation));
	SetNextTickTime(NodeMemory, RemainingWaitTime);

	return EBTNodeResult::InProgress;
}