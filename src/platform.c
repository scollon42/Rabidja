# include "meruvia.h"

GameObject  platforms[PLATFORMES_MAX];
SDL_Texture *platform_texture;
int         nb_platforms;

void        load_platform(void)
{
    if (!(platform_texture = load_image(PLATFORM_SPRITE)))
    {
        printf("Unable to load platform sprite %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

}

void        clean_platform(void)
{
    if (platform_texture)
        SDL_DestroyTexture(platform_texture);
    platform_texture = NULL;
}

int         get_platform_nb(void)
{
    return (nb_platforms);
}

void        reset_platforms(void)
{
    nb_platforms = 0;
}

void        init_platform(SDL_Point pos, char type)
{
    GameObject  *new;

    nb_platforms++;

    if (nb_platforms > PLATFORMES_MAX)
        exit(EXIT_FAILURE);

    new = &platforms[nb_platforms];

    new->state.x = pos.x;
    new->state.y = pos.y;
    new->begin.x = pos.x;
    new->begin.y = pos.y;

    SDL_QueryTexture(platform_texture, NULL, NULL, &new->state.w,  &new->state.h);
    new->platform_type = type;

    if (new->platform_type == 2)
        new->direction = UP;
    else
        new->direction = RIGHT;
}

void        update_platforms(void)
{
    int         i;
    SDL_Point   player;

    for (i = 1 ; i <= nb_platforms ; i++)
    {
        if (platforms[i].platform_type == 2)
        {
            if (platforms[i].direction == UP)
            {
                platforms[i].state.y -= PLATFORM_SPEED;

                if (platforms[i].hero_on_it == 1)
                {
                    player = get_player_state_xy();
                    set_player_state_xy((SDL_Point){ .x = player.x, .y = player.y - PLATFORM_SPEED });
                }
            }
            else
            {
                platforms[i].state.y += PLATFORM_SPEED;

                if (platforms[i].hero_on_it == 1)
                {
                    player = get_player_state_xy();
                    set_player_state_xy((SDL_Point){ .x = player.x, .y = player.y + PLATFORM_SPEED });
                }
            }

            if (platforms[i].state.y > platforms[i].begin.y + 5 * TILE_SIZE)
                platforms[i].direction = UP;

            if (platforms[i].state.y < platforms[i].begin.y)
                platforms[i].direction = DOWN;
        }
        else
        {
            if (platforms[i].direction == RIGHT)
            {
                platforms[i].state.x += PLATFORM_SPEED;

                if (platforms[i].hero_on_it == 1)
                {
                    player = get_player_state_xy();
                    set_player_state_xy((SDL_Point){ .x = player.x + PLATFORM_SPEED, .y = player.y });
                }
            }
            else
            {
                platforms[i].state.x -= PLATFORM_SPEED;

                if (platforms[i].hero_on_it == 1)
                {
                    player = get_player_state_xy();
                    set_player_state_xy((SDL_Point){ .x = player.x - PLATFORM_SPEED, .y = player.y });
                }
            }

            if (platforms[i].state.x> platforms[i].begin.x + 5 * TILE_SIZE)
                platforms[i].direction = LEFT;

            if (platforms[i].state.x< platforms[i].begin.x)
                platforms[i].direction = RIGHT;
        }
    }
}

void        draw_platforms(void)
{
    int     i;

    for (i = 1; i <= nb_platforms; i++)
        draw_image(platform_texture, platforms[i].state.x- get_start().x, platforms[i].state.y - get_start().y);
}

void        collisions_with_platform(GameObject *entity)
{
    int     i;

    for (i = 1 ; i <= nb_platforms ; i++)
    {
        if ((entity->state.x + entity->state.w >= platforms[i].state.x)
                && (entity->state.x <= platforms[i].state.x + platforms[i].state.w)
                && (entity->state.y + entity->state.h >= platforms[i].state.y)
                && (entity->state.y + entity->state.h < platforms[i].state.y + 32))
        {
            entity->state.y = platforms[i].state.y - entity->state.h;
            entity->dir.y = 0;
            entity->on_ground = 1;
            platforms[i].hero_on_it = 1;
        }
        else
        {
            platforms[i].hero_on_it = 0;
        }
    }
}
