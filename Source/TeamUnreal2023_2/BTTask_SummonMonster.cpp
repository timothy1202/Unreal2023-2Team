// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SummonMonster.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "MonsterBehavior.h"
#include "NPC.h"
#include "Engine/World.h" //SpawnActor �Լ��� ����ϱ� ���� ���


/// <summary>
/// ��� �̸� ���ϴ� �Լ� & BP_NPC�� ã�� ��
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

    UWorld* World = OwnerComp.GetWorld(); // ���� ���带 �����ɴϴ�.
    //World&&
    if (World && BP_PawnClass) // ���尡 ��ȿ�� ���
    {

        FVector Location = FVector(0.0f, 0.0f, 0.0f); // ������ ��ġ�� �����մϴ�. �� ��ġ�� ���� ��ǥ�Դϴ�.
        FRotator Rotation = FRotator(0.0f, 0.0f, 0.0f); // ������ ȸ���� �����մϴ�. 

        // ���͸� �����մϴ�. ���⼭ AMyCharacter�� �����Ϸ��� ���� Ŭ�����Դϴ�.
        ANPC* SpawnedPawn = World->SpawnActor<ANPC>(BP_PawnClass, Location, Rotation);

        // SpawnedPawn�� AController�� �Ҵ��մϴ�.
        if (SpawnedPawn)
        {
            AController* NewController = World->SpawnActor<AController>();
            if (NewController)
            {
                NewController->Possess(SpawnedPawn);

                // Task�� ���������� �Ϸ�Ǿ����ϴ�.
                return EBTNodeResult::Succeeded;
            }
        }
    }
    // Task�� �����Ͽ����ϴ�.
    return EBTNodeResult::Failed;
}
