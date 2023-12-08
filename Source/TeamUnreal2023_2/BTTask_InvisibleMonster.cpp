// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_InvisibleMonster.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "MonsterBehavior.h"
#include "Kismet/GameplayStatics.h"
#include "NPC.h"

UBTTask_InvisibleMonster::UBTTask_InvisibleMonster(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Go Invisible");
}

EBTNodeResult::Type UBTTask_InvisibleMonster::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Succeeded;
}
