#!/usr/bin/env bash
# Phase I build for macOS/Linux (Windows teammates use build-phase1.ps1).
# Set BREAKOUT_SFML_ROOT to a prefix containing include/ and lib/, or rely on Homebrew defaults.
# Optional: BREAKOUT_GPP=/path/to/g++ or clang++
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
OUT="${ROOT}/main"

GPP="${BREAKOUT_GPP:-}"
if [[ -z "$GPP" ]]; then
  if command -v g++ >/dev/null 2>&1; then
    GPP="$(command -v g++)"
  elif command -v clang++ >/dev/null 2>&1; then
    GPP="$(command -v clang++)"
  else
    echo "No g++ or clang++ on PATH. Install Xcode CLT or set BREAKOUT_GPP." >&2
    exit 1
  fi
fi

SFML="${BREAKOUT_SFML_ROOT:-}"
if [[ -z "$SFML" ]]; then
  if [[ -d "/opt/homebrew/opt/sfml" ]]; then
    SFML="/opt/homebrew/opt/sfml"
  elif [[ -d "/usr/local/opt/sfml" ]]; then
    SFML="/usr/local/opt/sfml"
  fi
fi

if [[ -z "$SFML" ]] || [[ ! -d "${SFML}/include" ]] || [[ ! -d "${SFML}/lib" ]]; then
  echo "Could not find SFML. Set BREAKOUT_SFML_ROOT to a folder with include/ and lib/." >&2
  echo "Homebrew example: export BREAKOUT_SFML_ROOT=\"\$(brew --prefix sfml)\"" >&2
  exit 1
fi

echo "Using compiler: ${GPP}"
echo "Using SFML root: ${SFML}"

"$GPP" -std=c++20 -g \
  "-I${SFML}/include" \
  "${ROOT}/phase1_main.cpp" \
  "${ROOT}/Game.cpp" \
  "${ROOT}/src/GameManager.cpp" \
  "-L${SFML}/lib" \
  -lsfml-graphics -lsfml-window -lsfml-system \
  -o "${OUT}"

echo "Built: ${OUT}"
