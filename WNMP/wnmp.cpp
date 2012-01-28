#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include "stdio.h"
#include "base.h"
#include "process.h"
#include "application.h"

using namespace std;


vector<string> SprintArgs(int *i, int argc, const char* argv[]) {
	vector<string> Additive;
	while(*i < argc) {
		if(*i == argc - 1)
			break;
		if(str_contains(argv[*i + 1], "-"))
			break;

		Additive.push_back(argv[++(*i)]);
	}
	return Additive;
}

void RunArgs(int Mode, vector<string> Additives) {
	if(!Additives.empty()) {
		// Handle the given
		string A;
		for(unsigned int i = 0; i < Additives.size(); i++) {
			A = Additives[i];
			if(A == "php")
				Application::PHP(Mode);
			else if(A == "nginx")
				Application::NGINX(Mode);
			else if(A == "mysql")
				Application::MySQL(Mode);
			else {
				cout << "Unknown Argument \"" << A << "\"" << endl;
				break;
			}
		}
	} else {
		// Handle all
		Application::PHP(Mode);
		Application::MySQL(Mode);
		Application::NGINX(Mode);
	}
}

void HandleArgs(int argc, const char* argv[]) {
	for(int i = 1; i < argc; i++) {
		if(str_contains(argv[i], "-")) {
			if(!strcmp(argv[i], "-s") || !strcmp(argv[i], "-start")) {
				vector<string> Args = SprintArgs(&i, argc, argv);
				RunArgs(Application::START, Args);
			} else if(!strcmp(argv[i], "-r") || !strcmp(argv[i], "-restart")) {
				vector<string> Args = SprintArgs(&i, argc, argv);
				RunArgs(Application::RESTART, Args);
			} else if(!strcmp(argv[i], "-c") || !strcmp(argv[i], "-stop")) {
				vector<string> Args = SprintArgs(&i, argc, argv);
				RunArgs(Application::STOP, Args);
			} else {
				cout << "Unknown Argument \"" << argv[i] << "\"" << endl;
				break;
			}
		}
	}
}

int main(int argc, const char* argv[]) {
	HandleArgs(argc, argv);
	
	return 0;
}
