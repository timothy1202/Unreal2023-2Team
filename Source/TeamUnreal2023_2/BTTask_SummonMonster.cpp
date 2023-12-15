// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_SummonMonster.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/World.h" //SpawnActor �Լ��� ����ϱ� ���� ���
#include "GameFramework/Character.h"
#include "NavigationSystem.h"
#include "MonsterBehavior.h"
#include "Kismet/GameplayStatics.h"
#include "NPC.h"
#include "TurretPawn.h"

///<summary>
///��� �̸� ���ϴ� �Լ� & BP_NPC�� ã�� ��
///<summary>
///param name="ObjectInitializer"></param>
UBTTask_SummonMonster::UBTTask_SummonMonster(FObjectInitializer const& ObjectInitializer)
{
	NodeName =TEXT("Spawn Child Monster");
}

EBTNodeResult::Type UBTTask_SummonMonster::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Succeeded;
}

void UBTTask_SummonMonster::SetSummoning(ANPC* npc, bool isHack)
{

}

void UBTTask_SummonMonster::AbletoSummon()
{

//// ����� ��ġ�� �����մϴ�.
//	FVector RelativeLocation = FVector(100.0f, 0.0f, 0.0f); // ���� ���ͷκ��� x�� �������� 100 ���� ������ ��ġ
//	FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);
//
//	// ��ȯ�� ��ġ�� ����մϴ�.
//	FVector SpawnLocation = GetActorLocation() + RelativeLocation;
//
//	// ��ȯ �Ķ���͸� �����մϴ�.
//	FActorSpawnParameters SpawnParams;
//
//	// ���� ��ȯ�մϴ�.
//	AMyPawn* SpawnedPawn = GetWorld()->SpawnActor<AMyPawn>(AMyPawn::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);

}
