// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCAIController.h"
#include "NPC.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_sight.h"

ANPCAIController::ANPCAIController(FObjectInitializer const& ObjectInitializer)
{
	SetupPerceptionSystem(); 
}

void ANPCAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (ANPC* const npc = Cast< ANPC>(InPawn)) //�� ���� npc �̸�
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
		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, ANPCAIController::OnTargetDetected);
		GetPerceptionComponent()->ConfigureSense(*SightConfig);
	}
}

void ANPCAIController::OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus)
{
	//�÷��̾ ���̴� ��
	if (auto* const = cast<ACppAITutorialCharacter>(Actor))
	{
		// npc�� �÷��̾� ��ġ�� ������ canseeplayer���� 
		GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", Stimulus.WasSuccessfullySensed());
	}
}
