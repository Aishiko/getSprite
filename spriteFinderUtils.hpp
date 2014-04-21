/*GetSprite, it finds and returns all found Sprites in spritesheet
    Copyright (C) 2014  Aishiko

    This program is free software: you can redistribute it and/or modify
    it under the terms of the License.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    License for more details.

    You should have received a copy of the License
    along with this program.  If not, see <https://github.com/Aishiko/getSprite/blob/master/Lincense>*/
#ifndef SPRITEFINDERUTILS_HPP_INCLUDED
#define SPRITEFINDERUTILS_HPP_INCLUDED
#endif // SPRITEFINDERUTILS_HPP_INCLUDED
/*#include <vector>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdint.h>
#include <iostream>
#include "spriteFinderUtils.hpp"
using namespace std;*/


// Get one of the SDL_Rects that will be stored
SDL_Rect GetSDL_Rect(int x,int y, int h, int w);

// We need to create our own program to compare the colours since we can't do it anyother way
bool compare_SDL_Colours(SDL_Colour border_colour,SDL_Colour comparision_colour);

void get_pixel_colours(const SDL_Surface& surf,Uint32& pixel,SDL_Colour& current_pixel_colours);

void set_pixel(const SDL_Surface& surf, int x, int y,Uint32& target_pixel);

int get_height(const SDL_Surface& surf, int x, int y,SDL_Colour border_colour);

int get_width(const SDL_Surface& surf, int x, int y,SDL_Colour border_colour);

int getRowLenght(const SDL_Surface& surf, int x, int y,SDL_Colour border_colour);
