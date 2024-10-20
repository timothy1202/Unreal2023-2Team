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
	
	bool SensedPlayer = false;

	// ������ - AIController�� �����ϴ� AI���۷���
	class ANPC* controlledPawn;

	class UAISenseConfig_Sight* SightConfig;

	class UBehaviorTree* TempBT;

	void SetupPerceptionSystem();

	UFUNCTION()
	void OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus);

	// ������ - AIController���� �ൿ�� ���� ����(�÷��̾ ���� �� �ൿ�� �ٲٱ� ����)
	void SetNPCBehavior(EMonsterBehavior newBehavior);

	// ������ - �� ƽ���� AI�� �ൿ(Behavior)�� �˻��Ͽ� �ڽ��� �ൿ�̶� �ٸ� �� �ڽ��� �ൿ�� �ٲٰ� �ൿ UI�� �˸°� �ٲ��ִ� �Լ�
	void SetUIOnBehaviorChange();

	// ������ - AI��ų ��Ұ� �̷������ �Լ�
	void CancleNPCSkill();

public:
	explicit ANPCAIController(FObjectInitializer const& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

public:
	// ������ - ��ų ��� �� MainBT�� ���ƿ��� ���� �Լ�
	void RunMainBT();

	// ������ - ��ų�� ����ϱ� ���� ����Ʈ�� ����
	void RunSkillBT();

	virtual void Tick(float DeltaTime) override;
	void MakeIsInvisible(bool isInvisible);


	/// <summary>
	/// �ڱ��� - �޽� ������Ʈ ��ȯ
	/// </summary>
	USkeletalMeshComponent* GetMeshComponent() const;
};