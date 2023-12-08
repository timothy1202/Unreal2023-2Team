// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPlayerLocation.h"
#include "BTFunction.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "MonsterBehavior.h"
#include "NPC.h"


UBTTask_FindPlayerLocation::UBTTask_FindPlayerLocation(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Find Player Location");
}

EBTNodeResult::Type UBTTask_FindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (Super::ExecuteTask(OwnerComp, NodeMemory) == EBTNodeResult::InProgress)
		return EBTNodeResult::InProgress;

	// 음영준 - 만약 Focus된 상태에서 넘어왔다면 AI포커스 해제
	if (OwnerComp.GetAIOwner()->GetFocusActor())
		OwnerComp.GetAIOwner()->ClearFocus(EAIFocusPriority::Gameplay);

	if (BTFunction::GetNPCAndSetBehavior(OwnerComp, GetNewBehavior()) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to set behavior!"));
	}

	//get player character
	if (auto* const Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)) // GameplayStatics으로 플레이어 캐릭터를 가져옴, 월드랑 플레이 명수도 가져옴
	{
		//get player location to use as an origin
		auto const PlayerLocation = Player->GetActorLocation();
		if (SearchRandom)
		{
			FNavLocation Loc;

			//get the navigation system and generate a random location near the player
			if (auto* const NavSys = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				//try to get a random location near the player
				if (NavSys->GetRandomPointInNavigableRadius(PlayerLocation, SearchRadius, Loc))
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Loc.Location);
					FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
					return EBTNodeResult::Succeeded;
				}
			}
		}
		else
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerLocation);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
