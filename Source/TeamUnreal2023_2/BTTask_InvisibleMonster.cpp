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
	NodeName = TEXT("Go Invisible");
}

EBTNodeResult::Type UBTTask_InvisibleMonster::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ApplyInvisibleMaterial(OwnerComp);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

/// <summary>
/// 박광훈 - NPC 투명 머티리얼 입히기
/// </summary>
void UBTTask_InvisibleMonster::ApplyInvisibleMaterial(UBehaviorTreeComponent& OwnerComp)
{
	ANPCAIController* AIController = Cast<ANPCAIController>(OwnerComp.GetAIOwner());
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