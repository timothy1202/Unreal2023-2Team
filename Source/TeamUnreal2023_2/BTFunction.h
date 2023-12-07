// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MonsterBehavior.h"

class UBehaviorTreeComponent;
class ANPC;

/**
 * ������ - �����̺�� Ʈ���� ��� Ŭ�����鿡�� ���� ���� �Լ����� ��Ƴ��� Ŭ����
 */
class TEAMUNREAL2023_2_API BTFunction
{
public:
	// ������ - ���ڷ� ���޹��� BT�� �����ϰ��ִ� Pawn�� ������
	static ANPC* GetControlledNPC(UBehaviorTreeComponent& OwnerComp);

	// ������ - ���ڷ� ���޹��� AI���� ���ο� �ൿ ����
	static void SetMonsterBehavior(ANPC& npc, EMonsterBehavior newBehavior);

	// ������ - ���ڷ� ���߹��� BT�� AI Pawn�� �����ͼ� ���ο� �ൿ���� ����
	static bool GetNPCAndSetBehavior(UBehaviorTreeComponent& OwnerComp, EMonsterBehavior newBehavior);
};
