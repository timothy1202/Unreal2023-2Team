// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MonsterBase.h"
#include "AIController.h"
#include "NPC.h"

bool UBTTask_MonsterBase::SetMonsterBehavior(UBehaviorTreeComponent& OwnerComp)
{
	if (bool result = OwnerComp.GetAIOwner()->GetPawn()->IsA(ANPC::StaticClass()))
	{
		ANPC* controlledPawn = Cast<ANPC>(OwnerComp.GetAIOwner()->GetPawn());
		controlledPawn->SetBehavior(newBehavior);
		return true;
	}
	return false;
}