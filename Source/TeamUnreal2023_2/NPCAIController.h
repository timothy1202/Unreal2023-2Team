// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "MonsterBehavior.h"
#include "NPCAIController.generated.h"

/**
 * 
 */
UCLASS()
class TEAMUNREAL2023_2_API ANPCAIController : public AAIController
{
	GENERATED_BODY()

private:
	// 음영준 - AIController의 행동(Behavior) Enum -> 이 Enum을 통해 AI의 행동을 검사
	EMonsterBehavior behavior;

	// 음영준 - AIController가 조종하는 AI레퍼런스
	class ANPC* controlledPawn;

	class UAISenseConfig_Sight* SightConfig;

	void SetupPerceptionSystem();

	UFUNCTION()
	void OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus);

	// 음영준 - 매 틱마다 AI의 행동(Behavior)을 검사하여 자신의 행동이랑 다를 시 자신의 행동을 바꾸고 행동 UI를 알맞게 바꿔주는 함수
	void SetUIOnBehaviorChange();
	
public:
	explicit ANPCAIController(FObjectInitializer const& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

public:
	virtual void Tick(float DeltaTime) override;
};
