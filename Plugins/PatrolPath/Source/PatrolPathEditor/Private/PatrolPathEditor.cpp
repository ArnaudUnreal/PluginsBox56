#include "PatrolPathEditor.h"
#include "UnrealEdGlobals.h"
#include "PatrolPathVisualizer.h"
#include "Editor/UnrealEdEngine.h"
#include "PatrolPath/Public/PatrolPathComponent.h"

#define LOCTEXT_NAMESPACE "FPatrolPathEditorModule"

void FPatrolPathEditorModule::StartupModule()
{
    FName ClassName =  UPatrolPathComponent::StaticClass()->GetFName();
    if (GUnrealEd)
    {
        Visualizer = MakeShared<FPatrolPathVisualizer>();
        GUnrealEd->RegisterComponentVisualizer(ClassName, Visualizer);
        Visualizer->OnRegister();
    }
}

void FPatrolPathEditorModule::ShutdownModule()
{
    FName ClassName =  UPatrolPathComponent::StaticClass()->GetFName();
    if (GUnrealEd)
    {
        GUnrealEd->UnregisterComponentVisualizer(ClassName);
    }
    Visualizer.Reset();
    
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FPatrolPathEditorModule, PatrolPathEditor)