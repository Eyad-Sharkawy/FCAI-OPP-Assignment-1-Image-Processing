## Photo Smith – System Report (v3.0.1)

### Cover

- Project: Photo Smith (Image Studio GUI)
- Version: 3.0.1
- Institution: Faculty of Computers and Artificial Intelligence, Cairo University (FCAI)
- Section: S33, Group B, Lab 7
- Team:
  - Ahmed Mohamed ElSayed Tolba (ID: 20242023)
  - Eyad Mohamed Saad Ali (ID: 20242062)
  - Tarek Sami Mohamed Mohamed (ID: 20242190)

Logos:

![App Logo](../assets/icons/logo.png)

---

## 1) System Structure

### 1.1 High-level Architecture

```
┌──────────────────────────────────────────────────────────┐
│                    Presentation Layer                    │
│  ┌─────────────────┐  ┌────────────────────────────────┐ │
│  │   Main Window   │  │        Qt Designer UI          │ │
│  │  (QMainWindow)  │  │      (src/gui/mainwindow.ui)   │ │
│  └─────────────────┘  └────────────────────────────────┘ │
└──────────────────────────────────────────────────────────┘
┌──────────────────────────────────────────────────────────┐
│                   Application Layer                      │
│  ┌─────────────────────────────────────────────────────┐ │
│  │                PhotoSmith class                     │ │
│  │ (src/gui/photo_smith.cpp)                           │ │
│  │  - Signal/slot wiring                               │ │
│  │  - Undo/redo + history                              │ │
│  │  - Progress & cancellation                          │ │
│  │  - Smart display (aspect ratio)                     │ │
│  └─────────────────────────────────────────────────────┘ │
└──────────────────────────────────────────────────────────┘
┌──────────────────────────────────────────────────────────┐
│                    Business Logic                        │
│  ┌─────────────────────────────────────────────────────┐ │
│  │              ImageFilters                            │ │
│  │ (src/core/filters/ImageFilters.{h,cpp})              │ │
│  │  - Filters (color, geometric, effects)               │ │
│  │  - Progress bar updates + status messages            │ │
│  │  - Atomic cancellation                              │ │
│  └─────────────────────────────────────────────────────┘ │
└──────────────────────────────────────────────────────────┘
┌──────────────────────────────────────────────────────────┐
│                   Data & Utilities                       │
│  ┌─────────────────────────────────────────────────────┐ │
│  │ Image (src/core/image/Image_Class.*)                 │ │
│  │ I/O    (src/core/io/ImageIO.h)                       │ │
│  │ History(src/core/history/HistoryManager.h)           │ │
│  │ STB    (third_party/stb)                             │ │
│  └─────────────────────────────────────────────────────┘ │
└──────────────────────────────────────────────────────────┘
```

### 1.2 Notable Design Choices
- Cancellation: long-running filters check an atomic flag each row, restoring `preFilterImage` on cancel with friendly status messages.
- UI Responsiveness: progress updates throttle with `QApplication::processEvents()` and update intervals.
- Undo/Redo: separate image history plus a parallel stack for the “active filter” label keeps UI state consistent with edits.

---

## 2) Sample Screens (placeholders)

Add screenshots to `docs/screens/` and they’ll render here:
- Main window idle: `docs/screens/main_idle.png`
- Image loaded: `docs/screens/image_loaded.png`
- Filters in action (progress): `docs/screens/filter_progress.png`
- Example outputs (Emboss, Double Vision, Fish‑Eye): `docs/screens/outputs_collage.png`

```
docs/
  screens/
    main_idle.png
    image_loaded.png
    filter_progress.png
    outputs_collage.png
```

---

## 3) Tools and Technologies

- Programming Language: C++20
- Framework: Qt 6 (Widgets, Multimedia)
- Imaging I/O: stb_image, stb_image_write
- Build System: CMake + Ninja (generated), CLion/CMake presets, Windows batch scripts in `scripts/`
- Packaging: Portable bundle under `build_portable/PhotoSmith_Portable`
- Docs: Doxygen (HTML under `docs/api/html`)

---

## 4) Team – Who Did What

- Ahmed Mohamed ElSayed Tolba (ID: 20242023)
  - Selected tasks: Small IDs (1, 4, 7, 10), bonus 17, menu wiring
- Eyad Mohamed Saad Ali (ID: 20242062)
  - Selected tasks: Middle IDs (2, 5, 8, 11), bonus 15, menu wiring
- Tarek Sami Mohamed Mohamed (ID: 20242190)
  - Selected tasks: Large IDs (3, 6, 9, 12), bonus 16, menu wiring

Note: Roles also reflected in file headers in `ImageFilters` and `photo_smith.cpp`.

---

## 5) New Filters – Creative Algorithms

### 5.1 Emboss (relief shading)
Concept: approximate per‑pixel gradient by differencing a diagonal neighbor, biasing by +128, then grayscale.

Algorithm summary:
- For each pixel (x, y): take current (x, y) and neighbor (x+1, y+1)
- Channel‑wise difference + bias → clamp → average to gray → write to all channels
- With progress updates and cancel support in long version

Reference implementation (immediate):

