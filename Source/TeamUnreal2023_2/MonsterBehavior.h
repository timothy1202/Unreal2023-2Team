#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"

UENUM(BlueprintType, Category = "Enums")
enum class EMonsterBehavior : uint8
{
	NOTHING = 0 UMETA(DisplayName = "Nothing"),
	CHASE UMETA(DisplayName = "Chase"),
	ATTACK UMETA(DisplayName = "Attack"),
	GOTHIT UMETA(DisplayName = "Gothit")
};