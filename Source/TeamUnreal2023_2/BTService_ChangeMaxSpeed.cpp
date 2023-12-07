// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_ChangeMaxSpeed.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BTFunction.h"
#include "AIController.h"
#include "NPC.h"

UBTService_ChangeMaxSpeed::UBTService_ChangeMaxSpeed() : speed(400.0f)
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Change Max Speed");
}

void UBTService_ChangeMaxSpeed::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	if (ANPC* const controlledPawn = BTFunction::GetControlledNPC(OwnerComp))
	{
		// 음영준 - 만약 BT에서 지정한 speed의 값이 넘어가면 최소, 최대 스피드로 설정 -> 최소: 0, 최대: 400
		speed = FMath::Clamp(speed, 0.0f, 400.0f);

		// 음영준 - AI의 MaxWalkSpeed를 BT에서 지정한 speed로 설정
		controlledPawn->GetCharacterMovement()->MaxWalkSpeed = speed;
	}
}