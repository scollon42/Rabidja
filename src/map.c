#include "rabidja.h"

Map map;

void            set_start(SDL_Point start)
{
    map.map_start = start;
}

SDL_Point       get_start(void)
{
    return (map.map_start);
}

SDL_Point       get_begin(void)
{
    return (map.hero_start);
}

SDL_Point       get_max(void)
{
    return (map.map_limit);
}

void            init_maps(void)
{
    map.background  = load_image(BACKGROUND);

    map.map_timer   = TIME_SWITCH * 3;
    map.tile_set_nb = 0;
}


SDL_Texture     *get_tile_set_a(void)
{
    return map.tile_set_a;
}

SDL_Texture     *get_tile_set_b(void)
{
    return map.tile_set_b;
}

int             get_tile_value(int y, int x)
{
    return (map.tile[y][x]);
}

void            load_map(char *name)
{
    int     x;
    int     y;
    FILE    *fp;

    if (!(fp = fopen(name, "rb")))
        exit(EXIT_FAILURE);

    fscanf(fp, "%d", &map.hero_start.x);
    fscanf(fp, "%d", &map.hero_start.y);
    
    fscanf(fp, "%d", &map.tile_set_id);

    map.map_limit.x = 0;
    map.map_limit.y = 0;


    for (y = 0; y < MAX_MAP_Y; y++)
    {
        for (x = 0; x < MAX_MAP_X; x++)
        {
            fscanf(fp, "%d", &map.tile[y][x]);
            if (map.tile[y][x] > 0)
            {
                if (x > map.map_limit.x)
                    map.map_limit.x = x;

                if (y > map.map_limit.y)
                    map.map_limit.y = y;
            }
        }
    }

    for (y = 0; y < MAX_MAP_Y; y++)
        for (x = 0; x < MAX_MAP_X; x++)
            fscanf(fp, "%d", &map.tile2[y][x]);
 
    for (y = 0; y < MAX_MAP_Y; y++)
        for (x = 0; x < MAX_MAP_X; x++)
            fscanf(fp, "%d", &map.tile3[y][x]);

    map.map_limit.x = (map.map_limit.x + 1) * TILE_SIZE;
    map.map_limit.y = (map.map_limit.y + 1) * TILE_SIZE;

    fclose(fp);
}

