#include "meruvia.h"

GameObject  monsters[MONSTER_MAX];
int         nb_monsters;
SDL_Texture *monster_sprite;

GameObject      *get_monster(int nb)
{
    if (nb >= nb_monsters || nb >= MONSTER_MAX)
        return (NULL);

    return (&monsters[nb]);
}

void            init_monster_sprite(void)
{
    monster_sprite = load_image(MONSTER_SPRITE);
}

int             get_monsters_nb(void)
{
    return (nb_monsters);
}

void            reset_monsters(void)
{
    nb_monsters = 0;
}

void            clean_monsters(void)
{
    if (monster_sprite)
        SDL_DestroyTexture(monster_sprite);
    monster_sprite = NULL;
}

void            new_monster(int x, int y)
{
    GameObject  *new;

    if (nb_monsters < MONSTER_MAX)
    {
        new  = &monsters[nb_monsters];

        new->frame_number = 0;
        new->frame_timer = TIME_SWITCH;
        new->state.x = x;
        new->state.y = y;
        new->state.w = MONSTER_WIDTH;
        new->state.h = MONSTER_HEIGHT;
        new->timer_death = 0;
        new->on_ground  = 0;

        nb_monsters++;
    }
}

void        update_monsters(void)
{
    int     i;
    char    coll;

    for (i = 0; i < nb_monsters; i++)
    {
        if (monsters[i].timer_death == 0)
        {
            monsters[i].dir.x = 0;
            monsters[i].dir.y += GRAVITY_SPEED;

            if (monsters[i].dir.y >= MAX_FALL_SPEED)
                monsters[i].dir.y = MAX_FALL_SPEED;
            
            char fall = check_fall(&monsters[i]);

            if (monsters[i].state.x == monsters[i].save.x || fall == 1)
            {
                if (monsters[i].direction == LEFT)
                    monsters[i].direction = RIGHT;
                else
                    monsters[i].direction = LEFT;
            }

            if (monsters[i].direction == LEFT)
                monsters[i].dir.x -= 2;
            else
                monsters[i].dir.x += 2;

            monsters[i].save.x = monsters[i].state.x;
            monster_collision_to_map(&monsters[i]);
            if (get_shuriken_nb() > 0)
            {
                if (shuriken_collide(&monsters[i]))
                {
                    monsters[i].timer_death = 1;
                    play_fx(DESTROY);
                }
            }
            coll = collide(get_player(), &monsters[i]);
            if (coll == 1)
                if (get_life() > 1)
                    player_hurts(&monsters[i]);
                else
                    kill_player();
            else if (coll == 2)
            {
                monsters[i].timer_death = 1;
                play_fx(DESTROY);
            }

        }

        if (monsters[i].timer_death > 0)
        {
            monsters[i].timer_death--;
            if (monsters[i].timer_death == 0)
            {
                monsters[i] = monsters[nb_monsters - 1];
                nb_monsters--;
            }
        }
    }
}

char        collide(GameObject *player, GameObject *monster)
{
    if ((player->state.x >= monster->state.x + monster->state.w)
            || (player->state.x + player->state.w <= monster->state.x)
            || (player->state.y >= monster->state.y + monster->state.h)
            || (player->state.y + player->state.h <= monster->state.y))
        return (0);
    else if (player->state.y + player->state.h <= monster->state.y + 10)
    {
        player->dir.y = -JUMP_HEIGHT; 
        return (2);
    }
    else
        return (1);
}

char        check_fall(GameObject *monster)
{
    SDL_Point   point;

    if (monster->direction == LEFT)
    {
        point.x = (int)(monster->state.x + monster->dir.x) / TILE_SIZE;
        point.y = (int)(monster->state.y + monster->state.h - 1) / TILE_SIZE;

        if (point.y < 0)
            point.y = 1;

        if (point.y > MAX_MAP_Y)
            point.y = MAX_MAP_Y;

        if (point.x < 0)
            point.x = 1;

        if (point.x > MAX_MAP_X)
            point.x = MAX_MAP_X;

        if (get_tile_value(point.y + 1, point.x) < BLANK_TILE - 20)
            return (1);
        else
            return (0);
    }

    else
    {
        point.x = (int)(monster->state.x + monster->state.w + monster->dir.x) / TILE_SIZE;
        point.y = (int)(monster->state.y + monster->state.h - 1) / TILE_SIZE;

        if (point.y <= 0)
            point.y = 1;

        if (point.y >= MAX_MAP_Y)
            point.y = MAX_MAP_Y - 1;

        if (point.x <= 0)
            point.x = 1;

        if (point.x >= MAX_MAP_X)
            point.x = MAX_MAP_X - 1;

        if (get_tile_value(point.y + 1, point.x) < BLANK_TILE - 20)
            return (1);
        else
            return (0);
    }
}

void            draw_monster(GameObject *monster)
{
    int         w;
    SDL_Rect    dst;
    SDL_Rect    src;
    
    if (monster->frame_timer <= 0)
    {
        monster->frame_timer = TIME_SWITCH;
        monster->frame_number++;

        SDL_QueryTexture(monster_sprite, NULL, NULL, &w, NULL);
        if (monster->frame_number >= w / monster->state.w)
            monster->frame_number = 0;
    }
    else
        monster->frame_timer--;

    dst.x   = monster->state.x - get_start().x;
    dst.y   = monster->state.y - get_start().y;
    dst.w   = monster->state.w;
    dst.h   = monster->state.h;

    src.x   = monster->frame_number * monster->state.w;
    src.y   = 0;
    src.w   = monster->state.w;
    src.h   = monster->state.h;

    if (monster->direction == LEFT)
        SDL_RenderCopyEx(get_renderer(), monster_sprite, &src, &dst, 0, 0, SDL_FLIP_HORIZONTAL);
    else
        SDL_RenderCopyEx(get_renderer(), monster_sprite, &src, &dst, 0, 0, SDL_FLIP_NONE);

}

