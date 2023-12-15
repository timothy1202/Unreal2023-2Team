// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_SummonMonster.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/World.h" //SpawnActor 함수를 사용하기 위한 헤더
#include "GameFramework/Character.h"
#include "NavigationSystem.h"
#include "MonsterBehavior.h"
#include "Kismet/GameplayStatics.h"
#include "NPC.h"
#include "TurretPawn.h"
#include "NPCAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

///<summary>
///노드 이름 정하는 함수 & BP_NPC를 찾는 것
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
        FVector RelativeLocation = FVector(100.0f, 0.0f, 0.0f); // AI 폰으로부터 x축 방향으로 100 유닛 떨어진 위치
        FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);

        // AI 컨트롤러의 폰 위치를 가져옵니다.
        FVector AILocation = AIController->GetPawn()->GetActorLocation();

        // 소환할 위치를 계산합니다.
        FVector SpawnLocation = AILocation + RelativeLocation;

        // 소환 파라미터를 생성합니다.
        FActorSpawnParameters SpawnParams;

        // 폰을 소환합니다.
        if (UWorld* World = AIController->GetWorld()) // AI 컨트롤러를 통해 월드를 얻습니다.
        {
            ATurretPawn* SpawnedPawn = World->SpawnActor<ATurretPawn>(ATurretPawn::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
            if (SpawnedPawn)
            {
                UE_LOG(LogTemp, Warning, TEXT("몬스터 소환 성공"));
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
    //    FVector RelativeLocation = FVector(100.0f, 0.0f, 0.0f); // AI 폰으로부터 x축 방향으로 100 유닛 떨어진 위치
    //    FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);

    //    // AI 컨트롤러의 폰 위치를 가져옵니다.
    //    FVector AILocation = AIController->GetPawn()->GetActorLocation();

    //    // 소환할 위치를 계산합니다.
    //    FVector SpawnLocation = AILocation + RelativeLocation;

    //    // 소환 파라미터를 생성합니다.
    //    FActorSpawnParameters SpawnParams;

    //    // 폰을 소환합니다.
    //    ATurretPawn* SpawnedPawn = GetWorld()->SpawnActor<ATurretPawn>(ATurretPawn::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);

    //    return EBTNodeResult::Succeeded;
    //}

    //return EBTNodeResult::Failed;
}
