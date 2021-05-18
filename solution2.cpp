#include<iostream>
#include<vector>
#include<unordered_set>
#include<unordered_map>

using hashSet = std::unordered_map<int, std::unordered_set<int>>;

void takeInput(hashSet &aliveCells, std::vector<std::vector<int>> &test){
	for(int i=0; i<test.size(); i++){
		int xCoord = test[i][0];
		int yCoord = test[i][1];
		aliveCells[xCoord].insert(yCoord);
	}
};

void getAllNeighbouringDeadCells(hashSet &neighbouringDeadCells, hashSet &aliveCells){
	for(auto i: aliveCells){
		for(auto j: i.second){
			int xCoord = i.first;                                 
			int yCoord = j;
			int dx[] = {1,1,0,-1,-1,-1,0,1};                                        
			int dy[] = {0,-1,-1,-1,0,1,1,1};			
			for(int k=0; k<8; k++){
				xCoord += dx[k];
				yCoord += dy[k];
				if((aliveCells.count(xCoord)==0)||(aliveCells[xCoord].count(yCoord)==0)){
					neighbouringDeadCells[xCoord].insert(yCoord);
				}
				xCoord -= dx[k];
				yCoord -= dy[k];
			}
		}
	}
};

void getAliveToAlive(hashSet &aliveCells, hashSet &nextGenAliveCells){
	for(auto i: aliveCells){
		for(auto j: i.second){
			int xCoord = i.first;                                
			int yCoord = j;
			int dx[] = {1,1,0,-1,-1,-1,0,1};                                        
			int dy[] = {0,-1,-1,-1,0,1,1,1};
			int numAliveNeighbours = 0;			
			for(int k=0; k<8; k++){
				xCoord += dx[k];
				yCoord += dy[k];
				if((aliveCells.count(xCoord))&&(aliveCells[xCoord].count(yCoord))){
					numAliveNeighbours++;
				}
				xCoord -= dx[k];
				yCoord -= dy[k];
			}
			if((numAliveNeighbours==2)||(numAliveNeighbours==3)){
				nextGenAliveCells[xCoord].insert(yCoord);
			}
		}
	}
};

void getDeadToAlive(hashSet &neighbouringDeadCells, hashSet &aliveCells, hashSet &nextGenAliveCells){
	for(auto i: neighbouringDeadCells){
		for(auto j: i.second){
			int xCoord = i.first;                                
			int yCoord = j;
			int dx[] = {1,1,0,-1,-1,-1,0,1};                                        
			int dy[] = {0,-1,-1,-1,0,1,1,1};
			int numAliveNeighbours = 0;			
			for(int k=0; k<8; k++){
				xCoord += dx[k];
				yCoord += dy[k];
				if((aliveCells.count(xCoord))&&(aliveCells[xCoord].count(yCoord))){
					numAliveNeighbours++;
				}
				xCoord -= dx[k];
				yCoord -= dy[k];
			}
			if(numAliveNeighbours==3){
				nextGenAliveCells[xCoord].insert(yCoord);
			}
		}
	}
};

void printCells(hashSet &aliveCells){
	for(auto i: aliveCells){
		for(auto j: i.second){
			std::cout<<i.first<<", "<<j<<"\n";
		}
	}
}

void solution(std::vector<std::vector<int>> &test){
	hashSet aliveCells;
	takeInput(aliveCells, test);
	
	hashSet neighbouringDeadCells;
	getAllNeighbouringDeadCells(neighbouringDeadCells, aliveCells);
	
	hashSet nextGenAliveCells;
	
	getAliveToAlive(aliveCells, nextGenAliveCells);
	
	getDeadToAlive(neighbouringDeadCells, aliveCells, nextGenAliveCells);
	
	std::cout<<"First Gen\n";
	printCells(aliveCells);
	std::cout<<"Next Gen\n";
	printCells(nextGenAliveCells);
};


int main(){
	std::vector<std::vector<int>> test1{{1,1},{1,2},{2,1},{2,2}};                         
	std::vector<std::vector<int>> test2{{0,1},{1,0},{2,1},{0,2},{1,2}};
	std::vector<std::vector<int>> test3{{1,1},{1,0},{1,2}};
	std::vector<std::vector<int>> test4{{1,1},{1,2},{1,3},{2,2},{2,3},{2,4}};
	
	solution(test1);                                                                      
	std::cout<<"...........\n";
	solution(test2);
	std::cout<<"...........\n";
	solution(test3);
	std::cout<<"...........\n";
	solution(test4);
	
	return 0;
}
