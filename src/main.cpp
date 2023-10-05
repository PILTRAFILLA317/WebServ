#include "../inc/server.hpp"

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fstream>
#include <sstream>

int main(int ac, char** av){
	if (ac != 2){
		std::cout << "Usage: ./WebServ <port>" << std::endl;
		return 1;
	}
	Server server(atoi(av[1]));
	server.start();
	return 0;
}
