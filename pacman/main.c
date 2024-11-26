#include <stdio.h>
#include "raylib.h"
#include <stdlib.h>

unsigned int frame_counter = 0;

#define vga_width    120
#define vga_height    60
#define vga_pixel_size 12

char Color_pixel[vga_width*vga_height];

const char WALL_TAB[] = {
		0,0,0,0,0,0,0,0,0,0,0,0,
		0,1,1,1,1,1,1,1,1,1,1,0,
		0,1,0,0,1,0,0,1,0,0,1,0,
		0,1,0,0,1,1,1,1,0,0,1,0,
		0,1,1,1,1,0,0,1,1,1,1,0,
		0,2,0,1,0,0,0,0,1,0,2,0,
		0,1,1,1,1,1,1,1,1,1,1,0,
		0,0,1,0,1,0,0,1,0,1,0,0,
		1,1,1,0,1,1,1,1,0,1,1,1,
		0,0,1,0,1,0,0,1,0,1,0,0,
		0,1,1,1,1,1,1,1,1,1,1,0,
		0,1,0,1,3,3,3,3,1,0,1,0,
		0,1,0,1,3,3,3,3,1,0,1,0,
		0,1,1,1,1,1,1,1,1,1,1,0,
		0,0,1,0,1,0,0,1,0,1,0,0,
		1,1,1,0,1,1,1,1,0,1,1,1,
		0,0,1,0,1,0,0,1,0,1,0,0,
		0,1,1,1,1,1,1,1,1,1,1,0,
		0,2,0,1,0,0,0,0,1,0,2,0,
		0,1,1,1,1,0,0,1,1,1,1,0,
		0,1,0,0,1,1,1,1,0,0,1,0,
		0,1,0,0,1,0,0,1,0,0,1,0,
		0,1,1,1,1,1,1,1,1,1,1,0,
		0,0,0,0,0,0,0,0,0,0,0,0,
};

unsigned int SCREEN_WIDTH = vga_width * vga_pixel_size;
unsigned int SCREEN_HEIGHT = vga_height * vga_pixel_size;

void putPixel(unsigned int x, unsigned int y, unsigned int color)
{
	Color_pixel[x*60+y]=color;
	Color c;
	if(color == 0)
		c = BLACK;
	if(color == 1)
		c = RED;
	if(color == 2)
		c = GREEN;
	if(color == 3)
		c = YELLOW;
	DrawRectangle(x*vga_pixel_size, y*vga_pixel_size, vga_pixel_size, vga_pixel_size, c);
}

#define enemy_color 1
#define enemy_dead 1000
typedef struct {
	int x;
	int y;
	int direction;
} enemy;
#define enemy_base_step_count 4
#define enemy_num 4
enemy enemies[enemy_num] = {{59,30,0},{59,30,1},{59,30,2},{59,30,3}}; 

// Dans VGAX cette fonction retourne la couleur du pixel
// Ici c'est chiant de le faire
// Vu que j'utilise cette fonction uniquement pour detecter la collision d'une balle avec un ennemie
// Je fais semblant avec une loop pour simuler
unsigned int getPixel(unsigned int x, unsigned int y)
{
	return Color_pixel[x*60+y];
}


int player_y = 52;
int player_x = 59;
int pacman_direction=4;
int pac_gum_count = 0;

