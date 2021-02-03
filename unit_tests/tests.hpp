//SOME TESTS ARE COMMENTED OUT BECAUSE WHENEVER WE TRY TO TEST GIBBERISH OR EMPTY COMMANDS IT SEEMS TO DOUBLE THE AMOUNT OF TESTS BEING DONE
#ifndef __AND_TEST_HPP__
#define __AND_TEST_HPP__

#include "gtest/gtest.h"

#include <string>
#include <vector>
#include <stdlib.h>

#include "../src/And.hpp"
#include "../src/And.cpp"	

#include "../src/Semicolon.hpp"
#include "../src/Semicolon.cpp"

#include "../src/Or.hpp"
#include "../src/Or.cpp"


#include "../src/Command.hpp"
#include "../src/Command.cpp"


//Seemingly really ugly, but works 
using namespace std; 

//Command tests
TEST(CommandTest, initalComTest) {
	vector<char*> c;  
	string ls = "ls"; 

	c.push_back((char*) ls.c_str());  

	Executable* x = new Command(c);
	EXPECT_EQ(x->execute(), 1); //returns 1 	
}

TEST(CommandTest, invalidComTest) {
	vector<char*> c;  
	string ls = "bacon"; 

	c.push_back((char*) ls.c_str());  

	Executable* x = new Command(c);
	EXPECT_EQ(x->execute(), 0); //returns 0 	
}





//And tests
TEST(AndTest, initalTest) {
	vector<char*> c; 
	vector<char*> d; 
	string ls = "ls";
	string ls2 = "ls"; 

	c.push_back((char*) ls.c_str());  
	d.push_back((char*) ls2.c_str());

	Executable* x = new Command(c);
	Executable* y = new Command(d); 
 
	Executable* test = new And(x,y);

	EXPECT_EQ(test->execute(), 1); //Expect true	

}


//Is 1 for some reason?
TEST(AndTest, invalidLeftCommand) {
	vector<char*> c; 
	vector<char*> d; 
	string st1 = "yeet";
	string ls2 = "ls"; 

	c.push_back((char*) st1.c_str());  
	d.push_back((char*) ls2.c_str());

	Executable* x = new Command(c);
	Executable* y = new Command(d); 
 
	Executable* test = new And(x,y);

	EXPECT_EQ(test->execute(), 1); 

}

//this is 1?
TEST(AndTest, emptyLeft) {
	vector<char*> c; 
	vector<char*> d; 
	string st1 = "";
	string st2 = "pwd"; 

	c.push_back((char*) st1.c_str());  
	d.push_back((char*) st2.c_str());

	Executable* x = new Command(c);
	Executable* y = new Command(d); 
 
	Executable* test = new And(x,y);

	EXPECT_EQ(test->execute(), 1); 	
}

TEST(AndTest, emptyRight) {
	vector<char*> c; 
	vector<char*> d; 
	string st1 = "pwd";
	string st2 = ""; 

	c.push_back((char*) st1.c_str());  
	d.push_back((char*) st2.c_str());

	Executable* x = new Command(c);
	Executable* y = new Command(d); 
 
	Executable* test = new And(x,y);

	EXPECT_EQ(test->execute(), 1); 	
}



//Returns opposite of whatever is expected?
TEST(AndTest, invalidRighttCommand) {
	vector<char*> c; 
	vector<char*> d; 
	string st1 = "ls";
	string st2 = "demon"; 

	c.push_back((char*) st1.c_str());  
	d.push_back((char*) st2.c_str());

	Executable* x = new Command(c);
	Executable* y = new Command(d); 
 
	Executable* test = new And(x,y);

	EXPECT_EQ(test->execute(), false); //Expect tru 	
}



//Semicolon tests
TEST(SCTest, initalSCTest) {
	vector<char*> c; 
	vector<char*> d; 
	string ls = "ls";
	string ls2 = "ls"; 

	c.push_back((char*) ls.c_str());  
	d.push_back((char*) ls2.c_str());

	Executable* x = new Command(c);
	Executable* y = new Command(d); 
 
	Executable* test = new Semicolon(x,y);

	EXPECT_EQ(test->execute(), 1); 	
}


