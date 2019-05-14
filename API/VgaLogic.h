#include <math.h>

/** @defgroup ErrorCode Error codes
 *  @{
 *  	Error codes values:
 * 		|	Error code	|	Error type									|
 * 		|:-------------:|:----------------------------------------------|
 * 		|		0x00	|	None error									|
 * 		|		0x0n	|	Hardware related							|
 * 		|		0x1n	|	Script commandos related					|
 * 		|		0x2n	|	Draw functions related						|
 * 		|		0x3n	|	Memory functions related					|
 *
 */

/** @}*/

#define		API_NONE_ERROR					0x00
/* Hardware related ------------------------------------------------------------------*/
#define		API_DISCONNECT_ERROR			0x01
#define		API_UNKNOWN_COMMAND_ERROR		0x02
#define		API_COMMAND_READ_ERROR			0x03
/* Script commandos related ----------------------------------------------------------*/
#define 	API_CLEARSCREEN_PARAM_ERROR		0x10
#define 	API_LINE_PARAM_ERROR			0x11
#define 	API_RECT_PARAM_ERROR			0x12
#define 	API_TEXT_PARAM_ERROR			0x13
#define 	API_BITMAP_PARAM_ERROR			0x14
#define 	API_WAIT_PARAM_ERROR			0x15
#define		API_REPEAT_PARAM_ERROR			0x16
#define		API_EXECUTE_PARAM_ERROR			0x17
#define		API_CIRCLE_PARAM_ERROR			0x18
#define		API_FIGURE_PARAM_ERROR			0x19
/* Draw functions related ------------------------------------------------------------*/
#define		API_OFF_SCREEN_ERROR			0x20
#define		API_COLOR_ERROR					0x21
/* Memory functions related ----------------------------------------------------------*/
#define		API_MEM_FAULT_ERROR				0x30


void API_init(void);

//Verplict
int API_draw_text (int x_lup, int y_lup, int color, char *text, char *fontname, int fontsize, int fontsytle, int reserved);
int API_draw_line (int x_l, int y_1, int x_2, int y2, int color, int weight, int reserved);
int API_draw_rectangle (int x_lup, int y_lup, int x_rdown, int y_rdown, int color, int style, int reserved);
int API_draw_bitmap (int x_lup, int y_lup, int bm_nr);
int API_clearscreen (int color);


//Optioneel
int API_wait (int msecs);
int API_repeat_commands (int nr_previous_commands, int iterations, int reserved);
int API_execute (void);
int API_draw_circle (int x, int y, int radius, int color, int reserved);
int API_draw_figure (int x_1, int y_1, int x_2, int y_2, int x_3, int y_3, int x_4, int y_4, int x_5, int y_5, int color, int reserved);

#define LINE_WIDTH_CUTOFF 150 //lager is minder dik       en hoger is dikker
