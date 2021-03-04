//
//  main.cpp
//  CS232 Command Shell
//
//  Created by Victor Norman on 1/20/15.
//  Copyright (c) 2015 Victor Norman. All rights reserved.
//
//  Edited by David Reidsma on 3/3/2021
//

#include <iostream>
#include "shell.h"

int main(int argc, const char *argv[], char *envp[])
{
    Shell myShell(envp);
    myShell.run();
    return 0;
}