void draw_pacman(int player_x, int player_y, int pacman_direction){
	for(int i=-2;i<=2;i++){
		for(int j=-2;j<=2;j++){
			if(pacman_direction==0){
				if((i+2)*5+(j+2)!=1
				&& (i+2)*5+(j+2)!=2
				&& (i+2)*5+(j+2)!=3
				&& (i+2)*5+(j+2)!=6
				&& (i+2)*5+(j+2)!=7
				&& (i+2)*5+(j+2)!=8
				&& (i+2)*5+(j+2)!=12
				&& (i+2)*5+(j+2)!=20
				&& (i+2)*5+(j+2)!=24){
					putPixel(player_x+j, player_y+i, 3);
				}
				else{
					putPixel(player_x+j, player_y+i, 0);
				}
			}
			if(pacman_direction==1){
				if((i+2)*5+(j+2)!=4
				&& (i+2)*5+(j+2)!=5
				&& (i+2)*5+(j+2)!=6
				&& (i+2)*5+(j+2)!=10
				&& (i+2)*5+(j+2)!=11
				&& (i+2)*5+(j+2)!=12
				&& (i+2)*5+(j+2)!=15
				&& (i+2)*5+(j+2)!=16
				&& (i+2)*5+(j+2)!=24){
					putPixel(player_x+j, player_y+i, 3);
				}
				else{
					putPixel(player_x+j, player_y+i, 0);
				}
			}
			if(pacman_direction==2){
				if((i+2)*5+(j+2)!=0
				&& (i+2)*5+(j+2)!=4
				&& (i+2)*5+(j+2)!=12
				&& (i+2)*5+(j+2)!=16
				&& (i+2)*5+(j+2)!=17
				&& (i+2)*5+(j+2)!=18
				&& (i+2)*5+(j+2)!=21
				&& (i+2)*5+(j+2)!=22
				&& (i+2)*5+(j+2)!=23){
					putPixel(player_x+j, player_y+i, 3);
				}
				else{
					putPixel(player_x+j, player_y+i, 0);
				}
			}
			if(pacman_direction==3){
				if((i+2)*5+(j+2)!=0
				&& (i+2)*5+(j+2)!=8
				&& (i+2)*5+(j+2)!=9
				&& (i+2)*5+(j+2)!=12
				&& (i+2)*5+(j+2)!=13
				&& (i+2)*5+(j+2)!=14
				&& (i+2)*5+(j+2)!=18
				&& (i+2)*5+(j+2)!=19
				&& (i+2)*5+(j+2)!=20){
					putPixel(player_x+j, player_y+i, 3);
				}
				else{
					putPixel(player_x+j, player_y+i, 0);
				}
			}
		}
	}
	for(int k=-2;k<=2;k++){
		if(pacman_direction%2==0){
			if(pacman_direction/2==0){
				putPixel(player_x+k, player_y+3, 0);
			}else if(pacman_direction/2==1){
				putPixel(player_x+k, player_y-3, 0);
			}
		}else if(pacman_direction%2==1){
			if(pacman_direction/2==0){
				putPixel(player_x+3, player_y+k, 0);
			}else if(pacman_direction/2==1){
				putPixel(player_x-3, player_y+k, 0);
			}
		}
	}
}

void draw_wall(int pos_tab,int center_x, int center_y, int color){
	int neighbour_cases;
	if(color==2){
		neighbour_cases = 0;
	}
	if(color==1){
		neighbour_cases = 3;
	}
	for(int i=-2;i<=2;i++){
		for(int j=-2;j<=2;j++){
			int pos_x, pos_y;
			if((pos_tab<12 && i==-2) || (pos_tab>=276 && i==2)){
				pos_x=0;
			}else{
				pos_x=i;
			}
			if((pos_tab%12==0 && j==-2)|| (pos_tab%12==11 && j==2)){
				pos_y=0;
			}else{
				pos_y=j;
			}
			if(pos_x*pos_x==4 && pos_y*pos_y==4){
				if((WALL_TAB[pos_tab+13]!=neighbour_cases && pos_x==2 && pos_y==2)){
					putPixel(center_x+pos_x,center_y+pos_y, color);
				}
				if((WALL_TAB[pos_tab+11]!=neighbour_cases && pos_x==2 && pos_y==-2)){
					putPixel(center_x+pos_x,center_y+pos_y, color);
				}
				if((WALL_TAB[pos_tab-11]!=neighbour_cases && pos_x==-2 && pos_y==2)){
					putPixel(center_x+pos_x,center_y+pos_y, color);
				}
				if((WALL_TAB[pos_tab-13]!=neighbour_cases && pos_x==-2 && j==-2)){
					putPixel(center_x+pos_x,center_y+pos_y, color);
				}
			}
			if(i*i==4){
				if((WALL_TAB[pos_tab+12]!=neighbour_cases && pos_x==2) || (WALL_TAB[pos_tab-12]!=neighbour_cases && pos_x==-2)){
					putPixel(center_x+pos_x,center_y+j, color);
				}
			}
			if(j*j==4){
				if((WALL_TAB[pos_tab+1]!=neighbour_cases && pos_y==2) || (WALL_TAB[pos_tab-1]!=neighbour_cases && pos_y==-2)){
					putPixel(center_x+pos_x,center_y+pos_y, color);
				}
			}
		}
	}
}

