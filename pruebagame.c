
#include "game.h"

void main(){
	Game *gm = create_game("testintrfsp.txt", "testintrfob.txt","testintrf_player.txt", "testintrf_dim.txt", "cmdfile.txt");
	play_game(gm);
}		