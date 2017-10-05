#include "meruvia.h"

SDL_Texture *UI_life;
SDL_Texture *UI_star;

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

void        draw_image_plus(SDL_Texture *img, int x, int y, double rotation, SDL_Point center, SDL_RendererFlip flip)
{
    SDL_Rect    dst;

    dst.x = x;
    dst.y = y;

    SDL_QueryTexture(img, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopyEx(get_renderer(), img, NULL, &dst, rotation, &center, flip);
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

    draw_platforms();

    draw_shuriken();

    draw_map(3);

    draw_ui();

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

void        init_ui(void)
{
    UI_life = load_image(LIFE_SPRITE);
    UI_star = load_image(STAR_SPRITE);
}

void        clean_ui(void)
{
    if (UI_life)
        SDL_DestroyTexture(UI_life);
    if (UI_star)
        SDL_DestroyTexture(UI_star);

    UI_life = NULL;
    UI_star = NULL;
}

void        draw_ui(void)
{
    char        text[200];
    int         i;
    SDL_Point   src;

    for (i = 0 ; i < get_life() ; i++)
    {
        src.y   = TILE_PWUP_HEART / 10 * TILE_SIZE;
        src.x   = TILE_PWUP_HEART % 10 * TILE_SIZE;
        draw_tile(get_tile_set_a(), 60 + i * 32, 20, src.x, src.y);
    }

    draw_image(UI_life, WIDTH - 120, HEIGHT - 70);
    sprintf(text, "x %d", get_nb_life());
    
    draw_string(text, (SDL_Point) { .x = WIDTH - 80, .y = HEIGHT - 60}, (SDL_Color){ .r = 0, .g = 0, .b = 0, .a = 255 });
    draw_string(text, (SDL_Point) { .x = WIDTH - 82, .y = HEIGHT - 62}, (SDL_Color){ .r = 255, .g = 255, .b = 255, .a = 255 });
    draw_image(UI_star, 60, 60);
    sprintf(text, "%d", get_nb_star());
    draw_string(text, (SDL_Point){ .x = 100, .y = 57 }, (SDL_Color){.r = 0, .g = 0, .b = 0, .a = 255});
    draw_string(text, (SDL_Point){ .x = 98, .y = 55 }, (SDL_Color){.r = 255, .g = 255, .b = 255, .a = 255});
}
