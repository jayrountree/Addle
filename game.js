let wordSequence = [];
let validWords = new Set();
let currentWordIndex = 0;
let currentWord = '';
let guesses = [];
let turn = 0;
let gameOver = false;
let newLetterIndex = -1;
let currentGuess = '';
let keyboardState = {};

// Initialize game
async function initGame() {
    await loadWords();
    startNewGame();
}

// Load word lists from files
async function loadWords() {
    try {
        const [keysResponse, wordsResponse] = await Promise.all([
            fetch('keys.txt'),
            fetch('words.txt')
        ]);
        
        const keysText = await keysResponse.text();
        const wordsText = await wordsResponse.text();
        
        // Parse keys.txt - each line is a sequence of words
        const keyLines = keysText.trim().split('\n');
        const randomLine = keyLines[Math.floor(Math.random() * keyLines.length)];
        wordSequence = randomLine.trim().split(' ');
        
        // Parse words.txt - each line is a valid word
        const wordList = wordsText.trim().split('\n');
        validWords = new Set(wordList.map(w => w.toLowerCase().trim()));
        
    } catch (error) {
        showMessage('Error loading word lists', 'error');
        console.error(error);
    }
}

// Start a new game
function startNewGame() {
    currentWordIndex = 0;
    currentWord = wordSequence[0];
    guesses = [];
    turn = 0;
    gameOver = false;
    newLetterIndex = -1;
    currentGuess = '';
    keyboardState = {};
    
    document.getElementById('giveUpBtn').style.display = 'block';
    document.getElementById('newGameBtn').style.display = 'none';
    
    buildKeyboard();
    renderBoard();
    showMessage(`Guess the ${currentWord.length}-letter word!`, 'info');
}

// Render the game board
function renderBoard() {
    const board = document.getElementById('gameBoard');
    board.innerHTML = '';
    
    guesses.forEach((guess, index) => {
        const row = createRow(guess.word, guess.colors, guess.newLetterPos);
        board.appendChild(row);
    });
    
    // Show current guess being typed
    if (!gameOver && currentGuess.length > 0) {
        const currentRow = createCurrentGuessRow(currentGuess, currentWord.length);
        board.appendChild(currentRow);
    } else if (!gameOver) {
        // Show current word length hint
        const hintRow = createEmptyRow(currentWord.length);
        board.appendChild(hintRow);
    }
}

// Create a row of tiles
function createRow(word, colors, newLetterPos = -1) {
    const row = document.createElement('div');
    row.className = 'row';
    
    for (let i = 0; i < word.length; i++) {
        const tile = document.createElement('div');
        tile.className = 'tile filled';
        tile.textContent = word[i];
        
        if (colors && colors[i]) {
            if (colors[i] === 'g') {
                tile.classList.add('correct');
            } else if (colors[i] === 'y') {
                tile.classList.add('present');
            } else {
                tile.classList.add('absent');
            }
        }
        
        if (i === newLetterPos) {
            tile.classList.add('new-letter');
        }
        
        row.appendChild(tile);
    }
    
    return row;
}

// Create an empty row (hint for current word)
function createEmptyRow(length) {
    const row = document.createElement('div');
    row.className = 'row';
    
    for (let i = 0; i < length; i++) {
        const tile = document.createElement('div');
        tile.className = 'tile';
        if (i === newLetterIndex && newLetterIndex !== -1) {
            tile.textContent = '^';
            tile.style.color = '#818384';
        }
        row.appendChild(tile);
    }
    
    return row;
}

// Create a row for the current guess being typed
function createCurrentGuessRow(guess, targetLength) {
    const row = document.createElement('div');
    row.className = 'row';
    
    for (let i = 0; i < targetLength; i++) {
        const tile = document.createElement('div');
        tile.className = 'tile';
        
        if (i < guess.length) {
            tile.classList.add('filled');
            tile.textContent = guess[i];
        } else if (i === newLetterIndex && newLetterIndex !== -1) {
            tile.textContent = '^';
            tile.style.color = '#818384';
        }
        
        row.appendChild(tile);
    }
    
    return row;
}

// Check if it's time to add a letter (easy mode: every 3 turns)
function shouldAddLetter() {
    return turn > 0 && turn % 3 === 0 && currentWordIndex < wordSequence.length - 1;
}

// Add a new letter to the word
function addLetter() {
    const oldWord = currentWord;
    currentWordIndex++;
    currentWord = wordSequence[currentWordIndex];
    
    // Find where the new letter was inserted
    for (let i = 0; i < currentWord.length; i++) {
        if (i >= oldWord.length || oldWord[i] !== currentWord[i]) {
            newLetterIndex = i;
            break;
        }
    }
    
    if (newLetterIndex === -1 || newLetterIndex >= currentWord.length - 1) {
        newLetterIndex = currentWord.length - 1;
    }
}

