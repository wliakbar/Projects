//Implemneted the game Hey, Get my Fish
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <vector>
#include <numeric>
#include <algorithm>
#include <regex>
#include <sstream>
using namespace std;
enum class Kind { COMP, HUMN, GONE, LIVE }; // global enumerator.
int myrandom (int i) { return rand()%i;} //help in randomly shuffling board
double distance(int a, int b, int c, int d){ //Calculates the distance between
	double value; value= sqrt(pow((c-a),2) + pow((d-b),2)); //two positions
	return value;
}
class Position { // class to hold board position.
  int m_row; int m_col;
public:
  Position(const int r = 0, const int c = 0) : m_row(r), m_col(c) {}
  void newrow(int x){m_row=x;} void newcol(int x){m_col=x;}//sets new position
  int row() const { return m_row; } int col() const { return m_col; }
  friend ostream& operator<<(ostream&, const Position&);
};
Position operator+(const Position& a, const Position& b){//overloads the '+'
	Position result;  result.newrow(a.row()+b.row());	 // operator
	result.newcol(a.col()+b.col());
	return result;
}
ostream& operator<<(ostream& o, const Position& i) {
	o<<"("<<i.m_row<<","<<i.m_col<<")";
	return o;
}
class Ice {   // class to hold each ice float on game board.
  Kind m_knd; // who is occuplied now, human (HUMN) computer (CMP)?
  int  m_num; // number of fish
public:
  Ice() : m_knd(Kind::LIVE), m_num(rand() % 3 + 1) {}
  void set_comp() { m_knd = Kind::COMP; }
  void set_humn() { m_knd = Kind::HUMN; }
  void set_gone() { m_knd = Kind::GONE; }
  int  get_fish() const { return m_num; }
  bool is_good()  const { // can reach this float?
    return m_knd != Kind::COMP && m_knd != Kind::HUMN && m_knd != Kind::GONE;
  }
  friend ostream& operator<<(ostream&, const Ice&);
};
ostream& operator<<(ostream& o, const Ice& i) {
  switch (i.m_knd) {
  case Kind::COMP: o << " (" << i.m_num << ')'; break; // computer.
  case Kind::HUMN: o << " =" << i.m_num << '='; break; // human.
  case Kind::GONE: o << "  . " ; break;
  case Kind::LIVE: o << "  " << i.m_num << ' '; break;
  default: cerr << "Unknown switch at operator<<(ostream&, const Ice&)...";
    abort();
  }
  return o;
}
class Board { // class to hold board situation.
  int m_size;   vector<vector<Ice> > m_board;       // 2D ice floe.
  int m_num_comp, m_num_humn;         // fish count for human and computer.
  Position m_pos_comp, m_pos_humn;    // current position.
  bool m_comp_passed, m_humn_passed;  // is player passed the turn?
public:
  Board(const int s = 8) : m_size(s), m_num_comp(0), m_num_humn(0),
			   m_comp_passed(false), m_humn_passed(false) {
    for (int row = 0; row < s; ++row) {
      vector<Ice> arow;
      for (int col = 0; col < s; ++col) arow.push_back(Ice());
      m_board.push_back(arow);
    }
  }
  void init() {
    vector<int> row(m_size), col(m_size);
    iota(row.begin(), row.end(), 0);
    random_shuffle(row.begin(), row.end(), myrandom);
    iota(col.begin(), col.end(), 0);
    random_shuffle(col.begin(), col.end(), myrandom);
    m_pos_comp = Position(row[0], col[0]);m_pos_humn = Position(row[1], col[1]);
    m_board[m_pos_comp.row()][m_pos_comp.col()].set_comp(); // place computer.
    m_board[m_pos_humn.row()][m_pos_humn.col()].set_humn(); // place human.
  }
  int get_fish_num(const Kind& k) const {
    return k == Kind::COMP? m_num_comp : m_num_humn;
  }
  void passed(const Kind& k) {
    switch(k) {
    case Kind::COMP: m_comp_passed = true; break;
    case Kind::HUMN: m_humn_passed = true; break;
    default: cerr << "Unknown switch at Board::passed ()..."; abort();
    }
  }
  bool is_game_over() const { return m_comp_passed && m_humn_passed; }
  bool is_valid_move(const Position& p, const Kind& k) const {//Checks if move
    if (!m_board[p.row()][p.col()].is_good()) return false;	  // is legal
    const Position& s = k == Kind::COMP? m_pos_comp : m_pos_humn;
    //If the rows of the desired and the current position are both even or odd
    if((s.row()%2==0&&p.row()%2==0) || (s.row()%2!=0&&p.row()%2!=0)){
    	int diff=((p.row()-s.row())/2); //half of difference between the rows
    	if((s.row()<p.row() && s.col()<=p.col()) ||        //downright
    			(s.row()>p.row() && s.col()>=p.col())){   //or upleft direction
    		if(s.col()+diff!=p.col()){return false;} //the new column has to be
    	}									//the old column plus the diff
    	if((s.row()<p.row() && s.col()>=p.col()) ||        //downleft
    			(s.row()>p.row() && s.col()<=p.col())){   //or upright direction
    		if(s.col()-diff!=p.col()){return false;} //the new column has to be
    	}										//the old column minus the diff
    } //if current row is even but desired row is odd
    if(s.row()%2==0 && p.row()%2!=0){
    	int differ=p.row()-s.row(); int y=(differ+1)/2; int z=(differ-1)/2;
    	if(((s.row()<p.row()) && (s.col()<p.col())) ||    //downright
    			((s.row()>p.row()) && (s.col()>p.col()))){   //upleft
    		if(s.col()+y!=p.col()){return false;} //the new column has to be
    		}						//the y value plus the old column
    	if(((s.row()<p.row()) && (s.col()>p.col())) ||   //downleft
    			((s.row()>p.row()) && (s.col()<p.col()))){   //upright
    		if(s.col()-z!=p.col()){return false;}//the new column has to be
    	}						//the z value minus the old column
    	if(((s.row()<p.row()) && (s.col()==p.col())) || //if columns are equal
    			((s.row()>p.row()) && (s.col()==p.col()))){
    		if(y!=0 && z!=0){return false;} //y and z have to be 0
    	}
    } //if current row is odd but desired row is even
    if(s.row()%2!=0 && p.row()%2==0){ //it follows a similar process as before
    	int differ=p.row()-s.row(); int y=(differ+1)/2; int z=(differ-1)/2;
    	if(((s.row()<p.row()) && (s.col()<p.col())) || //downright
    			((s.row()>p.row()) && (s.col()>p.col()))){ //upleft
    		if((s.col()+z)!=(p.col())){return false;} //new column will be
    	}										//old plus z value
    	if(((s.row()<p.row()) && (s.col()>p.col())) || //downleft
    			((s.row()>p.row()) && (s.col()<p.col()))){ //upright
    		if(s.col()-y!=p.col()){return false;} //new column has to be
    	}									//old column minus y
    	if(((s.row()<p.row()) && (s.col()==p.col())) ||//if columns are equal
    			((s.row()>p.row()) && (s.col()==p.col()))){
    		if(y!=0 && z!=0){return false;} // y and z have to be 0
    	}
    }//Checks if anything before the desired position isgone:downright direction
   if(s.row()<p.row() && s.col()<=p.col()){ int a=s.row(); int b=s.col();
    	while(a!=p.row() && b!=p.col()){
    		a+=1; ((s.row()%2==0)? b+=1:b);
    		if (!m_board[a][b].is_good()) {return false;}
    		if(a==p.row() && b==p.col()){break;}
    		((a%2==0)? b+=1:b); a+=1;if(!m_board[a][b].is_good()){return false;}
    	}
    }//Checks if anything before the desired position isgone:upleft direction
    if((s.row()>p.row() && s.col()>=p.col())){ int a=s.row(); int b=s.col();
    	while(a!=p.row() && b!=p.col()){
    		a-=1; ((s.row()%2==0)? b:b-=1);
    		if (!m_board[a][b].is_good()) {return false;}
    	    if(a==p.row() && b==p.col()){break;}
    	    ((a%2==0)? b:b-=1); a-=1;if(!m_board[a][b].is_good()){return false;}
    	    }
    }//Checks if anything before the desired position isgone:downleft direction
    if((s.row()<p.row() && s.col()>=p.col())){ int a=s.row(); int b=s.col();
    	while(a!=p.row() && b!=p.col()){
    		a+=1; ((s.row()%2==0)? b:b-=1);
    		if (!m_board[a][b].is_good()) {return false;}
    	    if(a==p.row() && b==p.col()){break;}
    	    ((a%2==0)? b:b-=1); a+=1;if(!m_board[a][b].is_good()){return false;}
    	}
    }//Checks if anything before the desired position isgone:upright direction
    if((s.row()>p.row() && s.col()<=p.col())){ int a=s.row(); int b=s.col();
    	while(a!=p.row() && b!=p.col()){
    	    a-=1; ((s.row()%2==0)? b+=1:b);
    	    if(!m_board[a][b].is_good()){return false;}
    	    if(a==p.row() && b==p.col()){break;}
    	    ((a%2==0)? b+=1:b); a-=1;if(!m_board[a][b].is_good()){return false;}
    	}
   }//Checks if anything before the desired position isgone:right direction
    if(s.row()==p.row() && s.col()<p.col()){int b=s.col(); int a=s.row();
    	while(b!=p.col()){
    		b+=1;
    		if(!m_board[a][b].is_good()){return false;}
    	}
    }//Checks if anything before the desired position isgone:left direction
    if(s.row()==p.row() && s.col()>p.col()){int b=s.col(); int a=s.row();
       	while(b!=p.col()){
       		b-=1;
       		if(!m_board[a][b].is_good()){return false;}
       	}
    }
    return true;
  }
  bool move(const Position& p, const Kind k) {
    if (!is_valid_move(p, k)) return false;
    switch(k) {
    case Kind::COMP:
      m_num_comp += m_board[m_pos_comp.row()][m_pos_comp.col()].get_fish();
      m_board[m_pos_comp.row()][m_pos_comp.col()].set_gone(); m_pos_comp = p;
      m_board[m_pos_comp.row()][m_pos_comp.col()].set_comp(); break;
    case Kind::HUMN:
      m_num_humn += m_board[m_pos_humn.row()][m_pos_humn.col()].get_fish();
      m_board[m_pos_humn.row()][m_pos_humn.col()].set_gone(); m_pos_humn = p;
      m_board[m_pos_humn.row()][m_pos_humn.col()].set_humn(); break;
    default: cerr << "Unknown switch at Board::move()..."; abort();
    }
    return true;
  }
  Position find_best_move() const {
	  Position np; //will represent the current position
	  Position s_a=Position(-1,1); Position sub=Position(-1,0);
	  Position s_s=Position(-1,-1); Position add=Position(1,0);
	  Position a_s=Position(1,-1); Position a_a=Position(1,1);
	  Position lsub=Position(0,-1); Position radd=Position(0,1);
//The positions above are the movements player can make in different directions
	  vector<Position>best; best.clear();  np=m_pos_comp;
	  while(np.row()>0 && np.col()<=(m_size-1)){      //Upright direction
		  Position move= ((np.row()%2==0)? s_a:sub);//current row is even/odd
		  if((np.col()==(m_size-1)&&np.row()%2==0)|| //if possible to move
				  !m_board[(np+move).row()][(np+move).col()].is_good())break;
		  np=np+move; best.push_back(np); move= ((np.row()%2==0)? s_a:sub);
		  if(np.row()<=0 ||(np.col()==(m_size-1)&&np.row()%2==0)||
				  !m_board[(np+move).row()][(np+move).col()].is_good())break;
		  np=(np+move); best.push_back(np); continue;
	  } //save all movements in the vector best
	  np=m_pos_comp; //reset the position np
	  while(np.row()>0 && np.col()>=0){     //Upleft direction
		  Position move= ((np.row()%2==0)? sub:s_s); //current row is even/odd
		  if(!m_board[(np+move).row()][(np+move).col()].is_good() ||
				  (np.row()%2!=0&&np.col()<=0)) {break;}
		  np=(np+move); best.push_back(np); move= ((np.row()%2==0)? sub:s_s);
		  if(np.row()<=0 || !m_board[(np+move).row()][(np+move).col()].is_good()
				  || (np.row()%2!=0&&np.col()<=0)) {break;}
		  np=(np+move); best.push_back(np); continue;
	  }  //save all movements in the vector best
	  np=m_pos_comp;  //reset the position np
	  while(np.row()<(m_size-1) && np.col()>=0){   //Downleft direction
		  Position move= ((np.row()%2==0)? add:a_s); //current row is even/odd
		  if(!m_board[(np+move).row()][(np+move).col()].is_good() ||
				  (np.row()%2!=0&&(np).col()==0)) break;
		  np=(np+move); best.push_back(np); move= ((np.row()%2==0)? add:a_s);
		  if(np.row()==(m_size-1)||
				  !m_board[(np+move).row()][(np+move).col()].is_good() ||
				  (np.row()%2!=0&&(np).col()==0)) break;
		  np=(np+move); best.push_back(np); continue;
	  }//save all movements in the vector best
	 np=m_pos_comp;  //reset the position np
	 while(np.row()<(m_size-1) && np.col()<=(m_size-1)){ //Downright direction
		 Position move= ((np.row()%2==0)? a_a:add); //current row is even/odd
		 if((np.col()==(m_size-1)&&np.row()%2==0)||
				 !m_board[(np+move).row()][(np+move).col()].is_good())break;
		 np=(np+move); best.push_back(np); move= ((np.row()%2==0)? a_a:add);
		 if(np.row()==(m_size-1) || (np.col()==(m_size-1)&&np.row()%2==0)||
				 !m_board[(np+move).row()][(np+move).col()].is_good())break;
		 np=(np+move); best.push_back(np); continue;
	 } //save all movements in the vector best
	 np=m_pos_comp;  //reset the position np
	 while(np.col()>0){ 	//Left Direction
		 if(!m_board[(np+lsub).row()][(np+lsub).col()].is_good())break;
		 np=(np+lsub); best.push_back(np);} //subtracts 1 from column
	 np=m_pos_comp;
	 while(np.col()<(m_size-1)){ //Right Direction
		 if(!m_board[(np+radd).row()][(np+radd).col()].is_good())break;
		 np=(np+radd);best.push_back(np);}  //adds 1 to column
	 int tempcount=0; Position element;
	 for(int i=0; i<best.size(); i++){ //Finds the move with greatest distance
	 	Position tempelem= best[i];
	 	double x=distance(
	 			m_pos_comp.row(),m_pos_comp.col(),best[i].row(),best[i].col());
	 	if(x>tempcount) {tempcount=x; element=tempelem;}
	 }
	  for(int i=0;i<best.size();++i){//Prints  the possible moves for computer
		  double x=distance(		 //and their distances
				 m_pos_comp.row(),m_pos_comp.col(),best[i].row(),best[i].col());
		  cout<<best[i]<<" = "<<x<<endl; x=0;
	  }							//if no moves are available computer will pass
	 if(best.size()==0){element=Position(99,99);}
	 if(best.size()!=0)cout<<"\nBest move is "<<element;
    return element;
  }
  friend ostream& operator<<(ostream&, const Board&);
};

