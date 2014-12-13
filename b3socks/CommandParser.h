//
//  CommandParser.h
//  b3socks
//
//  Created by Bahadir on 12/12/14.
//  Copyright (c) 2014 bahadir.me. All rights reserved.
//

#ifndef __b3socks__CommandParser__
#define __b3socks__CommandParser__

#include <stdio.h>
#include <iostream>
#include <cstring>

class CommandParser {
    
public:
    CommandParser();
    bool parse(char* command, char** response);
    
};

#endif /* defined(__b3socks__CommandParser__) */
