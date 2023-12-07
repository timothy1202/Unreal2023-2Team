// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_ChangeMaxSpeed.generated.h"

/**
 * 
 */
UCLASS()
class TEAMUNREAL2023_2_API UBTService_ChangeMaxSpeed : public UBTService_BlackboardBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	float speed = 400.f;

public:
	UBTService_ChangeMaxSpeed();
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
