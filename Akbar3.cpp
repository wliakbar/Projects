// Game in which you have to type in a random word correctly and within a specific time.
#include<iostream>
#include <ctime>
#include <cstdlib>
#include<chrono>
#include<algorithm>
using namespace std;

int main(){
	srand(time(0)); int ur_points=1000;
	//Game continues only if you are below 5000 and above 0 points.
	while(ur_points<5000 && ur_points>0){
		cout<<"\n\nYour current points "<<ur_points<<", type in order: ";
		string word; //Computer generated word
		for(unsigned int a=0;a<7;a++){ //'a' just represents the index
			word[a]='a'+(rand()%26);  //Random letters
	//Upper-case or lower-case letters are decided here on a 50-50 chance
			word[a]=((int(word[a])%2==0)?toupper(word[a]):tolower(word[a]));
			word+=word[a];
		} //Generates the random word
		cout<<word<<endl;
		sort(word.begin(), word.end()); //Puts the word in ASCII order
		string answer; //answer is what you type
		chrono::steady_clock::time_point begin = chrono::steady_clock::now();
		cin>>answer; //Type answer and time is being measured
		chrono::steady_clock::time_point end= chrono::steady_clock::now();
	//Time taken to type in millisecond= time.
		int time=chrono::duration_cast<chrono::milliseconds>(end-begin).count();
		cout<<endl<<time<<" milliseconds"<<flush;
		cout<<((time<=12000)?", you made it within the interval of 12000...":
			" you *failed* it within the interval of 12000...");
		int difference=0; //difference of letters between the two words
		while(answer.length()<word.length() || answer.length()>word.length()) {
			((answer.length()<word.length())?answer+=' ': word+=' ');
		} //pads spaces if the two words don't have equal characters
		for(int i=0;i<word.length();i++) {   //Calculates difference
				difference+=abs(word[i]-answer[i]);
		} // And checks if the letters match between the two words
		if(answer!=word) {cout<<endl<<"Answer must be: "<<word<<
			" String offset is "<<difference;
		}
	//if you take longer than 12 seconds the following will occur:
		((time>12000)? difference*=2:difference);
		int penalty= ((time>12000)? (time-12000):0);
		((time>12000)? ur_points-=(time-12000):ur_points);
	//if you type the write word in under 12 seconds you get 500 points
		((answer==word)&&(time<=12000)? ur_points+=500:ur_points-=difference);
		cout<<". Your penalty is:  "<<(difference+penalty);
	}
	cout<<endl<<"Bye"<<endl;
	return 0;
}

