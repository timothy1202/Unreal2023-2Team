// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetTarget.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"

UBTTask_SetTarget::UBTTask_SetTarget(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Set Target Location";
}

EBTNodeResult::Type UBTTask_SetTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* const Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		//FVector PlayerLocation = Player->GetActorLocation();

		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, PlayerLocation.ToString());

		OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), Player);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}