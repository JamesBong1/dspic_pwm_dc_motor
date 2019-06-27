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
//#include "encoder.h"

bool enter_cli_menu();
bool print_system_info();
bool print_help();

_cli_menu current_cli_menu;
uint8_t  mthd_param;
uint16_t mthd_parameters[5];

const char* cli_menu_title_strs[ cCliMenus ] =
{
	"main menu",
	"manual axis control" ,
};

_cli_shell main_cli_menu[] =
{
    { "v"   , "v n  - set velocity <n:0-100>"               , NULL              , NULL              },
    { "p"   , "p n  - set position <n=-100-100>"            , NULL              , NULL              },
    { "mc"  , "mc   - manually control position of stage"   , cManualAxisControl, enter_cli_menu    },
    { "info", "info - print current axis settings"          , NULL              , print_system_info },
    { "?"   , "?    - help"                                 , NULL              , print_help        },
    { NULL }
};

//_cli_shell axis_control_menu[] = 
//{
//    { "p", "p<n> - set position <n=-100-100>"   , NULL  , NULL  },
//    { "?"   , "?    - help"                     , NULL  , print_help        },
//};

_cli_shell manual_axis_control[] =
{
    { "A"   , "up arrow   - increase velocity"  , NULL  , NULL          },
    { "B"   , "down arrow - decrease velocity"  , NULL  , NULL          },
    { "C"   , "left arrow - reverse"            , NULL  , NULL          },
    { "D"   , "right arrow- forward"            , NULL  , NULL          },
    //{ "s"   , "s - stop pwm"                    , NULL  , NULL          },
    { "x"   , "x - exit menu"                   , cMain , enter_cli_menu},
    { "?"   , ""                                , NULL  , print_help    },
    { NULL }
};

_cli_shell *cli_menu_ptr_list[ cCliMenus ] =
{
	&main_cli_menu[0] ,
	&manual_axis_control[0],		
};

//bool print_axis_info()
//{
//    printf( "\n\n\raxis info: " );
//    printf( "\n\raxis.velocity:     %1.3f"      , (double)axis.velocity );
//    printf( "\n\raxis.acceleration: %ld um/s/s" , axis.accel            );
//    printf( "\n\raxis.position:     %ld\n\r"    , axis.position         );
//    return true;
//}

bool print_system_info()
{
    printf( "\n\n\raxis info: " );
    printf( "\n\raxis.velocity:         %1.3f"      , (double)axis.velocity );
    //printf( "\n\rmmc200.motor_polarity: %d um/s/s" , mmc200.motor_polarity );
    printf( "\n\rmmc200.position:       %1.4f mm\n\r"    , ((double)mmc200.position_nm/1000000.0)       );
    return true;
}

bool print_help()
{
    uint8_t i;
	_cli_shell *temp_menu_ptr;

	temp_menu_ptr = cli_menu_ptr_list[current_cli_menu];

    printf( "\n\n\r%s %s help menu\n\r", _ProductTitle,_Version );

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

    if( current_cli_menu == cManualAxisControl )
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
