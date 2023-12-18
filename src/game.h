#ifndef GAME_H
#define GAME_H

typedef enum {
    BEFORE_PLAY,
    PLAYING,
    HIT,
    WON,
    QUIT
} GameState;

int init_game();
void game_action(int update_actors);
void cleanup_game();
void reset_game();
void set_game_state(GameState new_game_state);
GameState get_game_state();

#endif /* GAME_H */