void draw_path(int center_x, int center_y, int color){
	putPixel(center_x,center_y, color);
}
void draw_power_up(int center_x, int center_y, int color, int color2){
	for(int i=-1;i<=1;i++){
		for(int j=-1;j<=1;j++){
			if(i==0 || j==0){
				putPixel(center_x+i,center_y+j, color);
			}else {
				putPixel(center_x+i,center_y+j, color2);
			}
		}
	}
}

void drawGround(){
	for(int i=0;i<4;i++){
		for(int j=0;j<sizeof(WALL_TAB);j++){
			if(i==0){
				if(WALL_TAB[j]==0){
					draw_wall(j,(j/12)*5+2,(j%12)*5+2,2);
				}
				if(WALL_TAB[j]==1){
					draw_path((j/12)*5+2,(j%12)*5+2,3);
				}
				if(WALL_TAB[j]==2){
					draw_power_up((j/12)*5+2,(j%12)*5+2,3,1);
				}
				if(WALL_TAB[j]==3){
					draw_wall(j,(j/12)*5+2,(j%12)*5+2,1);
				}
			}
		}
	}
}

void draw_ennemy(int ennemy_x, int ennemy_y, int enemy_direction, int color){
	for(int i=-2;i<=2;i++){
		for(int j=-2;j<=2;j++){
			if((i+2)*5+(j+2)!=0
			&& (i+2)*5+(j+2)!=20
			&& (i+2)*5+(j+2)!=9
			&& (i+2)*5+(j+2)!=19
			&& (i+2)*5+(j+2)!=6
			&& (i+2)*5+(j+2)!=16){
				putPixel(ennemy_x+i, ennemy_y+j, 1);
			}
			else{
				putPixel(ennemy_x+i, ennemy_y+j, 0);
			}
		}
	}
	for(int k=-2;k<=2;k++){
		if(enemy_direction%2==0){
			if(enemy_direction/2==0){
				putPixel(ennemy_x+k, ennemy_y+3, 0);
			}else if(enemy_direction/2==1){
				putPixel(ennemy_x+k, ennemy_y-3, 0);
			}
		}else if(enemy_direction%2==1){
			if(enemy_direction/2==0){
				putPixel(ennemy_x+3, ennemy_y+k, 0);
			}else if(enemy_direction/2==1){
				putPixel(ennemy_x-3, ennemy_y+k, 0);
			}
		}
	}
}

int get_collision(int x, int y, int direction, int is_ennemy){
	int collision_x,collision_x_bis, collision_y, collision_y_bis;
	if(direction%2==0){
		collision_x = x-2;
		collision_x_bis = x+2;
		if(direction/2==0){
			collision_y = y-3;
			collision_y_bis = y-3;
		}
		else if(direction/2==1){
			collision_y = y+3;
			collision_y_bis = y+3;
		}
	}
	else if(direction%2==1){
		collision_y = y-2;
		collision_y_bis = y+2;
		if(direction/2==0){
			collision_x = x-3;
			collision_x_bis = x-3;
		}
		else if(direction/2==1){
			collision_x = x+3;
			collision_x_bis = x+3;
		}
	}
	if(WALL_TAB[(collision_x)/5*12+(collision_y)/5]==0
	|| (WALL_TAB[(collision_x)/5*12+(collision_y)/5]==3 && is_ennemy==0)
	|| WALL_TAB[(collision_x_bis)/5*12+(collision_y_bis)/5]==0
	|| (WALL_TAB[(collision_x_bis)/5*12+(collision_y_bis)/5]==3 && is_ennemy==0)){
		return 1;
	}
		return 0;
}

void one_more_pac_gum(int player_x,int player_y){
	if(getPixel(player_x,player_y)==3){
		pac_gum_count++;
	}
}

