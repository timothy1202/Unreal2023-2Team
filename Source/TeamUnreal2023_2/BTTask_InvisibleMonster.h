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
	explicit UBTTask_InvisibleMonster(FObjectInitializer const& ObjectInitializer); // 박광훈 - 객체 초기화
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override; //박광훈 - 몬스터 소환 테스크

	/* 음영준 - 부모 클래스인 UBTTask_SkillBase로부터 상속받은 가상 함수들*/

	virtual void UseSkill(UBehaviorTreeComponent& OwnerComp) override;
	virtual void CancleSkill(UBehaviorTreeComponent& OwnerComp) override;

	/// <summary>
	/// 음영준 - NPC컨트롤러에 내장되어있는 FSetSkill델리게이트에 바인딩할 함수
	/// </summary>
	/// <param name="NPC컨트롤러"></param>
	/// <param name="AI가 보이는지 안보이는지"></param>
	UFUNCTION()
	void SetInvisibility(ANPC* npc, bool isVisible);

	/// <summary>
	/// 박광훈 - 투명화 머티리얼
	/// </summary>
	void ApplyInvisibleMaterial(USkeletalMeshComponent* mesh);

	/// <summary>
	/// 박공훈 - NPC 원래 머티리얼
	/// </summary>
	void RestoreOriginalMaterial(USkeletalMeshComponent* mesh);
};