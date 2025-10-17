Param(
    [string]$Version = "dev"
)

$ErrorActionPreference = "Stop"

# Resolve paths
$Root = Split-Path -Parent $MyInvocation.MyCommand.Path | Split-Path -Parent
$OutDir = Join-Path $Root "dev-package/PhotoSmith_Dev"
$ZipPath = Join-Path $Root ("dev-package/PhotoSmith_Dev_v$Version.zip")

Write-Host "Root: $Root"
Write-Host "Output: $OutDir"

# Clean output
if (Test-Path $OutDir) { Remove-Item -Recurse -Force $OutDir }
New-Item -ItemType Directory -Force -Path $OutDir | Out-Null

# Helper copy preserving structure
function Copy-Items([string]$src, [string]$dst) {
    if (-not (Test-Path $src)) { return }
    $dstDir = Split-Path -Parent $dst
    if ($dstDir -and -not (Test-Path $dstDir)) { New-Item -ItemType Directory -Force -Path $dstDir | Out-Null }
    Copy-Item -Recurse -Force $src $dst
}

# Include top-level files
$topFiles = @(
    "CMakeLists.txt",
    "resources.qrc",
    "PhotoSmith.pro",
    "README.md",
    "docs/README.md",
    "docs/INSTALLATION.md",
    "docs/USER_GUIDE.md",
    "Doxyfile"
)
foreach ($rel in $topFiles) {
    $src = Join-Path $Root $rel
    if (Test-Path $src) {
        $dst = Join-Path $OutDir $rel
        Copy-Items $src $dst
    }
}

# Include source and headers
Copy-Items (Join-Path $Root "src") (Join-Path $OutDir "src")
Copy-Items (Join-Path $Root "main.cpp") (Join-Path $OutDir "main.cpp")

# Include assets needed at dev time
Copy-Items (Join-Path $Root "assets") (Join-Path $OutDir "assets")

# Include third_party headers only
Copy-Items (Join-Path $Root "third_party") (Join-Path $OutDir "third_party")

# Include minimal scripts helpful for building
Copy-Items (Join-Path $Root "scripts/build_release.bat") (Join-Path $OutDir "scripts/build_release.bat")
Copy-Items (Join-Path $Root "scripts/build_all.bat") (Join-Path $OutDir "scripts/build_all.bat")

# Create a simple README_DEV
$readmeDev = @"
# PhotoSmith Dev Package

This package contains the minimal source and assets required to build the GUI version.

## Build (CMake)
1. Install Qt 6 (ensure qmake and Qt CMake packages are available) and a C++ compiler.
2. From this folder run:
   - Windows (PowerShell):
     mkdir build; cd build
     cmake -S .. -B . -DCMAKE_BUILD_TYPE=Release
     cmake --build . --config Release -j

## Build (qmake)
1. Open `PhotoSmith.pro` in Qt Creator, or run:
   qmake
   nmake / jom / mingw32-make

## Notes
- Assets are under `assets/` and referenced via `resources.qrc`.
- Third-party single-header libs are under `third_party/`.
"@
Set-Content -Path (Join-Path $OutDir "README_DEV.txt") -Value $readmeDev -Encoding UTF8

# Zip it
if (Test-Path $ZipPath) { Remove-Item -Force $ZipPath }
Add-Type -AssemblyName System.IO.Compression.FileSystem
[System.IO.Compression.ZipFile]::CreateFromDirectory($OutDir, $ZipPath)

Write-Host "Dev package prepared: $OutDir"
Write-Host "Zip created: $ZipPath"


