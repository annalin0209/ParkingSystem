/**************************************************************************************************
	Filename:       Parkingprofile.h
	Revised:        $Date:2016-05-09 14:51:58 $

	Description:    This file contains the GATT profile definitions and prototypes..

	Copyright 2013 EPLAB National Tsing Hua University. All rights reserved.
	The information contained herein is confidential property of NTHU. 	The material may be used for a personal and non-commercial use only in connection with 	a legitimate academic research purpose. Any attempt to copy, modify, and distribute any portion of this source code or derivative thereof for commercial, political, or propaganda purposes is strictly prohibited. All other uses require explicit written permission from the authors and copyright holders. This copyright statement must be retained in its entirety and displayed in the copyright statement of derived source code or systems.
**************************************************************************************************/
/*********************************************************************
 * INCLUDES
 */
#include "bcomdef.h"
#include "OSAL.h"
#include "linkdb.h"
#include "att.h"
#include "gatt.h"
#include "gatt_uuid.h"
#include "gattservapp.h"
#include "gapbondmgr.h"

#include "Parkingprofile.h"

/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * CONSTANTS
 */

#define SERVAPP_NUM_ATTR_SUPPORTED        17

/*********************************************************************
 * TYPEDEFS
 */

/*********************************************************************
 * GLOBAL VARIABLES
 */

// GATT Profile Service UUID: 0xFFF6
CONST uint8 ParkingprofileServUUID[ATT_BT_UUID_SIZE] =
{
  LO_UINT16(PARKINGPROFILE_SERV_UUID), HI_UINT16(PARKINGPROFILE_SERV_UUID)
};

// characteristic1 UUID: 0xFFF7
CONST uint8 characteristic1UUID[ATT_BT_UUID_SIZE] =
{
  LO_UINT16(CHARACTERISTIC1_UUID), HI_UINT16(CHARACTERISTIC1_UUID)
};

// characteristic2 UUID: 0xFFF8
CONST uint8 characteristic2UUID[ATT_BT_UUID_SIZE] =
{
  LO_UINT16(CHARACTERISTIC2_UUID), HI_UINT16(CHARACTERISTIC2_UUID)
};

// characteristic3 UUID: 0xFFF9
CONST uint8 characteristic3UUID[ATT_BT_UUID_SIZE] =
{
  LO_UINT16(CHARACTERISTIC3_UUID), HI_UINT16(CHARACTERISTIC3_UUID)
};

// characteristic4 UUID: 0xFFFA
CONST uint8 characteristic4UUID[ATT_BT_UUID_SIZE] =
{
  LO_UINT16(CHARACTERISTIC4_UUID), HI_UINT16(CHARACTERISTIC4_UUID)
};

// characteristic5 UUID: 0xFFFB
CONST uint8 characteristic5UUID[ATT_BT_UUID_SIZE] =
{
  LO_UINT16(CHARACTERISTIC5_UUID), HI_UINT16(CHARACTERISTIC5_UUID)
};

/*********************************************************************
 * EXTERNAL VARIABLES
 */

/*********************************************************************
 * EXTERNAL FUNCTIONS
 */

/*********************************************************************
 * LOCAL VARIABLES
 */

static ParkingprofileCBs_t *Parkingprofile_AppCBs = NULL;

/*********************************************************************
 * Profile Attributes - variables
 */

// Profile Service attribute
static CONST gattAttrType_t ParkingprofileService = { ATT_BT_UUID_SIZE, ParkingprofileServUUID };

// Profile characteristic1 Properties
static uint8 characteristic1Props = GATT_PROP_READ | GATT_PROP_WRITE;

// characteristic1 Value
static uint8 characteristic1Value = 0;// Profile characteristic1 User Description
static uint8 characteristic1UserDesp[17] = "characteristic 1\0";

// Profile characteristic2 Properties
static uint8 characteristic2Props = GATT_PROP_READ | GATT_PROP_WRITE;

// characteristic2 Value
static uint8 characteristic2Value = 0;// Profile characteristic2 User Description
static uint8 characteristic2UserDesp[17] = "characteristic 2\0";

