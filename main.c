#include <gb/gb.h>
#include <stdio.h>
#include <gb/drawing.h>
#include "headers/snakeSprite.h"

uint8_t spriteX, spriteY;
int8_t velocityX, velocityY;
uint8_t joypadCurrent = 0, joypadPrevious = 0;
char coordX[2] = "x";
char coordY[2] = "y";

//Returns a 3 digit number so x and y co-ordinates are displayed on scene correctly
char getCoordinateString(const char* coordinate, uint8_t number) { //note: In using const char* we are declaring coordinate is a pointer
    if (number < 100) {
        return gprintf("%s:0%u", coordinate, number);
    } else
        return gprintf("%s:%u", coordinate, number);
}

void main(void)
{
    SHOW_SPRITES;
    DISPLAY_ON;

    set_sprite_data(0, 1, snakeSprite);
    set_sprite_tile(0, 0);
    move_sprite(0, 84, 88); // center sprite

    // set default position
    spriteX = 80;
    spriteY = 72;

    // set default velocity
    velocityX = 0;
    velocityY = 0;


    // main game loop
    while (1)
    {   
        //draw x and y coordinates of the player position (debugging)
        gotogxy(0, 0);
        getCoordinateString(coordX, spriteX);
        gotogxy(0, 1);
        getCoordinateString(coordY, spriteY);

        //move player to opposite side of screen if they move off screen
        if (spriteX > 165)
        {
            spriteX = 1;
        }
        if (spriteX < 1)
        {
            spriteX = 164;
        }
        if (spriteY > 145) {
            spriteY = 1;
        }
        if (spriteY < 1) {
            spriteY = 144;
        }

        // apply velocity
        spriteX += velocityX;
        spriteY += velocityY;

        move_sprite(0, spriteX + 4, spriteY + 12);


        //todo: move player movement to seperate file
        joypadPrevious = joypadCurrent;
        joypadCurrent = joypad();

        if (joypadCurrent & J_RIGHT)
        {
            velocityX = 1;
        }
        else if (joypadCurrent & J_LEFT)
        {
            velocityX = -1;
        }
        else
        {
            velocityX = 0;
        }

        if (joypadCurrent & J_DOWN)
        {
            velocityY = 1;
        }
        else if (joypadCurrent & J_UP)
        {
            velocityY = -1;
        }
        else
        {
            velocityY = 0;
        }
    
        wait_vbl_done();
    }
}