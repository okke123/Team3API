#ifndef __APP_FRONT_H
#define __APP_FRONT_H

/** @addtogroup AppFront
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


void ErrorCodeHandler(int error, char* error_msg);

#endif