// Profile characteristic3 Properties
static uint8 characteristic3Props = GATT_PROP_READ | GATT_PROP_WRITE;

// characteristic3 Value
static uint8 characteristic3Value = 0;// Profile characteristic3 User Description
static uint8 characteristic3UserDesp[17] = "characteristic 3\0";

// Profile characteristic4 Properties
static uint8 characteristic4Props = GATT_PROP_READ | GATT_PROP_WRITE;

// characteristic4 Value
static uint8 characteristic4Value = 0;// Profile characteristic4 User Description
static uint8 characteristic4UserDesp[17] = "characteristic 4\0";

// Profile characteristic5 Properties
static uint8 characteristic5Props = GATT_PROP_READ | GATT_PROP_WRITE | GATT_PROP_NOTIFY;

// characteristic5 Value
static uint8 characteristic5Value = 0;// Profile characteristic5 User Description
static uint8 characteristic5UserDesp[17] = "characteristic 5\0";

// Parkingprofile characteristic5 Configuration Each client has its own
// instantiation of the Client Characteristic Configuration. Reads of the
// Client Characteristic Configuration only shows the configuration for
// that client and writes only affect the configuration of that client.
static gattCharCfg_t characteristic5Config[GATT_MAX_NUM_CONN];

/*********************************************************************
 * Profile Attributes - Table
 */

static gattAttribute_t ParkingprofileAttrTbl[SERVAPP_NUM_ATTR_SUPPORTED] = 
{
  // Simple Profile Service
  {
    { ATT_BT_UUID_SIZE, primaryServiceUUID }, /* type */
    GATT_PERMIT_READ,                         /* permissions */
    0,                                        /* handle */
    (uint8 *)&ParkingprofileService           /* pValue */
  },

    // characteristic1 Declaration
    {
      { ATT_BT_UUID_SIZE, characterUUID },
      GATT_PERMIT_READ,
      0,
      &characteristic1Props
    },

      // characteristic1 Value
      {
        { ATT_BT_UUID_SIZE, characteristic1UUID },
        GATT_PERMIT_READ | GATT_PERMIT_WRITE,
        0,
        &characteristic1Value
      },

      // characteristic1 User Description
      {
        { ATT_BT_UUID_SIZE, charUserDescUUID },
        GATT_PERMIT_READ, 
        0,
        characteristic1UserDesp
      },

    // characteristic2 Declaration
    {
      { ATT_BT_UUID_SIZE, characterUUID },
      GATT_PERMIT_READ,
      0,
      &characteristic2Props
    },

      // characteristic2 Value
      {
        { ATT_BT_UUID_SIZE, characteristic2UUID },
        GATT_PERMIT_READ | GATT_PERMIT_WRITE,
        0,
        &characteristic2Value
      },

      // characteristic2 User Description
      {
        { ATT_BT_UUID_SIZE, charUserDescUUID },
        GATT_PERMIT_READ, 
        0,
        characteristic2UserDesp
      },

    // characteristic3 Declaration
    {
      { ATT_BT_UUID_SIZE, characterUUID },
      GATT_PERMIT_READ,
      0,
      &characteristic3Props
    },

      // characteristic3 Value
      {
        { ATT_BT_UUID_SIZE, characteristic3UUID },
        GATT_PERMIT_READ | GATT_PERMIT_WRITE,
        0,
        &characteristic3Value
      },

      // characteristic3 User Description
      {
        { ATT_BT_UUID_SIZE, charUserDescUUID },
        GATT_PERMIT_READ, 
        0,
        characteristic3UserDesp
      },

    // characteristic4 Declaration
    {
      { ATT_BT_UUID_SIZE, characterUUID },
      GATT_PERMIT_READ,
      0,
      &characteristic4Props
    },

      // characteristic4 Value
      {
        { ATT_BT_UUID_SIZE, characteristic4UUID },
        GATT_PERMIT_READ | GATT_PERMIT_WRITE,
        0,
        &characteristic4Value
      },

      // characteristic4 User Description
      {
        { ATT_BT_UUID_SIZE, charUserDescUUID },
        GATT_PERMIT_READ, 
        0,
        characteristic4UserDesp
      },

    // characteristic5 Declaration
    {
      { ATT_BT_UUID_SIZE, characterUUID },
      GATT_PERMIT_READ,
      0,
      &characteristic5Props
    },

      // characteristic5 Value
      {
        { ATT_BT_UUID_SIZE, characteristic5UUID },
        GATT_PERMIT_READ | GATT_PERMIT_WRITE,
        0,
        &characteristic5Value
      },

      // characteristic5 configuration
      {
        { ATT_BT_UUID_SIZE, clientCharCfgUUID },
        GATT_PERMIT_READ | GATT_PERMIT_WRITE,
        0,
        (uint8 *) characteristic5Config
      },

      // characteristic5 User Description
      {
        { ATT_BT_UUID_SIZE, charUserDescUUID },
        GATT_PERMIT_READ, 
        0,
        characteristic5UserDesp
      },


};


