// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_SummonMonster.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/World.h" //SpawnActor 함수를 사용하기 위한 헤더
#include "GameFramework/Character.h"
#include "NavigationSystem.h"
#include "MonsterBehavior.h"
#include "Kismet/GameplayStatics.h"
#include "NPC.h"

///<summary>
///노드 이름 정하는 함수 & BP_NPC를 찾는 것
///<summary>
///param name="ObjectInitializer"></param>
UBTTask_SummonMonster::UBTTask_SummonMonster(FObjectInitializer const& ObjectInitializer)
{
	NodeName =TEXT("Spawn Child Monster");
}

EBTNodeResult::Type UBTTask_SummonMonster::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Succeeded;
}
