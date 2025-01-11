#include "stdlib.h"
#include "ports.h"

const static size_t NUM_COLS = 80;
const static size_t NUM_ROWS = 25;

struct Char
{
    uint8_t character;
    uint8_t color;
};

struct Char *buffer = (struct Char *)0xb8000;
size_t col = 0;
size_t row = 0;
uint8_t color = COLOR_WHITE | COLOR_BLACK << 4;

void updateCursor()
{
    unsigned temp = row * NUM_COLS + col; // Corrected cursor calculation

    outportb(0x3D4, 14);          // Send high byte of cursor position
    outportb(0x3D5, temp >> 8);   // High 8 bits
    outportb(0x3D4, 15);          // Send low byte of cursor position
    outportb(0x3D5, temp & 0xFF); // Low 8 bits
}

void clear_row(size_t row)
{
    struct Char empty = (struct Char){
        character : ' ',
        color : color,
    };

    for (size_t col = 0; col < NUM_COLS; col++)
    {
        buffer[col + NUM_COLS * row] = empty;
    }
}

void clear_console()
{
    for (size_t i = 0; i < NUM_ROWS; i++)
    {
        clear_row(i);
    }
    col = 0;
    row = 0;
    updateCursor();
}

void print_newline()
{
    col = 0;

    if (row < NUM_ROWS - 1)
    {
        row++;
    }
    else
    {
        // Scroll the screen up by 1 row
        for (size_t r = 1; r < NUM_ROWS; r++)
        {
            for (size_t c = 0; c < NUM_COLS; c++)
            {
                buffer[c + NUM_COLS * (r - 1)] = buffer[c + NUM_COLS * r];
            }
        }
        clear_row(NUM_ROWS - 1); // Clear the last row
    }

    updateCursor();
}

void printc(char character)
{
    if (character == '\n')
    {
        print_newline();
        return;
    }

    if (character == '\b')
    {
        if (col > 0)
        {
            col--;
        }
        else if (row > 0)
        {
            row--;
            col = NUM_COLS - 1;
        }
        buffer[col + NUM_COLS * row] = (struct Char){' ', color}; // Clear character
        updateCursor();
        return;
    }

    if (col >= NUM_COLS)
    {
        print_newline();
    }

    buffer[col + NUM_COLS * row] = (struct Char){
        character : (uint8_t)character,
        color : color,
    };

    col++;
    updateCursor();
}

void prints(char *str)
{
    for (size_t i = 0; 1; i++)
    {
        char character = (uint8_t)str[i];

        if (character == '\0')
        {
            return;
        }

        printc(character);
    }
}

void set_console_color(uint8_t foreground, uint8_t background)
{
    color = foreground + (background << 4);
}
