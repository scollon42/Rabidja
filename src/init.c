#include "meruvia.h"

SDL_Window      *screen;
SDL_Renderer    *renderer;


SDL_Renderer    *get_renderer(void)
{
    return (renderer);
}

void            load(void)
{
    init_maps();

    init_monster_sprite();
    init_player_sprite();

    set_level_value(2);
    change_level();

    set_nb_life(3);
    set_nb_star(0);

    init_ui();

    load_bg_music(BG_MUSIC);
    load_sound();
}

void            init(char *title)
{
    screen  = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (!screen)
    {
		printf("Impossible d'initialiser le mode écran à %d x %d: %s\n", WIDTH, HEIGHT, SDL_GetError());
        exit(EXIT_FAILURE);
    }

    renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
    {
		printf("Impossible de creer le renderer %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        printf( "SDL_image n'a pu être initialisée! SDL_image Error: %s\n", IMG_GetError() );
        exit(EXIT_FAILURE);
    }
    if (TTF_Init() < 0)
    { 
        printf("Impossible d'initialiser SDL TTF: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    
    load_font(FONT, 32);

    if ((Mix_Init(MIX_INIT_FLAC) & MIX_INIT_FLAC) != MIX_INIT_FLAC)
    {
        printf("Mix_Init: Failed to init SDL_Mixer\n");
        printf("Mix_Init: %s\n", Mix_GetError());
        exit(EXIT_FAILURE);
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
    {
        printf("Mix_OpenAudio: %s\n", Mix_GetError());
        exit(EXIT_FAILURE);
    }
    Mix_AllocateChannels(32);

}

void            cleanup(void)
{
    clean_maps();
    clean_monsters();
    clean_player();
    clean_ui();
    clean_music();
    free_sound();
    Mix_CloseAudio();
    Mix_Quit();

    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(screen);
    screen = NULL;

    TTF_Quit();
    SDL_Quit();
}