```1100:1122:src/core/filters/ImageFilters.cpp
void ImageFilters::applyEmboss(Image& currentImage)
{
    // ... immediate emboss (diff vs (x+1,y+1), +128 bias, grayscale)
}
```

Cancelable variant with progress:

```1124:1150:src/core/filters/ImageFilters.cpp
void ImageFilters::applyEmboss(Image& currentImage, Image& preFilterImage, std::atomic<bool>& cancelRequested)
{
    // ... same math, with updateProgress(...) and checkCancellation(...)
}
```

Why it works: the biased difference simulates a height‑map lit from one side, giving a metallic relief.

### 5.2 Double Vision (parallax blend)
Concept: horizontally offset a second sample and blend channels with a slight red bias to emulate chromatic parallax/ghosting.

Algorithm summary:
- For each pixel (x, y): sample (x, y) and (x+offset, y)
- Blend as 60/40; add small red lift to simulate optical separation

Reference implementation (immediate):

```1152:1178:src/core/filters/ImageFilters.cpp
void ImageFilters::applyDoubleVision(Image& currentImage, int offset)
{
    // ... 60/40 blend of base and right-shifted sample, red lift
}
```

Cancelable variant with progress:

```1180:1210:src/core/filters/ImageFilters.cpp
void ImageFilters::applyDoubleVision(Image& currentImage, Image& preFilterImage, std::atomic<bool>& cancelRequested, int offset)
{
    // ... same blend, with progress and cancellation
}
```

Creative twist: a gentle red channel boost mimics binocular color separation often seen in analog captures.

### 5.3 Fish‑Eye (barrel distortion remap)
Concept: radial coordinate remapping that compresses distances near edges, simulating a wide‑angle lens.

Algorithm summary:
- Normalize pixel vector from center → (dx, dy), compute r = sqrt(dx^2+dy^2)
- For r in (0, 1): new_r = r^(0.75); map back to source, clamp, sample
- Outside radius: copy as is

Reference implementation (immediate):

```1338:1366:src/core/filters/ImageFilters.cpp
void ImageFilters::applyFishEye(Image& currentImage)
{
    // ... radial remap with exponent < 1.0 (barrel)
}
```

Cancelable variant with progress:

```1368:1400:src/core/filters/ImageFilters.cpp
void ImageFilters::applyFishEye(Image& currentImage, Image& preFilterImage, std::atomic<bool>& cancelRequested)
{
    // ... same mapping with updateProgress and checkCancellation
}
```

Why it works: the exponent < 1 compresses radii, pulling edges inward to create the fish‑eye look without expensive lens models.

---

## 6) Complex/Important Filters – Highlights

### 6.1 Edge Detection (Sobel with Gaussian pre‑blur)
- Weighted grayscale → 5×5 Gaussian blur → Sobel X/Y → magnitude → threshold to white‑on‑black edges.

```901:989:src/core/filters/ImageFilters.cpp
void ImageFilters::applyEdges(Image& currentImage)
{
    // ... grayscale, 5x5 Gaussian, Sobel, threshold
}
```

Impact: robust edges with noise resilience from pre‑blur; good for outlines and further stylization.

### 6.2 Oil Painting (mode color in local histogram)
- For each pixel neighborhood, bin by intensity level; choose the most frequent level and average RGB for that level.

```1212:1251:src/core/filters/ImageFilters.cpp
void ImageFilters::applyOilPainting(Image& currentImage, int radius, int intensity)
{
    // ... local histogram mode + mean color per dominant bin
}
```

Effect: painterly, blocky strokes that preserve local color coherence.

### 6.3 TV/CRT (scanlines + color temperature + noise)
- Periodic dark scanlines, brightness‑dependent color temperature shifts, and small random noise for analog feel.

```175:285:src/core/filters/ImageFilters.cpp
void ImageFilters::applyTVFilter(...)
{
    // ... scanlines, warm/cool shifts, slight noise
}
```

UX: visually rich retro effect with adjustable progress/cancel behavior for responsiveness.

---

## 7) UI Highlights

- Real‑time progress with cancel button surfaced during long filters
- Smart display sizing to preserve aspect ratio and avoid unnecessary upscaling
- Drag & Drop load and drag‑to‑merge behavior
- Interactive crop with rubber‑band selection

---

## 8) How to Export this Report to PDF (Windows)

Quickest (no installs):
1. Open this file in Edge or any Markdown viewer that can print.
2. Ctrl+P → Printer: “Microsoft Print to PDF” → Save.

With VS Code:
1. Install “Markdown PDF” extension.
2. Right‑click in the Markdown → “Markdown PDF: Export (pdf)”.

With Pandoc (PowerShell):
1. `winget install Pandoc.Pandoc`
2. `pandoc -s docs/PhotoSmith_Report.md -o docs/PhotoSmith_Report.pdf`

---

## 9) Why We Deserve a Prize

- Thoughtful UX: responsive progress, cancel, undo/redo, and clear status messages.
- Engineering rigor: consistent cancellation pattern; careful clamping/bounds checks.
- Creative filters: Double Vision’s color‑aware blend and Fish‑Eye’s analytic remap provide striking visuals with simple, fast math.
- Portable delivery: one‑folder portable build with all Qt deps for easy evaluation.


