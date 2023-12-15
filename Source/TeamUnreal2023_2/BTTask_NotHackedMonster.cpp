// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_NotHackedMonster.h"
#include "TeamUnreal2023_2Character.h"
#include "Kismet/GameplayStatics.h"

UBTTask_NotHackedMonster::UBTTask_NotHackedMonster(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Stop Hacking");
}

EBTNodeResult::Type UBTTask_NotHackedMonster::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ATeamUnreal2023_2Character* PlayerInstance = Cast<ATeamUnreal2023_2Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (PlayerInstance) // PlayerInstance�� null�� �ƴ��� Ȯ���մϴ�.
	{
		UE_LOG(LogTemp, Log, TEXT("Player is not hacked. Execute the task."));
		PlayerInstance->SetPlayerHacked(false); // playerHacked ���¸� true�� �����մϴ�.
	}

	return EBTNodeResult::Succeeded;
}
