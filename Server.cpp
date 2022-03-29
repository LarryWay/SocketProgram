#include <iostream>
#include <sys/socket.h>

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <string>

#define PORT 8079


int main(){
    int sockfd, new_socket;
    int opt = 1;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    std::string line;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    char buffer[1024] = {0};

    std::cout << "Awaiting Connection" << std::endl;

    if(sockfd == 0){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }


    /* if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
        perror("setsockopt");
        exit(EXIT_FAILURE);
    } */

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    int b = bind(sockfd, (struct sockaddr *)&address, sizeof(address));

    if(b < 0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    

    if(listen(sockfd, 3) < 0){
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(sockfd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0){
        perror("accept");
        exit(EXIT_FAILURE);
    }

    std::cout << "Start" << std::endl;

    while(true){
        memset(&buffer, 0, sizeof(buffer));
        
        std::getline(std::cin, line);
        char sendMessage[line.length() + 1];
        strcpy(sendMessage, line.c_str());
        std::cin.sync();

        send(new_socket, sendMessage, strlen(sendMessage),0);
        read(new_socket, buffer, 1024);
        std::cout << buffer << std::endl;
        
        
        
    }

    return 0;
}