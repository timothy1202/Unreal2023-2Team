#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"

/// <summary>
/// AI스킬 타입을 정의하는 Enum클래스
/// </summary>
UENUM(BlueprintType, Category = "Enums")
enum class ESkillType : uint8
{
	RANDOM = 0 UMETA(DisplayName = "Random"),
	COOLTIME UMETA(DisplayName = "CoolTime"),
	CHARGING UMETA(DisplayName = "Charging")
};