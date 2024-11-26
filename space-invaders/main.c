#include <stdio.h>
#include "raylib.h"

unsigned int frame_counter = 0;

#define vga_width    120
#define vga_height    60
#define vga_pixel_size 12

unsigned int SCREEN_WIDTH = vga_width * vga_pixel_size;
unsigned int SCREEN_HEIGHT = vga_height * vga_pixel_size;

void putPixel(unsigned int x, unsigned int y, unsigned int color)
{
	Color c = WHITE;
	if(color == 0)
		c = BLACK;
	if(color == 2)
		c = BLUE;
	if(color == 3)
		c = RED;
	DrawRectangle(x*vga_pixel_size, y*vga_pixel_size, vga_pixel_size, vga_pixel_size, c);
}

#define enemy_color 3
#define enemy_dead 1000
typedef struct {
	int x;
	int y;
} enemy;
int enemy_direction = 1;
#define enemy_base_step_count 4
#define enemy_num 10
//enemy enemies[enemy_num] = {{5, 10}, {10, 10}, {15, 10}, {20, 10}, {25, 10}}; 
enemy enemies[enemy_num] = {{5, 10}, {10, 10}, {15, 10}, {20, 10}, {25, 10},
			    {5, 20}, {10, 20}, {15, 20}, {20, 20}, {25, 20}}; 
//enemy enemies[enemy_num] = {{5, 10}}; 

// Dans VGAX cette fonction retourne la couleur du pixel
// Ici c'est chiant de le faire
// Vu que j'utilise cette fonction uniquement pour detecter la collision d'une balle avec un ennemie
// Je fais semblant avec une loop pour simuler
unsigned int getPixel(unsigned int x, unsigned int y)
{
	for(unsigned int i = 0; i < enemy_num; i++)
	{
		enemy e = enemies[i];
		if((e.x == x || e.x == x-1) && (e.y == y || e.y == y-1))
			return enemy_color; // COLLISION
	}
	return 0; // Pas de collision > return NOIR
}


#define player_y 58
int player_x = 5;

#define default_bullet_y 57
#define bullet_ready -1 
int bullet_x = bullet_ready;
int bullet_y = default_bullet_y;

int main(int argc, char* argv[])
{
	printf("Hello, World!\n");
	
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Planets simulator");
	SetTargetFPS(60);

	bool gameLost = false;
	unsigned int killCount = 0;
	unsigned int enemy_step = 0, enemy_step_count = enemy_base_step_count;

	while(!WindowShouldClose())
	{
		printf(" ======== %d ============================== \n", frame_counter++);

		//prints
		//printf("bullet_x: %d\n", bullet_x);
		//printf("bullet_y: %d\n", bullet_y);

		printf("step: %u \t count: %u \n", enemy_step, enemy_step_count);

		// update positions
		// bullet
		if(bullet_x != bullet_ready){
			bullet_y--;
			
			// OUT OF SCREEN
			if(bullet_y < 0){
				bullet_x = bullet_ready;
			}else{	
				// test collision si balle tjrs dans l'écran
				unsigned collision_test = getPixel(bullet_x, bullet_y);
				if(collision_test == enemy_color)
				{
					// COLLISION 
					// Trouver l'enemie qui est touché
					for(unsigned int i = 0; i < enemy_num; i++)
					{
						enemy e = enemies[i];
						if((e.x == bullet_x || e.x == bullet_x-1) 
						&& (e.y == bullet_y || e.y == bullet_y-1))
							enemies[i].y = enemy_dead; // l'enemie est tué
					}

					bullet_x = bullet_ready; // la balle est détruite
					
					killCount++;

					if(killCount % 3 == 0 && enemy_step_count > 1)
						enemy_step_count--;
				}
			}
		}
		// enemies
		// Find max/min X pos to change direction if needed
		// Find if all enemies are dead
		unsigned int min_x, max_x;
		bool all_enemies_dead = true;
		for(unsigned int i = 0; i < enemy_num; i++)
		{
			enemy e = enemies[i];

			if(e.y > vga_height)
				continue;

			if(all_enemies_dead)
			{
				min_x = e.x;
				max_x = e.x;
			}

			if(e.x < min_x)
				min_x=e.x;
			if(e.x > max_x)
				max_x=e.x;

			all_enemies_dead = false;
		}
		if(enemy_step % enemy_step_count == 0)
		{
			unsigned int change_y = 0;
			if(min_x == 0 || max_x == vga_width){
				printf("min_x: %d \t max_x: %d \t vga_width\n", min_x, max_x);
				enemy_direction = -enemy_direction;
				change_y = 1;
			}
				

			for(unsigned int i = 0; i < enemy_num; i++)
			{
				enemies[i].x += enemy_direction;
				enemies[i].y += change_y;
			}
		}
		enemy_step++;
		// key presses
		if(IsKeyDown(KEY_RIGHT))
			player_x++;
		
		if(IsKeyDown(KEY_LEFT))
			player_x--;
	
		if(IsKeyPressed(KEY_SPACE) && bullet_x == bullet_ready){
			bullet_x = player_x;
			bullet_y = default_bullet_y;
		}
	
		// drawing
		BeginDrawing();
		{
			if(all_enemies_dead)
				DrawText("GAGNER", 50, 50, 50, WHITE);

			putPixel(player_x, player_y, 1);
			putPixel(bullet_x, bullet_y, 2);
			for(unsigned int i = 0; i < enemy_num; i++)
			{
				enemy e = enemies[i];
				if(e.y != enemy_dead){
					putPixel(e.x,   e.y,   enemy_color);
					putPixel(e.x+1, e.y,   enemy_color);
					putPixel(e.x,   e.y+1, enemy_color);
					putPixel(e.x+1, e.y+1, enemy_color);
					if(e.y == player_y && e.x == player_x)
						gameLost = true;
				}
			}

			if(gameLost)
				DrawText("PERDU", 50, 50, 50, WHITE);

			ClearBackground(BLACK);
		}
		EndDrawing();
	};

	CloseWindow();
	return 0;
}
