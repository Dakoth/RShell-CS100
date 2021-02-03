
#ifndef __COMMAND_HPP__
#define __COMMAND_HPP__
#pragma once 


#include "Executable.hpp"
#include <string.h>
#include <cstdlib>
using namespace std;

class Command : public Executable{
	private:
		vector<string> c;
	public:
		Command(vector<string> c);

		bool execute();
			
};

#endif
