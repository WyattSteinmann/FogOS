#include "stdlib.h"
#include "ports.h"
#include "types.h"

#define MAX_INPUT_LENGTH 2048 // Maximum length of the input string

// Static buffer to hold the string
char inputBuffer[MAX_INPUT_LENGTH];

// Keyboard scancode to ASCII mapping
char characterTable[] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0, // 0x00-0x0E
    9, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', 0, 0,  // 0x0F-0x1E
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', // 0x1F-0x2E
    'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ',     // 0x2F-0x3E
};

// Shifted key mappings
char shiftedCharacterTable[] = {
    0, 27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', 0, // 0x00-0x0E
    9, 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', 0, 0,  // 0x0F-0x1E
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~', 0, '|',   // 0x1F-0x2E
    'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0, '*', 0, ' ',     // 0x2F-0x3E
};

bool shifted = false;
bool capsLocked = false;

// Read a scancode from the keyboard
uint8 kbReadScancode()
{
    while (!(inportb(0x64) & 1))
        ; // Wait for the keyboard buffer to be ready
    return inportb(0x60);
}

// Handle keyboard events and print characters
void handleKeyboardEvent()
{
    uint8 scancode = kbReadScancode();

    // Check for key release events
    if (scancode & 0x80)
    {
        scancode &= 0x7F;                         // Clear the key release bit
        if (scancode == 0x2A || scancode == 0x36) // Shift release
            shifted = false;
        return;
    }

    // Check for special keys (Shift, Caps Lock)
    switch (scancode)
    {
    case 0x2A:
    case 0x36: // Shift press
        shifted = true;
        return;
    case 0x3A: // Caps Lock
        capsLocked = !capsLocked;
        return;
    }
}

// Read input from the keyboard and store it in the input buffer
string readline()
{
    uint8 i = 0;
    uint8 scancode;
    char character;

    while (1)
    {
        scancode = kbReadScancode(); // Read scancode from the keyboard

        // Handle key release events (skip them)
        if (scancode & 0x80)
        {
            scancode &= 0x7F;                         // Clear the key release bit
            if (scancode == 0x2A || scancode == 0x36) // Shift release
                shifted = false;
            continue;
        }

        // Handle the Enter key (when pressed, return the input)
        if (scancode == 0x1C) // Enter key
        {
            inputBuffer[i] = '\0'; // Null-terminate the string
            printc('\n');          // Print newline for better UX
            return inputBuffer;    // Return the input string
        }

        // Handle Backspace (remove the last character if pressed)
        if (scancode == 0x0E) // Backspace key
        {
            if (i > 0)
            {
                i--;
                // Print backspace and overwrite the character on screen
                printc('\b');
            }
            continue;
        }

        // Handle Shift key press and toggle shifted state
        if (scancode == 0x2A || scancode == 0x36) // Shift press
        {
            shifted = true;
            continue;
        }

        // Handle Caps Lock key press and toggle caps lock state
        if (scancode == 0x3A) // Caps Lock
        {
            capsLocked = !capsLocked;
            continue;
        }

        // Handle printable characters
        if (scancode < sizeof(characterTable))
        {
            // Map the scancode to the correct character
            if (shifted)
                character = shiftedCharacterTable[scancode];
            else
                character = characterTable[scancode];

            // Handle caps lock (convert to uppercase if needed)
            if (capsLocked && character >= 'a' && character <= 'z')
                character -= 32;

            if (character)
            {
                inputBuffer[i++] = character; // Append character to buffer
                printc(character);            // Print the character on the screen
                if (i >= MAX_INPUT_LENGTH - 1)
                {
                    inputBuffer[i] = '\0'; // Null-terminate the string
                    return inputBuffer;    // Return if max length reached
                }
            }
        }
    }
}

// Like Readline, But For Text Editors
void EDITOR_readline()
{
    uint8 scancode;
    char character;

    while (1)
    {
        scancode = kbReadScancode(); // Read scancode from the keyboard

        if (scancode == 0x01)
        {
            return;
        }

        // Handle key release events (skip them)
        if (scancode & 0x80)
        {
            scancode &= 0x7F;                         // Clear the key release bit
            if (scancode == 0x2A || scancode == 0x36) // Shift release
                shifted = false;
            continue;
        }

        // Handle the Enter key (when pressed, return the input)
        if (scancode == 0x1C) // Enter key
        {
            printc('\n'); // Print newline for better UX
        }

        // Handle Backspace (remove the last character if pressed)
        if (scancode == 0x0E) // Backspace key
        {
            // Print backspace and overwrite the character on screen
            printc('\b');
            continue;
        }

        // Handle Shift key press and toggle shifted state
        if (scancode == 0x2A || scancode == 0x36) // Shift press
        {
            shifted = true;
            continue;
        }

        // Handle Caps Lock key press and toggle caps lock state
        if (scancode == 0x3A) // Caps Lock
        {
            capsLocked = !capsLocked;
            continue;
        }

        // Handle printable characters
        if (scancode < sizeof(characterTable))
        {
            // Map the scancode to the correct character
            if (shifted)
                character = shiftedCharacterTable[scancode];
            else
                character = characterTable[scancode];

            // Handle caps lock (convert to uppercase if needed)
            if (capsLocked && character >= 'a' && character <= 'z')
                character -= 32;

            if (character)
            {
                printc(character);
            }
        }
    }
}
