#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"

/// <summary>
/// AI행동을 정의하는 enum 클래스
/// </summary>
UENUM(BlueprintType, Category = "Enums")
enum class EMonsterBehavior : uint8
{
	NOTHING = 0 UMETA(DisplayName = "Nothing"),
	PATROL UMETA(DisplayName = "Patrol"),
	CHASE UMETA(DisplayName = "Chase"),
	ATTACK UMETA(DisplayName = "Attack"),
	GOTHIT UMETA(DisplayName = "Gothit")
};