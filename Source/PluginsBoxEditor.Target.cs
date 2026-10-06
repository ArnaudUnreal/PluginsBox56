// Copyright Arnaud Szobad (Mecanode). All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class PluginsBoxEditorTarget : TargetRules
{
	public PluginsBoxEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_6;
		ExtraModuleNames.Add("PluginsBox");
	}
}
