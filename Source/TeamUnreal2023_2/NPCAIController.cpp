// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCAIController.h"
#include "NPC.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_sight.h"
//#include "TeamUnreal2023_2Character.h"

ANPCAIController::ANPCAIController(FObjectInitializer const& ObjectInitializer)
{
	SetupPerceptionSystem(); 
}

void ANPCAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (ANPC* const npc = Cast< ANPC>(InPawn)) //이 폰이 npc 이면
	{
		if (UBehaviorTree* const tree = npc->GetBehaviorTree()) //폰의 트리를 가져옴
		{
			UBlackboardComponent* b;
			UseBlackboard(tree->BlackboardAsset, b); //블랙보드 에셋을 트리한테 가져와서 존재하면 b에 넣어준다
			Blackboard = b;
			RunBehaviorTree(tree);
		}
	}
}

void ANPCAIController::SetupPerceptionSystem()
{
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	if (SightConfig)
	{
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(
		TEXT("Perception Component")));
		SightConfig->SightRadius = 500.f; // 감지 구역범위
		SightConfig->LoseSightRadius = SightConfig->SightRadius + 25.f; // npc가 플레이거 그만 보기시작하는 범위
		SightConfig->PeripheralVisionAngleDegrees = 90.f; //npc가 정면만 볼수있게
		SightConfig->SetMaxAge(5.f); 
		SightConfig->AutoSuccessRangeFromLastSeenLocation = 520.f; //계속 볼수있게 필요한 최소 거리?
		SightConfig->DetectionByAffiliation.bDetectEnemies = true; // 적 판단
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true; // 아군 판단
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true; // 중립 판단

		GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, ANPCAIController::OnTargetDetected);
		GetPerceptionComponent()->ConfigureSense(*SightConfig);
	}
}

void ANPCAIController::OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus)
{
	//플레이어가 보이는 지
	if (auto* const = cast<ATeamUnreal2023_2Character>(Actor))
	{
		// npc가 플레이어 위치를 잃으면 canseeplayer거짓 
		GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", Stimulus.WasSuccessfullySensed());
	}
}
