// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_InvisibleMonster.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "MonsterBehavior.h"
#include "Kismet/GameplayStatics.h"
#include "NPC.h"
#include "Components/SkeletalMeshComponent.h"
#include "Materials/MaterialInterface.h"
#include "NPCAIController.h"



UBTTask_InvisibleMonster::UBTTask_InvisibleMonster(FObjectInitializer const& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = TEXT("Set Visibility");
}

EBTNodeResult::Type UBTTask_InvisibleMonster::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetBlackboardComponent()->GetValueAsBool("IsInvisible") == true)
		return EBTNodeResult::Failed;

	// ������ - ���� ��ų�� ����� �� Visible�� 
	OwnerComp.GetBlackboardComponent()->SetValueAsBool("IsInvisible", true);

	AAIController* AIController = OwnerComp.GetAIOwner();
	ApplyInvisibleMaterial(AIController);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

/// <summary>
/// �ڱ��� - NPC ���� ��Ƽ���� ������
/// </summary>
void UBTTask_InvisibleMonster::ApplyInvisibleMaterial(AAIController* controller)
{
	ANPCAIController* AIController = Cast<ANPCAIController>(controller);
	if (AIController)
	{
		USkeletalMeshComponent* MeshComponent = AIController->GetMeshComponent();
		if (MeshComponent)
		{
			UMaterialInterface* NewMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("'/Game/M_Invisible.M_Invisible'"));
			if (NewMaterial)
			{
				MeshComponent->SetMaterial(0, NewMaterial);
				MeshComponent->SetMaterial(1, NewMaterial);
			}
		}
	}
}