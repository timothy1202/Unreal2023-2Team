// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTTask_MonsterBase.h"
#include "BTTask_NotHackedMonster.generated.h"

/**
 * 
 */
UCLASS()
class TEAMUNREAL2023_2_API UBTTask_NotHackedMonster : public UBTTask_MonsterBase
{
	GENERATED_BODY()

public:
	explicit UBTTask_NotHackedMonster(FObjectInitializer const& ObjectInitializer); // ¹Ú±¤ÈÆ - °´Ã¼ ÃÊ±âÈ­
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override; //¹Ú±¤ÈÆ - ¸ó½ºÅÍ ¼ÒÈ¯ Å×½ºÅ©
	
};
