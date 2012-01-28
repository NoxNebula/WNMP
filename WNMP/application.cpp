#include "application.h"
#include "process.h"
#include <iostream>


Application::Application(void) {}
Application::~Application(void) {}


void Application::PHP(int Mode) {
	switch(Mode) {
		case(START):
			if(Process::Create(".\\php\\php-cgi.exe", "-b 127.0.0.1:9000", ".\\php\\", false))
				std::cout << "PHP started" << std::endl;
			break;
		case(RESTART):
			if(Process::Stop("php-cgi.exe", 5) &&
				Process::Create(".\\php\\php-cgi.exe", "-b 127.0.0.1:9000", ".\\php\\", false))
				std::cout << "PHP restarted" << std::endl;
			break;
		case(STOP):
			if(Process::Stop("php-cgi.exe", 5))
				std::cout << "PHP stoped" << std::endl;
			break;
		default:
			std::cout << "Invalid Mode" << std::endl;
	}
}

void Application::NGINX(int Mode) {
	switch(Mode) {
		case(START):
			if(Process::Create(".\\nginx\\nginx.exe", "", ".\\nginx\\", false))
				std::cout << "NGINX started" << std::endl;
			break;
		case(RESTART):
			if(Process::Create(".\\nginx\\nginx.exe", "-s quit", ".\\nginx\\") &&
				Process::Create(".\\nginx\\nginx.exe", "", ".\\nginx\\", false))
				std::cout << "NGINX restarted" << std::endl;
			break;
		case(STOP):
			if(Process::Create(".\\nginx\\nginx.exe", "-s quit", ".\\nginx\\"))
				std::cout << "NGINX stoped" << std::endl;
			break;
		default:
			std::cout << "Invalid Mode" << std::endl;
	}
}

void Application::MySQL(int Mode) {
	switch(Mode) {
		case(START):
			if(Process::Create(".\\mysql\\bin\\mysqld.exe", "", ".\\mysql\\bin\\", false))
				std::cout << "MySQL started" << std::endl;
			break;
		case(RESTART):
			if(Process::Stop("mysqld.exe", 2) &&
				Process::Create(".\\mysql\\bin\\mysqld.exe", "", ".\\mysql\\bin\\", false))
				std::cout << "MySQL restarted" << std::endl;
			break;
		case(STOP):
			if(Process::Stop("mysqld.exe", 2))
				std::cout << "MySQL stoped" << std::endl;
			break;
		default:
			std::cout << "Invalid Mode" << std::endl;
	}
}