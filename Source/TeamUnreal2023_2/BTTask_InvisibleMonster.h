// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTTask_MonsterBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Materials/MaterialInterface.h"
#include "BTTask_SkillBase.h"
#include "BTTask_InvisibleMonster.generated.h"

/**
 *
 */
UCLASS()
class TEAMUNREAL2023_2_API UBTTask_InvisibleMonster : public UBTTask_SkillBase
{
	GENERATED_BODY()

public:
	explicit UBTTask_InvisibleMonster(FObjectInitializer const& ObjectInitializer); // �ڱ��� - ��ü �ʱ�ȭ
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override; //�ڱ��� - ���� ��ȯ �׽�ũ

	/* ������ - �θ� Ŭ������ UBTTask_SkillBase�κ��� ��ӹ��� ���� �Լ���*/

	virtual void UseSkill(UBehaviorTreeComponent& OwnerComp) override;
	virtual void CancleSkill(UBehaviorTreeComponent& OwnerComp) override;

	/// <summary>
	/// ������ - NPC��Ʈ�ѷ��� ����Ǿ��ִ� FSetSkill��������Ʈ�� ���ε��� �Լ�
	/// </summary>
	/// <param name="NPC��Ʈ�ѷ�"></param>
	/// <param name="AI�� ���̴��� �Ⱥ��̴���"></param>
	UFUNCTION()
	void SetInvisibility(ANPC* npc, bool isVisible);

	/// <summary>
	/// �ڱ��� - ����ȭ ��Ƽ����
	/// </summary>
	void ApplyInvisibleMaterial(USkeletalMeshComponent* mesh);

	/// <summary>
	/// �ڰ��� - NPC ���� ��Ƽ����
	/// </summary>
	void RestoreOriginalMaterial(USkeletalMeshComponent* mesh);
};