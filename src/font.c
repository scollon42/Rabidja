#include "meruvia.h"

TTF_Font    *font;


void        load_font(char *name, int size)
{
    if (!(font = TTF_OpenFont(name, size)))
    {
        printf("Failed to load font %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

}

void        close_font()
{
    if (font)
        TTF_CloseFont(font);
}

void        draw_string(char *str, SDL_Point pos, SDL_Color rgba)
{

    SDL_Rect        dst;
    SDL_Surface     *surface;
    SDL_Texture     *texture;
    

    if (!(surface = TTF_RenderUTF8_Blended(font, str, rgba)))
    {
        printf("Error while draw string %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    if (!(texture = SDL_CreateTextureFromSurface(get_renderer(), surface)))
    {
        SDL_FreeSurface(surface);
        printf("Error while draw string %s\n", SDL_GetError());    
        exit(EXIT_FAILURE);
    }

    SDL_FreeSurface(surface);
    surface = NULL;

    dst.x = pos.x;
    dst.y = pos.y;

    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(get_renderer(), texture, NULL, &dst);

    SDL_DestroyTexture(texture);
}
