# Tic-Tac-Toe with Minimax AI

A console-based Tic-Tac-Toe game in C++ featuring four difficulty tiers, from
pure randomness to an unbeatable minimax-driven AI. Built as a from-scratch
exercise in implementing the minimax algorithm.

## Features

- **PvP mode** — two players on the same machine
- **AI vs Player**, with four difficulty levels:
  - **Easy** — moves are fully random
  - **Medium** — takes winning moves and blocks opponent wins, otherwise random
  - **Hard** — adds center-priority opening and corner-fork defense on top of Medium's logic
  - **Impossible** — full minimax search; plays perfectly and cannot be beaten
- Input validation (rejects out-of-range and non-numeric input without crashing)
- Optional "AI thinking tree" debug mode that prints the minimax score at every explored node

## How it works

The Impossible difficulty is powered by a classic minimax implementation:

- `minMax(bool turn)` recursively explores every possible sequence of remaining
  moves and returns a score from the AI's perspective: `+1` (O wins), `-1`
  (X wins), or `0` (tie). On O's turn it maximizes this score; on X's turn it
  minimizes it — assuming both sides play optimally the rest of the way.
- `ai()` is a thin wrapper that calls `minMax` once for each empty cell and
  picks whichever move produces the best score, then actually applies it to
  the board.

Because the board is only 9 cells, the full game tree is small enough to
brute-force at every move with no pruning or depth limits — a good first
project for understanding minimax before tackling games with larger search
spaces.

The lower difficulties (`heuristicAI`) don't search the tree at all — they're
a short list of hand-coded rules (win if possible → block if necessary →
center/corner heuristics on Hard → otherwise random) checked in priority order.

## Building

Requires a C++ compiler (tested with g++/MinGW on Windows).

```bash
g++ minimax.cpp -o minimax
./minimax
```

> **Note:** the board rendering uses `system("cls")`, so this currently
> targets Windows. Swap it for `system("clear")` (or an `#ifdef`-guarded
> version of both) to run on Linux/macOS.

## Playing

- The board is numbered 1–9, left to right, top to bottom.
- On your turn, type the number of the cell you want to play and press Enter.
- Invalid input (out of range, already taken, or non-numeric) will just
  re-prompt you rather than crashing.

## Known limitations

- Windows-only console clearing (`system("cls")`)
- Single game per run — the program exits after each result rather than
  offering a rematch
- Game logic, AI, and I/O currently live together in one file; a larger
  version of this project would likely split these into separate modules

## Motivation

This project was built to actually understand minimax by implementing it
from scratch — including going through (and fixing) the classic beginner
pitfalls: conflating a move index with a position's score, C++ reference vs.
value parameter mixups, variable shadowing, and off-by-one/out-of-bounds
input handling.
