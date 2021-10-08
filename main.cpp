#include<bits/stdc++.h> 
#include <iostream>
#include <vector>
#include <string>
using namespace std;
namespace nshex{
enum Against{
	Player=1,
	Computer=2
};
class Cell{
private:
int column;
int row;
char cellChar;
public:
	Cell(int Row,int Column,char CellChar){
		column=Column;
		row=Row;
		cellChar=CellChar;
	}
	Cell(){
	}
	inline int getColumn(){
		return column;
	}
	void setColumn(const int col){
		column=col;
	}
	inline int getRow(){
		return row;
	}
	void setRow(const int Row){
		row=Row;
	}
	char getCellChar(){
		return cellChar;
	}
	void setCellChar(const char CellChar){
		cellChar=CellChar;
	}
	bool compareCells(Cell other){
		return other.cellChar==cellChar ? true:false;
	}
	bool movedTo(){
		return cellChar!='.'?true:false;
	}
	bool compareChar(char c){
		return cellChar==c ? true:false;
	}
};
class AbstractHex{
	virtual void print();
	virtual void readFromFile(string fileName);
	virtual void writeToFile(string fileName);
	virtual void reset();
	virtual void setsize(int size);
	virtual void play();
	virtual void play(Cell position);
	virtual bool isEnd();
	virtual Cell operator()(int index1,int index2);
	virtual bool operator==(AbstractHex &other);
	virtual Cell lastMove();
	virtual int numberOfMoves();
};
class HexVector:public AbstractHex{
	private:
		int size;
		int playAgainst;
		Cell lastmove;
	public:
	vector< vector<Cell> > board;
	HexVector(vector<vector<Cell>> Board){
		board=Board;
	}
	void setsize(int Size){
		size=Size;
	}
	Cell lastMove(){
		if(&lastmove==NULL){
			throw;
		}
		else{
			return lastmove;
		}
	}
	void writeToFile(string fileName){
	 ofstream savetoFile;
	  savetoFile.open (fileName);
	  savetoFile<<size<<endl;
		for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			savetoFile<<board[i][j].getCellChar();
		}
		savetoFile<<endl;
	}
	if(playAgainst==2){
		savetoFile<<"Computer"<<endl;
	}
	else{
		savetoFile<<"Player"<<endl;
	}
	  savetoFile.close();
	  cout<<"Game saved to "<<fileName<<endl;
	  exit(1);
}
void readFromFile(string fileName){
ifstream loadFile(fileName);
  string str;
  int lineNo=0;
  int size;
  while (getline(loadFile, str)) {
  	if(lineNo==0){
  		stringstream stoi(str);
  		stoi>>size;
  		setsize(size);
  		board.resize(size);
		for (int i = 0; i < size; ++i)
		  board[i].resize(size);
	  	}
	  else{
	  	if(lineNo<=size){
	  	char cstr[str.size()+1];
	  	str.copy(cstr,str.size()+1);
	  	cstr[str.size()]='\0';
		for(int j=0;j<str.size();j++){
			board[lineNo-1][j].setRow(lineNo-1);
			board[lineNo-1][j].setColumn(j);
			board[lineNo-1][j].setCellChar(cstr[j]);
		}
		}
		else{
	    Against selectAgainst;
		if(str.find("Computer")!= string::npos){
		selectAgainst=Computer;
		}	
		else if(str.find("Player")!= string::npos){
		selectAgainst=Player;
		}
		playAgainst=selectAgainst;
		}
	  }
  	
    lineNo++;
	}
  cout<<"File loaded."<<endl;
}
void print(){
	for(int i=0;i<size;i++)
	cout<<" "<<char(i+97);
	cout<<endl;
	for(int i=0;i<size;i++){
		cout<<i+1<<" ";
		for(int j=0;j<i;j++)cout<<" ";
		for(int j=0;j<size;j++){
			cout<<board[i][j].getCellChar()<<" ";
		}
		cout<<" "<<endl;
	}
}
bool isEnd(){
	bool ended=true;
	if(!(ended=moveLeft())){
	cout<<"No moves left."<<endl;
     return ended;	
	}
	if(ended=checkPaths('x')){
     	cout<<"x Wins!"<<endl;
     	return ended;
	 }
	 if(
     ended=checkPaths('o')){
     	cout<<"o Wins!"<<endl;
     	return ended;
	 }
     return ended;
}
void Play(){
		int size=size;
	if(lastmove.getRow()==-1){
		int comx,comy;
		comx=rand()%size;
		if(comx==0) comy=rand()%size;
		else comy=0;
		lastmove=Cell(comx,comy,'o');
	}
	 int rnd = rand()%6;
	int nextx,nexty;
	switch(rnd){
		case 0:
			nexty=lastmove.getColumn();
			nextx=lastmove.getRow()+1;
			break;
		case 1:
			nexty=lastmove.getColumn();
			nextx=lastmove.getRow()-1;
			break;
		case 2:
			nexty=lastmove.getColumn()-1;
			nextx=lastmove.getRow()+1;
			break;
		case 3:
			nexty=lastmove.getColumn()-1;
			nextx=lastmove.getRow();
			break;
		case 4:
			nexty=lastmove.getColumn()+1;
			nextx=lastmove.getRow();
			break;
		case 5:
			nexty=lastmove.getColumn()+1;
			nextx=lastmove.getRow()-1;
			break;
	}
	if(nextx>size || nextx<0 || nexty>size||nexty<0){
	Play();
	}
	else if(board[nextx][nexty].getCellChar()!='.'){
		Play();
	}
	else{
		board[nextx][nexty].setCellChar('o');
		cout<<"Computer's move is: "<<nextx+1<<","<<char(nexty+97)<<endl;
		lastmove = Cell(nextx,nexty,'o');
		print();
	}	
	}
	void Play(Cell cellPosition){
		int row = cellPosition.getRow();
		int col = cellPosition.getColumn();
		char cellChar = cellPosition.getCellChar();
		board[row][col].setCellChar(cellPosition.getCellChar());
	}
	bool moveLeft(){
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			if(!board[i][j].movedTo())return true;
			
		}
	}
	return false;
	}
	
