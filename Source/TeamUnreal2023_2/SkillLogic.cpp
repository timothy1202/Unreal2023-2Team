// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillLogic.h"

// Add default functionality here for any IISkillLogic functions that are not pure virtual.

void ISkillLogic::CancleSkillOnFailPerception(UBehaviorTreeComponent& OwnerComp)
{
    // 음영준 - 가상 함수를 호출하기 위해 인스턴스 생성
    TScriptInterface<ISkillLogic> SkillLogicInstance;

    // 음영준 - 가상 함수 호출
    SkillLogicInstance->CancleSkill(OwnerComp);
}