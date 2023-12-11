// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_NoneInvisibleMonster.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "MonsterBehavior.h"
#include "Kismet/GameplayStatics.h"
#include "NPC.h"
#include "Components/SkeletalMeshComponent.h"
#include "Materials/MaterialInterface.h"
#include "NPCAIController.h"

UBTTask_NoneInvisibleMonster::UBTTask_NoneInvisibleMonster(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Stop Invisible");
}

EBTNodeResult::Type UBTTask_NoneInvisibleMonster::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	RestoreOriginalMaterial(OwnerComp);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

void UBTTask_NoneInvisibleMonster::RestoreOriginalMaterial(UBehaviorTreeComponent& OwnerComp)
{
	ANPCAIController* AIController = Cast<ANPCAIController>(OwnerComp.GetAIOwner());
	if (AIController)
	{
		USkeletalMeshComponent* MeshComponent = AIController->GetMeshComponent();
		if (MeshComponent)
		{
			UMaterialInterface* OriginalMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("'/Game/Characters/Mannequins/Materials/MI_Manny_01.MI_Manny_01'"));
			if (OriginalMaterial)
			{
				MeshComponent->SetMaterial(0, OriginalMaterial);
			}
			UMaterialInterface* OriginalMaterial1 = LoadObject<UMaterialInterface>(nullptr, TEXT("'/Game/Characters/Mannequins/Materials/MI_Manny_02.MI_Manny_02'"));
			if (OriginalMaterial)
			{
				MeshComponent->SetMaterial(1, OriginalMaterial1);
			}
		}
	}
}