/*********************************************************************
 * LOCAL FUNCTIONS
 */
static uint8 Parkingprofile_ReadAttrCB( uint16 connHandle, gattAttribute_t *pAttr, 
                            uint8 *pValue, uint8 *pLen, uint16 offset, uint8 maxLen );
static bStatus_t Parkingprofile_WriteAttrCB( uint16 connHandle, gattAttribute_t *pAttr,
                                 uint8 *pValue, uint8 len, uint16 offset );

static void Parkingprofile_HandleConnStatusCB( uint16 connHandle, uint8 changeType );


/*********************************************************************
 * PROFILE CALLBACKS
 */
// ParkingprofileService Callbacks
CONST gattServiceCBs_t ParkingprofileCBs =
{
  Parkingprofile_ReadAttrCB,  // Read callback function pointer
  Parkingprofile_WriteAttrCB, // Write callback function pointer
  NULL                       // Authorization callback function pointer
};

/*********************************************************************
 * PUBLIC FUNCTIONS
 */

/*********************************************************************
 * @fn      Parkingprofile_AddService
 *
 * @brief   Initializes the Parkingprofile service by registering
 *          GATT attributes with the GATT server.
 *
 * @param   services - services to add. This is a bit map and can
 *                     contain more than one service.
 *
 * @return  Success or Failure
 */
bStatus_t Parkingprofile_AddService( uint32 services )
{
  uint8 status = SUCCESS;

  // Initialize Client Characteristic Configuration attributes
  GATTServApp_InitCharCfg( INVALID_CONNHANDLE, characteristic5Config);

  // Register with Link DB to receive link status change callback
  VOID linkDB_Register( Parkingprofile_HandleConnStatusCB );

  if ( services & PARKINGPROFILE_SERVICE )
  {
    // Register GATT attribute list and CBs with GATT Server App
    status = GATTServApp_RegisterService( ParkingprofileAttrTbl, 
                                          GATT_NUM_ATTRS( ParkingprofileAttrTbl ),
                                          &ParkingprofileCBs );
  }

  return ( status );
}


/*********************************************************************
 * @fn      Parkingprofile_RegisterAppCBs
 *
 * @brief   Registers the application callback function. Only call
 *          this function once.
 *
 * @param   callbacks - pointer to application callbacks.
 *
 * @return  SUCCESS or bleAlreadyInRequestedMode
 */
bStatus_t Parkingprofile_RegisterAppCBs( ParkingprofileCBs_t *appCallbacks )
{
  if ( appCallbacks )
  {
    Parkingprofile_AppCBs = appCallbacks;

    return ( SUCCESS );
  }
  else
  {
    return ( bleAlreadyInRequestedMode );
  }
}


/*********************************************************************
 * @fn      Parkingprofile_SetParameter
 *
 * @brief   Set a Parkingprofile parameter.
 *
 * @param   param - Profile parameter ID
 * @param   len - length of data to right
 * @param   value - pointer to data to write.  This is dependent on
 *          the parameter ID and WILL be cast to the appropriate
 *          data type (example: data type of uint16 will be cast to
 *          uint16 pointer).
 *
 * @return  bStatus_t
 */
