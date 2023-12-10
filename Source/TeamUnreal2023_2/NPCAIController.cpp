// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCAIController.h"
#include "NPC.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_sight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TeamUnreal2023_2Character.h"


ANPCAIController::ANPCAIController(FObjectInitializer const& ObjectInitializer)
{
	SetupPerceptionSystem(); 
}

void ANPCAIController::BeginPlay()
{
	Super::BeginPlay();

	if (ANPC* pawn = Cast<ANPC>(GetPawn()))
		controlledPawn = pawn;

	// 박광훈 - 소환 가능 유무 설정
	GetBlackboardComponent()->SetValueAsBool("CanSummon", true);
}

/// <summary>
/// 박광훈 - NPC 트리 설정 함수
/// </summary>
/// <param name="InPawn"></param>
void ANPCAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (ANPC* const npc = Cast<ANPC>(InPawn)) //이 폰이 npc 이면
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

/// <summary>
/// 박광훈 - 틱 함수
/// </summary>
/// <param name="DeltaTime"></param>
void ANPCAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	this->SetUIOnBehaviorChange();
}

/// <summary>
/// 박광훈 - NPC 기본 설정 함수
/// </summary>
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
		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ANPCAIController::OnTargetDetected);
		GetPerceptionComponent()->ConfigureSense(*SightConfig);
	}
}

/// <summary>
/// 박광훈 - NPC site 함수
/// </summary>
/// <param name="Actor"></param>
/// <param name="Stimulus"></param>
void ANPCAIController::OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus)
{
	//플레이어가 보이는 지
	if (ATeamUnreal2023_2Character* const ch = Cast<ATeamUnreal2023_2Character>(Actor))
	{
		bool Sensed;
		// 박광훈 - 플레이어가 투명인지에 따른 감지 유무
		if (ch->GetIsInvisible() == true)
		{
			Sensed = false;
		}
		else
		{
			Sensed = Stimulus.WasSuccessfullySensed();
		}
		// 음영준 - 플레이어 감지 성공 여부를 저장

		// 박광훈 -npc가 플레이어 위치를 잃으면 canseeplayer거짓 
		GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", Sensed);

		// 음영준 - 플레이어가 보이는지 안보이는지에 따라 IsFindPlayer의 Bool값 설정
		if (Sensed)
			controlledPawn->SetIsFindPlayer(true);
		else
			controlledPawn->SetIsFindPlayer(false);

	}
}

void ANPCAIController::SetUIOnBehaviorChange()
{
	// 음영준 - 자신이 조종하고있는 AI의 행동을 가져와서 자신의 행동이랑 비교
	if (controlledPawn->GetBehavior() != behavior)
	{
		behavior = controlledPawn->GetBehavior();
		controlledPawn->SetUI(behavior);
	}
}
