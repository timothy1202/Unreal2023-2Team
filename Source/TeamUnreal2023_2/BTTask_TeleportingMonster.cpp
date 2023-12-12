// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TeleportingMonster.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "NPCAIController.h"
#include "NavigationSystem.h"

/// <summary>
/// �ڱ��� - ������ġ�� �����̵� �׽�ũ �̸�
/// </summary>
UBTTask_TeleportingMonster::UBTTask_TeleportingMonster()
{
    NodeName = TEXT("Teleport To Random Location");
}

/// <summary>
/// �ڱ��� - ������ġ�� �����̵� �׽�ũ
/// </summary>
/// <param name="OwnerComp"></param>
/// <param name="NodeMemory"></param>
/// <returns></returns>
EBTNodeResult::Type UBTTask_TeleportingMonster::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    auto ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
    if (ControlledPawn == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    UWorld* World = ControlledPawn->GetWorld();
    if (World == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    FNavLocation RandomLocation;
    UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(World);
    if (NavSystem->GetRandomPointInNavigableRadius(ControlledPawn->GetActorLocation(), 500.0f, RandomLocation))
    {
        ControlledPawn->SetActorLocation(RandomLocation.Location);
        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}