# GC Batch Fracture

**GC Batch Fracture** is an Unreal Engine editor plugin that batch-converts selected Static Mesh assets into fractured Chaos Geometry Collections.

It is designed to save production time when preparing many props for Chaos destruction workflows.

Instead of manually converting and fracturing assets one by one in Fracture Mode, you can select multiple Static Meshes in the Content Browser, choose a preset, and generate runtime-ready Geometry Collections in batch.

---

## Current Version

```text
0.4.3
```

Target Unreal Engine version:

```text
Unreal Engine 5.6
```

Validated workflows:

- Plugin source build in a C++ project.
- Packaged plugin usage in a Blueprint-only project.
- Geometry Collection generation.
- Save All.
- Editor restart / project reopen.
- Placement in level.
- Play-in-editor runtime collision test.

---

## Features

- Batch-convert selected `UStaticMesh` assets into `UGeometryCollection` assets.
- Content Browser context-menu integration.
- Pre-generation Slate dialog.
- Preset-based workflow:
  - **Fast Preview**
  - **Balanced**
  - **Runtime Safe**
  - **Custom**
- Automatic output folder creation.
- Automatic asset naming with configurable prefix.
- Skip or auto-rename existing generated assets.
- Multi-level Voronoi fracture.
- Secondary fracture limiting to avoid excessive generation time.
- Runtime collision preparation.
- Convex hull generation for fractured pieces.
- Optional cluster convex hull generation.
- Optional non-overlapping convex hull generation.
- Optional tiny geometry cleanup.
- Optional Geometry Collection validation.
- Source mesh complexity limits.
- Fracture operation safety limits.
- Progress dialog with cancel support.
- Asset-by-asset saving.
- Periodic garbage collection during large batches.
- Dedicated log category: `LogGCBatchFracture`.

---

## Quick Demo

A demonstration video is available for this plugin.

The recommended video flow is:

```text
Select multiple Static Meshes
→ Right-click in Content Browser
→ Batch Chaos Fracturer...
→ Choose a preset
→ Generate Geometry Collections
→ Open generated assets
→ Place in level
→ Play
→ Verify runtime collision
```

---

## Requirements

- Unreal Engine **5.6**
- Chaos / Geometry Collection support
- Windows target validated
- Editor-only workflow

The plugin is intended for editor workflows. It generates Geometry Collection assets that can then be used in runtime gameplay.

---

## Installation

Copy the plugin into your project:

```text
YourProject/
└── Plugins/
    └── GCBatchFracture/
```

Then regenerate project files if needed and compile your project.

For a packaged plugin build, copy the packaged plugin folder into:

```text
YourProject/
└── Plugins/
    └── GCBatchFracture/
```

Blueprint-only projects can use the packaged plugin without converting the project to C++, provided the plugin has been packaged for the matching Unreal Engine version.

---

## Basic Usage

1. Open the **Content Browser**.
2. Select one or more `Static Mesh` assets.
3. Right-click the selection.
4. Choose:

```text
Batch Chaos Fracturer...
```

5. Choose a preset in the dialog.
6. Choose whether existing generated assets should be skipped.
7. Click **Create Geometry Collections**.

Generated assets are saved next to the source Static Meshes, inside a configurable subfolder.

Example:

```text
Source:
  /Game/Boats/SM_Boat_01

Generated:
  /Game/Boats/GC/GC_SM_Boat_01
```

---

## Output Naming

By default:

```text
Prefix: GC_
Output Subfolder: GC
```

Example:

```text
/Game/Props/SM_Crate
→ /Game/Props/GC/GC_SM_Crate
```

Both the prefix and output subfolder can be changed in the plugin settings.

---

## Presets

The plugin includes simple presets for common workflows.

Changing a preset applies its values to the visible settings fields.

If the user manually edits a preset-controlled setting, the preset automatically switches to **Custom**.

### Fast Preview

A lightweight preset designed for quick iteration.

Use this when you want to quickly generate fractured Geometry Collections for visual preview or early testing.

Typical behavior:

- Lower generation cost.
- Fewer fracture operations.
- Faster output.
- Suitable for large batches or early review.

### Balanced

Recommended default preset.

Use this for most production props when you want a good compromise between:

- visual fracture quality;
- generation time;
- generated piece count;
- runtime collision reliability.

### Runtime Safe

More conservative preset intended for runtime Chaos simulation.

Use this when the generated Geometry Collections are expected to be simulated or collide during gameplay.

This preset may take longer on complex meshes or large batches.

### Custom

Uses the values currently visible in Project Settings.

Any manual change to a preset-controlled setting switches the preset to **Custom**.

---

## Pre-Generation Dialog

When launching the tool from the Content Browser, a Slate dialog appears before processing starts.