void            draw_map(int layer)
{
    int     x;
    int     y;
    int     map_x;
    int     map_y;
    int     x1;
    int     x2;
    int     y1;
    int     y2;
    int     xsrc;
    int     ysrc;
    int     a;

    x1      = (map.map_start.x % TILE_SIZE) * -1;
    x2      = x1 + WIDTH + (x1 == 0 ? 0 : TILE_SIZE);
    y1      = (map.map_start.y % TILE_SIZE) * -1;
    y2      = y1 + HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);
    map_y   = map.map_start.y / TILE_SIZE;

    if (map.map_timer <= 0)
    {
        map.tile_set_nb = (map.tile_set_nb == 0 ? 1 : 0);
        map.map_timer = TIME_SWITCH * 3;
    }
    else
    {
        map.map_timer--;
    }


    if (layer == 1)
    {        
        for (y = y1; y < y2; y += TILE_SIZE)
        {
            map_x = map.map_start.x / TILE_SIZE;
            for (x = x1; x < x2; x += TILE_SIZE)
            {
                if (map.tile[map_y][map_x] == TILE_MONSTER)
                {
                    new_monster(map_x * TILE_SIZE, map_y * TILE_SIZE);
                    map.tile[map_y][map_x] = 0;
                }
                else if (map.tile[map_y][map_x] >= TILE_BEGIN_PLAT &&
                        map.tile[map_y][map_x] <= TILE_END_PLAT) 
                {
                    init_platform((SDL_Point){ .x = map_x * TILE_SIZE, .y = map_y * TILE_SIZE }, map.tile[map_y][map_x] - TILE_BEGIN_PLAT + 1);
                    map.tile[map_y][map_x] = 0;
                }

                a = map.tile[map_y][map_x];
 
                ysrc = a / 10 * TILE_SIZE;
                xsrc = a % 10 * TILE_SIZE;
 
                if (map.tile_set_nb == 0)
                    draw_tile(map.tile_set_a, x, y, xsrc, ysrc);
                else
                    draw_tile(map.tile_set_b, x, y, xsrc, ysrc);
 
                map_x++;
            }
 
            map_y++;
        }
    }
    else if(layer == 2)
    {
        for (y = y1; y < y2; y += TILE_SIZE)
        {
            map_x = map.map_start.x / TILE_SIZE;
 
            for (x = x1; x < x2; x += TILE_SIZE)
            {
                if (map.tile2[map_y][map_x] == TILE_MONSTER)
                {
                    new_monster(map_x * TILE_SIZE, map_y * TILE_SIZE);
                    map.tile2[map_y][map_x] = 0;
                }
                else if (map.tile2[map_y][map_x] >= TILE_BEGIN_PLAT &&
                        map.tile2[map_y][map_x] <= TILE_END_PLAT) 
                {
                    init_platform((SDL_Point){ .x = map_x * TILE_SIZE, .y = map_y * TILE_SIZE }, map.tile2[map_y][map_x] - TILE_BEGIN_PLAT + 1);
                    map.tile2[map_y][map_x] = 0;
                }


                a = map.tile2[map_y][map_x];
 
                ysrc = a / 10 * TILE_SIZE;
                xsrc = a % 10 * TILE_SIZE;
 
                if (map.tile_set_nb == 0)
                    draw_tile(map.tile_set_a, x, y, xsrc, ysrc);
                else
                    draw_tile(map.tile_set_b, x, y, xsrc, ysrc);
 
                map_x++;
            }
 
            map_y++;
        }

    }
    else if(layer == 3)
    {
        for (y = y1; y < y2; y += TILE_SIZE)
        {
            map_x = map.map_start.x / TILE_SIZE;
 
            for (x = x1; x < x2; x += TILE_SIZE)
            {
                if (map.tile3[map_y][map_x] == TILE_MONSTER)
                {
                    new_monster(map_x * TILE_SIZE, map_y * TILE_SIZE);
                    map.tile3[map_y][map_x] = 0;
                }
                else if (map.tile3[map_y][map_x] >= TILE_BEGIN_PLAT &&
                        map.tile3[map_y][map_x] <= TILE_END_PLAT) 
                {
                    init_platform((SDL_Point){ .x = map_x * TILE_SIZE, .y = map_y * TILE_SIZE }, map.tile3[map_y][map_x] - TILE_BEGIN_PLAT + 1);
                    map.tile3[map_y][map_x] = 0;
                }

                a = map.tile3[map_y][map_x];
 
                ysrc = a / 10 * TILE_SIZE;
                xsrc = a % 10 * TILE_SIZE;
 
                if (map.tile_set_nb == 0)
                    draw_tile(map.tile_set_a, x, y, xsrc, ysrc);
                else
                    draw_tile(map.tile_set_b, x, y, xsrc, ysrc);
 
                map_x++;
            }
 
            map_y++;
        }

    }
}

void            change_level(void)
{
    char        file[200];

    sprintf(file, MAP_FORMAT, get_level());
    load_map(file);
    
    if (map.tile_set_a)
        SDL_DestroyTexture(map.tile_set_a);
    if (map.tile_set_b)
        SDL_DestroyTexture(map.tile_set_b);

    sprintf(file, TILE_FORMAT_A, map.tile_set_id);
    map.tile_set_a = load_image(file);

    sprintf(file, TILE_FORMAT_B, map.tile_set_id);
    map.tile_set_b = load_image(file);
}


SDL_Texture     *get_background(void)
{
    return (map.background);
}

void            clean_maps(void)
{
    if (map.background)
    {
        SDL_DestroyTexture(map.background);
        map.background = NULL;
    }

    if (map.tile_set_a)
        SDL_DestroyTexture(map.tile_set_a);
    if (map.tile_set_b)
        SDL_DestroyTexture(map.tile_set_b);
    map.tile_set_a = NULL;
    map.tile_set_b = NULL;
}

