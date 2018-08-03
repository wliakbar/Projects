//This program structures a user entered program and outputs it as a paragraph where each line has a 
//specific number of characters decided by the user.
#include<iostream>
#include<vector>
using namespace std;
vector<string>in_paragraph;// This is the paragraph entered by user
void fix_print(vector<string>paragraph, int &width, int &uwidth){
	for (int i = 0; i < paragraph.size(); ++i) {
		width+=paragraph[i].length();
		if(i==paragraph.size()-1){ //This pads spaces to the end of last word
			int x=uwidth-width;
			while(x!=1){
				paragraph[paragraph.size()-1]+=" ";
				x--;}}
		if(((width+paragraph[i+1].length())>=uwidth)){// if a line still has
				int x=uwidth-width;					  // less characters than
				while(x!=0){						  // desired width(uwidth)
					paragraph[i-1]+=" ";			  // pad spaces
					x--;}
		}
		if(width<uwidth && (((width+1)+paragraph[i+1].length())<=uwidth)){
			paragraph[i]+=" ";
			width+=1; continue;
		}//Adds spaces between words and fit as many words according to uwidth
		 if(width==uwidth||(((width+1)+paragraph[i+1].length())>uwidth)){
			paragraph[i]+="|\n|";
			width=0; continue;
		}//if desired length is exceeded print on new line
		}
	cout<<"|"; //The following prints the box and the paragraph
	for (int i = 0; i < uwidth; ++i) cout<<"=";
	cout<<"|";cout<<endl; cout<<"|";
	for (int i = 0; i < paragraph.size(); ++i){
		cout<<paragraph[i];
	}
	cout<<"|";cout<<endl; cout<<"|";
	for (int i = 0; i < uwidth; ++i) cout<<"=";
	cout<<"|";
} //This void is responsible for adjusting and printing the text!!
int main() {
	cout << "Enter text, empty return will quit the input" << endl << "> ";
	string sentence, word;
	while (true) {
		getline(cin, sentence);
		cout << "> ";
		if (sentence == "") { //if input is empty break
			break;
		}
		for (int i = 0; i < sentence.length(); ++i) {
			if (!isspace(sentence[i])) { //if character is not a space
				word += sentence[i];
			}
			if ((i!=0 && isspace(sentence[i]) && !isspace(sentence[i-1])) || i
					== sentence.length() - 1) {
				in_paragraph.push_back(word);
				word=""; //if character is space the a word is complete
			}
		} //push back all the words in the in_paragraph vector
	}
	int width = 0; // x is the width of the text
	int lword=in_paragraph[0].length(); //lword is the longest word
		for (int i = 0; i < in_paragraph.size(); ++i) {
			int x= in_paragraph[i].length();
			if(x>lword) lword=x; continue;
	} //updates//keeps track of the longest word
	vector<string>paragraph; //helps in running the following loop
	while(true){			 // by resetting the vector
		width=0; paragraph=in_paragraph; //resets all the values and runs
		cout<<"Enter the width of the text: ";int uwidth=0; cin>>uwidth;
		while(uwidth<lword) { // uwidth is the desired width entered by you
			if(uwidth>=lword || uwidth==0) break;
			cout<<"Shorter than the longest word "<<lword<<endl;
			cout<<"Enter the width of the test: ";cin>>uwidth;
		} //checks if uwidth is greater/equal to the longest word
		if(uwidth==0) break; //breaks if desired width (uwidth) is 0
		fix_print(paragraph, width, uwidth);
		cout<<endl;
		paragraph.clear(); //clears the vector for now to execute the loop
	}
	cout<<"Bye!";
	return 0;
}
