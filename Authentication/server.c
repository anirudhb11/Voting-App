#include "packet.h"

typedef struct tok{
    int tokenNumber;
    bool isValid;
}tokens;

tokens validTokens[MAXCLIENTS];

tokens tokenGiver(){
    tokens t;
    t.isValid = true;
    t.tokenNumber = rand()%10000;
    return t;
}

int find(int t){
    for(int i=0;i<MAXCLIENTS; i++){
        if(validTokens[i].tokenNumber ==  t && validTokens[i].isValid == true){
            validTokens[i].isValid = false;
            return 1;
        }
    }
    return 0;

}
int main(){
    
    for(int i=0;i<MAXCLIENTS;i++){
        validTokens[i] = tokenGiver();
        printf("%d: %d\n", i, validTokens[i].tokenNumber);
    }
    int sockServer;
    sockServer = socket(AF_INET, SOCK_STREAM, 0);
    if(sockServer < 0){
        printf("Error in socket connection on server side:\n");
        return 0;
    }
    printf("Server Socket created successfully:\n");

    struct sockaddr_in serverAddr;

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int r1 = bind(sockServer, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if(r1 < 0){
        printf("Error in binding :\n");
        return 0;
    }
    printf("Binding successful:\n");

    int l = listen(sockServer, MAXCLIENTS);
    if(l < 0){
        printf("Error in listening:\n");
        return 0;
    }
    printf("Now listening:\n");
    //waiting for new connections from clients
    struct sockaddr_in newClientAddr;
    int sz = sizeof(newClientAddr);
    int newClientSock;
    while(1){
        
        newClientSock = accept(sockServer, (struct sockaddr *)&newClientAddr, (socklen_t *)&sz);

        if(newClientSock < 0){
            printf("Connection from client failed:\n");
            return 0;
        }
        //Dispays IP:PORT of client.
        printf("Connection accepted from %s:%d\n", inet_ntoa(newClientAddr.sin_addr), ntohs(newClientAddr.sin_port));

        //Going to fork for the child process;
        pid_t childProcess;
        if((childProcess = fork()) == 0 ){//child process
            auth packFromClient, packToClient;
            int r = recv(newClientSock, &packFromClient, sizeof(packFromClient), 0);
            if(r < 0){
                printf("Error in rcving packet from client:\n");
            }
            else{
                int t = packFromClient.token;
                int status = find(t);
                if(status == 0){
                    printf("Sending auth fail to client:\n");
                    packToClient.status = 0;
                    int s = send(newClientSock, &packToClient, sizeof(packToClient), 0);
                    if(s < 0){
                        printf("Error in sending:\n");
                    }



                }
                else{
                    printf("Sending auth pass to client:\n");
                    packToClient.status = 1;
                    int s = send(newClientSock, &packToClient, sizeof(packToClient), 0);
                    if(s < 0){
                        printf("Error in sending:\n");
                    }



                }


            }


        }

    }

    


}