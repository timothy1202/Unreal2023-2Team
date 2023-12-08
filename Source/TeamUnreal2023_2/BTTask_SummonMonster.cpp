// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_SummonMonster.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/World.h" //SpawnActor �Լ��� ����ϱ� ���� ���
#include "GameFramework/Character.h"
#include "NavigationSystem.h"
#include "MonsterBehavior.h"
#include "Kismet/GameplayStatics.h"
#include "NPC.h"

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
    //UBlackboardComponent* BB_NPC; // ������ ������Ʈ ����
    //FName BoolKeyName = "CanSummon"; // �����Ϸ��� ������ Ű�� �̸�

    //// ������ ������Ʈ�� ��ȿ���� Ȯ���մϴ�.
    //if (BB_NPC)
    //{
    //    // SetValueAsBool �Լ��� ����Ͽ� ������ Ű�� ��(�� ���, bool)�� �����մϴ�.
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

    //UWorld* World = OwnerComp.GetWorld(); // ���� ���带 �����ɴϴ�.
    ////World&&
    //if (World && BP_PawnClass) // ���尡 ��ȿ�� ���
    //{

    //    FVector Location = FVector(0.0f, 0.0f, 0.0f); // ������ ��ġ�� �����մϴ�. �� ��ġ�� ���� ��ǥ�Դϴ�.
    //    FRotator Rotation = FRotator(0.0f, 0.0f, 0.0f); // ������ ȸ���� �����մϴ�. 
    //    // ���͸� �����մϴ�. ���⼭ AMyCharacter�� �����Ϸ��� ���� Ŭ�����Դϴ�.
    //    ANPC* SpawnedPawn = World->SpawnActor<ANPC>(BP_PawnClass, Location, Rotation);

    //    // SpawnedPawn�� AController�� �Ҵ��մϴ�.
    //    if (SpawnedPawn)
    //    {
    //        AController* NewController = World->SpawnActor<AController>();
    //        if (NewController)
    //        {
    //            NewController->Possess(SpawnedPawn);

    //            // Task�� ���������� �Ϸ�Ǿ����ϴ�.
    //            return EBTNodeResult::Succeeded;
    //        }
    //    }
    //}
    //// Task�� �����Ͽ����ϴ�.
    //return EBTNodeResult::Failed;
    return EBTNodeResult::Failed;
}


