#include "../includes/wolf3d.h"

void    init_monster(t_wolf *wolf)
{
    wolf->monster->image_monster[0] = IMG_Load("textures/demon.png");
    wolf->monster->image_monster[1] = IMG_Load("textures/repteloid.png");
    wolf->monster->image_monster[2] = IMG_Load("textures/osa.png");
    if (!wolf->monster->image_monster[0] ||
        !wolf->monster->image_monster[1] ||
        !wolf->monster->image_monster[2])
		error(wolf, SDL_GetError());
    wolf->monster->monster_pos[0].x = 5.5 * CUBE;
    wolf->monster->monster_pos[0].y = 2.5 * CUBE;
    wolf->monster->monster_pos[1].x = 4.5 * CUBE;
    wolf->monster->monster_pos[1].y = 2.5 * CUBE;
    wolf->monster->monster_pos[2].x = 6.5 * CUBE;
    wolf->monster->monster_pos[2].y = 4.5 * CUBE;
    wolf->monster->count_monster = 3;
}