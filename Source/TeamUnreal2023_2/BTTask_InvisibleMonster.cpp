// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_InvisibleMonster.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "MonsterBehavior.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"
#include "Materials/MaterialInterface.h"
#include "NPCAIController.h"



UBTTask_InvisibleMonster::UBTTask_InvisibleMonster(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Set Invisible Skill");
}

EBTNodeResult::Type UBTTask_InvisibleMonster::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// 음영준 - 스킬 사용은 부모 클래스에서
	if (Super::ExecuteTask(OwnerComp, NodeMemory) == EBTNodeResult::InProgress)
		return EBTNodeResult::InProgress;

	return EBTNodeResult::Succeeded;
}

void UBTTask_InvisibleMonster::UseSkill(UBehaviorTreeComponent& OwnerComp)
{
	ANPC* npc = Cast<ANPC>(OwnerComp.GetAIOwner()->GetPawn());
	if (OwnerComp.GetBlackboardComponent()->GetValueAsBool("CanSeePlayer"))
	{
		// 음영준 - 델리게이트 할당
		if (npc->Skill.IsBound() == false)
			npc->Skill.BindUFunction(this, FName("SetInvisibility"));
	}
}

void UBTTask_InvisibleMonster::CancleSkill(UBehaviorTreeComponent& OwnerComp)
{
	ANPC* npc = Cast<ANPC>(OwnerComp.GetAIOwner()->GetPawn());
	SetInvisibility(npc, false);
}

void UBTTask_InvisibleMonster::SetInvisibility(ANPC* npc, bool isSkillOnGoing)
{
	// 음영준 - isVisible의 값에 따라 투명화시킬것인지 다시 되돌릴것인지 결정
	USkeletalMeshComponent* MeshComponent = npc->GetMesh();
	if (!isSkillOnGoing)
	{
		RestoreOriginalMaterial(MeshComponent);
	}
	else
	{
		ApplyInvisibleMaterial(MeshComponent);
	}
}

/// <summary>
/// 박광훈 - NPC 투명 머티리얼 입히기
/// </summary>
void UBTTask_InvisibleMonster::ApplyInvisibleMaterial(USkeletalMeshComponent* mesh)
{
	if (mesh)
	{
		UMaterialInterface* NewMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("'/Game/M_Invisible.M_Invisible'"));
		if (NewMaterial)
		{
			mesh->SetMaterial(0, NewMaterial);
			mesh->SetMaterial(1, NewMaterial);
		}
	}
}

void UBTTask_InvisibleMonster::RestoreOriginalMaterial(USkeletalMeshComponent* mesh)
{
	if (mesh)
	{
		UMaterialInterface* OriginalMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("'/Game/Characters/Mannequins/Materials/MI_Manny_01.MI_Manny_01'"));
		if (OriginalMaterial)
		{
			mesh->SetMaterial(0, OriginalMaterial);
		}
		UMaterialInterface* OriginalMaterial1 = LoadObject<UMaterialInterface>(nullptr, TEXT("'/Game/Characters/Mannequins/Materials/MI_Manny_02.MI_Manny_02'"));
		if (OriginalMaterial)
		{
			mesh->SetMaterial(1, OriginalMaterial1);
		}
	}
}