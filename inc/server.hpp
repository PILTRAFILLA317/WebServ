#ifndef SERVER_HPP
#define SERVER_HPP

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class Server {
	public:
		Server();
		Server(int port);
		~Server();
		void start();
	private:
		int sckt;
		struct sockaddr_in addr;
		fd_set fdSet;
};

#endif
