/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

/* TODO Application specific user parameters used in user.c may go here */

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */
typedef struct _StageVaribles
{
    long accel;
    long position;

    float velocity;  // going by a percentage 0%<0> - coast / 100%<1.0> - full speed
}_stage_settings;
 
extern _stage_settings stage;

void InitApp(void);         /* I/O and Peripheral Initialization */