bStatus_t Parkingprofile_SetParameter( uint8 param, uint8 len, void *value )
{
  bStatus_t ret = SUCCESS;
  switch ( param )
  {
    case CHARACTERISTIC1:
      if ( len == CHARACTERISTIC1_LEN )
      {
        VOID osal_memcpy( &characteristic1Value, value, CHARACTERISTIC1_LEN );
      }
      else
      {
        ret = bleInvalidRange;
      }
      break;

    case CHARACTERISTIC2:
      if ( len == CHARACTERISTIC2_LEN )
      {
        VOID osal_memcpy( &characteristic2Value, value, CHARACTERISTIC2_LEN );
      }
      else
      {
        ret = bleInvalidRange;
      }
      break;

    case CHARACTERISTIC3:
      if ( len == CHARACTERISTIC3_LEN )
      {
        VOID osal_memcpy( &characteristic3Value, value, CHARACTERISTIC3_LEN );
      }
      else
      {
        ret = bleInvalidRange;
      }
      break;

    case CHARACTERISTIC4:
      if ( len == CHARACTERISTIC4_LEN )
      {
        VOID osal_memcpy( &characteristic4Value, value, CHARACTERISTIC4_LEN );
      }
      else
      {
        ret = bleInvalidRange;
      }
      break;

    case CHARACTERISTIC5:
      if ( len == CHARACTERISTIC5_LEN )
      {
        VOID osal_memcpy( &characteristic5Value, value, CHARACTERISTIC5_LEN );
        // See if Notification has been enabled 
        GATTServApp_ProcessCharCfg( characteristic5Config, &characteristic5Value, FALSE,
        ParkingprofileAttrTbl, GATT_NUM_ATTRS( ParkingprofileAttrTbl ),
        INVALID_TASK_ID );
      }
      else
      {
        ret = bleInvalidRange;
      }
      break;

    default:
      ret = INVALIDPARAMETER;
      break;
  }

  return ( ret );
}

/*********************************************************************
 * @fn      Parkingprofile_GetParameter
 *
 * @brief   Get a Parkingprofile parameter.
 *
 * @param   param - Profile parameter ID
 * @param   value - pointer to data to put.  This is dependent on
 *          the parameter ID and WILL be cast to the appropriate
 *          data type (example: data type of uint16 will be cast to
 *          uint16 pointer).
 *
 * @return  bStatus_t
 */
bStatus_t Parkingprofile_GetParameter( uint8 param, void *value )
{
  bStatus_t ret = SUCCESS;
  switch ( param )
  {
    case CHARACTERISTIC1:
      VOID osal_memcpy( value, &characteristic1Value, CHARACTERISTIC1_LEN );
      break;

    case CHARACTERISTIC2:
      VOID osal_memcpy( value, &characteristic2Value, CHARACTERISTIC2_LEN );
      break;

    case CHARACTERISTIC3:
      VOID osal_memcpy( value, &characteristic3Value, CHARACTERISTIC3_LEN );
      break;

    case CHARACTERISTIC4:
      VOID osal_memcpy( value, &characteristic4Value, CHARACTERISTIC4_LEN );
      break;

    case CHARACTERISTIC5:
      VOID osal_memcpy( value, &characteristic5Value, CHARACTERISTIC5_LEN );
      break;

    default:
      ret = INVALIDPARAMETER;
      break;
  }

  return ( ret );
}

/*********************************************************************
 * @fn          Parkingprofile_ReadAttrCB
 *
 * @brief       Read an attribute.
 *
 * @param       connHandle - connection message was received on
 * @param       pAttr - pointer to attribute
 * @param       pValue - pointer to data to be read
 * @param       pLen - length of data to be read
 * @param       offset - offset of the first octet to be read
 * @param       maxLen - maximum length of data to be read
 *
 * @return      Success or Failure
 */
