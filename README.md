# 🎮 Twixt (CLI Version)

## Players & Colors

* **Red (R)** → Connects **Top → Bottom**
* **Black (B)** → Connects **Left → Right**

---

## Basic Rules

* The board is an **N × N grid** (5 to 25)
* Players place pegs one by one:

  * `R` for Red
  * `B` for Black
* After placing a peg, links are automatically created using **knight moves**
* Links **cannot cross** each other
* **Red wins** if it connects top to bottom
* **Black wins** if it connects left to right

---

## Controls

* Enter moves as: `row col`
* Enter `-1 -1` → Undo last move
* Enter `0 0` → Quit game

---

## How to Run

```bash
make
make run
```