void toUppercase(bool **visited){
	for(int i=0;i<size;i++)
		cout<<" "<<char(i+97);
		cout<<endl;
		for(int i=0;i<size;i++){
			cout<<i+1<<" ";
			for(int j=0;j<i;j++)cout<<" ";
			for(int j=0;j<size;j++){
				if(visited[i][j]){
					cout<<(char)toupper(board[i][j].getCellChar())<<" ";
				}
				else{
					cout<<board[i][j].getCellChar()<<" ";
				}
			}
			cout<<" "<<endl;
		}
}
	bool checkPaths(char c){
		for(int i=0;i<size;i++){
		if(board[0][i].compareChar(c)){
				bool **visited; 
				visited = new bool*[size]; 
				for (int k = 0; k < size;k++){
					visited[k] = new bool[size];
				    memset(visited[k], false, size*sizeof(bool));
				}
				if(checkResult(0,i,c,0,visited)){
					toUppercase(visited);
					return true;
				}
				for( int k = 0 ; k < size ; k++ )
				{
				    delete[] visited[k]; 
				}
				delete[] visited;
			}
		}
		for(int i=0;i<size;i++){
			if(board[i][0].compareChar(c)){
				bool **visited; 
				visited = new bool*[size]; 
				for (int k = 0; k < size;k++){
					visited[k] = new bool[size];
				    memset(visited[k], false, size*sizeof(bool));
				}
				    
				if(checkResult(i,0,c,1,visited)){
					toUppercase(visited);
					return true;
				}
				for( int k = 0 ; k < size ; k++ )
				{
				    delete[] visited[k]; 
				}
				delete[] visited;
			}
		}
		return false;
	}
	bool checkResult(int y,int x,char c,int dir,bool **visited){
		char east='N',west='N',northeast='N',northwest='N',southeast='N',southwest='N';
			if(x+1<size) east = board[y][x+1].getCellChar(); 
			if(x-1>=0) west = board[y][x-1].getCellChar(); 
			if(y-1>=0&&x+1<size) northeast =board[y-1][x+1].getCellChar(); 
			if(y-1>=0) northwest = board[y-1][x].getCellChar(); 
			if(y+1<size) southeast = board[y+1][x].getCellChar();
			if(y+1<size&&x-1>=0) southwest =  board[y+1][x-1].getCellChar(); 
			visited[y][x]=true;
			if(dir==0){
				if(y==size-1)return true;
				else if(southeast==c&&!visited[y+1][x]){
					checkResult(y+1,x,c,dir,visited);
				}
				else if(southwest==c&&!visited[y+1][x-1]){
					checkResult(y+1,x-1,c,dir,visited);
				}
				else if(east==c&&!visited[y][x+1]){
					checkResult(y,x+1,c,dir,visited);
				}
				else if(west==c&&!visited[y][x-1]){
					checkResult(y,x-1,c,dir,visited);
				}
				else{
					return false;
				}
			}
			else{
					if(x==size-1)return true;
					else if(east==c&&!visited[y][x+1]){
					checkResult(y,x+1,c,dir,visited);
					}
					else if(southeast==c&&!visited[y+1][x]){
					checkResult(y+1,x,c,dir,visited);
					}
					else if(northeast==c&&!visited[y+1][x]){
					checkResult(y+1,x,c,dir,visited);
					}
					else if(southwest==c&&!visited[y+1][x-1]){
					checkResult(y+1,x-1,c,dir,visited);
					}
					else if(northwest==c&&!visited[y+1][x-1]){
					checkResult(y-1,x+1,c,dir,visited);
					}
				else{
					return false;
				}
			}
}
};
class HexArray1D:public AbstractHex{
	public:
		Cell* board;
};
template<typename T>
class HexAdapter:public AbstractHex{
	public:
		T board;
		HexAdapter(T Board){
			board=Board;
		}
};
}
void playGame(){
	int r,user=0;
	cout<<"Please enter board size (-1 to Load file):";
	cin>>r;
	
	if(r==-1){
		string fileName;
		cout<<"Enter filename to load game:";
		cin>>fileName;
		readFromFile(fileName);
	}
	else{
	setRowsize(r);
	setColsize(r);
	cout<<"Row and Column sizes of table defined as: "<<getRowsize()<<"x"<<getColsize()<<endl;
	cout<<"1-Play against user"<<endl<<"2-Play against computer"<<endl<<"Choice:";
	while(user<1||user>2){
		cin>>user;
		if(user<1||user>2){
			cout<<"Invalid input"<<endl;
		}
	}
	setCells();
	setPlayAgainst(user);
	}
	
	while(true){
		PlayersPlay('x');
		if(gameEnded()){
			break;
		}
		else{
			if(getPlayAgainst()==1){
			PlayersPlay('o');
		}
		else{
			Play();
		}
		if(gameEnded()){
			break;
		}
		}
}
}
class Hex{
	int rowsize;
	int playAgainst;
	int colsize;
public:
	static int minSize;
	Hex(const int rowSize,const int colSize){
		minSize=5;
		if(rowSize<minSize){
			rowsize=minSize;
		}
		if(colSize<minSize){
			colsize=minSize;
		}
	 vector<Cell> board(rowsize);
	}
	Hex(){
		rowsize=5;
		colsize=5;
	}
	Hex(int size){
		rowsize=size;
		colsize=size;
	}
	void setRowsize(int rowSize){
		if(rowSize<5){
			rowsize=5;
		}
		else{
		rowsize=rowSize;
		}
	}
	inline int getRowsize(){
		return rowsize;
	}
	void setColsize(int colSize){
		if(colSize<5){
		colsize=5;
		}
		else{
			colsize=colSize;
		}
		
	}
	inline int getColsize(){
		return colsize;
	}
	inline int getPlayAgainst(){
			return playAgainst;
	}
	