The dialog shows:

- number of selected Static Mesh assets;
- preset selector;
- skip existing assets option;
- warning messages for expensive/runtime-safe options.

This allows users to choose the most common batch options without manually opening Project Settings first.

Project Settings remain the source of truth. Values chosen in the dialog are written back to the plugin settings before the batch starts.

---

## Settings

Settings are available in:

```text
Project Settings
→ Plugins
→ GC Batch Fracture
```

### Output

| Setting | Description |
|---|---|
| `OutputSubfolder` | Subfolder created next to the source mesh folder. |
| `NamePrefix` | Prefix added to generated Geometry Collection assets. |
| `bSkipExistingAssets` | If enabled, existing generated assets are skipped. If disabled, unique names are generated instead of overwriting. |

---

### Batch Safety

| Setting | Description |
|---|---|
| `SoftSelectionWarningCount` | Shows a warning when many assets are selected. |
| `HardSelectionBlockCount` | Prevents processing extremely large selections. |
| `bSaveAfterEachAsset` | Saves each generated asset immediately after processing. |
| `GarbageCollectEveryNAssets` | Runs garbage collection periodically during long batches. |
| `MaxSourceVertices` | Optional source mesh vertex limit. `0` disables the limit. |
| `MaxSourceTriangles` | Optional source mesh triangle limit. `0` disables the limit. |

---

### Fracture

| Setting | Description |
|---|---|
| `FractureLevelCount` | Number of Voronoi fracture passes. |
| `VoronoiSites` | Number of Voronoi sites per fracture pass. |
| `RandomSeed` | Base random seed for deterministic fracture. |
| `RandomSeedOffsetPerLevel` | Seed offset applied per fracture level. |
| `ChanceToFracture` | Chance for a selected transform to be fractured. |
| `PerLevelChanceToFracture` | Chance used on secondary levels to avoid refracturing every piece. |
| `MaxTransformsToFracturePerLevel` | Limits how many transforms can be fractured per level. |
| `MaxTransformsAfterFracture` | Stops additional fracture levels when the transform count becomes too high. |
| `MaxEstimatedFractureOperationsPerLevel` | Prevents launching fracture operations estimated to be too expensive. |

---

### Advanced Fracture

| Setting | Description |
|---|---|
| `bSplitIslands` | Allows disconnected geometry islands to be split during fracture. |
| `Grout` | Adds spacing between fractured pieces. Usually kept at `0`. |
| `Amplitude` | Noise amplitude for fracture surfaces. |
| `Frequency` | Noise frequency for fracture surfaces. |
| `Persistence` | Noise persistence. |
| `Lacunarity` | Noise lacunarity. |
| `OctaveNumber` | Number of noise octaves. |
| `PointSpacing` | Point spacing used by the fracture engine. |
| `bAddSamplesForCollision` | Adds collision samples during fracture. |
| `CollisionSampleSpacing` | Spacing used for collision samples. |

---

### Collision

| Setting | Description |
|---|---|
| `bFixTinyGeometry` | Merges or fixes very small fragments before simulation data is generated. |
| `TinyGeometryMinSizeCm` | Minimum tiny geometry size threshold in centimeters. |
| `bValidateGeometryCollectionAfterFracture` | Cleans invalid or useless collection data after fracture. |
| `bGenerateLeafConvexHulls` | Generates convex hulls for leaf pieces. Recommended for runtime collision. |
| `bGenerateClusterConvexHulls` | Generates convex hulls for cluster nodes. |
| `bCreateNonOverlappingConvexHulls` | Generates non-overlapping convex hulls. Slower and considered advanced / experimental. |

---

## Existing Assets

The plugin does **not** directly overwrite existing Geometry Collections.

This is intentional.

Overwriting loaded Geometry Collection assets can leave stale render or physics resources in the editor.

Current behavior:

```text
If target asset does not exist:
  → create normally

If target asset exists and Skip Existing is enabled:
  → skip asset

If target asset exists and Skip Existing is disabled:
  → create a uniquely named asset
```

Example:

```text
GC_SM_Crate
GC_SM_Crate_001
GC_SM_Crate_002
```

---

## Runtime Collision

The plugin prepares generated Geometry Collections for runtime usage by running several post-fracture steps:

```text
Fracture
→ Fix tiny geometry
→ Validate Geometry Collection
→ Generate convex hulls
→ Prepare for Chaos simulation
→ Create simulation data
→ Rebuild render data
→ Save asset
```

This is required because visible fractured pieces are not enough for runtime physics. Chaos also needs valid implicit collision geometry.

---

## Safety Features

GC Batch Fracture includes several safety mechanisms to reduce the risk of editor crashes or extremely expensive operations.

