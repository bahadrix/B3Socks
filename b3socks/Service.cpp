//
//  Service.cpp
//  b3socks
//
//  Created by Bahadir on 12/12/14.
//  Copyright (c) 2014 bahadir.me. All rights reserved.
//

#include "Service.h"

using namespace B3Socks;

Service::Service(ServiceListener* listener, int port, int bufferSize) {
    
    this->started = false;
    this->listener = listener;
    this->port = port;
    this->bufferSize = bufferSize;


}

void Service::start() {
    
    
    
    socklen_t clilen;
    char buffer[bufferSize];
    
    struct sockaddr_in serv_addr, cli_addr;
    
    
    
    
    //Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        listener->onError(SERVER_ERR_CANT_OPEN_PORT);
        return;
    }
    
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);
    
    //Bind
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        listener->onError(SERVER_ERR_BINDING_ERROR);
        return;
    }
    
    //Listen
    listen(sockfd,5);
    
    listener->onListeningStart();
    
    clilen = sizeof(cli_addr);
    
    //Wait for connection and then accept it.
    newsockfd = accept(sockfd,
                       (struct sockaddr *) &cli_addr,
                       &clilen);
    
    
    if (newsockfd < 0) {
        if(!listener->onError(SERVER_ERR_ACCEPT)) {
            stop();
            return;
        }
    }
    
    
    char *client_ip =  inet_ntoa(cli_addr.sin_addr);
    
    listener->onClientConnect(client_ip);
    
    //Wait for client to send data and then read it
    int n; //bytes read
    bzero(buffer,bufferSize);
    
    //while start
    
    n = read(newsockfd,buffer,bufferSize - 1);
    
    if (n < 0) {
        if(!listener->onError(SERVER_ERR_READ)) {
            stop();
            return;
        }
    }
    
    listener->onMessageReceive(buffer, n);
    
    /* write back to client
     n = write(newsockfd,"I got your message",18);
     
     if (n < 0) {
     fprintf(stderr,"ERROR writing to socket");
     }
     */
    stop();
}

void Service::stop() {
    close(newsockfd);
    close(sockfd);
}