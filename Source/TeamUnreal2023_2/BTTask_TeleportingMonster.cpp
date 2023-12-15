// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TeleportingMonster.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/Character.h"
#include "NPCAIController.h"
#include "NavigationSystem.h"
#include "NPC.h"

/// <summary>
/// 박광훈 - 랜덤위치로 순간이동 테스크 이름
/// </summary>
UBTTask_TeleportingMonster::UBTTask_TeleportingMonster()
{
    NodeName = TEXT("Teleport To Random Location");
}

/// <summary>
/// 박광훈 - 랜덤위치로 순간이동 테스크
/// </summary>
/// <param name="OwnerComp"></param>
/// <param name="NodeMemory"></param>
/// <returns></returns>
EBTNodeResult::Type UBTTask_TeleportingMonster::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    // 음영준 - 스킬 사용은 부모 클래스에서
    if (Super::ExecuteTask(OwnerComp, NodeMemory) == EBTNodeResult::InProgress)
        return EBTNodeResult::InProgress;

    return EBTNodeResult::Succeeded;
}

void UBTTask_TeleportingMonster::UseSkill(UBehaviorTreeComponent& OwnerComp)
{
    ANPC* npc = Cast<ANPC>(OwnerComp.GetAIOwner()->GetPawn());
    if (OwnerComp.GetBlackboardComponent()->GetValueAsBool("InSkillRange"))
    {
        // 음영준 - 델리게이트 할당
        if (npc->Skill.IsBound() == false)
        {
            OwnerComp.GetAIOwner()->StopMovement();
            npc->Skill.BindUFunction(this, FName("TeleportSkill"));
        }
    }
}

void UBTTask_TeleportingMonster::CancleSkill(UBehaviorTreeComponent& OwnerComp)
{
    // 음영준 - 취소할 수 있는 스킬이 아니어서 동작 없음
}

void UBTTask_TeleportingMonster::TeleportSkill(ANPC* npc, bool isTeleport)
{
    if (!isTeleport)
    {
        float rand = FMath::RandRange(0.f, 100.f);

        if (rand <= triggerPercentage)
        {
            npc->SetBehavior(EMonsterBehavior::SKILL);
            npc->PlayMontageOnBehavior(EMonsterBehavior::SKILL);
        }

        return;
    }

    UBehaviorTreeComponent* OwnerComp = Cast<UBehaviorTreeComponent>(UAIBlueprintHelperLibrary::GetAIController(npc)->GetBrainComponent());
    OwnerComp->GetBlackboardComponent()->SetValueAsBool("InAttackRange", false);
    
    FNavLocation RandomLocation;
    UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
    if (NavSystem->GetRandomPointInNavigableRadius(npc->GetActorLocation(), 500.0f, RandomLocation))
    {
        npc->SetActorLocation(RandomLocation.Location);
    }
}