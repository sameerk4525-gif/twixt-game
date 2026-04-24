# Twixt (CLI Version)

## Players & Colors
- **Red (R)** → Connects **Top → Bottom**
- **Black (B)** → Connects **Left → Right**

## Basic Rules
- The board is an **N × N** grid (5 to 25).
- Players place pegs one by one:
  - `R` for Red  
  - `B` for Black
- After placing a peg, the game automatically creates links to nearby same-color pegs using **knight moves**.
- Links **cannot cross** any existing links.
- **Red wins** if a connected path reaches from the **top row to the bottom row**.
- **Black wins** if a connected path reaches from the **left column to the right column**.
- Enter moves as:  
  `row col`  
  Use `0 0` anytime to quit.

## How to Run
```bash
make
make run
