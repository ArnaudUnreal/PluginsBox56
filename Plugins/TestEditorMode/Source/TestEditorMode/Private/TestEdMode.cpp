#include "TestEdMode.h"
#include "TestEditorMode/Public/FTestEditorModeToolkit.h"

#include "Editor.h"
#include "EditorModeManager.h"
#include "EditorViewportClient.h"
#include "Subsystems/EditorActorSubsystem.h"
#include "ScopedTransaction.h"
#include "Misc/MessageDialog.h"
#include "Engine/StaticMesh.h"
#include "Toolkits/ToolkitManager.h"

#define LOCTEXT_NAMESPACE "TestEdMode"

const FEditorModeID FTestEdMode::EM_TestEdModeId = TEXT("EM_TestEdMode");

FTestEdMode::FTestEdMode()
{
}

FTestEdMode::~FTestEdMode()
{
}

void FTestEdMode::Enter()
{
    FEdMode::Enter();

    if (!Toolkit.IsValid())
    {
        Toolkit = MakeShareable(new FTestEditorModeToolkit);
        Toolkit->Init(Owner->GetToolkitHost());
    }
}

void FTestEdMode::Exit()
{
    if (Toolkit.IsValid())
    {
        FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
        Toolkit.Reset();
    }

    FEdMode::Exit();
}

bool FTestEdMode::ConfirmPlacement(const FString& AssetName) const
{
    const FText Message = FText::Format(
        LOCTEXT("ConfirmPlacement", "Placer le mesh \"{0}\" dans le level ?"),
        FText::FromString(AssetName)
    );

    const EAppReturnType::Type Result = FMessageDialog::Open(
        EAppMsgType::OkCancel,
        Message
    );

    return Result == EAppReturnType::Ok;
}

void FTestEdMode::GetSpawnTransformFromViewport(FVector& OutLocation, FRotator& OutRotation) const
{
    OutLocation = FVector::ZeroVector;
    OutRotation = FRotator::ZeroRotator;

    if (!GEditor || !GEditor->GetActiveViewport())
    {
        return;
    }

    FEditorViewportClient* ViewportClient =
        static_cast<FEditorViewportClient*>(GEditor->GetActiveViewport()->GetClient());

    if (!ViewportClient)
    {
        return;
    }

    OutLocation = ViewportClient->GetViewLocation() + ViewportClient->GetViewRotation().Vector() * 300.0f;
    OutRotation = FRotator::ZeroRotator;
}

void FTestEdMode::PlaceMeshFromPath(const FString& MeshPath)
{
    UStaticMesh* Mesh = LoadObject<UStaticMesh>(nullptr, *MeshPath);
    if (!Mesh)
    {
        FMessageDialog::Open(
            EAppMsgType::Ok,
            LOCTEXT("MeshNotFound", "Impossible de charger ce Static Mesh.")
        );
        return;
    }

    if (!ConfirmPlacement(Mesh->GetName()))
    {
        return;
    }

    FVector SpawnLocation;
    FRotator SpawnRotation;
    GetSpawnTransformFromViewport(SpawnLocation, SpawnRotation);

    const FScopedTransaction Transaction(LOCTEXT("PlaceStaticMeshTransaction", "Place Static Mesh"));

    UEditorActorSubsystem* ActorSubsystem = GEditor->GetEditorSubsystem<UEditorActorSubsystem>();
    if (!ActorSubsystem)
    {
        return;
    }

    AActor* NewActor = ActorSubsystem->SpawnActorFromObject(
        Mesh,
        SpawnLocation,
        SpawnRotation
    );

    if (NewActor)
    {
        GEditor->SelectNone(false, true, false);
        GEditor->SelectActor(NewActor, true, true, true);
    }
}

#undef LOCTEXT_NAMESPACE