// Validate and submit a guess
function submitGuess() {
    if (gameOver) return;
    
    const guess = currentGuess.toLowerCase().trim();
    
    // Validate guess length
    if (guess.length !== currentWord.length) {
        showMessage(`Please enter a ${currentWord.length}-letter word`, 'error');
        return;
    }
    
    // Validate it's a real word
    if (!validWords.has(guess)) {
        showMessage('Not a valid word', 'error');
        return;
    }
    
    // Calculate colors
    const colors = getColors(guess, currentWord);
    
    // Store the guess
    const guessData = {
        word: guess,
        colors: colors,
        newLetterPos: newLetterIndex
    };
    guesses.push(guessData);
    
    // Update keyboard colors
    updateKeyboardColors(guess, colors);
    
    // Clear current guess
    currentGuess = '';
    
    // Check for win
    if (guess === currentWord) {
        gameOver = true;
        renderBoard();
        const tries = turn === 0 ? 'try' : 'tries';
        showMessage(`Congrats! You beat Addle in ${turn + 1} ${tries}!`, 'success');
        showGameSummary();
        document.getElementById('giveUpBtn').style.display = 'none';
        document.getElementById('newGameBtn').style.display = 'block';
        return;
    }
    
    // Increment turn
    turn++;
    
    // Check if we should add a letter
    if (shouldAddLetter()) {
        addLetter();
        showMessage(`New letter added! Now guess the ${currentWord.length}-letter word`, 'info');
    } else {
        showMessage(`Guess the ${currentWord.length}-letter word`, 'info');
    }
    
    // Reset new letter indicator after showing it once
    if (turn % 3 !== 0) {
        newLetterIndex = -1;
    }
    
    renderBoard();
}

// Calculate colors for a guess (Wordle logic)
function getColors(guess, target) {
    const colors = new Array(guess.length).fill('x');
    const targetLetters = target.split('');
    const used = new Array(target.length).fill(false);
    
    // First pass: mark correct positions (green)
    for (let i = 0; i < guess.length; i++) {
        if (guess[i] === target[i]) {
            colors[i] = 'g';
            used[i] = true;
        }
    }
    
    // Second pass: mark present but wrong position (yellow)
    for (let i = 0; i < guess.length; i++) {
        if (colors[i] === 'g') continue;
        
        for (let j = 0; j < target.length; j++) {
            if (!used[j] && guess[i] === target[j]) {
                colors[i] = 'y';
                used[j] = true;
                break;
            }
        }
    }
    
    return colors;
}

// Show a message to the user
function showMessage(text, type = 'info') {
    const messageEl = document.getElementById('message');
    messageEl.textContent = text;
    messageEl.className = `message ${type}`;
}

// Show game summary at the end
function showGameSummary() {
    setTimeout(() => {
        const summary = wordSequence.join(' → ');
        showMessage(`Word sequence: ${summary}`, 'info');
    }, 2000);
}

// Build the on-screen keyboard
function buildKeyboard() {
    const keyboard = document.getElementById('keyboard');
    keyboard.innerHTML = '';
    
    const rows = [
        ['Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P'],
        ['A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L'],
        ['ENTER', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '⌫']
    ];
    
    rows.forEach(rowKeys => {
        const row = document.createElement('div');
        row.className = 'keyboard-row';
        
        rowKeys.forEach(key => {
            const button = document.createElement('button');
            button.className = 'key';
            button.textContent = key;
            button.dataset.key = key;
            
            if (key === 'ENTER' || key === '⌫') {
                button.classList.add('large');
            }
            
            // Apply color state if exists
            if (keyboardState[key.toLowerCase()]) {
                button.classList.add(keyboardState[key.toLowerCase()]);
            }
            
            button.addEventListener('click', () => handleKeyPress(key));
            row.appendChild(button);
        });
        
        keyboard.appendChild(row);
    });
}

// Update keyboard colors after a guess (only green and yellow, NO gray)
function updateKeyboardColors(guess, colors) {
    for (let i = 0; i < guess.length; i++) {
        const letter = guess[i].toLowerCase();
        const color = colors[i];
        
        // Only update if green or yellow (skip gray)
        if (color === 'g') {
            keyboardState[letter] = 'correct';
        } else if (color === 'y' && keyboardState[letter] !== 'correct') {
            keyboardState[letter] = 'present';
        }
        // Do NOT update for gray (x) - this is the key difference
    }
    
    buildKeyboard();
}

// Handle keyboard key press
function handleKeyPress(key) {
    if (gameOver) return;
    
    if (key === 'ENTER') {
        submitGuess();
    } else if (key === '⌫') {
        if (currentGuess.length > 0) {
            currentGuess = currentGuess.slice(0, -1);
            renderBoard();
        }
    } else {
        if (currentGuess.length < currentWord.length) {
            currentGuess += key.toLowerCase();
            renderBoard();
        }
    }
}

// Handle physical keyboard input
function handlePhysicalKeyboard(e) {
    if (gameOver) return;
    
    const key = e.key.toUpperCase();
    
    if (key === 'ENTER') {
        submitGuess();
    } else if (key === 'BACKSPACE') {
        if (currentGuess.length > 0) {
            currentGuess = currentGuess.slice(0, -1);
            renderBoard();
        }
    } else if (key.length === 1 && key >= 'A' && key <= 'Z') {
        if (currentGuess.length < currentWord.length) {
            currentGuess += key.toLowerCase();
            renderBoard();
        }
    }
}

// Give up and reveal the word sequence
function giveUp() {
    if (gameOver) return;
    
    gameOver = true;
    
    document.getElementById('giveUpBtn').style.display = 'none';
    document.getElementById('newGameBtn').style.display = 'block';
    
    // Show the current word and full sequence
    const summary = wordSequence.join(' → ');
    showMessage(`The word was: ${currentWord.toUpperCase()}`, 'error');
    
    // Add a visual display of the full word sequence on the board
    setTimeout(() => {
        showMessage(`Full sequence: ${summary}`, 'info');
    }, 1500);
}

// Event listeners
document.addEventListener('keydown', handlePhysicalKeyboard);
document.getElementById('giveUpBtn').addEventListener('click', giveUp);
document.getElementById('newGameBtn').addEventListener('click', () => {
    location.reload();
});

// Start the game
initGame();
