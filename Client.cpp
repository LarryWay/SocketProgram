#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>


#define PORT 8080

int main(){
    int sock, valread;
    struct sockaddr_in server_addr;
    char buffer[1024] = {0};

    char* buff = new char[100];

    if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("\n Socket creation error \n");
        return -1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    // THE STRING IS THE IP ADDRESS OF THE SERVER TO BE CONNECTED TO
    if(inet_pton(AF_INET, "10.30.3.207", &server_addr.sin_addr) <= 0){
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
        printf("\nConnection Failed \n");
        return -1;
    }

    while(read(sock, buffer, 1024)){
        std::cout << buffer << std::endl;
        memset(&buffer, 0, sizeof(buffer));
    }



    return 0;
}