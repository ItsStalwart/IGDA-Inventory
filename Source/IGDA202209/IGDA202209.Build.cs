// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class IGDA202209 : ModuleRules
{
	public IGDA202209(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
