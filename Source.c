#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

int main() {
	/*size of map*/
	int map[41][41];
	/*size of pathfinding, it should be same as map*/
	int path[41][41];
	int mapWidth, mapHeight;


	clock_t start, stop;

	/* Seeding random*/
	srand(time(0));
	
	/*Set size of map
	the size has to be odd because maze generation makes free rooms every 2 steps
	if size is even then it will make free room at the edge
	The map size can be a minimum of 3 * 5 big, if 3 * 3 is choosen it will fail somewere*/
	printf("How wide should the map be?(odd number, max 41)\n");
	scanf_s("%d", &mapWidth);
	printf("How tall should the map be?(odd number, max 41)\n");
	scanf_s("%d", &mapHeight);

	/*Make everything in the map a wall and give pathfinding tiles its default value 1000*/
	for (int y = 0; y < mapHeight; y++) {
		for (int x = 0; x < mapWidth; x++) {
			map[y][x] = 4;
			path[y][x] = 1000;
		}
	}

	/*Make every other tile a unvisited open tile*/
	for (int y = 1; y < mapHeight; y += 2) {
		for (int x = 1; x < mapWidth; x += 2) {
			map[y][x] = 5;
		}
	}
	/*Randomize maze generation start*/
	int mazeX = (rand() % mapWidth / 2) * 2 + 1, mazeY = (rand() % mapHeight / 2) * 2 + 1;
	/*Arrays to store previous postitions during maze generation*/
	int mazeBackTrackX[1000];
	int mazeBackTrackY[1000];
	/*Track the stored positions*/
	int backTrack = 0;

	while(1){
		start = clock();
		stop = clock();
		/*Run every 0.1 seconds in order to see the maze generating.
		Change the constant to 0 for it to run as fast as possible*/
		while (stop < start + 100)
			stop = clock();
		/*Random value to see were the maze want to move*/
			int random = rand() % 4;
			/*Check if there is a neighboring unvisited open tile*/
			if (map[mazeY][mazeX + 2] == 5 || map[mazeY][mazeX - 2] == 5 || map[mazeY + 2][mazeX] == 5 || map[mazeY - 2][mazeX] == 5) {
				switch (random) {
				case 0: {
					/*If the tile to the right is a unvisited open room and we are not a the edge*/
					if (map[mazeY][mazeX + 2] == 5 && mazeX != mapWidth - 2) {
						/*Make the two tiles to the right in to visited tiles*/
						map[mazeY][mazeX + 1] = 1;
						map[mazeY][mazeX] = 1;
						/*Save this move*/
						mazeBackTrackX[backTrack] = mazeX;
						mazeBackTrackY[backTrack] = mazeY;

						backTrack++;
						mazeX += 2;
					}
					break;
				}
				case 1: {
					/*If the tile to the left is a unvisited open room and we are not a the edge*/
					if (map[mazeY][mazeX - 2] == 5 && mazeX != 1) {
						/*Make the two tiles to the left in to visited tiles*/
						map[mazeY][mazeX - 1] = 1;
						map[mazeY][mazeX] = 1;
						/*Save this move*/
						mazeBackTrackX[backTrack] = mazeX;
						mazeBackTrackY[backTrack] = mazeY;
						backTrack++;
						mazeX -= 2;
					}
					break;
				}
				case 2: {
					/*If the tile to the down is a unvisited open room and we are not a the edge*/
					if (map[mazeY + 2][mazeX] == 5 && mazeY != mapHeight - 2) {
						/*Make the two tiles to the down in to visited tiles*/
						map[mazeY + 1][mazeX] = 1;
						map[mazeY][mazeX] = 1;
						/*Save this move*/
						mazeBackTrackX[backTrack] = mazeX;
						mazeBackTrackY[backTrack] = mazeY;
						backTrack++;
						mazeY += 2;
					}
					break; }
				case 3: {
					/*If the tile to the up is a unvisited open room and we are not a the edge*/
					if (map[mazeY - 2][mazeX] == 5 && mazeY != 1) {
						/*Make the two tiles to the up in to visited tiles*/
						map[mazeY - 1][mazeX] = 1;
						map[mazeY][mazeX] = 1;
						/*Save this move*/
						mazeBackTrackX[backTrack] = mazeX;
						mazeBackTrackY[backTrack] = mazeY;
						backTrack++;
						mazeY -= 2;
					}
					break; }
				}
			}
			/*If there is no unvisited tiles neighboring*/
			else {
				/*Make the current tile in to a visited room*/
				map[mazeY][mazeX] = 1;
				/*Change the maze position to the previous move*/
				mazeX = mazeBackTrackX[backTrack - 1];
				mazeY = mazeBackTrackY[backTrack - 1];
				backTrack--;
				/*If backtracking has returned to its original position we can assume there is no unvisited
				tiles left and the maze is done*/
				if (backTrack < 0) {
					break;
				}
			}
			/*clear console*/
			system("cls");
			/*Draw the tiles*/
			for (int y = 0; y < mapHeight; y++) {
				for (int x = 0; x < mapWidth; x++) {
					switch (map[y][x]) {
						/*
						1 = visited open room
						2 = character
						3 = target
						4 = wall
						5 = unvisited open room
						*/
					case 1: printf(" ."); break;
					case 2: printf(" C"); break;
					case 3: printf(" X"); break;
					case 4: printf(" W"); break;
					case 5: printf(" F"); break;
					}
				}
				printf("\n");
			}
		}


		/*start the character at 1,1*/
	int moverX = 1, moverY = 1;
	map[moverY][moverX] = 2;
	/*create target variables*/
	int targetX = 0, targetY = 0;
	do{
		/*find a random position for the target*/
		targetX = rand() % mapWidth, targetY = rand() % mapHeight;
	} while (map[targetY][targetX] != 1);

	/*Hardcoded position for the target to be at bottom right corner. This overrides the random
	position previously. This is for testing it can be removed or commented out.*/
	targetX = mapWidth - 2;
	targetY = mapHeight - 2;
	/*Set the target out on the map and set starting postion for pathfinding on target*/
	map[targetY][targetX] = 3;
	path[targetY][targetX] = 0;
	
	/*Current pathfinding number*/
	int k = 0;
	/*Variables for pathing around walls*/
	int noPath = 0;
	int Pathed = 0;

	while (1) {
		start = clock();
		stop = clock();
		/*Runs every 0.1 seconds, this is the see the pathfinding happen*/
		while(stop < start + 100)
			stop = clock();
		/*Start saying that no path has been found*/
			Pathed = 0;
			for (int y = 0; y < mapHeight; y++) {
				for (int x = 0; x < mapWidth; x++) {
					/*find the current tiles that are being pathed around*/
					if (path[y][x] <= k) {
						/*Check if the tile to the right + noPath is closer to the character then the current tile.
						also if that tile is not a wall and is a unpathed tile*/
						if ((double)sqrt(pow(x + 1 - moverX, 2) + pow(y - moverY, 2)) <= (double)sqrt(pow(x - moverX, 2) + pow(y - moverY, 2)) + noPath&& map[y][x + 1] != 4 && path[y][x + 1] == 1000) {
							/*Set the tile to the next number for pathing*/
							path[y][x + 1] = k + 1;
							/*We found a path*/
							Pathed = 1;
						}
						/*Check left*/
						if ((double)sqrt(pow(x - 1 - moverX, 2) + pow(y - moverY, 2)) <= (double)sqrt(pow(x - moverX, 2) + pow(y - moverY, 2)) + noPath&& map[y][x - 1] != 4 && path[y][x - 1] == 1000) {
							path[y][x - 1] = k + 1;
							Pathed = 1;
						}
						/*Check down*/
						if ((double)sqrt(pow(x - moverX, 2) + pow(y + 1 - moverY, 2)) <= (double)sqrt(pow(x - moverX, 2) + pow(y - moverY, 2)) + noPath&& map[y + 1][x] != 4 && path[y + 1][x] == 1000) {
							path[y + 1][x] = k + 1;
							Pathed = 1;
						}
						/*Check up*/
						if ((double)sqrt(pow(x - moverX, 2) + pow(y - 1 - moverY, 2)) <= (double)sqrt(pow(x - moverX, 2) + pow(y - moverY, 2)) + noPath&& map[y - 1][x] != 4 && path[y - 1][x] == 1000) {
							path[y - 1][x] = k + 1;
							Pathed = 1;
						}

					}
				}
			}
			/*If we found a path set reset the wall checking and move up in pathing number*/
			if (Pathed == 1) {
				noPath = 0;
				k++;
			}
			/*If no path was found increase the noPath variable, this variable allows tiles not closer to
			the character to still be activated*/
			else {
				noPath++;
			}
			/*Clear console*/
			system("cls");
			/*Draw to console*/
			for (int y = 0; y < mapHeight; y++) {
				for (int x = 0; x < mapWidth; x++) {
					if (path[y][x] != 1000) {
						/*If the tiles pathing number is visited, then write its pathing number*/
						printf(" %d", path[y][x]);
					}
					else {
						/*Draw out the walls*/
						if (map[y][x] == 4) {
							printf(" W");
						}
						else {
							/*Draw out the open rooms*/
							printf(" .");
						}
					}
				}
				printf("\n");
			}
			/*If the character tile has been visited end the pathfinding*/
			if (path[moverY][moverX] != 1000) {
				break;
			}
		}

		while (1) {
			start = clock();
			stop = clock();
			/*Runs every 0.2 seconds, this is to see the character move*/
			while (stop < start + 200)
				stop = clock();
			/*Clear console*/
				system("cls");
				/*Draw to console*/
				for (int y = 0; y < mapHeight; y++) {
					for (int x = 0; x < mapWidth; x++) {
						/*100 tiles around the character is drawn out as normal
						This gives a "fog of war" effect were the character can't see beyond 100 tiles
						At current size that means we can see everything but this can be changed to a lower number
						to get the limited view effect.*/
						if ((double)sqrt(pow(x - moverX, 2) + pow(y - moverY, 2)) < 100) {
							switch (map[y][x]) {
								/*
								1 = open room
								2 = character
								3 = target
								4 = wall
								*/
							case 1: printf(" ."); break;
							case 2: printf(" C"); break;
							case 3: printf(" X"); break;
							case 4: printf(" W"); break;
							}
						}
						else {
							/*unknown tile if the "fog of war" effect is active*/
							printf(" *");
						}
					}
					printf("\n");
				}
				while (1) {
					/*If the tile to the right has lower path number the current tile move there*/
					if (path[moverY][moverX + 1] < path[moverY][moverX]) {
						map[moverY][moverX] = 1;
						moverX++;
						map[moverY][moverX] = 2;
						break;
					}
					/*Check left*/
					if (path[moverY][moverX - 1] < path[moverY][moverX]) {
						map[moverY][moverX] = 1;
						moverX--;
						map[moverY][moverX] = 2;
						break;
					}
					/*Check down*/
					if (path[moverY + 1][moverX] < path[moverY][moverX]) {
						map[moverY][moverX] = 1;
						moverY++;
						map[moverY][moverX] = 2;
						break;
					}
					/*Check up*/
					if (path[moverY - 1][moverX] < path[moverY][moverX]) {
						map[moverY][moverX] = 1;
						moverY--;
						map[moverY][moverX] = 2;
						break;
					}
					/*Because every theck break the loop the character movement favors certain directions.
					The character will still move optimaly tough*/
				}
			}

		getchar();
		return 0;
}