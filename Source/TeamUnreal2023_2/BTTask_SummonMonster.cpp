// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_SummonMonster.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/World.h" //SpawnActor 함수를 사용하기 위한 헤더
#include "GameFramework/Character.h"
#include "NavigationSystem.h"
#include "MonsterBehavior.h"
#include "Kismet/GameplayStatics.h"
#include "NPC.h"

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
    //UBlackboardComponent* BB_NPC; // 블랙보드 컴포넌트 참조
    //FName BoolKeyName = "CanSummon"; // 변경하려는 블랙보드 키의 이름

    //// 블랙보드 컴포넌트가 유효한지 확인합니다.
    //if (BB_NPC)
    //{
    //    // SetValueAsBool 함수를 사용하여 블랙보드 키의 값(이 경우, bool)을 설정합니다.
    //    BB_NPC->SetValueAsBool(BoolKeyName, true);
    //    UE_LOG(LogTemp, Log, TEXT("Log Message"));
    //}

    /*static ConstructorHelpers::FClassFinder<AActor> PawnClass(TEXT("/Game/AI/BP_NPC.BP_NPC"));
    if (PawnClass.Succeeded())
    {
        BP_PawnClass = PawnClass.Class;
        UE_LOG(LogTemp, Log, TEXT("Log Message"));
    }*/
    //Super::ExecuteTask(OwnerComp, NodeMemory);

    //UWorld* World = OwnerComp.GetWorld(); // 현재 월드를 가져옵니다.
    ////World&&
    //if (World && BP_PawnClass) // 월드가 유효한 경우
    //{

    //    FVector Location = FVector(0.0f, 0.0f, 0.0f); // 스폰할 위치를 설정합니다. 이 위치는 월드 좌표입니다.
    //    FRotator Rotation = FRotator(0.0f, 0.0f, 0.0f); // 스폰할 회전을 설정합니다. 
    //    // 액터를 스폰합니다. 여기서 AMyCharacter는 스폰하려는 액터 클래스입니다.
    //    ANPC* SpawnedPawn = World->SpawnActor<ANPC>(BP_PawnClass, Location, Rotation);

    //    // SpawnedPawn에 AController를 할당합니다.
    //    if (SpawnedPawn)
    //    {
    //        AController* NewController = World->SpawnActor<AController>();
    //        if (NewController)
    //        {
    //            NewController->Possess(SpawnedPawn);

    //            // Task가 성공적으로 완료되었습니다.
    //            return EBTNodeResult::Succeeded;
    //        }
    //    }
    //}
    //// Task가 실패하였습니다.
    //return EBTNodeResult::Failed;
    return EBTNodeResult::Failed;
}


