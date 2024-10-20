// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_SummonMonster.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "NavigationSystem.h"
#include "MonsterBehavior.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "NPCAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

///<summary>
///노드 이름 정하는 함수 & BP_NPC를 찾는 것
///<summary>
///param name="ObjectInitializer"></param>
UBTTask_SummonMonster::UBTTask_SummonMonster(FObjectInitializer const& ObjectInitializer)
{
	NodeName =TEXT("Spawn Monster");
}

EBTNodeResult::Type UBTTask_SummonMonster::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// 음영준 - 스킬 사용은 부모 클래스에서
	if (Super::ExecuteTask(OwnerComp, NodeMemory) == EBTNodeResult::InProgress)
		return EBTNodeResult::InProgress;

	return EBTNodeResult::Succeeded;
}

void UBTTask_SummonMonster::UseSkill(UBehaviorTreeComponent& OwnerComp)
{
	ANPC* npc = Cast<ANPC>(OwnerComp.GetAIOwner()->GetPawn());
	if (OwnerComp.GetBlackboardComponent()->GetValueAsBool("InSkillRange"))
	{
		// 음영준 - 델리게이트 할당
		if (npc->Skill.IsBound() == false)
		{
			OwnerComp.GetAIOwner()->StopMovement();
			OwnerComp.GetAIOwner()->SetFocus(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			npc->SetBehavior(EMonsterBehavior::SKILL);
			npc->PlayMontageOnBehavior(EMonsterBehavior::SKILL);
			npc->Skill.BindUFunction(this, FName("Summon"));
		}
	}
}

void UBTTask_SummonMonster::CancleSkill(UBehaviorTreeComponent& OwnerComp)
{
	if (ANPC* npc = Cast<ANPC>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		OwnerComp.GetAIOwner()->ClearFocus(EAIFocusPriority::Gameplay);
		npc->StopAnimMontage();
	}
}

void UBTTask_SummonMonster::Summon(ANPC* npc, bool isRight)
{
	FRotator SpawnRotation = npc->GetActorRotation();
	FVector AILocation = npc->GetActorLocation();
	float Offset = 200.0f;
	Offset = isRight ? Offset : -Offset;
	FVector SpawnLocation = AILocation + (npc->GetActorRightVector() * Offset);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	ATurretPawn* SpawnedPawn = GetWorld()->SpawnActor<ATurretPawn>(turret_BP, SpawnLocation, SpawnRotation, SpawnParams);
}