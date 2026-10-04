# MiniMap

**MiniMap** is an Unreal Engine editor plugin that adds a top-down mini-map of the current level to the editor.

Use it to see the whole level at a glance, find and select actors, and move the editor camera anywhere with a single click.

---

## Current Version

```text
1.1
```

Target Unreal Engine version:

```text
Unreal Engine 5.6
```

Platform:

```text
Win64 (editor only)
```

---

## Features

- Dockable **Mini-Map** tab, listed in **Window > Level Editor**.
- Top-down map automatically fitted to the level bounds.
- Uniform scale: the map is never stretched, whatever the panel size.
- Adaptive world-space grid with X = 0 / Y = 0 axes.
- Shows every actor as its footprint outline, or as a dot when too small on screen.
- Selected actors highlighted.
- Active editor camera shown with its position and field of view.
- Click an actor to select it, Ctrl+click to toggle it in the selection (undoable).
- Double-click an actor to focus the editor camera on it.
- Click empty space to move the editor camera there, keeping its rotation and height above ground.
- Top / Bottom orthographic viewports follow the camera moves.
- Actor filter by class name or actor label, available when **All actors** is unchecked.
- Optional top-down captured background image of the level.
- Automatic refresh when actors are added, deleted, moved or renamed, and when another level is opened.

---

## Installation

1. Copy the `MiniMap` folder into your project's `Plugins` folder.
2. Open the project. If prompted, rebuild the plugin.
3. Make sure **MiniMap** is enabled in **Edit > Plugins** (category **Editor**).

---

## Usage

Open the tab from **Window > Level Editor > Mini-Map**, then dock it wherever you like.

### Toolbar

| Control | Action |
|---|---|
| **Fit** | Recompute the level bounds and reset pan / zoom. |
| **All actors** | Show every actor of the level. Uncheck it to use the filter. |
| **Capture** | Render a top-down image of the current map area and use it as background. |
| **Background** | Show / hide the captured background. |
| **Filter** | Enabled when **All actors** is unchecked. Shows only the actors whose class name or label contains the text (case-insensitive). Empty: only the selection is shown. |

### Mouse controls

| Input | Action |
|---|---|
| Left click on an actor | Select the actor. |
| Ctrl + left click on an actor | Add / remove the actor from the selection. |
| Left click on empty space | Move the editor camera to look at that point. |
| Double-click on an actor | Focus the editor camera on the actor. |
| Right mouse drag | Pan the map. |
| Mouse wheel | Zoom, centered on the cursor. |

A reminder of these controls is displayed at the bottom of the tab.

---

## Map Conventions

The map uses the same orientation as the editor **Top** viewport:

- World **+X** points to the right.
- World **+Y** points down.

Actors are drawn as:

- **Blue** outline or dot: regular actor.
- **Yellow** outline or dot: selected actor.
- **Green** wedge: active editor camera and its field of view.

---

## Background Capture

The background is an orthographic scene capture taken from above the level, at 2048 × 2048.

- It is only taken when you click **Capture**. It is not updated automatically.
- It covers the map area at the time of the capture. If the level grew, click **Fit** before **Capture**.
- It is cleared when another level is opened.
- Fog and volumetric fog are disabled during the capture.

Content that is not loaded in the editor is not captured:

- **Without World Partition**: the whole level is captured, except streaming sub-levels that are not loaded in the **Levels** panel.
- **With World Partition**: only the cells currently loaded in the editor are captured. Unloaded areas stay black.

Lighting quality of the capture depends on the project rendering settings (Lumen in orthographic view in particular).

---

## Which Actors Are Mapped

Included:

- Any actor placed in the editor world with a spatial meaning.

Ignored:

- Editor-only actors.
- Actors hidden in the editor.
- `AInfo` actors (World Settings, Game Mode, etc.).
- The builder brush.

Actors whose bounds exceed 10 km in half-size (sky spheres, for example) are mapped as a point at their location, so they do not blow up the level bounds.

---

## Known Limitations

- The map is 2D: overlapping actors at different heights are drawn on top of each other.
- With World Partition, only loaded actors are shown and taken into account for the bounds.
- On levels with tens of thousands of actors, each keystroke in the filter rebuilds the actor list.
- The background capture briefly stalls the editor while it renders.

---

## Module Overview

| File | Role |
|---|---|
| `MiniMapEditor.cpp` | Module startup / shutdown, registers the **Mini-Map** nomad tab. |
| `SMiniMapPanel` | Tab content: toolbar, map viewport and controls reminder. |
| `SMiniMapViewport` | The map widget: drawing, input, actor cache, camera moves, background capture. |

Module dependencies:

```text
Core, CoreUObject, Engine, RenderCore, Slate, SlateCore, InputCore, UnrealEd, WorkspaceMenuStructure
```

---

## Changelog

### 1.1

- Map fitted to the level when the tab opens, and refitted when another level is opened.
- Uniform scale (no more stretching) and stable cursor-centered zoom.
- Multiplicative zoom, range 0.1 – 50.
- Pan follows the cursor at any DPI scale.
- Map content clipped to the panel.
- Bounds computed from actor footprints instead of actor locations.
- Camera moves keep rotation and target the ground under the clicked point.
- New toolbar: Fit, All actors, Capture, Background, Filter.
- All actors display, actor selection from the map, double-click focus.
- Active camera display.
- Top-down background capture.
- Tab moved to **Window > Level Editor**, with an icon.

### 1.0

- Initial version: mini-map tab with grid, selected actors, pan / zoom and click-to-move camera.
