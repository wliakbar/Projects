//Implemenetd the famous crazy eights game
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <ctime>
using namespace std;
int myrandom (int i) { return rand()%i;} //help in randomly shuffling the deck
class Card {
  char m_suit; int  m_num; // card suit, either 'S','C','D','H'. & 1 through 13.
public:
  Card(const char s = '\0', const int n = 0) : m_suit(s), m_num(n) {}
  void usuit(char x) {m_suit=x; } void unum(int y) {m_num=y;}
  // ^ Helps to change the suit and number of the card
  char suit() const { return m_suit; } int num() const { return m_num; }
  //^ Returns the suit and number of the card
  bool operator<(const Card& lhd) const { return m_num < lhd.m_num; }
  friend ostream& operator<<(ostream& o, const Card& c) {
    o << c.m_suit;
    switch(c.m_num) {
    case 0:  o << '*'; break; // used to show wild number.
    case 1:  o << 'A'; break; // Ace.
    case 11: o << 'J'; break; // Jack.
    case 12: o << 'Q'; break; // Queen.
    case 13: o << 'K'; break; // King
    default: o << c.m_num;
    }
    return o;
  }
};
class Player {
  vector<Card> hand; // holding cards.
public:
  Player() {}        // default Ctor.
  void push_back(const Card& c) { hand.push_back(c); }
  int size() const { return hand.size(); } //Returns the # of cards
  char Suit(int a){return hand[a].suit();} //Returns the suit of the card
  int Numb(int a){return hand[a].num();} //Returns the number of the card
  Card remove(const int p) { // simply remove the specified position.
    Card c = hand[p]; hand[p] = hand.back();   // swap with the tail of vector.
    hand.pop_back();         // then remove the tail element.
    return c;                // the one removed will be turned back.
  }
  char find(){ //Finds the most occurring suit
	  char element; int count=0;
	  for(int i=0; i<hand.size(); i++){
		  char tempelem= hand[i].suit(); int tempcount=0;
		  for(int j=0; j<hand.size(); j++){
			  if(hand[j].suit()==tempelem){tempcount++;}
			  if(tempcount>count){
				  element=tempelem; count=tempcount;
			  }
		  }
	  }
	  return element;
  }
  Card creturn(const int r) {return hand[r];} //Returns the card
  friend ostream& operator<<(ostream& o, const Player& p) {
    for (int i = 0, len = p.hand.size(); i < len; ++i)
      o << setw(3) << '(' << (char)('a' + i) << ") " << p.hand[i];
    return o;
  }
};
int main() {
	srand(time(0));
	vector<Card> deck; // initialize a standard 52 card deck.
	for (int i = 1; i <= 13; ++i) {
		deck.push_back(Card('S', i)); deck.push_back(Card('C', i));
		deck.push_back(Card('D', i)); deck.push_back(Card('H', i));
	}
	random_shuffle(deck.begin(), deck.end(), myrandom); // shuffle them.
	vector<Player> players(4); // players altogether in the game.
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 6; ++j) { // each has #cards in the beginning.
			players[i].push_back(deck.back()); deck.pop_back();
		}
	Card pile = deck.back(); deck.pop_back(); // the initial card in the pile.
	if(pile.num()==8){
		cout<<"Pile has: "<<pile<<"\nPick a suit: "; char pick; cin>>pick;
		pile.usuit(pick);pile.unum(0);
	}
	char which;
	while (true) {
		if (deck.size() <= 0) {
			cout << "\nNo more card, ending game..." << endl; goto END;
    		}
		cout << "\nPile has " << pile << " <--- your turn" << endl;
		while (true) {
			char draw = 'a' + players[0].size();
			cout << endl << players[0] << "  (" << draw << ") draw" << endl;
			cout << "\nWhich one to play? "; cin >> which;
			if(which=='?'){ // ? mark is cheating!
				for(int i=1; i<players.size(); i++){ //displays other
					char nope= 'a'+players[i].size(); //players hand
					cout<<"Player "<<i<<" has: "<<players[i]<<" ("<<nope
							<<") draw"<<endl;
        			}
				continue;
			}
			if (which == draw) { //if draw is chosen
				if (deck.size() <= 0) { //And there are cards left in the deck
					cout << "\nNo more card, ending game...\n"; goto END;
				}
				players[0].push_back(deck.back()); deck.pop_back(); continue;
			}
			if(which>draw){cout<<"\nWrong input\n"; continue;} //error check
			if (which < draw) {	//if the pile and your card don't have the same:
				if(players[0].Numb(which-'a') != pile.num() && //the number,
        			players[0].Numb(which-'a') != 8 && //the number isn't 8,
        			players[0].Suit(which-'a') != pile.suit()) {//the suit then
					if(which!='?'){cout<<"Wrong input";} continue;//try again
				}
				if(players[0].Numb(which-'a') == 8) {//if # of card is 8
					players[0].remove(which - 'a');
				UWRONG: //error check
					cout<<"Which suit do you want? ";char us; cin>>us;
					if(us!= 'H' && us!='C' && us!='D' && us!='S'){
						cout<<"\nWrong input\n"; goto UWRONG;
					}
        			pile.usuit(us); pile.unum(0);
        			cout<<"Pile has: "<<pile<<endl; goto CHECK;
        		}
				if(players[0].Numb(which-'a') == pile.num() ||  //if number or
        			players[0].Suit(which-'a') ==pile.suit()) { //suit of the
        			pile = players[0].remove(which - 'a');  //cards match, good
        			cout<<"Pile has: "<<pile<<endl; goto CHECK;
				}
			CHECK: //You win if you don't have cards lefts
				if(players[0].size()==0) {cout<<"\nYou won!"; goto END;}
			}
			for(int i=1;i<4;++i){ //Generate card picks for other players
			START:
				for(int j=0; j<players[i].size(); ++j){ //Checks for the same
					if(players[i].Numb(j)==pile.num()) {// number first
						cout<<"\tPlayer "<<i<<" choose "<<players[i].creturn(j);
						pile=players[i].creturn(j);
						if(i!=3) {cout<<"\nPile has "<<pile<<endl;}
						players[i].remove(j); goto CARDFOUND;
						}
					}
				for(int j=0; j<players[i].size(); ++j){//Then the suit
					if(players[i].Numb(j)!=8 &&players[i].Suit(j)==pile.suit()){
						cout<<"\tPlayer "<<i<<" choose "<<players[i].creturn(j);
						pile=players[i].creturn(j);
						if(i!=3){cout<<"\nPile has "<<pile<<endl;}
						players[i].remove(j); goto CARDFOUND;
						}
					}
				for(int j=0; j<players[i].size(); ++j){//Then checks if there
					if((players[i].Numb(j)==8)){//       is a 8
						cout<<"\tPlayer "<<i<<" choose "<<players[i].creturn(j);
						players[i].remove(j);
						char ps=players[i].find();//find most occurring card
						pile.usuit(ps); pile.unum(0);//& pick it as the suit
						cout<<"\n\tPlayer "<<i<<" declared suit "<<ps<<endl;
						if(i!=3){cout<<"Pile has "<<pile<<endl;} goto CARDFOUND;
						}
					}								        //if nothing matches
				for(int j=0; j<players[i].size(); ++j){//players draws a card
					if(j==players[i].size()-1 && players[i].Numb(j) !=pile.num()
			    					&& (players[i].Suit(j) != pile.suit())) {
						if (deck.size() == 0) {
							cout << "\nNo more card, ending game...\n";goto END;
			    		}
						cout<<"\tPlayer "<<i<<" drawing..."<<endl;
						players[i].push_back(deck.back()); deck.pop_back();
						goto START;
					}
				}
				CARDFOUND:
				if(players[i].size()==0){cout<<"\nPlayer "<<i<<" won";goto END;}
				}//if any players finishes hand game ends
			break;
			}
    	}
	END:
    	cout << endl<<"\n[ Final card distributions ]" << endl;
    	for (int i = 0; i < 4; ++i) cout << "Player " << i << players[i] <<endl;
    return 0;
}