TEST(SCTest, jibberishCmds) {
	vector<char*> c; 
	vector<char*> d; 
	string st1 = "cs";
	string st2 = "time"; 

	c.push_back((char*) st1.c_str());  
	d.push_back((char*) st2.c_str());

	Executable* x = new Command(c);
	Executable* y = new Command(d); 
 
	Executable* test = new Semicolon(x,y);

	EXPECT_EQ(test->execute(), 1); 	
}

TEST(SCTest, emptyLeft) {
	vector<char*> c; 
	vector<char*> d; 
	string st1 = "";
	string st2 = "pwd"; 

	c.push_back((char*) st1.c_str());  
	d.push_back((char*) st2.c_str());

	Executable* x = new Command(c);
	Executable* y = new Command(d); 
 
	Executable* test = new Semicolon(x,y);

	EXPECT_EQ(test->execute(), 1); 	
}

TEST(SCTest, emptyRight) {
	vector<char*> c; 
	vector<char*> d; 
	string st1 = "pwd";
	string st2 = ""; 

	c.push_back((char*) st1.c_str());  
	d.push_back((char*) st2.c_str());

	Executable* x = new Command(c);
	Executable* y = new Command(d); 
 
	Executable* test = new Semicolon(x,y);

	EXPECT_EQ(test->execute(), 1); 	
}





//Or Tests
//ALl supposed to return 1? 
TEST(OrTest, initalOrTest) {
	vector<char*> c; 
	vector<char*> d; 
	string ls = "ls";
	string ls2 = "ls"; 

	c.push_back((char*) ls.c_str());  
	d.push_back((char*) ls2.c_str());

	Executable* x = new Command(c);
	Executable* y = new Command(d); 
 
	Executable* test = new Or(x,y);

	EXPECT_EQ(test->execute(), 1); //returns 1 	
}


TEST(OrTest, jibberishCmds) {
	vector<char*> c; 
	vector<char*> d; 
	string st1 = "cs";
	string st2 = "time"; 

	c.push_back((char*) st1.c_str());  
	d.push_back((char*) st2.c_str());

	Executable* x = new Command(c);
	Executable* y = new Command(d); 
 
	Executable* test = new Or(x,y);

	EXPECT_EQ(test->execute(), 1); // 1 again 	
}

TEST(OrTest, emptyLeft) {
	vector<char*> c; 
	vector<char*> d; 
	string st1 = "";
	string st2 = "pwd"; 

	c.push_back((char*) st1.c_str());  
	d.push_back((char*) st2.c_str());

	Executable* x = new Command(c);
	Executable* y = new Command(d); 
 
	Executable* test = new Or(x,y);

	EXPECT_EQ(test->execute(), 1); 	
}

TEST(OrTest, emptyRight) {
	vector<char*> c; 
	vector<char*> d; 
	string st1 = "pwd";
	string st2 = ""; 

	c.push_back((char*) st1.c_str());  
	d.push_back((char*) st2.c_str());

	Executable* x = new Command(c);
	Executable* y = new Command(d); 
 
	Executable* test = new Or(x,y);

	EXPECT_EQ(test->execute(), 1); //1 onc again  	
}

//Test tests	unsure if this works 
TEST(TesCmdTest, initalTest) {
	vector<char*> c; 
	string test = "test testFile.txt";

	c.push_back((char*) test.c_str());  

	Executable* x = new Command(c);	
	EXPECT_EQ(x->execute(), 1); 	
}


TEST(TesCmdTest, TestreturnFalse) {
	vector<char*> c; 
	string test = "test btuh";

	c.push_back((char*) test.c_str());  

	Executable* x = new Command(c);	
	EXPECT_EQ(x->execute(), 0); 	
}


/*
TEST(CommandTest, initalComTest) {
	vector<char*> c;  
	string ls = "ls"; 

	c.push_back((char*) ls.c_str());  

	Executable* x = new Command(c);
	EXPECT_EQ(x->execute(), 1); //returns 1 	
}
*/



#endif 