ostream& operator<<(ostream& o, const Board& b) {
  char c = 'Z' - b.m_size * 2 + 1;
  o << "  ";
  for (int col = 0, len = b.m_size * 2; col < len; ++col)
    o << setw(2) <<char(c + col);
  o << endl;
  for (int row = 0; row < b.m_size; ++row) {
    cout <<char('A' + row);
    if (!(row % 2)) o << setw(2) << ' ';
    for (int col = 0; col < b.m_size; ++col) o << b.m_board[row][col];
    o << endl;
  }
  return o;
}
Position parse(const int size = 1) {    // study this but do not change logic.
  cout << "Enter " << (size == 1? "board size (4 - 8): " : "your move: ");
  string line, token;
  char ce = 'a' + size - 1, cs = 'z' - size * 2 + 1, row, col;
  regex pattern0("[[:space:]]*[4-8][[:space:]]*");
  regex pattern1("quit|pass");
  regex pattern2("[a-" + string(1, ce) + "][[:space:]]*[" + string(1, cs) + "-z][[:space:]]*");
  while (getline(cin, line)) { // read a whole line and convert to lower cases.
    transform(line.begin(), line.end(), line.begin(), ::tolower);
    if (size <= 1 && regex_match(line, pattern0)) {
      istringstream iss(line);          // then read into 2 parts.
      int num; iss >> num;              // stringstream is the one to use!
      return Position(num, 0);
    }
    else if (regex_match(line, pattern1)) {  // match reset or quit?
      if (line.find("quit") != string::npos) return Position(-1, -1);
      if (line.find("pass") != string::npos) return Position(99, 99);
    }
    else if (regex_match(line, pattern2)) {  // match 2 word input?
      istringstream iss(line);          // then read into 2 parts.
      iss >> row >> col;                // stringstream is the one to use!
      int r = row - 'a', c = col - cs;  // obtain row and column indexes.
      if (r % 2 == 0) { c -= 1;         // the first trick for this game.
	if (c < 0) { cout << "Value error, try again: "; continue; }
      }
      if (c % 2 != 0) { cout << "Value error, try again: "; continue; }
      return Position(r, c / 2);        // c/2 is the second trick.
    }
    assert(!cin.fail());                // placed for debugging purpose.
    cout << "Syntax error, try again: ";
  }
  abort(); // should not reach here, placed debugging purpose.
}
int main() {
  srand(time(0));
  cout << "Hey, That's My Fish, Akira's Version!" << endl;
  Position next = parse(); int size = next.row(); Board b(size); b.init();
  while(!b.is_game_over()) { // game over is both players passed their turn.
    cout << endl <<  b;
    cout << endl << "Your fish count is " << b.get_fish_num(Kind::HUMN)
	 << ", and computer's fish count is " << b.get_fish_num(Kind::COMP)
	 << "..." << endl;
    bool valid_move;
    do {
      next = parse(size);                             // read your turn.
      if (next.row() < 0 && next.col() < 0) goto end; // you quitted the game.
      if (next.row() > 90 && next.col() > 90) {       // you passed your turn.
    	  b.passed(Kind::HUMN);cout << "You passed..." << endl; break;
      }
      valid_move = b.move(next, Kind::HUMN);
      if (!valid_move) 	cout << "You can't move there..." << endl;
    } while (!valid_move);
    next = b.find_best_move();                        // find computer's move.
    if (next.row() > 90 && next.col() > 90) {       // comp passed turn.
    	b.passed(Kind::COMP);cout << "\nComputer passed..." << endl; continue;
    }
    b.move(next, Kind::COMP);                         // place the chosen move.
  }
  cout<<((b.get_fish_num(Kind::HUMN)>b.get_fish_num(Kind::COMP))?
		  "\nYou Win!" : "\nComputer Wins");
  end:
   cout << "\nBye..." << endl;
  return 0;
}
