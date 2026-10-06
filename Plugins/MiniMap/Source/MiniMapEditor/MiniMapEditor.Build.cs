// Copyright Arnaud Szobad (Mecanode). All Rights Reserved.

using UnrealBuildTool;

public class MiniMapEditor : ModuleRules
{
    public MiniMapEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "Core", "CoreUObject", "Engine", "RenderCore",
                "Slate", "SlateCore", "InputCore",
                "UnrealEd", "WorkspaceMenuStructure"
            }
        );
    }
}
