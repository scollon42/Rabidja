#ifndef DEF_MERUVIA
# define DEF_MERUVIA

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <math.h>
# include <errno.h>
# include <SDL2/SDL.h>

# include <SDL2/SDL_image.h>
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL_mixer.h>

# define WIDTH              800
# define HEIGHT             480

# define MAX_MAP_X          400
# define MAX_MAP_Y          150

# define TILE_SIZE          32

# define TIME_SWITCH        20

# define IDLE               0
# define WALK               1
# define JUMP1              2
# define JUMP2              3
# define DEAD               4

# define PLAYER_WIDTH       40
# define PLAYER_HEIGHT      50

# define PLAYER_SPEED       4

# define RIGHT              1
# define LEFT               2

# define LIMIT_X            400
# define LIMIT_Y            220
# define LIMIT_W            100
# define LIMIT_H            80

# define GRAVITY_SPEED      0.6
# define MAX_FALL_SPEED     15
# define JUMP_HEIGHT        10

# define BLANK_TILE         89
# define TILE_TRAVERSABLE   70
# define TILE_PWUP_BEGIN    67
# define TILE_PWUP_END      69
# define TILE_PWUP_HEART    68
# define TILE_RESSORT       115
# define TILE_CHECKPOINT    23
# define TILE_MONSTER       126
# define TILE_PIKES         117
# define TILE_BEGIN_PLAT    120
# define TILE_END_PLAT      121

# define BACKGROUND         "./data/sprites/background.png"
# define TILE_FORMAT_A      "./data/sprites/tileset%d.png"
# define TILE_FORMAT_B      "./data/sprites/tileset%dB.png"
# define PLAYER_SPRITE      "./data/sprites/rabidja.png"
# define MAP_FORMAT         "./data/maps/map%d.txt"

typedef struct          s_float_point
{
    float       x;
    float       y;
}                       FloatPoint;

typedef struct          s_game_object
{

    int         life;
    int         invicible_timer;
    
    SDL_Rect    state;

    char        checkpoint;

    SDL_Point   respawn;

    int         frame_number;
    int         frame_timer;
    int         frame_max;

    char        sprite_type;
    char        direction;

    char        on_ground;
    int         timer_death;

    FloatPoint  dir;

    SDL_Point   save;
    char        jump;

    SDL_Texture *sprite;
}                       GameObject;

typedef struct          s_map
{
    SDL_Texture *background;
    SDL_Texture *tile_set_a;
    SDL_Texture *tile_set_b;

    int         tile_set_id;

    SDL_Point   hero_start;
    SDL_Point   map_start;
    SDL_Point   map_limit;
    
    int         tile[MAX_MAP_Y][MAX_MAP_X];
    int         tile2[MAX_MAP_Y][MAX_MAP_X];
    int         tile3[MAX_MAP_Y][MAX_MAP_X];
    
    int         map_timer;
    int         tile_set_nb;
}                       Map;


typedef struct          s_input
{
    char        left;
    char        right;
    char        up;
    char        down;
    char        jump;
    char        attack;
    char        enter;
    char        erase;
    char        pause;
}                       Input;


extern  void            change_level(void);
extern  void            set_level_value(int value);
extern  int             get_level(void);
extern  void            draw_map(int);
extern  void            draw_tile(SDL_Texture *image, int destx, int desty, int srcx, int srcy);
extern  void            load(void);
extern  void            init_maps(void);
extern  SDL_Texture     *get_background(void);
extern  SDL_Texture     *load_image(char *name);
extern  void            draw_image(SDL_Texture *img, int x, int y);
extern  void            clean_maps(void);
extern  void            cleanup(void);
extern  void            delay(unsigned int frame_limit);
extern  void            draw(void);
extern  void            keybool(Input *input, SDL_Event *event, char value);
extern  void            input_handler(Input *input);
extern  void            get_input(Input *input);
extern  SDL_Renderer    *get_renderer(void);
extern  void            init(char *title);

extern  GameObject      *get_player(void);
extern  SDL_Rect        get_player_sate(void);
extern  void            set_player_state_xy(SDL_Point xy);
extern  void            init_player_sprite(void);
extern  void            clean_player(void);
extern  void            init_player(char new_level);
extern  void            draw_player(void);
extern  void            set_start(SDL_Point start);

extern  void            set_start(SDL_Point start);
extern  SDL_Point       get_start(void);
extern  SDL_Point       get_begin(void);
extern  SDL_Point       get_max(void);
extern  void            update_player(Input *input);
extern  void            center_scrolling_on_player(void);
extern  void            map_collision(GameObject *entity);

#endif