void        map_collision(GameObject *entity)
{
    int         i;
    SDL_Point   a;
    SDL_Point   b;

    entity->on_ground = 0;
    
    if (entity->state.h > TILE_SIZE)
        i = TILE_SIZE;
    else
        i = entity->state.h;

    while(1)
    {
        a.x = (entity->state.x + entity->dir.x) / TILE_SIZE;
        b.x = (entity->state.x + entity->dir.x + entity->state.w - 1) / TILE_SIZE;
        a.y = (entity->state.y) / TILE_SIZE;
        b.y = (entity->state.y + i - 1)/ TILE_SIZE;

        if (a.x >= 0 && b.x < MAX_MAP_X && a.y >= 0 && b.y < MAX_MAP_Y)
        {
            if (entity->dir.x > 0)
            {
                if (map.tile[a.y][b.x] >= TILE_PWUP_BEGIN && map.tile[a.y][b.x] <= TILE_PWUP_END)
                {
                    get_item(map.tile[a.y][b.x] - TILE_PWUP_BEGIN + 1);
                    map.tile[a.y][b.x] = 0;
                }
                else if (map.tile[b.y][b.x] >= TILE_PWUP_BEGIN && map.tile[b.y][b.x] <= TILE_PWUP_END)
                {
                    get_item(map.tile[b.y][b.x] - TILE_PWUP_BEGIN + 1);
                    map.tile[b.y][b.x] = 0;
                }

                if (map.tile[a.y][b.x] == TILE_CHECKPOINT)
                {
                    entity->checkpoint = 1;
                    entity->respawn.x = b.x * TILE_SIZE;
                    entity->respawn.y = (a.y * TILE_SIZE) - entity->state.h;
                }
                else if (map.tile[b.y][b.x] == TILE_CHECKPOINT)
                {
                    entity->checkpoint = 1;
                    entity->respawn.x = b.x * TILE_SIZE;
                    entity->respawn.y = (b.y * TILE_SIZE) - entity->state.h;
                }


                if (map.tile[a.y][b.x] > BLANK_TILE || map.tile[b.y][b.x] > BLANK_TILE)
                {
                    entity->state.x = b.x * TILE_SIZE;
                    entity->state.x -= entity->state.w + 1;
                    entity->dir.x   = 0;
                }
            }
            else if (entity->dir.x < 0)
            {
                if (map.tile[a.y][a.x] >= TILE_PWUP_BEGIN && map.tile[a.y][a.x] <= TILE_PWUP_END)
                {
                    get_item(map.tile[a.y][a.x] - TILE_PWUP_BEGIN + 1);
                    map.tile[a.y][a.x] = 0;
                }
                else if (map.tile[b.y][a.x] >= TILE_PWUP_BEGIN && map.tile[b.y][a.x] <= TILE_PWUP_END)
                {
                    get_item(map.tile[b.y][a.x] - TILE_PWUP_BEGIN + 1);
                    map.tile[b.y][a.x] = 0;
                }

                if (map.tile[a.y][a.x] == TILE_CHECKPOINT)
                {
                    entity->checkpoint = 1;
                    entity->respawn.x = a.x * TILE_SIZE;
                    entity->respawn.y = (a.y * TILE_SIZE) - entity->state.h;
                }
                else if (map.tile[b.y][a.x] == TILE_CHECKPOINT)
                {
                    entity->checkpoint = 1;
                    entity->respawn.x = a.x * TILE_SIZE;
                    entity->respawn.y = (b.y * TILE_SIZE) - entity->state.h;
                }



                if (map.tile[a.y][a.x] > BLANK_TILE || map.tile[b.y][a.x] > BLANK_TILE)
                {
                    entity->state.x = (a.x + 1) * TILE_SIZE;
                    entity->dir.x   = 0;
                }
            }
        }
        if (entity->state.h == i)
            break;

        i += TILE_SIZE;

        if (i > entity->state.h)
            i = entity->state.h;

    }


    if (entity->state.w > TILE_SIZE)
        i = TILE_SIZE;
    else
        i = entity->state.w;

    while (1)
    {
        a.x = (entity->state.x) / TILE_SIZE;
        b.x = (entity->state.x + i) / TILE_SIZE;
        a.y = (entity->state.y + entity->dir.y) / TILE_SIZE;
        b.y = (entity->state.y + entity->dir.y + entity->state.h)/ TILE_SIZE;


        if (a.x >= 0 && b.x < MAX_MAP_X && a.y >= 0 && b.y < MAX_MAP_Y)
        {
            if (entity->dir.y > 0)
            {
                if (map.tile[b.y][a.x] >= TILE_PWUP_BEGIN && map.tile[b.y][a.x] <= TILE_PWUP_END)
                {
                    get_item(map.tile[b.y][a.x] - TILE_PWUP_BEGIN + 1);
                    map.tile[b.y][a.x] = 0;
                }
                else if (map.tile[b.y][b.x] >= TILE_PWUP_BEGIN && map.tile[b.y][b.x] <= TILE_PWUP_END)
                {
                    get_item(map.tile[b.y][b.x] - TILE_PWUP_BEGIN + 1);
                    map.tile[b.y][b.x] = 0;
                }

                
                if (map.tile[b.y][a.x] == TILE_CHECKPOINT)
                {
                    entity->checkpoint = 1;
                    entity->respawn.x = a.x * TILE_SIZE;
                    entity->respawn.y = (b.y * TILE_SIZE) - entity->state.h;
                }
                else if (map.tile[b.y][b.x] == TILE_CHECKPOINT)
                {
                    entity->checkpoint = 1;
                    entity->respawn.x = b.x * TILE_SIZE;
                    entity->respawn.y = (b.y * TILE_SIZE) - entity->state.h;
                }

                if (map.tile[b.y][a.x] == TILE_PIKES || map.tile[b.y][b.x] == TILE_PIKES)
                {
                    play_fx(DESTROY);
                    entity->dir.y = -JUMP_HEIGHT;
                    if (entity->life > 1)
                    {
                        if (entity->invicible_timer == 0)
                        {
                            entity->life--;
                            entity->invicible_timer = 80;
                        }
                    }
                    else
                    {
                        entity->timer_death = 1;
                        play_fx(DESTROY);
                    }
                }

                else if (map.tile[b.y][a.x] == TILE_RESSORT || map.tile[b.y][b.x] == TILE_RESSORT)
                {
                    entity->dir.y       = -20;
                    entity->on_ground   = 1;
                    play_fx(BUMPER);
                }

                else if (map.tile[b.y][a.x] > TILE_TRAVERSABLE || map.tile[b.y][b.x] > TILE_TRAVERSABLE)
                {
                    entity->state.y     = b.y * TILE_SIZE;
                    entity->state.y     -= entity->state.h;
                    entity->dir.y       = 0;
                    entity->on_ground   = 1;
                }

                if (get_platform_nb() > 0)
                    collisions_with_platform(entity);
            }
            else if (entity->dir.y < 0)
            {
                if (map.tile[a.y][a.x] >= TILE_PWUP_BEGIN && map.tile[a.y][a.x] <= TILE_PWUP_END)
                {
                    get_item(map.tile[a.y][a.x] - TILE_PWUP_BEGIN + 1);
                    map.tile[a.y][a.x] = 0;
                }
                else if (map.tile[a.y][b.x] >= TILE_PWUP_BEGIN && map.tile[a.y][b.x] <= TILE_PWUP_END)
                {
                    get_item(map.tile[a.y][b.x] - TILE_PWUP_BEGIN + 1);
                    map.tile[a.y][b.x] = 0;
                }

                if (map.tile[a.y][a.x] == TILE_CHECKPOINT)
                {
                    entity->checkpoint = 1;
                    entity->respawn.x = a.x * TILE_SIZE;
                    entity->respawn.y = (a.y * TILE_SIZE) - entity->state.h;
                }
                else if (map.tile[a.y][b.x] == TILE_CHECKPOINT)
                {
                    entity->checkpoint = 1;
                    entity->respawn.x = b.x * TILE_SIZE;
                    entity->respawn.y = (a.y * TILE_SIZE) - entity->state.h;
                }


                if (map.tile[a.y][a.x] > BLANK_TILE || map.tile[a.y][b.x] > BLANK_TILE)
                {
                    entity->state.y = (a.y + 1) * TILE_SIZE;
                    entity->dir.y   = 0;
                }
            }
        }

        if (entity->state.w == i)
           break; 

        i += TILE_SIZE;

        if (i > entity->state.w)
            i = entity->state.w;
    }

    entity->state.x += entity->dir.x;
    entity->state.y += entity->dir.y;

    if (entity->state.x < 0)
        entity->state.x = 0;
    else if (entity->state.x + entity->state.w >= map.map_limit.x)
        entity->state.x = map.map_limit.x - entity->state.w - 1;

    if (entity->state.y > map.map_limit.y)
        entity->timer_death = 60;
}

