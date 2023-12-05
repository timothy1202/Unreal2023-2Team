// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MonsterBehavior.h"

class UBehaviorTreeComponent;
class ANPC;

/**
 * 
 */
class TEAMUNREAL2023_2_API BTFunction
{
public:
	static ANPC* GetControlledNPC(UBehaviorTreeComponent& OwnerComp);
	static void SetMonsterBehavior(ANPC& npc, EMonsterBehavior newBehavior);
	static bool GetNPCAndSetBehavior(UBehaviorTreeComponent& OwnerComp, EMonsterBehavior newBehavior);
};
