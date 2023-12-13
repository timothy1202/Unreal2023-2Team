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
	// ������ - AIController�� �ൿ(Behavior) Enum -> �� Enum�� ���� AI�� �ൿ�� �˻�
	EMonsterBehavior behavior;

	// ������ - AIController�� �����ϴ� AI���۷���
	class ANPC* controlledPawn;

	class UAISenseConfig_Sight* SightConfig;

	class UBehaviorTree* TempBT;

	void SetupPerceptionSystem();

	UFUNCTION()
		void OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus);

	// ������ - �� ƽ���� AI�� �ൿ(Behavior)�� �˻��Ͽ� �ڽ��� �ൿ�̶� �ٸ� �� �ڽ��� �ൿ�� �ٲٰ� �ൿ UI�� �˸°� �ٲ��ִ� �Լ�
	void SetUIOnBehaviorChange();

public:
	explicit ANPCAIController(FObjectInitializer const& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

	// ������ - AIController���� �ൿ�� ���� ����(�÷��̾ ���� �� �ൿ�� �ٲٱ� ����)
	void SetNPCBehavior(EMonsterBehavior newBehavior);

public:
	// ������ - ��ų ��� �� MainBT�� ���ƿ��� ���� �Լ�
	void RunMainBT();

	// ������ - ��ų�� ����ϱ� ���� ����Ʈ�� ����
	void RunSkillBT();

	virtual void Tick(float DeltaTime) override;
	void MakeIsInvisibleFalse(bool what);


	/// <summary>
	/// �ڱ��� - �޽� ������Ʈ ��ȯ
	/// </summary>
	USkeletalMeshComponent* GetMeshComponent() const;
};