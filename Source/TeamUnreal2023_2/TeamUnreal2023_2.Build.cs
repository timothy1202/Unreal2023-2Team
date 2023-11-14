// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TeamUnreal2023_2 : ModuleRules
{
	public TeamUnreal2023_2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
	}
}
