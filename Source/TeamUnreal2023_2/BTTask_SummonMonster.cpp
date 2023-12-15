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
#include "NPCAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

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
    if (ANPCAIController* AIController = Cast<ANPCAIController>(OwnerComp.GetAIOwner()))
    {
        FVector RelativeLocation = FVector(100.0f, 0.0f, 0.0f); // AI �����κ��� x�� �������� 100 ���� ������ ��ġ
        FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);

        // AI ��Ʈ�ѷ��� �� ��ġ�� �����ɴϴ�.
        FVector AILocation = AIController->GetPawn()->GetActorLocation();

        // ��ȯ�� ��ġ�� ����մϴ�.
        FVector SpawnLocation = AILocation + RelativeLocation;

        // ��ȯ �Ķ���͸� �����մϴ�.
        FActorSpawnParameters SpawnParams;

        // ���� ��ȯ�մϴ�.
        if (UWorld* World = AIController->GetWorld()) // AI ��Ʈ�ѷ��� ���� ���带 ����ϴ�.
        {
            ATurretPawn* SpawnedPawn = World->SpawnActor<ATurretPawn>(ATurretPawn::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
            if (SpawnedPawn)
            {
                UE_LOG(LogTemp, Warning, TEXT("���� ��ȯ ����"));
                return EBTNodeResult::Succeeded;
            }
        }
    }

    return EBTNodeResult::Failed;
}



void UBTTask_SummonMonster::SetSummoning(ANPC* npc, bool isHack)
{

}

void UBTTask_SummonMonster::AbletoSummon()
{
    //if (ANPCAIController* AIController = OwnerComp.GetAIOwner())
    //{
    //    FVector RelativeLocation = FVector(100.0f, 0.0f, 0.0f); // AI �����κ��� x�� �������� 100 ���� ������ ��ġ
    //    FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);

    //    // AI ��Ʈ�ѷ��� �� ��ġ�� �����ɴϴ�.
    //    FVector AILocation = AIController->GetPawn()->GetActorLocation();

    //    // ��ȯ�� ��ġ�� ����մϴ�.
    //    FVector SpawnLocation = AILocation + RelativeLocation;

    //    // ��ȯ �Ķ���͸� �����մϴ�.
    //    FActorSpawnParameters SpawnParams;

    //    // ���� ��ȯ�մϴ�.
    //    ATurretPawn* SpawnedPawn = GetWorld()->SpawnActor<ATurretPawn>(ATurretPawn::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);

    //    return EBTNodeResult::Succeeded;
    //}

    //return EBTNodeResult::Failed;
}