int can_go_left(int x,int y,int direction){
	int left=(direction+1)%4;
	for(int i=-2;i<2;i++){
		if(left==0){
			if(WALL_TAB[(x+i)/5*12+(y-3)/5]==0
			|| WALL_TAB[(x-3)/5*12+(y+i)/5]==3){
				return 0;
			}
		}
		if(left==1){
			if(WALL_TAB[(x-3)/5*12+(y+i)/5]==0
			|| WALL_TAB[(x-3)/5*12+(y+i)/5]==3){
				return 0;
			}
		}
		if(left==2){
			if(WALL_TAB[(x+i)/5*12+(y+3)/5]==0
			|| WALL_TAB[(x-3)/5*12+(y+i)/5]==3){
				return 0;
			}
		}
		if(left==3){
			if(WALL_TAB[(x+3)/5*12+(y+i)/5]==0
			|| WALL_TAB[(x-3)/5*12+(y+i)/5]==3){
				return 0;
			}
		}
	}
	return 1;
}

int can_go_right(int x,int y,int direction){
	int right=(direction-1)%4;
	for(int i=-2;i<2;i++){
		if(right==0){
			if(WALL_TAB[(x+i)/5*12+(y-3)/5]==0
			|| WALL_TAB[(x+i)/5*12+(y-3)/5]==3){
				return 0;
			}
		}
		if(right==1){
			if(WALL_TAB[(x-3)/5*12+(y+i)/5]==0
			|| WALL_TAB[(x-3)/5*12+(y+i)/5]==3){
				return 0;
			}
		}
		if(right==2){
			if(WALL_TAB[(x+i)/5*12+(y+3)/5]==0
			|| WALL_TAB[(x+i)/5*12+(y+3)/5]==3){
				return 0;
			}
		}
		if(right==3){
			if(WALL_TAB[(x+3)/5*12+(y+i)/5]==0
			|| WALL_TAB[(x+3)/5*12+(y+i)/5]==3){
				return 0;
			}
		}
	}
	return 1;
}

int change_direction_random(int forward,int left,int right, int can_go_left, int can_go_right){
	if(can_go_left!=0 && can_go_right!=0){
		int tab[3] = {forward,left,right};
		return tab[rand()%3];
	}
	if(can_go_left!=0){
		int tab[2] = {forward,left};
		return tab[rand()%2];
	}
	if(can_go_right!=0){
		int tab[2] = {forward,right};
		return tab[rand()%2];
	}
	return forward;
}

void Move_ennemy(){
	for (int i=0;i<1;i++){
		if(can_go_left(enemies[i].x,enemies[i].y,enemies[i].direction)!=0 || can_go_right(enemies[i].x,enemies[i].y,enemies[i].direction)!=0){
			enemies[i].direction = change_direction_random(enemies[i].direction,(enemies[i].direction+1)%4,(enemies[i].direction-1)%4,can_go_left(enemies[i].x,enemies[i].y,enemies[i].direction),can_go_right(enemies[i].x,enemies[i].y,enemies[i].direction));
		}
		if(enemies[i].direction%2==0){
			if(enemies[i].direction/2==0 && get_collision(enemies[i].x,enemies[i].y,enemies[i].direction,1)!=1){
				enemies[i].y--;
			}
			else if(enemies[i].direction/2==0){
				enemies[i].direction=4;
			}
			else if(enemies[i].direction/2==1 && get_collision(enemies[i].x,enemies[i].y,enemies[i].direction,1)!=1){
				enemies[i].y++;
			}
		}
		else if(enemies[i].direction%2==1){
			if(enemies[i].direction/2==0 && get_collision(enemies[i].x,enemies[i].y,enemies[i].direction,1)!=1){
				enemies[i].x--;
			}
			else if(enemies[i].direction/2==1 && get_collision(enemies[i].x,enemies[i].y,enemies[i].direction,1)!=1){
				enemies[i].x++;
			}
		}
	}
}

