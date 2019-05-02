/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

/* TODO Application specific user parameters used in user.c may go here */

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */
typedef struct _AxisVariables
{
    long accel;
    long position;
    float velocity;  // going by a percentage 0%<0-brake/coast>/100%<1.0- full speed>
}_axis_settings;
 
extern _axis_settings axis;

void initialize_app(void);    /* I/O and Peripheral Initialization */
