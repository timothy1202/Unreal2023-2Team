// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_SetTarget.generated.h"

/**
 * 음영준 - 공격할 타겟을 지정해주는 BT서비스
 */
UCLASS()
class TEAMUNREAL2023_2_API UBTService_SetTarget : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_SetTarget();
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
