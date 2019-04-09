/*
 * File:   cli.c
 * Author: sstevens
 *
 * Created on April 9, 2019, 11:58 AM
 */


#include <stdio.h>

#include "xc.h"
#include "cli.h"

bool fun(void)
{
    return true;
}

_cli_shell cli_commands[] = 
{
    { "duty" , "duty n set duty cycle <n-duty cycle>", fun  },
    { NULL }
};


