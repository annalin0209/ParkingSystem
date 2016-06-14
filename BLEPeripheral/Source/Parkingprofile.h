/**************************************************************************************************
	Filename:       Parkingprofile.h
	Revised:        $Date:2016-05-09 14:51:58 $

	Description:    This file contains the GATT profile definitions and prototypes..

	Copyright 2013 EPLAB National Tsing Hua University. All rights reserved.
	The information contained herein is confidential property of NTHU. 	The material may be used for a personal and non-commercial use only in connection with 	a legitimate academic research purpose. Any attempt to copy, modify, and distribute any portion of this source code or derivative thereof for commercial, political, or propaganda purposes is strictly prohibited. All other uses require explicit written permission from the authors and copyright holders. This copyright statement must be retained in its entirety and displayed in the copyright statement of derived source code or systems.
**************************************************************************************************/

#ifndef PARKINGPROFILE_H
#define PARKINGPROFILE_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************************************************************
 * INCLUDES
 */

/*********************************************************************
 * CONSTANTS
 */

// Profile Parameters
#define CHARACTERISTIC1		0
#define CHARACTERISTIC2		1
#define CHARACTERISTIC3		2
#define CHARACTERISTIC4		3
#define CHARACTERISTIC5		4

// Parkingprofile Profile Service UUID
#define PARKINGPROFILE_SERV_UUID		0xFFF6

// Parkingprofile UUID
#define CHARACTERISTIC1_UUID		0xFFF7
#define CHARACTERISTIC2_UUID		0xFFF8
#define CHARACTERISTIC3_UUID		0xFFF9
#define CHARACTERISTIC4_UUID		0xFFFA
#define CHARACTERISTIC5_UUID		0xFFFB

// Parkingprofile Profile Services bit fields
#define PARKINGPROFILE_SERVICE		0x00000001

// Length of Characteristics
#define CHARACTERISTIC1_LEN		1
#define CHARACTERISTIC2_LEN	        1
#define CHARACTERISTIC3_LEN		1
#define CHARACTERISTIC4_LEN		1
#define CHARACTERISTIC5_LEN		1

/*********************************************************************
 * TYPEDEFS
 */

/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * Profile Callbacks
 */

// Callback when a characteristic value has changed
typedef NULL_OK void (*ParkingprofileChange_t)( uint8 paramID );

typedef struct
{
  ParkingprofileChange_t		pfnParkingprofileChange; // Called when characteristic value changes
} ParkingprofileCBs_t;



/*********************************************************************
 * API FUNCTIONS 
 */

/*
 * Parkingprofile_AddService- Initializes the GATT Profile service by registering
 *          GATT attributes with the GATT server.
 *
 * @param   services - services to add. This is a bit map and can
 *                     contain more than one service.
 */

extern bStatus_t Parkingprofile_AddService( uint32 services );

/*
 * Parkingprofile_RegisterAppCBs - Registers the application callback function.
 *                    Only call this function once.
 *
 *    appCallbacks - pointer to application callbacks.
 */
extern bStatus_t Parkingprofile_RegisterAppCBs( ParkingprofileCBs_t *appCallbacks );

/*
 * Parkingprofile_SetParameter - Set a GATT Profile parameter.
 *
 *    param - Profile parameter ID
 *    len - length of data to right
 *    value - pointer to data to write.  This is dependent on
 *          the parameter ID and WILL be cast to the appropriate
 *          data type (example: data type of uint16 will be cast to
 *          uint16 pointer).
 */
extern bStatus_t Parkingprofile_SetParameter( uint8 param, uint8 len, void *value );

/*
 * Parkingprofile_GetParameter - Get a GATT Profile parameter.
 *
 *    param - Profile parameter ID
 *    value - pointer to data to write.  This is dependent on
 *          the parameter ID and WILL be cast to the appropriate 
 *          data type (example: data type of uint16 will be cast to 
 *          uint16 pointer).
 */
extern bStatus_t Parkingprofile_GetParameter( uint8 param, void *value );


/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* PARKINGPROFILE_H */	
