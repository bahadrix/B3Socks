//
//  main.cpp
//  b3socks
//
//  Created by Bahadir on 12/12/14.
//  Copyright (c) 2014 bahadir.me. All rights reserved.
//

#include <iostream>
#include "service.h"

using namespace B3Socks;
using namespace std;

class Listener: public ServiceListener {
  
    bool onError(int errorCode) {
        
        cerr << "Error code: " << errorCode << endl;
        
        return true; //continue if possible
    }
    
    void onListeningStart() {
        cout << "Service is running now." << endl;
    }
    
};


int main(int argc, const char * argv[]) {
    
    
    Listener *listener = new Listener();
    
    Service *service = new Service(listener, 12500, 256);
    
    service->start();
    
    
    delete service;
    delete listener;
    
    return 0;
}
