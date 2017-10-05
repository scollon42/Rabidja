#include "rabidja.h"

Input input;

int main(void)
{
    char            go;
    unsigned int    frame_limit;

    go          = 1;
    frame_limit = SDL_GetTicks() + 16;

    init("rabidja 3");
    atexit(cleanup);

    load();
    init_player(1);
    init_menus();

    while (go)
    {
        input_handler(&input);

        if (get_on_menu() == 0)
        {
            update_player(&input);
            update_shuriken();
            update_monsters();
            update_platforms();
            draw();
        }
        else
        {
            update_start_menu(&input);
            draw_start_menu();
            SDL_RenderPresent(get_renderer());
            SDL_Delay(1);
        }

        delay(frame_limit);
        frame_limit = SDL_GetTicks() + 16;
    }

    exit (EXIT_SUCCESS);
}
