// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillLogic.h"

// Add default functionality here for any IISkillLogic functions that are not pure virtual.

void ISkillLogic::CancleSkillOnFailPerception(UBehaviorTreeComponent& OwnerComp)
{
    // ������ - ���� �Լ��� ȣ���ϱ� ���� �ν��Ͻ� ����
    TScriptInterface<ISkillLogic> SkillLogicInstance;

    // ������ - ���� �Լ� ȣ��
    SkillLogicInstance->CancleSkill(OwnerComp);
}