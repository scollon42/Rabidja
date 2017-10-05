#include "meruvia.h"

char        on_menu;
int         menu_type;
int         choice; 
SDL_Texture *menu_texture;

int     get_on_menu(void)
{
    return (on_menu);
}


int     get_menu_type(void)
{
    return (menu_type);
}

void    set_on_menu(char v, int type)
{
    on_menu = v;
    menu_type = type;
}

void    init_menus(void)
{
    if (!(menu_texture = load_image(MENU_SCREEN)))
    {
        printf("unable to load menu %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

void    clean_menus(void)
{
    if (menu_texture)
        SDL_DestroyTexture(menu_texture);
    menu_texture = NULL;
}


void    update_start_menu(Input *input)
{
    if (input->down)
    {
        if (choice == 0)
            choice++;
        input->down = 0;
    }

    if (input->up)
    {
        if (choice == 1)
            choice--;
        input->up = 0;
    }
    if (input->right)
    {
        if (get_level() >= LEVEL_MAX)
            set_level_value(1);
        else
            set_level_value(get_level() + 1);
        input->right = 0;
    }
    if (input->left)
    {
        if (get_level() <= 1)
            set_level_value(LEVEL_MAX);
        else
            set_level_value(get_level() - 1);
        input->left = 0;
    }

    if (input->enter)
    {
        if (choice == 0)
        {
            reset_check_point();
            init_player(1);
            change_level();

            set_nb_life(3);
            set_nb_star(0);
            on_menu = 0;
        }
        else if (choice == 1)
        {
            exit(EXIT_SUCCESS);
        }

        input->enter = 0;
    }
    
}

void        draw_start_menu(void)
{
    char        text[200];
    SDL_Color   highlight;
    SDL_Color   white;
    SDL_Color   shadow;

    white       = (SDL_Color){ .r = 255, .g = 255, .b = 255, .a = 255 };
    highlight   = (SDL_Color){ .r = 255, .g = 255, .b = 0, .a = 255 };
    shadow      = (SDL_Color){ .r = 0, .g = 0, .b = 0, .a = 255 };

    draw_image(menu_texture, 0, 0);
    sprintf(text, "START: Lvl %d", get_level());
    draw_string(text, (SDL_Point) { .x = 375, .y = 252}, shadow);
    
    draw_string(text, (SDL_Point) { .x = 373, .y = 250}, (choice == 0 ? highlight : white));
        
    sprintf(text, "QUIT");
    draw_string(text, (SDL_Point) { .x = 425, .y = 292}, shadow);
    draw_string(text, (SDL_Point) { .x = 422, .y = 290}, (choice == 1 ? highlight : white));
}
