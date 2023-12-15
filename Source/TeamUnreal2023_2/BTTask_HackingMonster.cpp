// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_HackingMonster.h"
#include "TeamUnreal2023_2Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "NPC.h"

UBTTask_HackingMonster::UBTTask_HackingMonster(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Go Hacking");
}

EBTNodeResult::Type UBTTask_HackingMonster::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (Super::ExecuteTask(OwnerComp, NodeMemory) == EBTNodeResult::InProgress)
		return EBTNodeResult::InProgress;

	return EBTNodeResult::Succeeded;
}

void UBTTask_HackingMonster::UseSkill(UBehaviorTreeComponent& OwnerComp)
{
	ANPC* npc = Cast<ANPC>(OwnerComp.GetAIOwner()->GetPawn());
	if (OwnerComp.GetBlackboardComponent()->GetValueAsBool("CanSeePlayer"))
	{
		// 음영준 - 델리게이트 할당
		if (npc->Skill.IsBound() == false)
			npc->Skill.BindUFunction(this, FName("SetHacking"));
	}
}

void UBTTask_HackingMonster::CancleSkill(UBehaviorTreeComponent& OwnerComp)
{
	ANPC* npc = Cast<ANPC>(OwnerComp.GetAIOwner()->GetPawn());
	SetHacking(npc, false);
}

void UBTTask_HackingMonster::SetHacking(ANPC* npc, bool isHack)
{
	if (!isHack)
		StopHacking(npc);
	else
		AbleToHack(npc);

}

void UBTTask_HackingMonster::AbleToHack(ANPC* npc)
{
	ATeamUnreal2023_2Character* PlayerInstance = Cast<ATeamUnreal2023_2Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (PlayerInstance) // PlayerInstance가 null이 아닌지 확인합니다.
	{
		npc->SetIsSkillOn(true);
		PlayerInstance->SetPlayerHacked(true); // playerHacked 상태를 skillOn로 변경합니다.
		PlayerInstance->ChangeHackedPlayerToInvisible();
	}
}

void UBTTask_HackingMonster::StopHacking(ANPC* npc)
{
	ATeamUnreal2023_2Character* PlayerInstance = Cast<ATeamUnreal2023_2Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (PlayerInstance) // PlayerInstance가 null이 아닌지 확인합니다.
	{
		npc->SetIsSkillOn(false);
		PlayerInstance->SetPlayerHacked(false); // playerHacked 상태를 skillOn로 변경합니다.
		PlayerInstance->RestoreOriginalMaterial();
	}
}