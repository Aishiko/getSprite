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
#include "spriteFinder.hpp"
using namespace std;

std::vector<SDL_Rect>get_sprite_locations(const SDL_Surface& surf)
{
        bool skip=0;
        Uint32 pixel;
	set_pixel(surf,0,0,pixel);	//set the current pixel to the first pixel
        SDL_Colour current_pixel_colour,
		last_pixel,
		nextRowPixel;

	get_pixel_colours(surf,pixel,current_pixel_colour);	// read pixel 0,0 for the border colour and make constant
	const SDL_Colour border_colour = current_pixel_colour;
        last_pixel=current_pixel_colour;                        // we need to this for control

	std::vector<SDL_Rect> sprite_locations;	// decalre our vector that will hold all our found sprites
	int current_X=0,		//Delcaring our control variables for row and column
		current_Y=0,
//		last_row=0,
//		last_column=0,
		working_X=0,
		next_Y=0,
		width=0,
		height=0,
		rowLenght;
        set_pixel(surf,1,0,pixel);
        get_pixel_colours(surf,pixel,current_pixel_colour);
	if(compare_SDL_Colours(border_colour,current_pixel_colour))
	{
		cout << "Error message malformed spritesheet no border colour detected!";
		skip=1;
		printf("Skipping everything... Bad program! bad spritesheet!  bad lazy artist!\n");
	}
	while(skip!=1)
	{
	        current_Y++;
	        rowLenght=getRowLenght(surf, current_X, current_Y, border_colour);
	        current_Y++;
	        set_pixel(surf,current_X,current_Y,pixel);
	        get_pixel_colours(surf,pixel,current_pixel_colour);
	        //Set up and make sure that the rowLenght is the rowlenght as it might not be.
	        set_pixel(surf,rowLenght,current_Y+1,pixel);
	        get_pixel_colours(surf,pixel,nextRowPixel);
	        if(compare_SDL_Colours(border_colour,nextRowPixel)==0)
	        {
	                while(compare_SDL_Colours(border_colour,nextRowPixel)==0)
	                {
	                        rowLenght--;
	                        set_pixel(surf,rowLenght,current_Y+1,pixel);
                                get_pixel_colours(surf,pixel,nextRowPixel);
	                }
	        }
	        last_pixel=current_pixel_colour;
	        working_X++;
	        while(rowLenght<=working_X)
	        {
	                set_pixel(surf,working_X,current_Y,pixel);
	                get_pixel_colours(surf,pixel,current_pixel_colour);
	                // If the last pixel was a border colour pixel and the current pixel is not start counting!
	                if(compare_SDL_Colours(border_colour,last_pixel)&&(compare_SDL_Colours(border_colour,current_pixel_colour)==0))
	                {
	                        width=get_width(surf,working_X,current_Y,border_colour);
	                        height=get_height(surf,working_X,current_Y,border_colour);
	                        sprite_locations.push_back(GetSDL_Rect(working_X,current_Y, height, width));
	                        working_X=+width+1;
	                        next_Y=height+current_Y;
	                }
	                working_X++;
	        }
	        current_Y=next_Y;
	        if(((current_Y-5)>surf.w)||(rowLenght==0))
	        {
	                skip=1;
	        }
	}
	return sprite_locations;
}
