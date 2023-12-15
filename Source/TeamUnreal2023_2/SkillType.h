#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"

/// <summary>
/// AI��ų Ÿ���� �����ϴ� EnumŬ����
/// </summary>
UENUM(BlueprintType, Category = "Enums")
enum class ESkillType : uint8
{
	RANDOM = 0 UMETA(DisplayName = "Random"),
	COOLTIME UMETA(DisplayName = "CoolTime"),
	CHARGING UMETA(DisplayName = "Charging")
};