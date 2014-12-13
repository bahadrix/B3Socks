//
//  Service.h
//  b3socks
//
//  Created by Bahadir on 12/12/14.
//  Copyright (c) 2014 bahadir.me. All rights reserved.
//

#ifndef __b3socks__Service__
#define __b3socks__Service__

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>


#define SERVER_ERR_CANT_OPEN_PORT 101
#define SERVER_ERR_BINDING_ERROR 102
#define SERVER_ERR_ACCEPT 103
#define SERVER_ERR_READ 104
#define SERVER_ERR_WRITE 105

#define SERVER_LISTENING_START 201
#define SERVER_CLIENT_CONNECTED 202
#define SERVER_MESSAGE_RECIVED 203


namespace B3Socks {
 
    class ServiceListener {
    public:
        virtual void onAttach() {};
        virtual void onListeningStart(int *port) {};
        virtual void onClientConnect(char* ip){};
        virtual bool onMessageReceive(char *msg, char** response) {return true;};
        virtual bool onError(int errorCode){return false;};
        
    };
    
    class Service {
        bool started;
        int port, bufferSize;
        int sockfd, newsockfd;
        ServiceListener *listener;
    public:
        Service(ServiceListener*, int port, int bufferSize);
        void start();
        void stop();
        
        ~Service() {
            stop();
        }
        
    };
}

#endif /* defined(__b3socks__Service__) */
