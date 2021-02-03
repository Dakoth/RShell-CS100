#include "Command.hpp"
Command::Command(vector<string> c){
	this->c = c;	
}

bool Command::execute(){
	//for some reason we have to have a vector<string> member variable and then convert it into a char* for it to work
	//we cannot just have a char* vector apparently or we get some very wierd pointer error
	vector<char*> charVector;
	for(int i = 0; i < c.size(); ++i){
		charVector.push_back((char*)c.at(i).c_str());
	}
	//create a boolean to check if the command executes without failure
	bool actuallyWorked = 1;
	string firstCommand(charVector.at(0));
	string lastInput(c.at(charVector.size() -1)); 
	//converting the vector in to a char* array
	char* args[charVector.size() + 1];
	for(int i = 0; i < c.size(); ++i){
		args[i] = charVector.at(i);
	}

	//setting the end of the argumants array to NULL
	args[c.size()] = 0;
	

	//checking to see if exit was called
	string Exit = "exit";

	
	
	if(Exit  == firstCommand){
		exit(0);
	}

	
	//checking if the command is a test	
	
	if("test" == firstCommand || "[" == firstCommand && "]" == lastInput ){
		string firstTestInput(args[1]);
		struct stat buf;
		
		if(firstTestInput == "-e"){
			
			if(stat(args[2], &buf) == 0){
				cout << "(True)" << endl;
				return true;
			}
			else{
				cout << "(False)" << endl;
				return false;
			}			
		}
		else if(firstTestInput == "-d"){
			
			stat(args[2], &buf);
			if(S_ISDIR(buf.st_mode)){
				cout << "(True)" << endl;
				return true;
			}
			else{
				cout << "(False)" << endl;
				return false;
			}
		}
		else if(firstTestInput == "-f"){
			
			stat(args[2], &buf);
			if(S_ISREG(buf.st_mode)){
				cout << "(True)" << endl;
				return true;
			}
			else{
				cout << "(False)" << endl;
				return false;
			}
		}
		else{
			if(stat(args[1], &buf) == 0){
				cout << "(True)" << endl;
				return true;	
			}
			else{
				cout << "(False)" << endl;
				return false;
			}
		}
	}
	
	
	//executes functions using execvp
	pid_t pid = fork();
	if(pid == 0){
			
		if(execvp(args[0], args) == -1){
			perror("exec");
			actuallyWorked = 0;
			exit(0);
		}
	}
	if(pid > 0){
		waitpid(pid, NULL, 0);
		/*
		if(wait(0) == -1){
			perror("wait");
		}*/
	}
	return actuallyWorked;
			
}
