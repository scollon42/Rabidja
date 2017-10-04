#include "meruvia.h"

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

    while (go)
    {
        input_handler(&input);
        update_player(&input);
        update_monsters();
        draw();

        delay(frame_limit);
        frame_limit = SDL_GetTicks() + 16;
    }

    exit (EXIT_SUCCESS);
}
