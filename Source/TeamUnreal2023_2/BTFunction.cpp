// Fill out your copyright notice in the Description page of Project Settings.

#include "BTFunction.h"
#include "AIController.h"
#include "NPC.h"

ANPC* BTFunction::GetControlledNPC(UBehaviorTreeComponent& OwnerComp)
{
	if (bool result = OwnerComp.GetAIOwner()->GetPawn()->IsA(ANPC::StaticClass()))
	{
		ANPC* controlledPawn = Cast<ANPC>(OwnerComp.GetAIOwner()->GetPawn());
		return controlledPawn;
	}

	return nullptr;
}

void BTFunction::SetMonsterBehavior(ANPC& npc, EMonsterBehavior newBehavior)
{
	if(npc.GetBehavior() != EMonsterBehavior::GOTHIT)
		npc.SetBehavior(newBehavior);
}

bool BTFunction::GetNPCAndSetBehavior(UBehaviorTreeComponent& OwnerComp, EMonsterBehavior newBehavior)
{
	ANPC* controlledPawn = nullptr;

	if (ANPC* pawn = GetControlledNPC(OwnerComp))
		controlledPawn = pawn;
	else
		return false;

	SetMonsterBehavior(*controlledPawn, newBehavior);
	return true;
}