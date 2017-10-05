#include "meruvia.h"

int         nb_shuriken;
GameObject  shurikens[SHURIKEN_MAX];
SDL_Texture *shuriken_texture;

void        load_shuriken(void)
{
    if (!(shuriken_texture = load_image(SHURIKEN_SPRITE)))
    {
        printf("Error while loading shuriken sprite : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

}


void        clean_shuriken(void)
{
    if (shuriken_texture)
        SDL_DestroyTexture(shuriken_texture);
    shuriken_texture = NULL;
}

int         get_shuriken_nb(void)
{
    return (nb_shuriken);
}

void        reset_shuriken(void)
{
    nb_shuriken = 0;
}

void        create_shuriken(void)
{
    GameObject  *new;

    if (nb_shuriken < SHURIKEN_MAX)
    {
        new = &shurikens[nb_shuriken];

        SDL_QueryTexture(shuriken_texture, NULL, NULL, &new->state.w, &new->state.h); 
        new->rotation   = 0;
        new->center.x   = 10;
        new->center.y   = 10;
        
        if (get_player_direction() == RIGHT)
        {
            new->state.x            = get_player_sate().x + 15;
            new->state.y            = get_player_sate().y + 20;
            new->direction          = RIGHT;
        }
        else
        {
            new->state.x            = get_player_sate().x - 15;
            new->state.y            = get_player_sate().y + 20;
            new->direction          = LEFT;
        }
        nb_shuriken++;
    }
    new = NULL;
}

void        update_shuriken(void)
{
    int     i;

    for(i = 0; i < nb_shuriken; i++)
    {
        if (shurikens[i].direction == RIGHT)
            shurikens[i].state.x += 10;
        else
            shurikens[i].state.x -= 10;
        
        shurikens[i].rotation += 20; 
        if (shurikens[i].rotation >= 360)
            shurikens[i].rotation = 0;

        if (shurikens[i].state.x < get_start().x || shurikens[i].state.x > get_start().x + WIDTH)
        {
            shurikens[i] = shurikens[nb_shuriken - 1];
            nb_shuriken--;
        }

    }
}

void        draw_shuriken(void)
{
    int         i;
    GameObject  *current;

    for(i = 0; i < nb_shuriken; i++)
    {
        current = &shurikens[i];
        draw_image_plus(shuriken_texture, current->state.x - get_start().x, current->state.y - get_start().y, current->rotation, current->center, SDL_FLIP_NONE);

    }
    current = NULL;
}

char         shuriken_collide(GameObject *monster)
{
    int         i;
    GameObject  *current;

    for (i = 0; i< nb_shuriken; i++)
    {
        current = &shurikens[i];
        if (!(monster->state.x >= current->state.x + current->state.w
                || monster->state.x + monster->state.w <= current->state.x
                || monster->state.y >= current->state.y + current->state.h
                || monster->state.y + monster->state.h <= current->state.y
            ))
        {
            shurikens[i] = shurikens[nb_shuriken - 1];
            nb_shuriken--;
            return (1);
        }
    }
    current = NULL;
    return (0);
}
