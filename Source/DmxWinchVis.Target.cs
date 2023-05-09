// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DmxWinchVisTarget : TargetRules
{
	public DmxWinchVisTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange(new[] { "DmxWinchVis" });
	}
}