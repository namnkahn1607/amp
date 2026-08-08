#!/usr/bin/env bash
# Setup VSCode development environment.
#
# Usage: bash setup.sh
set -euo pipefail

PROJECT_ROOT="$(git rev-parse --show-toplevel)"  # amp/
cd "$PROJECT_ROOT"

log() { echo "[INFO] $*" >&2; }
warn() { echo "[WARN] $*" >&2; }
die() { echo "[ERROR] $*" >&2; exit 1; }

log "[1/4] Installing VSCode extensions."
code --install-extension llvm-vs-code-extensions.vscode-clangd
code --install-extension vadimcn.vscode-lldb

log "[2/4] Creating intial directories & files."
mkdir -p .vscode/ debug/
echo "[Paste input testcase here]" > in.txt

log "[3/4] Configuring VSCode."
# Configuring launch.json
cat << 'EOF' > .vscode/launch.json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Clang++ Debug Active File",
            "type": "lldb",
            "request": "launch",
            "program": "${workspaceFolder}/debug/${fileBasenameNoExtension}.out",
            "args": [],
            "stopOnEntry": false,
            "cwd": "${workspaceFolder}",
            "stdio": ["${workspaceFolder}/in.txt", null, null],
            "preLaunchTask": "Clang++ Build Active File"
        }
    ]
}
EOF

# Configuring settings.json
cat << 'EOF' > .vscode/settings.json
{
    // Clangd
    "clangd.path": "/usr/bin/clangd",
    "[cpp]": {
        "editor.defaultFormatter": "llvm-vs-code-extensions.vscode-clangd",
        "editor.formatOnSave": true
    },

    // GitLens
    "gitlens.codeLens.enabled": false,

    // Switch off code suggestion
    "editor.quickSuggestions": {
        "other": false,
        "comments": false,
        "strings": false
    },
    "editor.suggestOnTriggerCharacters": false,
    "editor.wordBasedSuggestions": "off",
    "editor.parameterHints.enabled": false,
    "editor.acceptSuggestionOnEnter": "off",
}
EOF

# Configuring tasks.json
cat << 'EOF' > .vscode/tasks.json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "Clang++ Build Active File",
            "type": "shell",
            "command": "/usr/bin/clang++-17",
            "args": [
                "-g", // show debug info
                "-std=c++17", // C++17
                "-Wall",
                "-Wextra",
                "-Wpedantic",
                "-Wshadow",
                "-Wunreachable-code",
                
                "-I${workspaceFolder}/include", // all common header .h files

                "${file}", // current opening source .cpp file
                "-o",
                "${workspaceFolder}/debug/${fileBasenameNoExtension}.out"
            ],
            "options": {
                "cwd": "${workspaceFolder}"
            },
            "problemMatcher": {
                "owner": "cpp",
                "fileLocation": ["relative", "${workspaceFolder}"],
                "pattern": {
                    "regexp": "^(.*):(\\d+):(\\d+):\\s+(warning|error):\\s+(.*)$",
                    "file": 1,
                    "line": 2,
                    "column": 3,
                    "severity": 4,
                    "message": 5
                }
            },
            "group": {
                "kind": "build",
                "isDefault": true
            }
        }
    ]
}
EOF

log "Completed!"
