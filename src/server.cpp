#include "../inc/server.hpp"

Server::Server(){
	this->sckt = socket(AF_INET, SOCK_STREAM, 0);
	if (this->sckt == -1){
		std::cout << "Error: socket creation failed" << std::endl;
		exit(1);
	}
	this->addr.sin_family = AF_INET;
	this->addr.sin_addr.s_addr = INADDR_ANY;
	this->addr.sin_port = htons(8080);
	if (bind(this->sckt, (struct sockaddr*)&this->addr, sizeof(this->addr)) == -1){
		std::cout << "Error: socket binding failed" << std::endl;
		exit(1);
	}
	if (listen(this->sckt, 10) == -1){
		std::cout << "Error: socket listening failed" << std::endl;
		exit(1);
	}
}

Server::Server(int port){
	this->sckt = socket(AF_INET, SOCK_STREAM, 0);
	if (this->sckt == -1){
		std::cout << "Error: socket creation failed" << std::endl;
		exit(1);
	}
	this->addr.sin_family = AF_INET;
	this->addr.sin_addr.s_addr = INADDR_ANY;
	this->addr.sin_port = htons(port);
	if (bind(this->sckt, (struct sockaddr*)&this->addr, sizeof(this->addr)) == -1){
		std::cout << "Error: socket binding failed" << std::endl;
		exit(1);
	}
	if (listen(this->sckt, 10) == -1){
		std::cout << "Error: socket listening failed" << std::endl;
		exit(1);
	}
}

Server::~Server(){
	close(this->sckt);
}

void Server::start(){
	std::cout << "Server started" << std::endl;
	FD_ZERO(&fdSet);
	FD_SET(sckt, &fdSet);
	if (listen(sckt, 5) == -1) {
		perror("Error al escuchar");
		exit(EXIT_FAILURE);
	}
	while (1){
		fd_set tempSet = fdSet;
		int maxFd = sckt;
		int selectResult = select(maxFd + 1, &tempSet, NULL, NULL, NULL);
		 if (selectResult == -1) {
			perror("Error en select");
			exit(EXIT_FAILURE);
		}
		for (int i = 0; i <= maxFd; ++i) {
			if (FD_ISSET(i, &tempSet)) {
				if (i == sckt) {
					// Nuevo cliente conectado
					socklen_t clientLen = sizeof(addr);
					int client = accept(sckt, (struct sockaddr*)&addr, &clientLen);
					// Agregar el nuevo socket al conjunto
					FD_SET(client, &fdSet);
					if (client > maxFd) {
						maxFd = client;
					}
					std::cout << "Client connected" << std::endl;
					std::ifstream file("html/index.html");
					std::stringstream buffer;
					buffer << file.rdbuf();
					std::string contents = buffer.str();
					// Create HTTP response with HTML contents
					std::string response = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: " + std::to_string(contents.length()) + "\n\n" + contents;
					send(client, response.c_str(), response.length(), 0);
				} else {
					// Datos disponibles en un cliente existente
					char buffer[1024];
					int bytesRead = recv(i, buffer, sizeof(buffer), 0);
					if (bytesRead <= 0) {
						// Error o cliente desconectado
						close(i);
						FD_CLR(i, &fdSet);
					} else {
						// Procesar datos del cliente
						buffer[bytesRead] = '\0';
						std::cout << "Data: " << buffer << std::endl;
						recv(i, buffer, sizeof(buffer), 0);
					}
				}
			}
		}
	}
}