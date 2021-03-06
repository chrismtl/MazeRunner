#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef vector<vector<int>> Table;
typedef vector<int> Coord;

Table maze;
Table all_directions = {{0,-1},{-1,0},{0,1},{1,0}};
vector<Table> all_paths;

Coord target;
Coord init_pos;

int count;
int SIZE_X;
int SIZE_Y;
int NB_COLORS;

string P;

bool bool_found = false;

string WRONG_COORD("==Wrong coordinates==");
string NOT_FOUND("== Target not found ==");
string FOUND    ("==   Target found   ==");

void createMaze(){
	string text_x,text_y,text_nb;
	
	cin>>P;
	cin>>text_x>>text_y;
	cin>>text_nb;
	
	SIZE_X = stoi(text_x);
	
	SIZE_Y = stoi(text_y);
	NB_COLORS = stoi(text_nb);
	
	Table em(SIZE_Y);
	maze = em;
	
}

void fillMaze(){
	for(int i(0); i<SIZE_Y; i++){
		for(int j(0); j<SIZE_X;j++){
			string text;
			cin>>text;
			int number = stoi(text);
			maze[i].push_back(number);
		}
	}
}

void display(){
	for(auto row : maze){
		for(auto number:row){
			cout<<number;
			if(number<10) cout<<"  ";
			else cout<<" ";
		}
		cout<<endl;
	}
}

void showVisited(vector<vector<bool>> visited){
	for(auto row:visited){
		for(auto n:row){
			cout<<n<<" ";
		}
		cout<<endl;
	}
}

void showCoord(string name, Coord coord){
	cout<<name<<": "<<coord[0]<<","<<coord[1]<<endl;
}

void setCoord(Coord& coord){
	string text_x,text_y;
	int x,y;
	do{
		cin>>text_x>>text_y;
		x = stoi(text_x);
		y = stoi(text_y);
	}while(x>SIZE_X || y>SIZE_Y || maze[y][x]!=NB_COLORS);
	
	coord = {y,x};
}

void explore(Coord position, Table path, vector<vector<bool>> visited){
	visited[position[0]][position[1]] = true;
	if(position==target){
		bool_found = true;
		all_paths.push_back({});
		for(auto element:path){
			all_paths[count].push_back(element);
		}
		count++;
	}
	
	else{
		for(unsigned int i(0); i<all_directions.size(); i++){
			Coord look(2);
			look[0] = position[0] + all_directions[i][0];
			look[1] = position[1] + all_directions[i][1];
			if((maze[look[0]][look[1]]==NB_COLORS && visited[look[0]][look[1]]==false) || look==target){
				Table new_path(path);	
				if(look!=target)new_path.push_back(look);
				explore(look, new_path, visited);
			}
		}
	}
}

void save(){
	system("cat > path.pbm");
}

int main(){
	createMaze();
	fillMaze();
	
	setCoord(init_pos);
	setCoord(target);
	//showCoord("Position",init_pos);	
	//showCoord("Target",target);
	
	vector<vector<bool>> visited(SIZE_Y);
	vector<bool> e(SIZE_X, false);
	for(int i(0); i<SIZE_Y;i++){
		visited[i]=e;
	}
	
	//Find all paths
	explore(init_pos, {}, visited);
	
	if(bool_found){
		//Find shortest path
		Table min_path = all_paths[0];
		for(Table path:all_paths){
			if(path.size()<min_path.size()) min_path = path;
		}
		
		//Draw shortest path
		double path_color  = (2./3.) * NB_COLORS;
		double point_color =  (1./3.) * NB_COLORS;
		maze[init_pos[0]][init_pos[1]] = (int) point_color;
		maze[ target[0] ][ target[1] ] = (int) point_color;
	
		for(Coord c:min_path){
			maze[c[0]][c[1]] = path_color;
		}
		cout<<P<<endl;
		cout<<SIZE_X<<" "<<SIZE_Y<<endl;
		cout<<NB_COLORS<<endl;
		display();
	}
}
