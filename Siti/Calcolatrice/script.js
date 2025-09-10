const display = document.getElementById('display');
const buttons = document.querySelectorAll('button');

let input = '';
let badInput = false;

function updateDisplay() {
    display.value = input;
}

function calculate() {
    try {
        const expression = input.replace(/x/g, '*').replace(/÷/g, '/');
        const result = eval(expression);

        if (!isFinite(result) || isNaN(result)) {
            throw new Error('Invalid calculation');
        }

        input = result.toString();
        updateDisplay();
    } catch (error) {
        input = error;
        badInput = true;
        updateDisplay();
    }
}


function toggleSign() {
    if (input) {
        if (input.startsWith('-')) {
            input = input.slice(1);
        } else {
            input = '-' + input;
        }
        updateDisplay();
    }
}

function applyPercentage() {
    try {
        input = (eval(input) / 100).toString();
        updateDisplay();
    } catch {
        badInput = true;
        input = 'Error';
        updateDisplay();
    }
}

function backspace() {
    input = input.slice(0, -1);
    updateDisplay();
}

buttons.forEach(button => {
    button.addEventListener('click', () => {
        const value = button.textContent;

        if (badInput) {
            input = '';
            badInput = false;
            updateDisplay();
        }

        switch (value) {
            case '=':
                calculate();
                break;
            case 'C':
                input = '';
                updateDisplay();
                break;
            case '←':
                backspace();
                break;
            case '+/-':
                toggleSign();
                break;
            case '%':
                applyPercentage();
                break;
            default:
                input += value;
                updateDisplay();
        }
    });
});

// Optional: Keyboard support
document.addEventListener('keydown', (e) => {
    const key = e.key;

    if (badInput) {
        input = '';
        badInput = false;
        updateDisplay();
    }

    if (key === 'Enter') {
        calculate();
    } else if (key === 'Escape') {
        input = '';
        updateDisplay();
    } else if (key === 'Backspace') {
        backspace();
    } else if (!isNaN(key) || ['+', '-', '*', '/', '.', '%'].includes(key)) {
        input += key;
        updateDisplay();
    }
});
