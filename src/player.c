#include "meruvia.h"

int         level;
GameObject  player;
int         lifes;
int         stars;


int         get_nb_life(void)
{
    return (lifes);
}

void        set_nb_life(int value)
{
    lifes = value;
}

int         get_nb_star(void)
{
    return (stars);
}

void         set_nb_star(int value)
{
    stars = value;
}

int         get_life(void)
{
    return (player.life);
}

void        kill_player(void)
{
    player.timer_death = 1;
    play_fx(DESTROY);
}

void        player_hurts(GameObject *monster)
{
    if (player.invicible_timer == 0)
    {
        player.life--;
        player.invicible_timer = 80;
        monster->timer_death = 1;
        play_fx(DESTROY);
        player.dir.y = -JUMP_HEIGHT;
    }
}

int         get_level(void)
{
    return (level);
}

void        set_level_value(int value)
{
    level = value;
}

GameObject  *get_player(void)
{
    return (&player);
}

SDL_Rect   get_player_sate(void)
{
    return (player.state);
}

void        set_player_state_xy(SDL_Point xy)
{
    player.state.x = xy.x;
    player.state.y = xy.y;
}

void        init_player_sprite(void)
{
    player.sprite = load_image(PLAYER_SPRITE);
}

void        clean_player(void)
{
    if (player.sprite)
        SDL_DestroyTexture(player.sprite);

    player.sprite = NULL;
}

void        init_player(char new_level)
{
    player.life             = 3;
    player.invicible_timer  = 0;
    player.direction        = RIGHT;
    player.sprite_type      = IDLE;
    player.frame_number     = 0;
    player.frame_timer      = TIME_SWITCH;
    player.frame_max        = 8;
    player.state.x          = get_begin().x;
    player.state.y          = get_begin().y;
    player.state.w          = PLAYER_WIDTH;
    player.state.h          = PLAYER_HEIGHT;
    player.timer_death      = 0;
    player.on_ground        = 0;
    player.jump             = 0;

    if (new_level)
        set_start(get_begin());

    reset_monsters();

}

void        draw_player(void)
{
    SDL_Rect    dest;
    SDL_Rect    src;

    if (player.frame_timer <= 0)
    {
        player.frame_timer = TIME_SWITCH;
        player.frame_number++;
        if (player.frame_number >= player.frame_max)
            player.frame_number = 0;
    }
    else
        player.frame_timer--;
    
    dest.x  = player.state.x - get_start().x;
    dest.y  = player.state.y - get_start().y;
    dest.w  = player.state.w;
    dest.h  = player.state.h;

    src.x   = player.frame_number * player.state.w;
    src.w   = player.state.w;
    src.h   = player.state.h;
    src.y   = player.sprite_type * player.state.h;

    if (player.invicible_timer <= 0 || player.frame_number % 2 == 0)
    {
        if (player.direction == LEFT)
            SDL_RenderCopyEx(get_renderer(), player.sprite, &src, &dest, 0, 0, SDL_FLIP_HORIZONTAL);
        else
            SDL_RenderCopyEx(get_renderer(), player.sprite, &src, &dest, 0, 0, SDL_FLIP_NONE);
    }
}

