//things to fix for next time: quotes, exit function behaving bizarrely sometimes, and google unit test behaving wierdly
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include "Command.hpp"
#include "Command.cpp"
#include "Or.hpp"
#include "Or.cpp"
#include "And.hpp"
#include "And.cpp"
#include "Semicolon.hpp"
#include "Semicolon.cpp"
#include <cstring>
#include <string.h>
using namespace std;


Executable* breakupCommand(string str){
	vector<string> c;
	string strProcessed = str;
	bool firstQuoteSet = false;
	string theFirstStringInQuotes = "";
	unsigned indexOfFirstQuote = 0;
	unsigned indexOfSecondQuote = 0;
	
	//checks if there are any comments in the input and removes them

	
	
	//checks if there are quotes in the input and if there are, the index of the first and second occurance of the character '"' is taken
	for(unsigned i = 0; i < strProcessed.size(); i++){
		if(strProcessed[i] == '"' && !firstQuoteSet){
			firstQuoteSet = true;
			indexOfFirstQuote = i;
		}
		else if(strProcessed[i] == '"' && firstQuoteSet){
			indexOfSecondQuote = i;
		}			
	}
	if(indexOfFirstQuote != 0 && indexOfSecondQuote != 0){
		//im just assuming that theres only one set of quotes in a given command and that it is always the last argument for a command	
		theFirstStringInQuotes = strProcessed.substr(indexOfFirstQuote + 1, indexOfSecondQuote - indexOfFirstQuote-1);
		strProcessed = strProcessed.substr(0, indexOfFirstQuote);
	}
	
	//creates an array of characters that has the same values as strProcessed because strtok only takes in an array of chars terminated by a null char	
	int stringlength = strProcessed.length();
	char array[strProcessed.length()+1];
	strcpy(array, strProcessed.c_str());
	array[stringlength] = 0;	

	//after the array is made, breaks up the string every time there is a spacce and puts it into vector c, for example if str is "echo hello", c.at(0) = "echo" and c.at(1) = "hello"
	char* ptr = strtok(array, " ");
	
	while(ptr != NULL){
		//converts the char pointer to a string before adding it to the vector
		string x(ptr);
		c.push_back(x);
		ptr = strtok(NULL, " ");
	}
	
	//if theFirstStringInQuotes is not empty, then there was a quote in this output, so we add it back
	if(theFirstStringInQuotes != ""){
		c.push_back(theFirstStringInQuotes);
	}

	return new Command(c);
	
}

//helper function for Get_List_Commands to figure out if the current index is in a set of quotes
bool inQuotes(string str, int index){
	int quotes = 0;
	for(int i = 0; i < index; i++){
		if(str[i] == '"'){
			quotes++;
		}
	}

	//if there is an odd number of quotes behind the index, it will be in quotes if there is a quote after index
	if(quotes % 2 == 0){
		return false;
	}
	
	for(int i = index + 1; i < str.size(); ++i){
		if(str[i] == '"'){
			return true;
		}
	}
	return false;
	
	
}
/*
//Gets the string and separates it by connectors, then it uses the breackupCommand function to break up the command into its arguments
vector<vector<string> > Get_List_Commands(string str){
	vector<vector<string> > c; 
	//vector<string> temp;
	//begin deonotes the place where to start parsing each individual command
	unsigned begin = 0;
	for(unsigned i = 0; i < str.size(); i++){
		if(!inQuotes(str, i)){
			if(str[i] == '|' && str[i+1] == '|'){
				c.push_back(breakupCommand(str.substr(begin, i- begin)));
				//temp.push_back(str.substr(begin, i-begin));
				begin = i+2;
			}
			else if(str[i] == '&' && str[i+1] == '&'){
				c.push_back(breakupCommand(str.substr(begin, i- begin)));
				//temp.push_back(str.substr(begin, i-begin));
				begin = i+2;
			}
			else if(str[i] == ';' && str[i+1] == ' '){
				c.push_back(breakupCommand(str.substr(begin, i- begin)));
				//temp.push_back(str.substr(begin, i-begin));
				begin = i+2;
			}
		}	
	}
	c.push_back(breakupCommand(str.substr(begin)));
	//temp.push_back(str.substr(begin));
	
	return c;
}

vector<string> List_Connectors(string str){
	vector<string> c;
	for(unsigned i = 0; i < str.size(); i++){
		if(!inQuotes(str, i)){
			if(str[i] == '|' && str[i+1] == '|'){
				c.push_back("||");
			}
			else if(str[i] == '&' && str[i+1] == '&'){
				c.push_back("&&");
			}
			else if(str[i] == ';' && str[i+1] == ' '){
				c.push_back("; ");
			}
		}
	}
	return c;
}

Executable* createtree(vector<vector<char*> > commands, vector<string> connectors){
	Executable* root = new Command(commands.at(0));
	commands.erase(commands.begin());
	if(connectors.size() == 0){
		return root;
	}
	Executable* temp;
	
	while(connectors.size() != 0){
		if(connectors.at(0) == "||"){
			Executable* right = new Command(commands.at(0));
			temp = new Or(root, right);
			root = temp;
			commands.erase(commands.begin());
			connectors.erase(connectors.begin());
		}
		else if(connectors.at(0) == "&&"){		
			Executable* right = new Command(commands.at(0));
			temp = new And(root, right);
			root = temp;
			commands.erase(commands.begin());
			connectors.erase(connectors.begin());

		}
		else if(connectors.at(0) == "; "){
			Executable* right = new Command(commands.at(0));
			temp = new Semicolon(root, right);
			root = temp;
			commands.erase(commands.begin());
			connectors.erase(connectors.begin());

		}
	
	}
	return root;

}
*/
string removeComments(string str){
	for(unsigned i = 0; i < str.size(); i++){
		if(str.at(i) == '#'){
			return str.substr(0, i);
		}
	}
	return str;
}

