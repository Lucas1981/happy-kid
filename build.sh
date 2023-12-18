brew install sdl2;
brew install sdl2_image;
brew install sdl2_ttf;
brew install sdl2_mixer;
cd src;
gcc main.c graphics.c input.c image_loader.c world.c collision.c diamond.c animation.c enemy.c player.c user_interface.c game.c sound.c -o ../happykid `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_mixer -lSDL2_ttf;