void        update_player(Input *input)
{
    if (player.timer_death == 0)
    {
        if (player.invicible_timer > 0)
            player.invicible_timer--;

        player.dir.x = 0;
        player.dir.y += GRAVITY_SPEED;
       
        if (player.dir.y >= MAX_FALL_SPEED)
            player.dir.y = MAX_FALL_SPEED;


        if (input->left || input->right)
        {
            if (input->left)
            {
                player.direction    = LEFT;
                player.dir.x        -= PLAYER_SPEED;
            }
            else
            {
                player.direction    = RIGHT;
                player.dir.x        += PLAYER_SPEED;
            }

            if (player.sprite_type != WALK && player.on_ground)
            {
                player.sprite_type  = WALK;
                player.frame_number = 0;
                player.frame_timer  = TIME_SWITCH;
                player.frame_max    = 8;
            }
        }
        else if (player.on_ground)
        {
            if (player.sprite_type != IDLE)
            {
                player.sprite_type  = IDLE;
                player.frame_number = 0;
                player.frame_timer  = TIME_SWITCH;
                player.frame_max    = 8;
            }
        }


        if (input->jump == 1)
        {
            if (player.on_ground == 1)
            {
                play_fx(JUMP);
                player.dir.y        = -JUMP_HEIGHT;
                player.on_ground    = 0;
                player.jump         = 1;
            }
            else if (player.jump)
            {
                play_fx(JUMP);
                player.dir.y        = -JUMP_HEIGHT;
                player.jump         = 0;
            }
            input->jump = 0;
        }

        if (player.on_ground)
            player.jump = 1;

        if (player.on_ground == 0)
        {
            if (player.jump)
            {
                if (player.sprite_type != JUMP1)
                {
                    player.sprite_type  = JUMP1;
                    player.frame_number = 0;
                    player.frame_timer  = TIME_SWITCH;
                    player.frame_max    = 2;
                }
            }
            else
            {
                if (player.sprite_type != JUMP2)
                {
                    player.sprite_type  = JUMP2;
                    player.frame_number = 0;
                    player.frame_timer  = TIME_SWITCH;
                    player.frame_max    = 4;
                }

            }
        }

        map_collision(&player);
        center_scrolling_on_player();
    }

    if (player.timer_death > 0)
    {
        player.timer_death--;
        if (player.timer_death == 0)
        {
            set_nb_life(get_nb_life() - 1);

            change_level();
            init_player(0);
        }

    }
}

void            center_scrolling_on_player(void)
{
    SDL_Point       center;
    SDL_Point       min_limit;
    SDL_Point       max_limit;
    SDL_Point       new_start;
    SDL_Point       start;

    start       = get_start();
    center.x    = player.state.x + player.state.w / 2;
    center.y    = player.state.y + player.state.h / 2;
    min_limit.x = start.x + LIMIT_X;
    min_limit.y = start.y + LIMIT_Y;
    max_limit.x = min_limit.x + LIMIT_W;
    max_limit.y = min_limit.y + LIMIT_H;

    if (center.x < get_start().x)
    {
        new_start   = get_start();
        new_start.x -= 30;
        set_start(new_start);
    }
    else if (center.x < min_limit.x)
    {
        new_start   = get_start();
        new_start.x -= 4;
        set_start(new_start);
    }

    if (center.x > get_start().x + WIDTH)
    {
        new_start   = get_start();
        new_start.x += 30;
        set_start(new_start);
    }
    else if (center.x > max_limit.x)
    {
        new_start   = get_start();
        new_start.x += 4;
        set_start(new_start);
    }

    if (get_start().x < 0)
    {
        new_start = get_start();
        new_start.x = 0;
        set_start(new_start);
    }
    else if ((get_start().x + WIDTH) >= get_max().x)
    {
        new_start = get_start();
        new_start.x -= WIDTH;
        set_start(new_start);
    }

    if (center.y < min_limit.y)
    {
        new_start   = get_start();
        new_start.y -= 4;
        set_start(new_start);
    }

    if (center.y > max_limit.y)
    {
        new_start   = get_start();

        if (player.dir.y >= MAX_FALL_SPEED - 2)
            new_start.y += MAX_FALL_SPEED + 1;
        else
            new_start.y += 4;
        set_start(new_start);
    }

    if (get_start().y + HEIGHT >= get_max().y)
    {
        new_start = get_start();
        new_start.y -= HEIGHT;
        set_start(new_start);
    }
    if (get_start().y < 0)
    {
        new_start = get_start();
        new_start.y = 0;
        set_start(new_start);
    }

}

void            get_item(int    item_type)
{
    switch ( item_type )
    {
        case 1:
            set_nb_star(get_nb_star() + 1);
            play_fx(STAR);

            if (get_nb_star() >= 100)
            {
                if (get_nb_life() < 99)
                    set_nb_life(get_nb_life() + 1);
            }
            break;
        case 2:
            if (player.life < 3)
                player.life++;
            play_fx(STAR);
            break;
        case 3:
            if (get_nb_life() < 99)
                set_nb_life(get_nb_life() + 1);
            play_fx(STAR);
            break;
        default:
            break;
    }

}
