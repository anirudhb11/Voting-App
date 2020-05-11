#include "packet.h"
int main(){
    int clSocket;
    struct sockaddr_in serverAddr;

    clSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(clSocket < 0){
        printf("Error in creating client socket:\n");
        return 0;
    }
    printf("Client Socket successfully created:\n");

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int c1 = connect(clSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
    if(c1 < 0){
        printf("Error in connecting to server:\n");
        return 0;
    }
    printf("Connection to server created:\n");
    printf("*******\n");
    printf("Please enter you token that has been provided to you by EC:\n");
    int tokenVal;
    scanf("%d", &tokenVal);

    auth clientAuth, serverResp;
    clientAuth.token = tokenVal;
    

    int b = send(clSocket, &clientAuth, sizeof(auth), 0);
    if(b < 0){
        printf("Error in sending token to EC, Please try again:\n");
    }
    int r = recv(clSocket, &serverResp, sizeof(serverResp), 0);
    if(r > 0){
        if(serverResp.status == 1)
            printf("You have been successfully Authenticated:\n");
        else
            printf("Your authentication has failed:\n");
    }
    else{
        printf("Your authentication has failed:\n");
    }



    
}