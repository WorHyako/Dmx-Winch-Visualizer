// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DmxWinchVis : ModuleRules
{
	public DmxWinchVis(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"DMXRuntime",
			"DMXProtocol"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });
	}
}