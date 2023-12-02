// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MonsterBehavior.h"
#include "BTTask_MonsterBase.generated.h"

/**
 * 
 */
UCLASS()
class TEAMUNREAL2023_2_API UBTTask_MonsterBase : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior", meta = (AllowPrivateAccess = "true"))
	EMonsterBehavior newBehavior;

protected:
	bool SetMonsterBehavior(UBehaviorTreeComponent& OwnerComp);

};
