// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Shadow_Weaver : ModuleRules
{
	public Shadow_Weaver(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
	}
}