bool no_connectors(string str){
	for(int i = 0; i < str.size(); i++){
		if(!inQuotes(str, i)){
			if(str.at(i) == ';' && str.at(i+1)== ' '){
				return false;
			}
			if(str.at(i) == '|' && str.at(i+1) == '|'){
				return false;
			}
			if(str.at(i) == '&' && str.at(i+1) == '&'){
				return false;
			}

		}
	}
	return true;
}

//new function 
int getIndexOfNextConnector(string str, int index) {
	//If index never found, return str.size()
	int indexOfNC; 

	//Give this index, find the next connector
	for (indexOfNC = index; indexOfNC < str.size(); indexOfNC++) {
		if (!inQuotes(str, indexOfNC)) { 

			if (str.at(indexOfNC) == ';') {
				return indexOfNC; 	
			}
			else if (str.at(indexOfNC) == '|' && str.at(indexOfNC + 1) == '|') {
				return indexOfNC;	 
			}
			else if (str.at(indexOfNC) == '&' && str.at(indexOfNC + 1) == '&') {
				return indexOfNC; 
			}
		 }
	}

	return indexOfNC; 
}


//new funct 2
int getIndexOfMatchingParenthesis(string str, int index) {
	int numLeftP = 0;
	int numRightP = 0; 

	int i;
	for (i = index; i < str.size(); i++) { 
		//returns if same number of  left and right parentheses
		if(!inQuotes(str, i)){
			if (str.at(i) == '(') {
				numLeftP++;
			}

			if (str.at(i) == ')') {
				numRightP++;
			
				if (numLeftP == numRightP) {
					return i;
				}		
			}
		}	
	}
	//if no closing thing
	return i; 
}

Executable* createtree(string str1){
	string str = removeComments(str1);
	if(no_connectors(str)){
		return breakupCommand(str);
	}
	string connector = "";
	string whatsleft;
	Executable* root = 0;
	Executable* temp = 0;
	int begin = 0;
	int i = 0;

	if(str.at(i) == '('){
		i = getIndexOfMatchingParenthesis(str, i);
		root = createtree(str.substr(begin+1, i-1));
		while(i != str.size() && (str.at(i) == ')' || str.at(i) == ' ')){
			i++;
		}
		if(i == str.size()){
			return root;
		}
	}
	else{
		i = getIndexOfNextConnector(str, i);
		root = createtree(str.substr(begin, i));
	}

	

	while(i != str.size()){
		if(str.at(i) == '&' && str.at(i+1) == '&'){
			connector = "&&";
		}
		else if(str.at(i) == '|' && str.at(i+1) == '|'){
			connector = "||";
		}
		else if(str.at(i) == ';' && str.at(i+1) == ' '){
			connector = "; ";
		}

		while(str.at(i) == '|' || str.at(i) == '&' || str.at(i) == ';' || str.at(i) == ' '){
			i++;
		}
		begin = i;
		
		if(str.at(i) == '('){
			i = getIndexOfMatchingParenthesis(str, i);
			temp = createtree(str.substr(begin+1, i-1));
			if(connector == "&&"){
				root = new And(root, temp);
			}
			else if(connector == "||"){
				root = new Or(root, temp);
			}
			else if(connector == "; "){
				root = new Semicolon(root, temp);
			}

			while(i != str.size() && (str.at(i) == ')' || str.at(i) == ' ')){
				i++;
			}
			if(i == str.size()){
				return root;
			}
		}
		else{
			i = getIndexOfNextConnector(str,i);
			temp = createtree(str.substr(begin, i));
			if(connector == "&&"){
				root = new And(root, temp);
			}
			else if(connector == "||"){
				root = new Or(root, temp);
			}
			else if(connector == "; "){
				root = new Semicolon(root, temp);
			}
			
			if(i == str.size()){
				return root;
			}
		}
		
	}
	return root;
}

int main(){
	while(1){
	cout << "$ ";	
	string input;
	
	getline(cin, input);
	
	//vector<vector<string> > commands = Get_List_Commands(input);
	//vector<vector<char*> > commandsChar;


	//vector<string> connectors =  List_Connectors(input);	
	
	/*
	for(int i = 0; i < connectors.size(); i++){
		cout << connectors.at(i) << endl;
	}
	*/

	/*	
	for(int j = 0; j < commands.size(); j++)
	{
		vector<char*> tempCharCommand;
		vector<string> tempCommand = commands.at(j);
	
		for(int i = 0; i < tempCommand.size(); ++i){
			tempCharCommand.push_back((char*)tempCommand.at(i).c_str());
		}
		commandsChar.push_back(tempCharCommand);
		tempCharCommand.clear();

		
	}
	*/
	/*	
	for(int i = 0; i < commandsChar.size(); ++i){
		for(int j = 0; j < commandsChar.at(i).size(); ++j){
			cout << "Vector " << i << ": \"" << commandsChar.at(i).at(j) << "\" ";
		}
		cout << endl;
	}
	*/
	
	Executable* x = createtree(input);
	x->execute();

	}
	
		return 0; 
}  

