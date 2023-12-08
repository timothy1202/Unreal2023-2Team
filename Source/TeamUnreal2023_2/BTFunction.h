// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MonsterBehavior.h"

class UBehaviorTreeComponent;
class ANPC;

/**
 * 음영준 - 비헤이비어 트리의 노드 클래스들에서 자주 쓰는 함수들을 모아놓은 클래스
 */
class TEAMUNREAL2023_2_API BTFunction
{
public:
	// 음영준 - 인자로 전달받은 BT를 실행하고있는 Pawn을 가져옴
	static ANPC* GetControlledNPC(UBehaviorTreeComponent& OwnerComp);

	// 음영준 - 인자로 전달받은 AI에게 새로운 행동 설정
	static void SetMonsterBehavior(ANPC& npc, EMonsterBehavior newBehavior);

	// 음영준 - 인자로 전잘받은 BT의 AI Pawn을 가져와서 새로운 행동으로 설정
	static bool GetNPCAndSetBehavior(UBehaviorTreeComponent& OwnerComp, EMonsterBehavior newBehavior);
};
