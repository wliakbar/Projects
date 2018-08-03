// Project Name        : Akbar2.cpp        Author      : Wli Akbar
//	Odd/Eveen Dice Gambling Game
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int dices() { //stimulates a dice
	return rand() % 6 + 1;
}
int main() {
	int your_money=100,p1_money=100,p2_money=100;
	cout << "You Have: $" << your_money << endl << "Player 1 has: $"
			<< p1_money << endl << "Player 2 has: $" << p2_money<< endl;
	srand(time(0));
		//Game continues only if everyone has money
	while (your_money > 0 && p1_money > 0 && p2_money > 0) {
		int roles = dices() + dices(); char c_in; 			//House roles
		if ((roles%2) == 0) {c_in = 'c';} else {c_in='h'; } //cho or han
		char ur_in; int your_bet; 				//your input & bet
		cout << endl<<"Enter \"c\" (even) or \"h\" (odd): "; cin>>ur_in;
		cout<<"Enter your bet: $"; cin>>your_bet; cout<<endl;
		if(your_bet>your_money || (ur_in !='c' && ur_in!='h')){ //if the inputs
			cout<<"Wrong inputs\n"; continue;				    //are wrong
		}
		cout<< "You Bet: $"<<your_bet;
		int player1_bet, player2_bet; //Players bets
		char p1_in, p2_in; //Player inputs
		int x = rand() % 2 /*player 1 guess*/, y = rand() % 2; //player 2 guess
		(x == 0)? p1_in = 'c': p1_in = 'h'; //player 1 cho or han
		(y == 0)? p2_in = 'c': p2_in = 'h';	//player 2 cho or han
		((ur_in==c_in)? your_money+=your_bet : your_money-=your_bet);
	//Your new allowance is dependent on if you win or loose
		cout<<((ur_in==c_in)?"  \t ->You won!\n":"  \t ->You lost!\n");

		//Player 1 bet and process
		int halfp1=p1_money/2; //half of player 1 money
    //if Player 1 money goes below your money, player 1 bets with precaution
		player1_bet=((p1_money>= your_money)?rand()%p1_money+1:rand()%halfp1+1);
		cout<<"Player 1 bet: $"<<player1_bet;
	//Player 1 wins only if his/her input is the same as the house role
		cout<<((p1_in==c_in)?" ->Player 1 won!\n":" ->Player 1 lost!\n");
	//Player 1 new allowance is dependent on if he/she wins or looses
		((p1_in==c_in)? p1_money+=player1_bet:p1_money-=player1_bet);

		//PLayer 2 bet and process
		int halfp2=p2_money/2; //half of player 2 money
	//if Player 2 money goes below your money, player 2 bets with precaution
		player2_bet=((p2_money>= your_money)?rand()%p2_money+1:rand()%halfp2+1);
		cout<<"Player 2 bet: $"<<player2_bet;
	//Player 2 wins only if his/her input is the same as the house role
		cout<<((p2_in==c_in)?" ->Player 2 won!\n":" ->Player 2 lost!\n");
	//Player 2 new allowance is dependent on if he/she wins or looses
		((p2_in==c_in)? p2_money+=player2_bet:p2_money-=player2_bet);

		cout<<"\nYou now have: $"<<your_money<<"\nPlayer 1 now has: $"
				<<p1_money<<"\nPlayer 2 now has: $" << p2_money<<endl;
	}
	cout<<endl<<"You are Broke!"<<endl<<"Bye";
	return 0;
}
