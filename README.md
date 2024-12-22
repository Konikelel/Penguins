# Penguins Game

Welcome to the "Penguins" Game! This project is a simplified version of the board game "Hey, that's mine fish." Below are the instructions on how to play.

## Game Instructions

### Overview
- The game is played in turns, with each player moving one penguin at a time. 
- The objective is to collect the most fish.

### Game Board
- The game board is arranged in a square grid with `m` rows and `n` columns. 
- Each cell can either be empty or contain an ice floe with 1, 2, or 3 fish.

### Game Setup
- Each game is played on a new, possibly randomly generated, board.
- Each player starts with a known number of penguins.

### Game Phases
The game consists of two phases:
1. **Placing the Penguins**
2. **Playing the Game**

#### 1. Placing the Penguins
- In each turn, a player places one of their penguins on an unoccupied ice floe that has exactly one fish.
- When a penguin is placed, the fish on that ice floe is collected by the player and removed.
- The move is compulsory, and the placing phase ends when all penguins have been placed on the board.

#### 2. Playing the Game
- During their turn, the player selects one of their penguins and moves it in a straight line (only along grid lines) to another unoccupied ice floe.
- The previous ice floe is removed from the board after the move. Moving over an empty field or another penguin is not allowed.
- The player collects any fish on the target ice floe immediately upon moving.
- If a move is possible, it is compulsory.
- The game ends when no penguins can make a move.

### Winning the Game
- The player who collects the most fish during the game wins!
