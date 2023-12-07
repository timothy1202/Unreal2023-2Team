// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindRandomLocation.h"
#include "NPCAIController.h"
#include "BTFunction.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MonsterBehavior.h"
#include "NPC.h"

UBTTask_FindRandomLocation::UBTTask_FindRandomLocation(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Find Random Location In NavMesh";
}

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	//get AI Conroller and its npc
	if (auto* const cont = Cast<ANPCAIController>(OwnerComp.GetAIOwner())) //폰의 컨트롤러를 가져와서 트리를 가져옴
	{
		if (auto* const npc = cont->GetPawn())
		{
			//obatin npc location to use as an origin
			auto const Origin = npc->GetActorLocation();

			//get the navigation system and generate a radom location
			if (auto* const NavSys = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				FNavLocation Loc;
				//랜덤위치를 찾으면 if문 실행
				
				if (NavSys->GetRandomPointInNavigableRadius(Origin, SearchRadius, Loc))
				{
					cont->GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Loc.Location);
				}


				//finish with success
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}

	return EBTNodeResult::Failed;
}
