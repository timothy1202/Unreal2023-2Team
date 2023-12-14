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
	ATeamUnreal2023_2Character* PlayerInstance = Cast<ATeamUnreal2023_2Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (PlayerInstance) // PlayerInstance�� null�� �ƴ��� Ȯ���մϴ�.
	{
		PlayerInstance->SetPlayerHacked(true); // playerHacked ���¸� true�� �����մϴ�.
	}

	return EBTNodeResult::Succeeded;
}
