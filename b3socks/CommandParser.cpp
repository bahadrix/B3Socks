//
//  CommandParser.cpp
//  b3socks
//
//  Created by Bahadir on 12/12/14.
//  Copyright (c) 2014 bahadir.me. All rights reserved.
//

#include "CommandParser.h"


char PING[] = "PING";
char PONG[] = "PONG";

CommandParser::CommandParser() {
    
}

bool CommandParser::parse(char *command, char **response){

    if(std::strcmp(command, PING) == 0) {
        *response = PONG;
    } else {
        *response = nullptr;
    }

    return false;
}