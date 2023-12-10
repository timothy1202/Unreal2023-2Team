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

	// �ڱ��� - ��ȯ ���� ���� ����
	GetBlackboardComponent()->SetValueAsBool("CanSummon", true);
}

/// <summary>
/// �ڱ��� - NPC Ʈ�� ���� �Լ�
/// </summary>
/// <param name="InPawn"></param>
void ANPCAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (ANPC* const npc = Cast<ANPC>(InPawn)) //�� ���� npc �̸�
	{
		if (UBehaviorTree* const tree = npc->GetBehaviorTree()) //���� Ʈ���� ������
		{
			UBlackboardComponent* b;
			UseBlackboard(tree->BlackboardAsset, b); //������ ������ Ʈ������ �����ͼ� �����ϸ� b�� �־��ش�
			Blackboard = b;
			RunBehaviorTree(tree);
		}
	}
}

/// <summary>
/// �ڱ��� - ƽ �Լ�
/// </summary>
/// <param name="DeltaTime"></param>
void ANPCAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	this->SetUIOnBehaviorChange();
}

/// <summary>
/// �ڱ��� - NPC �⺻ ���� �Լ�
/// </summary>
void ANPCAIController::SetupPerceptionSystem()
{
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	if (SightConfig)
	{
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(
		TEXT("Perception Component")));
		SightConfig->SightRadius = 500.f; // ���� ��������
		SightConfig->LoseSightRadius = SightConfig->SightRadius + 25.f; // npc�� �÷��̰� �׸� ��������ϴ� ����
		SightConfig->PeripheralVisionAngleDegrees = 90.f; //npc�� ���鸸 �����ְ�
		SightConfig->SetMaxAge(5.f); 
		SightConfig->AutoSuccessRangeFromLastSeenLocation = 520.f; //��� �����ְ� �ʿ��� �ּ� �Ÿ�?
		SightConfig->DetectionByAffiliation.bDetectEnemies = true; // �� �Ǵ�
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true; // �Ʊ� �Ǵ�
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true; // �߸� �Ǵ�

		GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ANPCAIController::OnTargetDetected);
		GetPerceptionComponent()->ConfigureSense(*SightConfig);
	}
}

/// <summary>
/// �ڱ��� - NPC site �Լ�
/// </summary>
/// <param name="Actor"></param>
/// <param name="Stimulus"></param>
void ANPCAIController::OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus)
{
	//�÷��̾ ���̴� ��
	if (ATeamUnreal2023_2Character* const ch = Cast<ATeamUnreal2023_2Character>(Actor))
	{
		bool Sensed;
		// �ڱ��� - �÷��̾ ���������� ���� ���� ����
		if (ch->GetIsInvisible() == true)
		{
			Sensed = false;
		}
		else
		{
			Sensed = Stimulus.WasSuccessfullySensed();
		}
		// ������ - �÷��̾� ���� ���� ���θ� ����

		// �ڱ��� -npc�� �÷��̾� ��ġ�� ������ canseeplayer���� 
		GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", Sensed);

		// ������ - �÷��̾ ���̴��� �Ⱥ��̴����� ���� IsFindPlayer�� Bool�� ����
		if (Sensed)
			controlledPawn->SetIsFindPlayer(true);
		else
			controlledPawn->SetIsFindPlayer(false);

	}
}

void ANPCAIController::SetUIOnBehaviorChange()
{
	// ������ - �ڽ��� �����ϰ��ִ� AI�� �ൿ�� �����ͼ� �ڽ��� �ൿ�̶� ��
	if (controlledPawn->GetBehavior() != behavior)
	{
		behavior = controlledPawn->GetBehavior();
		controlledPawn->SetUI(behavior);
	}
}
