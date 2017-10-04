#include "meruvia.h"

void        input_handler(Input *input)
{
    get_input(input);
}

void        keybool(Input *input, SDL_Event *event, char value)
{
    switch (event->key.keysym.sym)       
    {
        case SDLK_ESCAPE:
            exit(EXIT_SUCCESS);
            break;
        case SDLK_DELETE:
            input->erase = value;
            break;
        case SDLK_UP:
            input->jump = value;
            input->up   = value;
            break;
        case SDLK_c:
            input->attack = value;
            break;
        case SDLK_LEFT:
            input->left = value;
            break;
        case SDLK_RIGHT:
            input->right = value;
            break;
        case SDLK_DOWN:
            input->down = value;
            break;
        case SDLK_RETURN:
            input->enter = value;
            break;
        default:
            break;
    }

}

void        get_input(Input *input)
{
    SDL_Event   event;
    
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                exit(EXIT_SUCCESS);
                break;
            case SDL_KEYDOWN:
                keybool(input, &event, 1);
                break;
            case SDL_KEYUP:
                keybool(input, &event, 0);
                break;
            default:
                break;
        }
    }
}