Implemented safeguards include:

- selection count soft warning;
- selection count hard block;
- progress dialog with cancel support;
- asset-by-asset saving;
- periodic garbage collection;
- null Static Mesh checks;
- source mesh vertex / triangle limits;
- safe existing asset handling through Skip / Auto Rename;
- no direct overwrite of existing Geometry Collections;
- destination asset overwrite guard before creation;
- validated Dataflow transform selection;
- empty collection validation before fracture;
- secondary-level fracture chance filtering;
- maximum selected transforms per fracture level;
- maximum transforms after fracture;
- maximum estimated fracture operations per level;
- optional tiny geometry cleanup;
- optional Geometry Collection validation;
- configurable convex hull generation;
- warning messages for expensive collision options.

If a safety limit stops further fracture levels, the asset is finalized using the fracture data already generated.

---

## Performance Notes

Batch fracture can be expensive.

Generation time depends on:

- source mesh complexity;
- number of selected assets;
- number of fracture levels;
- number of Voronoi sites;
- number of generated pieces;
- convex hull generation;
- non-overlapping hull generation;
- runtime simulation data generation;
- package saving.

If generation is too slow, try:

- using **Fast Preview**;
- reducing `FractureLevelCount`;
- reducing `VoronoiSites`;
- lowering `PerLevelChanceToFracture`;
- lowering `MaxTransformsToFracturePerLevel`;
- lowering `MaxEstimatedFractureOperationsPerLevel`;
- disabling `bCreateNonOverlappingConvexHulls`.

---

## Logs

The plugin uses a dedicated log category:

```text
LogGCBatchFracture
```

To enable verbose logs, use the Unreal console:

```text
Log LogGCBatchFracture Verbose
```

Or add this to your config:

```ini
[Core.Log]
LogGCBatchFracture=Verbose
```

Verbose logs include detailed timing for fracture, collision generation, simulation data creation, render data rebuild and saving.

---

## Recommended Workflow

For large batches:

1. Start with **Fast Preview** on a few assets.
2. Check the generated Geometry Collections visually.
3. Test runtime collision on representative assets.
4. Move to **Balanced** for production use.
5. Use **Runtime Safe** only where stronger runtime stability is needed.
6. Avoid overwriting assets already placed in open levels.
7. Save frequently during large batch operations.

---

## Known Limitations

- Very small fragments may be merged or skipped by Chaos.
- Extremely complex source meshes can produce heavy Geometry Collections.
- Multi-level fracture can grow fragment counts quickly.
- Non-overlapping convex hull generation can be slow.
- Generated assets should be tested in context before shipping gameplay content.
- Current validated target is Unreal Engine 5.6.

---

## Troubleshooting

### The generated Geometry Collection falls through the floor

Check that runtime collision preparation is enabled:

- `bGenerateLeafConvexHulls`
- `bFixTinyGeometry`
- `bValidateGeometryCollectionAfterFracture`

Also verify the placed actor/component collision settings in the level.

---

### Generation is too slow

Use a lighter preset or reduce:

- `FractureLevelCount`
- `VoronoiSites`
- `MaxTransformsToFracturePerLevel`
- `MaxEstimatedFractureOperationsPerLevel`

Disable:

```text
bCreateNonOverlappingConvexHulls
```

unless specifically needed.

---

### Existing assets are not replaced

This is expected.

The plugin avoids direct overwrite of existing Geometry Collections to prevent stale render or physics data issues.

Use **Skip Existing** to ignore existing assets, or disable it to auto-generate unique names.

---

### Some geometry is too small to be simulated

Chaos may log:

```text
Some geometry is too small to be simulated and has been skipped.
```

This usually means that some generated fragments are too small for reliable physics simulation.

Try increasing:

```text
TinyGeometryMinSizeCm
```

or reducing fracture detail.

---

### Runtime Safe is slow

This is expected on complex meshes or large batches.

Runtime Safe uses more conservative settings and can generate more robust collision data.

For faster iteration, use **Fast Preview** or **Balanced**.

---

## Support Notes

When reporting an issue, please include:

- Unreal Engine version;
- plugin version;
- selected preset;
- number of selected assets;
- approximate source mesh triangle count;
- relevant `LogGCBatchFracture` output;
- whether the asset was newly generated or already existed;
- whether the asset was used in an open level.

---

## Packaging Notes

The plugin has been validated as:

- source plugin in a C++ project;
- packaged plugin in a Blueprint-only project.

For distribution, package the plugin for the supported Unreal Engine version and test it in a clean project before release.

---

## License

This plugin is intended for use under the license terms provided with its distribution platform.

---

## Version

```text
GC Batch Fracture 0.4.3
Unreal Engine 5.6
```
