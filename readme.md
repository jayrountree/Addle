# Welcome to Addle
A twist on the game Wordle where each turn, a new letter will be inserted to create a new guessable word! Players start with a three letter word and letters will continue to be added until a seven letter word is reached. 
Try and guess the word as quick as you can. Good luck!

## Project Type
Web-based game with Wordle-style interface (JavaScript frontend)

## Project Structure
### Web Frontend (Active)
- `index.html` - Main game page with Wordle-style layout
- `style.css` - Wordle-themed dark mode styling
- `game.js` - Game logic implementation (Easy mode only)
- `keys.txt` - Word sequences for game puzzles
- `words.txt` - Valid English word dictionary

### C++ Console Version (Legacy)
- `main.cpp` - Entry point for console game
- `playGame.cpp/h` - Core game logic and turn management
- `gamePlayer.cpp/h` - Bot player AI implementation
- `Makefile` - Build configuration

## Game Mode
- **Easy mode**: New letter added every 3 turns (3→4→5→6→7 letters)

## How to Play
1. Start with a 3-letter word
2. Every 3 guesses, a new letter is added
3. Green = correct letter in correct position
4. Yellow = correct letter in wrong position
5. Gray = letter not in word

## Run Web Version
- Server runs automatically on port 5000
- Open the webview to play

## Build & Run C++ Version
- Build: `make`
- Run: `./addle`
- Clean: `make clean`
