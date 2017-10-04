#include "meruvia.h"


void        draw_tile(SDL_Texture *image, int destx, int desty, int srcx, int srcy)
{
    SDL_Rect    src;
    SDL_Rect    dest;

    dest.x      = destx;
    dest.y      = desty;
    dest.w      = TILE_SIZE;
    dest.h      = TILE_SIZE;

    src.x       = srcx;
    src.y       = srcy;
    src.w       = TILE_SIZE;
    src.h       = TILE_SIZE;

    SDL_RenderCopy(get_renderer(), image, &src, &dest);
}

void        draw(void)
{
    int     i;

    SDL_SetRenderDrawColor(get_renderer(), 0, 0, 0, 255);
    SDL_RenderClear(get_renderer());
    
    draw_image(get_background(), 0, 0);
    

    draw_map(2);
    draw_map(1);

    draw_player();

    for (i = 0; i < get_monsters_nb(); i++)
        draw_monster(get_monster(i));

    draw_map(3);


    SDL_RenderPresent(get_renderer());


    SDL_Delay(1);
}

SDL_Texture *load_image(char *name)
{
    SDL_Surface *loaded_img;
    SDL_Texture *texture;

    loaded_img = IMG_Load(name);
    if (!loaded_img)
    {
        printf("L'image n'a pas pu etre charger : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    texture = SDL_CreateTextureFromSurface(get_renderer(), loaded_img);

    SDL_FreeSurface(loaded_img);
    
    return (texture);
}

void        draw_image(SDL_Texture *img, int x, int y)
{
    SDL_Rect    dest;

    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(img, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(get_renderer(), img, NULL, &dest);
}

void        delay(unsigned int frame_limit)
{
    unsigned int ticks;
    
    ticks = SDL_GetTicks();

    if (frame_limit < ticks)
        return ;

    if (frame_limit > ticks + 16)
        SDL_Delay(16);
    else
        SDL_Delay(frame_limit - ticks);
}
