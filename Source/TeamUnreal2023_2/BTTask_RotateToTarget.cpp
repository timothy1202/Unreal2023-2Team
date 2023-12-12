// Fill out your copyright notice in the Description page of Project Settings.
// ¾ø¾Ö¾ß µÊ

#include "BTTask_RotateToTarget.h"
#include "BTFunction.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NPC.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "AIController.h"

UBTTask_RotateToTarget::UBTTask_RotateToTarget(FObjectInitializer const& ObjectInitializer) : Precision(10.0f)
{
	NodeName = "Rotate To Target";
}

namespace
{
	FORCEINLINE_DEBUGGABLE FVector::FReal CalculateAngleDifferenceDot(const FVector& VectorA, const FVector& VectorB)
	{
		return (VectorA.IsNearlyZero() || VectorB.IsNearlyZero())
			? 1.f
			: VectorA.CosineAngle2D(VectorB);
	}
}

EBTNodeResult::Type UBTTask_RotateToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* const Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		PrecisionDot = FMath::Cos(FMath::DegreesToRadians(Precision));
		OwnerComp.GetAIOwner()->StopMovement();

		const ANPC* controlledPawn = BTFunction::GetControlledNPC(OwnerComp);
		const FVector controlledPawnDirection = controlledPawn->GetActorForwardVector();
		const FVector desiredDirectionPoint = Player->GetActorLocation() - controlledPawn->GetActorLocation();

		const float tmp = CalculateAngleDifferenceDot(controlledPawnDirection, desiredDirectionPoint);

		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::SanitizeFloat(tmp));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::SanitizeFloat(PrecisionDot));

		if (tmp >= PrecisionDot)
		{
			startRotation = controlledPawn->GetActorRotation();
			rotateTime = 0.0f;
			//bNotifyTick = true;
			//return EBTNodeResult::InProgress;
		}
		else
		{
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}

void UBTTask_RotateToTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	auto* const Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	const AAIController* AIController = OwnerComp.GetAIOwner();

	const FVector controlledPawnDirection = AIController->GetPawn()->GetActorForwardVector();
	const FVector desiredDirection = Player->GetActorLocation() - AIController->GetPawn()->GetActorLocation();

	FVector desiredLocation = Player->GetActorLocation();
	FVector controlledPawnLocation = AIController->GetPawn()->GetActorLocation();
	FRotator desiredRotation = UKismetMathLibrary::FindLookAtRotation(controlledPawnLocation, desiredLocation);

	if (CalculateAngleDifferenceDot(controlledPawnDirection, desiredDirection) >= PrecisionDot)
	{

		FRotator newRotation = FMath::Lerp(startRotation, desiredRotation, rotateTime);
		AIController->GetPawn()->SetActorRotation(newRotation);
	}
	else
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}