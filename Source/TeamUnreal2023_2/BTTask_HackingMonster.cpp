// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_HackingMonster.h"
#include "TeamUnreal2023_2Character.h"
#include "Kismet/GameplayStatics.h"

UBTTask_HackingMonster::UBTTask_HackingMonster(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Go Hacking");
}

EBTNodeResult::Type UBTTask_HackingMonster::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	return EBTNodeResult::Succeeded;
}

void UBTTask_HackingMonster::SetHacking(ANPC* npc, bool isSkillOnGoing)
{
	if (!isSkillOnGoing)
	{
		StopHacking();
	}
	else
	{
		AbletoHack();
	}
}



void UBTTask_HackingMonster::AbletoHack()
{
	ATeamUnreal2023_2Character* PlayerInstance = Cast<ATeamUnreal2023_2Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (PlayerInstance) // PlayerInstance가 null이 아닌지 확인합니다.
	{
		UE_LOG(LogTemp, Log, TEXT("Player is hacked. Execute the task."));
		PlayerInstance->SetPlayerHacked(true); // playerHacked 상태를 true로 변경합니다.
	}

}

void UBTTask_HackingMonster::StopHacking()
{
	ATeamUnreal2023_2Character* PlayerInstance = Cast<ATeamUnreal2023_2Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (PlayerInstance) // PlayerInstance가 null이 아닌지 확인합니다.
	{
		UE_LOG(LogTemp, Log, TEXT("Player is not hacked. Execute the task."));
		PlayerInstance->SetPlayerHacked(false); // playerHacked 상태를 true로 변경합니다.
	}
}