static uint8 Parkingprofile_ReadAttrCB( uint16 connHandle, gattAttribute_t *pAttr, 
                            uint8 *pValue, uint8 *pLen, uint16 offset, uint8 maxLen )
{
  bStatus_t status = SUCCESS;

  // If attribute permissions require authorization to read, return error
  if ( gattPermitAuthorRead( pAttr->permissions ) )
  {
    // Insufficient authorization
    return ( ATT_ERR_INSUFFICIENT_AUTHOR );
  }

  // Make sure it's not a blob operation (no attributes in the profile are long)
  if ( offset > 0 )
  {
    return ( ATT_ERR_ATTR_NOT_LONG );
  }

  if ( pAttr->type.len == ATT_BT_UUID_SIZE )
  {
    // 16-bit UUID
    uint16 uuid = BUILD_UINT16( pAttr->type.uuid[0], pAttr->type.uuid[1]);
    switch ( uuid )
    {
      // No need for "GATT_SERVICE_UUID" or "GATT_CLIENT_CHAR_CFG_UUID" cases;
      // gattserverapp handles those reads

      case CHARACTERISTIC1_UUID:
        *pLen = CHARACTERISTIC1_LEN;
        VOID osal_memcpy( pValue, pAttr->pValue, CHARACTERISTIC1_LEN );
        break;

      case CHARACTERISTIC2_UUID:
        *pLen = CHARACTERISTIC2_LEN;
        VOID osal_memcpy( pValue, pAttr->pValue, CHARACTERISTIC2_LEN );
        break;

      case CHARACTERISTIC3_UUID:
        *pLen = CHARACTERISTIC3_LEN;
        VOID osal_memcpy( pValue, pAttr->pValue, CHARACTERISTIC3_LEN );
        break;

      case CHARACTERISTIC4_UUID:
        *pLen = CHARACTERISTIC4_LEN;
        VOID osal_memcpy( pValue, pAttr->pValue, CHARACTERISTIC4_LEN );
        break;

      case CHARACTERISTIC5_UUID:
        *pLen = CHARACTERISTIC5_LEN;
        VOID osal_memcpy( pValue, pAttr->pValue, CHARACTERISTIC5_LEN );
        break;

      default:
        // Should never get here!
        *pLen = 0;
        status = ATT_ERR_ATTR_NOT_FOUND;
        break;
    }
  }
  else
  {
    // 128-bit UUID
    *pLen = 0;
    status = ATT_ERR_INVALID_HANDLE;
  }

  return ( status );
}

/*********************************************************************
 * @fn      Parkingprofile_WriteAttrCB
 *
 * @brief   Validate attribute data prior to a write operation
 *
 * @param   connHandle - connection message was received on
 * @param   pAttr - pointer to attribute
 * @param   pValue - pointer to data to be written
 * @param   len - length of data
 * @param   offset - offset of the first octet to be written
 * @param   complete - whether this is the last packet
 * @param   oper - whether to validate and/or write attribute value
 *
 * @return  Success or Failure
 */
