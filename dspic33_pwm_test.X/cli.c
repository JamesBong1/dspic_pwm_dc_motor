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
#include "pwm.h"
#include "uart.h"
#include "axis.h"

bool enter_cli_menu();
bool print_stage_info();
bool print_help();
bool print_jog_help();


_cli_menu current_cli_menu;
uint8_t  mthd_param;
uint16_t mthd_parameters[5];

const char* cli_menu_title_strs[ cCliMenus ] =
{
	"main menu",
	"axis jog" ,
};

_cli_shell main_cli_menu[] = 
{
    { "vel" , "vel n - set velocity <n:0-100>"                , NULL         , NULL             },
    { "pos" , "pos n - set desired postion <n: -100 - 100 >"  , NULL         , NULL             },
    { "jog" , "jog - manually control position of stage"      , cJog         , enter_cli_menu   },
    { "info", "info - print current stage settings"           , NULL         , print_stage_info },
    { "?"   , "? - help"                                      , NULL         , print_help       },
    { NULL }
};

_cli_shell motor_jog_menu[] = 
{
//    { "D"   , ""                    , cMotorReverse, cli_move_motor },
//    { "C"   , ""                    , cMotorForward, cli_move_motor },
    { "x"   , ""                    , cMain        , enter_cli_menu },
    { "?"   , ""                    , NULL         , print_jog_help },
    { NULL }
};

_cli_shell *cli_menu_ptr_list[ cCliMenus ] =
{
	&main_cli_menu[0] ,
	&motor_jog_menu[0],		
};

bool print_stage_info()
{
    //printf( "\n\rMMC-200 dc motor controller test version %s", _Version );
    printf( "\n\n\rstage info: " );
    printf( "\n\rstage.velocity: %1.3f"             , (double)stage.velocity);
    printf( "\n\rstage.acceleration: %ld um/s/s"    , stage.accel           );
    printf( "\n\rstage.position: %ld\n\r"           , stage.position        );
    return true;
}


bool print_jog_help()
{
    printf( "\n\rpress/hold left or right arrow keys to move stage " );
    printf( "forward\n\ror reverse, respectively\n\renter x to exit jog mode\n\n\r" );
    return true;
}

bool print_help()
{
    uint8_t i;
	_cli_shell *temp_menu_ptr;
	
	temp_menu_ptr = main_cli_menu;

    printf( "\n\r%s %s help menu\n\r", _ProductTitle,_Version );
	
    for( i = 0; i < 55; i++ )
        printf("=");
    
    printf( "\n\r" );
    
	while( temp_menu_ptr->token )
	{
		printf( "%s\n\r" , temp_menu_ptr->descriptor );
		temp_menu_ptr++;
	}
	//cli_print_menu( cli_menu_ptr_list[current_cli_menu]/*SER_CMD_MENU*/ , cli_t.level );
	
	return true;
}

/**
 * \brief enters a cli menu
 *
 * \param 
 */
bool enter_cli_menu()
{
	/* is cli menu already set to desired menu? */
	if( mthd_param == (uint8_t)current_cli_menu )
		return false;		
	
    printf( "\n\r%s -> %s\n\n\r", cli_menu_title_strs[ current_cli_menu ], cli_menu_title_strs[ mthd_param ] );
	
	current_cli_menu = (_cli_menu)mthd_param;

    if( current_cli_menu == cJog )
        set_uart_rx_isr( axis_rx_isr );
    else
        set_uart_rx_isr( uart1_rx_isr );
 
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
            mthd_param = command_lut->entry_par;
            if( (*command_lut->entry)( (char *)cmd->rx ) ) 
               return true;
        }
        command_lut++;
    }

	 return false;
}
