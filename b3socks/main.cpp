//
//  main.cpp
//  b3socks
//
//  Created by Bahadir on 12/12/14.
//  Copyright (c) 2014 bahadir.me. All rights reserved.
//

#include <iostream>
#include "Service.h"
#include "CommandParser.h"
#include "../blacklib/BlackLib.h"

using namespace B3Socks;
using namespace std;

class Listener: public ServiceListener {
    CommandParser *parser;
    
    
public:
    
    Listener(CommandParser *parser) {
        this->parser = parser;
    }
    
    bool onError(int errorCode) {
        
        cerr << "Error code: " << errorCode << endl;
        
        return true; //continue if possible
    }
    
    void onListeningStart(int *port) {
        cout << "Service is running now." << endl;
        cout << "Port: " << *port << endl;
        cout << "--------------------------------------" << endl;
        
        test();
    }
    
    void test() {
        //test msgRec
        char msg[] = "PING";
        char* response;
        onMessageReceive(msg, &response);
        cout << "Response: " << response << endl;
    }
    
    void onClientConnect(char *ip) {
        
        cout << "Client connected: " << ip << endl;
   
        
    }
    
    bool onMessageReceive(char *msg, char** response) {
        
        bool loop = parser->parse(msg, response);
        
        return loop;
    }
    
};


void testGPIO() {
 
    BlackLib::BlackGPIO led(BlackLib::GPIO_60, BlackLib::output, BlackLib::SecureMode);
    

    led.setValue(BlackLib::low);
    for(int i = 0; i < 6; i++) {
        led.toggleValue();
        sleep(1);
    }
}

int main(int argc, const char * argv[]) {
    cout << "--------------------------------------" << endl;
    cout << "Beaglebone Socket Service by Bahadrix." << endl;
    cout << "--------------------------------------" << endl;
    
    cout << "Testing GPIO..";
    
    testGPIO();
    
    cout << "Starting..\n";
    
    CommandParser *parser = new CommandParser();
    
    Listener *listener = new Listener(parser);
    
    Service *service = new Service(listener, 12500, 256);
    
    service->start();
    

    delete service;
    delete listener;
    delete parser;
    
    return 0;
}