void        monster_collision_to_map(GameObject *entity)
{
    int         i;
    SDL_Point   a;
    SDL_Point   b;

    entity->on_ground = 0;
    
    if (entity->state.h > TILE_SIZE)
        i = TILE_SIZE;
    else
        i = entity->state.h;

    while(1)
    {
        a.x = (entity->state.x + entity->dir.x) / TILE_SIZE;
        b.x = (entity->state.x + entity->dir.x + entity->state.w - 1) / TILE_SIZE;
        a.y = (entity->state.y) / TILE_SIZE;
        b.y = (entity->state.y + i - 1)/ TILE_SIZE;

        if (a.x >= 0 && b.x < MAX_MAP_X && a.y >= 0 && b.y < MAX_MAP_Y)
        {
            if (entity->dir.x > 0)
            {
                if (map.tile[a.y][b.x] > BLANK_TILE || map.tile[b.y][b.x] > BLANK_TILE)
                {
                    entity->state.x = b.x * TILE_SIZE;
                    entity->state.x -= entity->state.w + 1;
                    entity->dir.x   = 0;
                }
            }
            else if (entity->dir.x < 0)
            {
                if (map.tile[a.y][a.x] > BLANK_TILE || map.tile[b.y][a.x] > BLANK_TILE)
                {
                    entity->state.x = (a.x + 1) * TILE_SIZE;
                    entity->dir.x   = 0;
                }
            }
        }
        if (entity->state.h == i)
            break;

        i += TILE_SIZE;

        if (i > entity->state.h)
            i = entity->state.h;

    }


    if (entity->state.w > TILE_SIZE)
        i = TILE_SIZE;
    else
        i = entity->state.w;

    while (1)
    {
        a.x = (entity->state.x) / TILE_SIZE;
        b.x = (entity->state.x + i) / TILE_SIZE;
        a.y = (entity->state.y + entity->dir.y) / TILE_SIZE;
        b.y = (entity->state.y + entity->dir.y + entity->state.h)/ TILE_SIZE;


        if (a.x >= 0 && b.x < MAX_MAP_X && a.y >= 0 && b.y < MAX_MAP_Y)
        {
            if (entity->dir.y > 0)
            {
                if (map.tile[b.y][a.x] > TILE_TRAVERSABLE || map.tile[b.y][b.x] > TILE_TRAVERSABLE)
                {
                    entity->state.y     = b.y * TILE_SIZE;
                    entity->state.y     -= entity->state.h;
                    entity->dir.y       = 0;
                    entity->on_ground   = 1;
                }
            }
            else if (entity->dir.y < 0)
            {
                if (map.tile[a.y][a.x] > BLANK_TILE || map.tile[a.y][b.x] > BLANK_TILE)
                {
                    entity->state.y = (a.y + 1) * TILE_SIZE;
                    entity->dir.y   = 0;
                }
            }
        }

        if (entity->state.w == i)
           break; 

        i += TILE_SIZE;

        if (i > entity->state.w)
            i = entity->state.w;
    }

    entity->state.x += entity->dir.x;
    entity->state.y += entity->dir.y;

    if (entity->state.x < 0)
        entity->state.x = 0;
    else if (entity->state.x + entity->state.w >= map.map_limit.x)
        entity->state.x = map.map_limit.x - entity->state.w - 1;

    if (entity->state.y > map.map_limit.y)
        entity->timer_death = 60;
}
