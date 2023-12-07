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
		// ������ - ���� BT���� ������ speed�� ���� �Ѿ�� �ּ�, �ִ� ���ǵ�� ���� -> �ּ�: 0, �ִ�: 400
		speed = FMath::Clamp(speed, 0.0f, 400.0f);

		// ������ - AI�� MaxWalkSpeed�� BT���� ������ speed�� ����
		controlledPawn->GetCharacterMovement()->MaxWalkSpeed = speed;
	}
}