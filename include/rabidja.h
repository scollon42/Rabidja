#ifndef DEF_RABIDJA
# define DEF_RABIDJA

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <math.h>
# include <errno.h>
# include <SDL2/SDL.h>

# include <SDL2/SDL_image.h>
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL_mixer.h>

# define WIDTH              1280
# define HEIGHT             720

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

# define MONSTER_MAX        50
# define MONSTER_WIDTH      40
# define MONSTER_HEIGHT     50

# define PLATFORMES_MAX     50
# define PLATFORM_SPEED     2
# define UP                 3
# define DOWN               4

# define LEVEL_MAX          2

# define BACKGROUND         "./data/sprites/background.png"
# define TILE_FORMAT_A      "./data/sprites/tileset%d.png"
# define TILE_FORMAT_B      "./data/sprites/tileset%dB.png"
# define PLAYER_SPRITE      "./data/sprites/rabidja.png"
# define MONSTER_SPRITE     "./data/sprites/monster.png"
# define MAP_FORMAT         "./data/maps/map%d.txt"
# define FONT               "./data/font/GenBasB.ttf"
# define LIFE_SPRITE        "./data/sprites/life.png"
# define STAR_SPRITE        "./data/sprites/star.png"
# define BUMPER_SOUND       "./data/sounds/bumper.wav"
# define DESTROY_SOUND      "./data/sounds/destroy.wav"
# define JUMP_SOUND         "./data/sounds/jump.wav"
# define STAR_SOUND         "./data/sounds/star.wav"
# define BG_MUSIC           "./data/sounds/bg_music.ogg"
# define PLATFORM_SPRITE    "./data/sprites/plateforme.png"
# define MENU_SCREEN        "./data/sprites/title.png"
# define SHURIKEN_SPRITE    "./data/sprites/shuriken.png"

# define SHURIKEN_MAX       6
enum
{
    START,
    PAUSE
};

enum
{
    BUMPER,
    DESTROY,
    JUMP,
    STAR
};

typedef struct          s_float_point
{
    float       x;
    float       y;
}                       FloatPoint;

typedef struct          s_game_object
{

    int         life;
    int         stars;
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
    SDL_Texture *sprite;

    SDL_Point   begin;
    char        platform_type;
    char        hero_on_it;
    char        jump;

    double      rotation;
    SDL_Point   center;
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


extern  GameObject      *get_monster(int nb);

extern  void            draw_monster(GameObject *monster);
extern  char            check_fall(GameObject *monster);
extern  char            collide(GameObject *player, GameObject *monster);
extern  void            update_monsters(void);
extern  void            new_monster(int x, int y);
extern  void            clean_monsters(void);
extern  void            reset_monsters(void);
extern  int             get_monsters_nb(void);
extern  void            init_monster_sprite(void);
extern  void            monster_collision_to_map(GameObject *entity);
extern  int             get_life(void);
extern  void            kill_player(void);
extern  void            player_hurts(GameObject *monster);
extern  int             get_tile_value(int x, int y);

extern  void            init_ui(void);
extern  void            clean_ui(void);
extern  void            draw_ui(void);

extern  void            load_font(char *name, int size);
extern  void            close_font();
extern  void            draw_string(char *str, SDL_Point pos, SDL_Color rgba);


extern  int             get_nb_life(void);
extern  void            set_nb_life(int value);
extern  int             get_nb_star(void);
extern  void            set_nb_star(int value);

extern  SDL_Texture     *get_tile_set_a(void);
extern  SDL_Texture     *get_tile_set_b(void);

extern  void            load_bg_music(char *filename);
extern  void            clean_music(void);
extern  void            load_sound(void);
extern  void            free_sound(void);
extern  void            play_fx(int type);
extern  void            get_item(int item_type);

extern  void            load_platform(void);
extern  void            clean_platform(void);
extern  int             get_platform_nb(void);
extern  void            reset_platforms(void);
extern  void            init_platform(SDL_Point pos, char type);
extern  void            update_platforms(void);
extern  void            collisions_with_platform(GameObject *entity);
extern  void            draw_platforms(void);

extern  SDL_Point       get_player_state_xy(void);
extern  void            reset_check_point(void);


extern  int             get_on_menu(void);
extern  int             get_menu_type(void);
extern  void            set_on_menu(char v, int type);
extern  void            init_menus(void);
extern  void            clean_menus(void);
extern  void            update_start_menu(Input *input);
extern  void            draw_start_menu(void);

extern  void            load_shuriken(void);
extern  void            clean_shuriken(void);
extern  int             get_shuriken_nb(void);
extern  void            reset_shuriken(void);
extern  void            create_shuriken(void);
extern  void            update_shuriken(void);
extern  void            draw_shuriken(void);
extern  char            shuriken_collide(GameObject *monster);

extern  void            draw_image_plus(SDL_Texture *img, int x, int y, double rotation, SDL_Point center, SDL_RendererFlip flip);

extern  int             get_player_direction(void);
#endif