int Move_pacman(int pacman_direction){
	if(IsKeyDown(KEY_UP)){
		if(get_collision(player_x,player_y,0,0)!=1){
			one_more_pac_gum(player_x,player_y-3);
			if(player_y==0){
				for(int k=-2;k<=2;k++){
					putPixel(player_x+k, player_y, 0);
					putPixel(player_x+k, player_y+1, 0);
					putPixel(player_x+k, player_y+2, 0);
				}
				player_y=60;
			}
			player_y--;
			return 0;
		}
	}
	if(IsKeyDown(KEY_LEFT)){
		if(get_collision(player_x,player_y,1,0)!=1){
			one_more_pac_gum(player_x-3,player_y);
			player_x--;
			return 1;
		}
	}
	if(IsKeyDown(KEY_DOWN)){
		if(get_collision(player_x,player_y,2,0)!=1){
			one_more_pac_gum(player_x,player_y+3);
			if(player_y==56){
				for(int k=-2;k<=2;k++){
					putPixel(player_x+k, player_y+2, 0);
					putPixel(player_x+k, player_y+1, 0);
					putPixel(player_x+k, player_y, 0);
					putPixel(player_x+k, player_y-1, 0);
					putPixel(player_x+k, player_y-2, 0);
				}
				player_y=0;
			}
			player_y++;
			return 2;
		}
	}
	if(IsKeyDown(KEY_RIGHT)){
		if(get_collision(player_x,player_y,3,0)!=1){
			one_more_pac_gum(player_x+3,player_y);
			player_x++;
			return 3;
		}
	}
	if(true){
		if(pacman_direction%2==0){
			if(pacman_direction/2==0){
				if(get_collision(player_x,player_y,0,0)!=1){
					one_more_pac_gum(player_x,player_y-3);
					player_y--;
					return 0;
				}
			}else if(pacman_direction/2==1){
				if(get_collision(player_x,player_y,2,0)!=1){
					one_more_pac_gum(player_x,player_y+3);
					player_y++;
					return 2;
				}
			}
		}else if(pacman_direction%2==1){
			if(pacman_direction/2==0){
				if(get_collision(player_x,player_y,1,0)!=1){
					one_more_pac_gum(player_x-3,player_y);
					player_x--;
					return 1;
				}
			}else if(pacman_direction/2==1){
				if(get_collision(player_x,player_y,3,0)!=1){
					one_more_pac_gum(player_x+3,player_y);
					player_x++;
					return 3;
				}
			}
		}
	}
	return pacman_direction;
}

int main(int argc, char* argv[])
{
	//printf("Hello, World!\n");
	
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Planets simulator");
	SetTargetFPS(60);

	for(int i=0;i<vga_width*vga_height;i++){
		//printf("%d \n",WALL_TAB[60/5*12+14/5]);
		//printf("%d \n",WALL_TAB[i/12]);
	}

	//bool gameLost = false;
	//unsigned int killCount = 0;
	//unsigned int enemy_step = 0, enemy_step_count = enemy_base_step_count;

	BeginDrawing();
		{
			drawGround();
		}
		EndDrawing();

	while(!WindowShouldClose())
	{
		// enemies
		// Find max/min X pos to change direction if needed
		// Find if all enemies are dead
		//unsigned int min_x, max_x;
		//bool all_enemies_dead = true;
		/*for(unsigned int i = 0; i < enemy_num; i++)
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
		}*/
		/*if(enemy_step % enemy_step_count == 0)
		{
			unsigned int change_y = 0;
			if(min_x == 0 || max_x == vga_width){
				//printf("min_x: %d \t max_x: %d \t vga_width\n", min_x, max_x);
				enemy_direction = -enemy_direction;
				change_y = 1;
			}
				

			for(unsigned int i = 0; i < enemy_num; i++)
			{
				enemies[i].x += enemy_direction;
				enemies[i].y += change_y;
			}
		}
		enemy_step++;*/
		Move_ennemy();

		pacman_direction=Move_pacman(pacman_direction);
	
		// drawing
		BeginDrawing();
		{
			//drawGround();
			if(pac_gum_count==153)
				DrawText("GAGNER", 50, 50, 50, WHITE);

			draw_pacman(player_x, player_y, pacman_direction);

			//putPixel(bullet_x, bullet_y, 2);
			for(unsigned int i = 0; i < enemy_num; i++)
			{
				enemy e = enemies[i];
				//if(e.y != enemy_dead){
					draw_ennemy(e.x,e.y,e.direction,enemy_color);
					//if(e.y == player_y && e.x == player_x)
					//	gameLost = true;
				//}
			}

			//if(gameLost)
				//DrawText("PERDU", 50, 50, 50, WHITE);

			//ClearBackground(BLACK);
		}
		EndDrawing();
	};

	CloseWindow();
	return 0;
}
