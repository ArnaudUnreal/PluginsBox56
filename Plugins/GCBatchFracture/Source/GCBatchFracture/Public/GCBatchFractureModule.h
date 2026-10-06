// Copyright Arnaud Szobad (Mecanode). All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

struct FToolMenuSection;

class GCBATCHFRACTURE_API FGCBatchFractureModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

private:
    void RegisterMenus();
    void AddMenuEntry(FToolMenuSection& Section);
    void ExecuteOnSelectedStaticMeshes();
};
