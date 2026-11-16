from pathlib import Path

PROJECT_NAME = "Renzo-SimCore"

folders = [
    "src",
    "include",
    "docs",
    "tests",
    "assets",
    "data",
]

files = {
    "README.md": "# Renzo-SimCore\n\nSimulation Kernel for Renzoverse\n",
    "docs/vision.md": "# Vision\n\nThe computational heart of CaveSharp-OS.\n",
    "src/main.cpp": "",
    "src/Creature.cpp": "",
    "src/World.cpp": "",
    "include/Creature.h": "",
    "include/World.h": "",
    "tests/test_creature.cpp": "",
    ".gitignore": "build/\n.vscode/\n",
}

root = Path(PROJECT_NAME)

root.mkdir(exist_ok=True)

for folder in folders:
    (root / folder).mkdir(parents=True, exist_ok=True)

for file_path, content in files.items():
    target = root / file_path
    target.parent.mkdir(parents=True, exist_ok=True)

    if not target.exists():
        target.write_text(content)

print(f"{PROJECT_NAME} scaffold generated successfully.")