// Copyright Epic Games, Inc. All Rights Reserved.

#include "TeamUnreal2023_2GameMode.h"
#include "TeamUnreal2023_2Character.h"
#include "UObject/ConstructorHelpers.h"

ATeamUnreal2023_2GameMode::ATeamUnreal2023_2GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
