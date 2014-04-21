#ifndef SPRITEFINDER_HPP_INCLUDED
#define SPRITEFINDER_HPP_INCLUDED



#endif // SPRITEFINDER_HPP_INCLUDED
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
#include <vector>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdint.h>
#include <iostream>
#include "spriteFinderUtils.hpp"
using namespace std;

std::vector<SDL_Rect>get_sprite_locations(const SDL_Surface& surf);
