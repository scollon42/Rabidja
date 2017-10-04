#include "meruvia.h"

Mix_Chunk   *bumper_sound;
Mix_Chunk   *destroy_sound;
Mix_Chunk   *jump_sound;
Mix_Chunk   *star_sound;

Mix_Music   *bg_music;


void        load_bg_music(char *filename)
{
    if (bg_music)
    {
        Mix_HaltMusic();
        Mix_FreeMusic(bg_music);
    }

    if (!(bg_music = Mix_LoadMUS(filename)))
    {
        printf("Cant load music %s\n", Mix_GetError());
        exit(EXIT_FAILURE);
    }

    if (Mix_PlayMusic(bg_music, -1) == -1)
        printf("Music cant be played : %s\n", Mix_GetError());
}

void        clean_music(void)
{
    if (bg_music)
        Mix_FreeMusic(bg_music);
    bg_music = NULL;
}

void        load_sound(void)
{
    bumper_sound        = Mix_LoadWAV(BUMPER_SOUND);
    destroy_sound       = Mix_LoadWAV(DESTROY_SOUND);
    jump_sound          = Mix_LoadWAV(JUMP_SOUND);
    star_sound          = Mix_LoadWAV(STAR_SOUND);

    if (!bumper_sound || !destroy_sound || !jump_sound || !star_sound)
    {
        printf("Cant read one the sound : %s\n", Mix_GetError());
        exit(EXIT_FAILURE);
    }
}

void        free_sound(void)
{
    Mix_FreeChunk(bumper_sound);
    Mix_FreeChunk(destroy_sound);
    Mix_FreeChunk(jump_sound);
    Mix_FreeChunk(star_sound);
}


void        play_fx(int type)
{
    switch (type)
    {
 
        case BUMPER:
            Mix_PlayChannel(-1, bumper_sound, 0);
            break;
 
        case DESTROY:
            Mix_PlayChannel(-1, destroy_sound, 0);
            break;
 
        case JUMP:
            Mix_PlayChannel(-1, jump_sound, 0);
            break;

        case STAR:
            Mix_PlayChannel(-1, star_sound, 0);
            break;
    } 
}
