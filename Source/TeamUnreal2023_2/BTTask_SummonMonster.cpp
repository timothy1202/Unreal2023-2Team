// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SummonMonster.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "MonsterBehavior.h"
#include "NPC.h"
#include "Engine/World.h" //SpawnActor 함수를 사용하기 위한 헤더


/// <summary>
/// 노드 이름 정하는 함수 & BP_NPC를 찾는 것
/// </summary>
/// <param name="ObjectInitializer"></param>
UBTTask_SummonMonster::UBTTask_SummonMonster(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Spawn Child Monster";
    /*static ConstructorHelpers::FClassFinder<APawn> PawnClass(TEXT("/Game/AI/BP_NPC.BP_NPC"));
    if (PawnClass.Succeeded())
    {
        BP_PawnClass = PawnClass.Class;
    }*/
}

EBTNodeResult::Type UBTTask_SummonMonster::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    UWorld* World = OwnerComp.GetWorld(); // 현재 월드를 가져옵니다.
    //World&&
    if (World && BP_PawnClass) // 월드가 유효한 경우
    {

        FVector Location = FVector(0.0f, 0.0f, 0.0f); // 스폰할 위치를 설정합니다. 이 위치는 월드 좌표입니다.
        FRotator Rotation = FRotator(0.0f, 0.0f, 0.0f); // 스폰할 회전을 설정합니다. 

        // 액터를 스폰합니다. 여기서 AMyCharacter는 스폰하려는 액터 클래스입니다.
        ANPC* SpawnedPawn = World->SpawnActor<ANPC>(BP_PawnClass, Location, Rotation);

        // SpawnedPawn에 AController를 할당합니다.
        if (SpawnedPawn)
        {
            AController* NewController = World->SpawnActor<AController>();
            if (NewController)
            {
                NewController->Possess(SpawnedPawn);

                // Task가 성공적으로 완료되었습니다.
                return EBTNodeResult::Succeeded;
            }
        }
    }
    // Task가 실패하였습니다.
    return EBTNodeResult::Failed;
}
