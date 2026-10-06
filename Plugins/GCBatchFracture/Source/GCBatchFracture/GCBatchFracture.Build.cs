// Copyright Arnaud Szobad (Mecanode). All Rights Reserved.

using UnrealBuildTool;

public class GCBatchFracture : ModuleRules
{
    public GCBatchFracture(ReadOnlyTargetRules target) : base(target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new[]
        {
            "Core",
            "CoreUObject",
            "Engine"
        });

        PrivateDependencyModuleNames.AddRange(new[]
        {
            "AssetRegistry",
            "AssetTools",
            "ContentBrowser",
            "Core",
            "CoreUObject",
            "EditorFramework",
            "EditorScriptingUtilities",
            "EditorSubsystem",
            "Engine",
            "GeometryCollectionEngine",
            "InputCore",
            "Projects",
            "Slate",
            "SlateCore",
            "ToolMenus",
            "UnrealEd", 
            "GeometryCollectionEditor",
            "Chaos",
            "FractureEditor",
            "FractureEngine",
            "DeveloperSettings", 
            "DataflowCore",
        });
    }
}
