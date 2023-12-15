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
    if (okToSummon == false)
    {
        if (ANPCAIController* AIController = Cast<ANPCAIController>(OwnerComp.GetAIOwner()))
        {
            FVector RelativeLocation = FVector(100.0f, 0.0f, 0.0f);
            FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);
            FVector AILocation = AIController->GetPawn()->GetActorLocation();
            FVector SpawnLocation = AILocation + RelativeLocation;
            FActorSpawnParameters SpawnParams;

            if (UWorld* World = AIController->GetWorld())
            {
                UClass* TurretPawnBP = LoadObject<UClass>(NULL, TEXT("/Game/TurretPawn.TurretPawn_C"));

                if (!TurretPawnBP)
                {
                    UE_LOG(LogTemp, Warning, TEXT("Failed to load class: /Game/TurretPawn.TurretPawn_C"));
                    return EBTNodeResult::Failed;
                }

                ATurretPawn* SpawnedPawn = World->SpawnActor<ATurretPawn>(TurretPawnBP, SpawnLocation, SpawnRotation, SpawnParams);
                if (!SpawnedPawn)
                {
                    UE_LOG(LogTemp, Warning, TEXT("Failed to spawn ATurretPawn"));
                    return EBTNodeResult::Failed;
                }
                okToSummon = true;
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
    
}