static bStatus_t Parkingprofile_WriteAttrCB( uint16 connHandle, gattAttribute_t *pAttr,
                                 uint8 *pValue, uint8 len, uint16 offset )
{
  bStatus_t status = SUCCESS;
  uint8 notifyApp = 0xFF;

  // If attribute permissions require authorization to write, return error
  if ( gattPermitAuthorWrite( pAttr->permissions ) )
  {
    // Insufficient authorization
    return ( ATT_ERR_INSUFFICIENT_AUTHOR );
  }

  if ( pAttr->type.len == ATT_BT_UUID_SIZE )
  {
    // 16-bit UUID
    uint16 uuid = BUILD_UINT16( pAttr->type.uuid[0], pAttr->type.uuid[1]);
    switch ( uuid )
    {
      case CHARACTERISTIC1_UUID:
        //Validate the value
        // Make sure it's not a blob oper
        if ( offset == 0 )
        {
          if ( len != CHARACTERISTIC1_LEN )
          {
            status = ATT_ERR_INVALID_VALUE_SIZE;
          }
        }
        else
        {
          status = ATT_ERR_ATTR_NOT_LONG;
        }

        //Write the value
        if ( status == SUCCESS )
        {
          VOID osal_memcpy( pAttr->pValue, pValue, CHARACTERISTIC1_LEN );
          notifyApp = CHARACTERISTIC1;
        }
        break;

      case CHARACTERISTIC2_UUID:
        //Validate the value
        // Make sure it's not a blob oper
        if ( offset == 0 )
        {
          if ( len != CHARACTERISTIC2_LEN )
          {
            status = ATT_ERR_INVALID_VALUE_SIZE;
          }
        }
        else
        {
          status = ATT_ERR_ATTR_NOT_LONG;
        }

        //Write the value
        if ( status == SUCCESS )
        {
          VOID osal_memcpy( pAttr->pValue, pValue, CHARACTERISTIC2_LEN );
          notifyApp = CHARACTERISTIC2;
        }
        break;

      case CHARACTERISTIC3_UUID:
        //Validate the value
        // Make sure it's not a blob oper
        if ( offset == 0 )
        {
          if ( len != CHARACTERISTIC3_LEN )
          {
            status = ATT_ERR_INVALID_VALUE_SIZE;
          }
        }
        else
        {
          status = ATT_ERR_ATTR_NOT_LONG;
        }

        //Write the value
        if ( status == SUCCESS )
        {
          VOID osal_memcpy( pAttr->pValue, pValue, CHARACTERISTIC3_LEN );
          notifyApp = CHARACTERISTIC3;
        }
        break;

      case CHARACTERISTIC4_UUID:
        //Validate the value
        // Make sure it's not a blob oper
        if ( offset == 0 )
        {
          if ( len != CHARACTERISTIC4_LEN )
          {
            status = ATT_ERR_INVALID_VALUE_SIZE;
          }
        }
        else
        {
          status = ATT_ERR_ATTR_NOT_LONG;
        }

        //Write the value
        if ( status == SUCCESS )
        {
          VOID osal_memcpy( pAttr->pValue, pValue, CHARACTERISTIC4_LEN );
          notifyApp = CHARACTERISTIC4;
        }
        break;

      case CHARACTERISTIC5_UUID:
        //Validate the value
        // Make sure it's not a blob oper
        if ( offset == 0 )
        {
          if ( len != CHARACTERISTIC5_LEN )
          {
            status = ATT_ERR_INVALID_VALUE_SIZE;
          }
        }
        else
        {
          status = ATT_ERR_ATTR_NOT_LONG;
        }

        //Write the value
        if ( status == SUCCESS )
        {
          VOID osal_memcpy( pAttr->pValue, pValue, CHARACTERISTIC5_LEN );
          notifyApp = CHARACTERISTIC5;
        }
        break;


      case GATT_CLIENT_CHAR_CFG_UUID:
        status = GATTServApp_ProcessCCCWriteReq( connHandle, pAttr, pValue, len,
                                                 offset, GATT_CLIENT_CFG_NOTIFY );
        break;

      default:
        status = ATT_ERR_ATTR_NOT_FOUND;
        break;
    }
  }
  else
  {
    // 128-bit UUID
    status = ATT_ERR_INVALID_HANDLE;
  }

  // If a charactersitic value changed then callback function to notify application of change
  if ( (notifyApp != 0xFF ) && Parkingprofile_AppCBs && Parkingprofile_AppCBs->pfnParkingprofileChange )
  {
    Parkingprofile_AppCBs->pfnParkingprofileChange( notifyApp );  
  }

  return ( status );
}

/*********************************************************************
 * @fn          Parkingprofile_HandleConnStatusCB
 *
 * @brief       Parkingprofile link status change handler function.
 *
 * @param       connHandle - connection handle
 * @param       changeType - type of change
 *
 * @return      none
 */
static void Parkingprofile_HandleConnStatusCB( uint16 connHandle, uint8 changeType )
{
  // Make sure this is not loopback connection
  if ( connHandle != LOOPBACK_CONNHANDLE )
  {
    // Reset Client Char Config if connection has dropped
    if ( ( changeType == LINKDB_STATUS_UPDATE_REMOVED )      ||
         ( ( changeType == LINKDB_STATUS_UPDATE_STATEFLAGS ) && 
           ( !linkDB_Up( connHandle ) ) ) )
    {
      GATTServApp_InitCharCfg( connHandle, characteristic5Config );
    }
  }
}



/*********************************************************************
*********************************************************************/
