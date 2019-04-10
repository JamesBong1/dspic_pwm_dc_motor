/*
 * File:   cli.c
 * Author: sstevens
 *
 * Created on April 9, 2019, 11:58 AM
 */


#include <stdio.h>
#include <string.h>
#include "xc.h"
#include "cli.h"
#include "user.h"
#include "project.h"
#include "ring_buffer.h"

uint16_t mthd_parameters[5];

bool print_stage_info();

bool fun(void)
{
    return true;
}

_cli_shell cli_commands[] = 
{
    { "vel" , "vel n - set velocity <n:0-100>"                , NULL },
    { "pos" , "pos n - set desired postion <n: -100 - 100 >"  , NULL },
    { "6"   , "<- of numeric keypad - move stage in reverse"  , NULL },
    { "4"   , "-> of numeric keypad - move stage forward"     , NULL },
    { "info", "info - print current stage settings"           , print_stage_info },
    { NULL }
};

bool print_stage_info()
{
    printf( "\n\rMMC-200 dc motor controller test version %s", _Version );
    printf( "\n\rstage info: ");
    printf( "\n\rstage.velocity: %1.3f"     , (double)stage.velocity);
    printf( "\n\rstage.acceleration: %ld"   , stage.accel           );
    printf( "\n\rstage.position: %ld"       , stage.position        );
    return true;
}


/*
 *	\brief! parses data from Serial_Data_t
 *
 *  \param! raw - pointer to serial data struct <ser_cfg.h>
 */
int parse_raw_data( _ring_buffer * raw )
{
	char cmd[10]={0};
    int  par_q;   //parameter quantity of string.

	par_q = sscanf( (const char *)raw->rx , "%s %x %x %x %x" , cmd , &mthd_parameters[0], \
                        &mthd_parameters[1], &mthd_parameters[2] , &mthd_parameters[3] );
	
	/* copy parsed cmd string to raw.buf */
	memcpy( &raw->rx , cmd , sizeof(cmd) );
	
	return par_q;
}

/*
 *	\brief! executes a parsed string 
 *
 *  \param! cmd  - pointer to serial data struct <ser_cfg.h>
            CMDS - pointer to SHELLCMD struct
 */
bool execute_command( _ring_buffer * cmd , _cli_shell *command_lut )
{
        
    parse_raw_data( cmd );
    
    while( command_lut->token )
    {
        if( !strcmp( (char *)cmd->rx , command_lut->token ) )
        {
            //cmd.mtd_par = command_lut->mthd_par;
            if( (*command_lut->entry)( (char *)cmd->rx ) ) 
               return true;
        }
        command_lut++;
    }

	 return false;
}
