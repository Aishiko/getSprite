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

SDL_Rect GetSDL_Rect(int x,int y, int h, int w)
{
        /* Here we we take each value found and store them in
           our SDL_Rect, the idea is to fast and reuseable. */
        SDL_Rect Current_Sprite;
        Current_Sprite.x=x;
        Current_Sprite.y=y;
        Current_Sprite.h=h;
        Current_Sprite.w=w;
        return Current_Sprite;
}

bool compare_SDL_Colours(SDL_Colour border_colour,SDL_Colour comparision_colour)
{
    bool bool_value=0;          // Start with a false value
    if(border_colour.r == comparision_colour.r)
    {
        if(border_colour.g == comparision_colour.g)
        {
            if(border_colour.b == comparision_colour.b)
            {
                //if(border_colour.a == comparision_colour.a)  //commented out until I can figure out why its not happy with this
                //{
                    bool_value=1;               // only change to True after making sure each of the 3 values match, 4 if we get the alpha to work.
                //}
            }
        }
    }

    return bool_value;
}

void get_pixel_colours(const SDL_Surface& surf,Uint32& pixel,SDL_Colour& current_pixel_colours)
{
	SDL_PixelFormat *fmt;
	fmt = surf.format;      // we need the format to get the values for the mask, shift and loss of each colour
        Uint32 *ptr = (Uint32*)surf.pixels;    //set up to access the pixel data
        SDL_GetRGB(ptr[pixel],                // send pixel pointer with the value of the pixel the ptr is an array and needs to be accessed as one!
                fmt,                    // send format
                &current_pixel_colours.r,       // get and store the colour values in their SDL_Colour holder
                &current_pixel_colours.g,
                &current_pixel_colours.b);

	//cout << "Pixel Color -> R: "<< current_pixel_colours.r << "  G: "<< current_pixel_colours.g << "  B: " << current_pixel_colours.b << "\n";
	printf("Pixel Color -> R: %d,  G: %d,  B: %d\n", current_pixel_colours.r, current_pixel_colours.g, current_pixel_colours.b);
	return;
}
void set_pixel(const SDL_Surface& surf, int x, int y,Uint32& target_pixel)
{
        int lineoffset = y * (surf.w);         //set start of working row
        target_pixel=lineoffset+x;              // set target_pixel to the location in the image's array that we need
        /* since the pixels are in a line pixel 0,1 is actually pixel 640 on a 640x400 image
           so we need to take the row times the surface width and then add the column to get
           the pixel we need to get and assign to our location pixel of target_pixel.*/
        printf("Surface width is %d, Surface height is %d, X is %d, Y is %d\n",surf.w,surf.h,x,y);
        printf("Targeted Pixel is %d\n",target_pixel);
        return;
}

int get_height(const SDL_Surface& surf, int x, int y,SDL_Colour border_colour)
{
        int height=1;
        Uint32 pixel;
        SDL_Colour pixelColours;
                // Create and prime our loop to get the height
        set_pixel(surf,x,y,pixel);
        get_pixel_colours(surf, pixel, pixelColours);
        while(compare_SDL_Colours(border_colour,pixelColours)==0)
        {
                y++;
                set_pixel(surf,x,y,pixel);
                get_pixel_colours(surf, pixel, pixelColours);
                if(compare_SDL_Colours(border_colour,pixelColours)==0)
                {
                        height++;
                }
        }
        return height;
}

int get_width(const SDL_Surface& surf, int x, int y,SDL_Colour border_colour)
{
        int width=1;
        Uint32 pixel;
        SDL_Colour pixelColours;
                // Create and prime our loop to get the width
        set_pixel(surf,x,y,pixel);
        get_pixel_colours(surf, pixel, pixelColours);
        while(compare_SDL_Colours(border_colour,pixelColours)==0&&(x<surf.w))
        {
                x++;
                set_pixel(surf,x,y,pixel);
                get_pixel_colours(surf, pixel, pixelColours);
                if(compare_SDL_Colours(border_colour,pixelColours)==0)
                {
                        width++;
                }
        }
        return width;
}

int getRowLenght(const SDL_Surface& surf, int x, int y,SDL_Colour border_colour)
{
        int width=1;
        Uint32 pixel;
        SDL_Colour pixelColours;
                // Create and prime our loop to get the width
        set_pixel(surf,x,y,pixel);
        get_pixel_colours(surf, pixel, pixelColours);
        while(compare_SDL_Colours(border_colour,pixelColours)&&(x<surf.w))
        {
                x++;
                set_pixel(surf,x,y,pixel);
                get_pixel_colours(surf, pixel, pixelColours);
                if(compare_SDL_Colours(border_colour,pixelColours))
                {
                        width++;
                }
        }
        return width;
}