	void setCells(){
		board.resize(rowsize);
		for (int i = 0; i < rowsize; ++i)
		  board[i].resize(colsize);
			for(int i=0;i<rowsize;i++){
			for(int j=0;j<colsize;j++){
				board[i][j].setRow(i);
				board[i][j].setColumn(j);
				board[i][j].setCellChar('.');
			}
		}
		cout<<"Cells setted up"<<endl;
	}
	int charToint(char c){
		return int(c-97);
	}
	
void PlayersPlay(char p){
	do{
				displayBoard();
				cout<<p<<" playing."<<endl;
				int Orow,Ocol;
				char Ochar;
				cout<<"Enter coordinates (ex: 1a) or -1 to save:";
				cin>>Orow;
				if(Orow==-1){
					string fileName;
					cout<<"Enter filename to save game:";
					cin>>fileName;
					writeToFile(fileName);
				}
				else{
					cin>>Ochar;
				Ocol=charToint(Ochar);
				Orow--;
				if(Orow>=rowsize || Orow<0 || Ocol>=colsize||Ocol<0){
					cout<<"Invalid Coordinates!"<<endl;
				}
				else if(board[Orow][Ocol].getCellChar()!='.'){
					cout<<"Invalid Coordinates!"<<endl;
				}
				else{
				Cell c(Orow,Ocol,p);
				Play(c);
				break;
				}
				}
				}while(true);
}
	bool compareGames(Hex other){
		int otherCount=0;
		int thisCount=0;
			for(int i=0;i<rowsize;i++){
			for(int j=0;j<colsize;j++){
				if(board[i][j].getCellChar()!='.')
				thisCount++;
			}
		}
		int otherRow=other.getRowsize(),otherCol=other.getColsize();
			for(int i=0;i<otherCol;i++){
			for(int j=0;j<otherRow;j++){
				if(other.board[i][j].getCellChar()!='.')
				otherCount++;
			}
		}	
		return thisCount>otherCount ? true:false;
	}
};

int main(int argc, char** argv) {
	Hex Game1(4);
	Game1.playGame();
	return 0;
}
