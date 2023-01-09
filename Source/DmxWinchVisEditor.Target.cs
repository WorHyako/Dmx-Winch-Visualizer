// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DmxWinchVisEditorTarget : TargetRules
{
	public DmxWinchVisEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange(new[] { "DmxWinchVis" });
	}
}