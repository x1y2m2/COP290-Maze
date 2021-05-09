#include "setup.h"

bool** maze;

void maze_init(){
	maze = new bool*[HEIGHT];
	for(int i=0;i<HEIGHT;i++){
		maze[i] = new bool[WIDTH];
	}
	for(int i=0;i<HEIGHT;i++){
		for(int j=0;j<WIDTH;j++){
			maze[i][j] = true;
		}
	}
}

void maze_generate(int x, int y){
	maze[x][y] = false;
	while (true){
		int t = 0;
		if((x>1)&&(cc(x-1,y))){
			t++;
		}
		if((x<WIDTH-2)&&(cc(x+1,y))){
			t++;
		}
		if((y>1)&&(cc(x,y-1))){
			t++;
		}
		if((y<HEIGHT-2)&&(cc(x,y+1))){
			t++;
		}
		if(t>0){
			int r = rand()%t;
			if((x>1)&&(cc(x-1,y))){
				if(r>0){
					r--;
				}else if(r==0){
					maze_generate(x-1,y);
					continue;
				}
			}
			if((x<WIDTH-2)&&(cc(x+1,y))){
				if(r>0){
					r--;
				}else if(r==0){
					maze_generate(x+1,y);
					continue;
				}
			}
			if((y>1)&&(cc(x,y-1))){
				if(r>0){
					r--;
				}else if(r==0){
					maze_generate(x,y-1);
					continue;
				}
			}
			if((y<HEIGHT-2)&&(cc(x,y+1))){
				if(r>0){
					r--;
				}else if(r==0){
					maze_generate(x,y+1);
					continue;
				}
			}
		}else{
			break;
		}
	}
}

bool** setup()
{
	srand((unsigned int)time(NULL));
	maze_init();
	maze_generate(1,1);
	
	return maze;
}

bool cc(int x, int y){
	bool check = maze[x][y];
	int ch=0;
	if((x>1)&&(!maze[x-1][y])){
		ch++;
	}
	if((x<WIDTH-2)&&(!maze[x+1][y])){
		ch++;
	}
	if((y>1)&&(!maze[x][y-1])){
		ch++;
	}
	if((y<HEIGHT-2)&&(!maze[x][y+1])){
		ch++;
	}
	return check && (ch<2);
}
