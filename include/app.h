/* ----------------------------------------------------------------------------
 * Copyright (c) 2015-2017 Semiconductor Components Industries, LLC (d/b/a
 * ON Semiconductor), All Rights Reserved
 *
 * Copyright (C) RivieraWaves 2009-2016
 *
 * This module is derived in part from example code provided by RivieraWaves
 * and as such the underlying code is the property of RivieraWaves [a member
 * of the CEVA, Inc. group of companies], together with additional code which
 * is the property of ON Semiconductor. The code (in whole or any part) may not
 * be redistributed in any form without prior written permission from
 * ON Semiconductor.
 *
 * The terms of use and warranty for this code are covered by contractual
 * agreements between ON Semiconductor and the licensee.
 *
 * This is Reusable Code.
 *
 * ----------------------------------------------------------------------------
 * app.h
 * - Main application header
 * ----------------------------------------------------------------------------
 * $Revision: 1.54 $
 * $Date: 2018/02/21 18:04:04 $
 * ------------------------------------------------------------------------- */

#ifndef APP_H
#define APP_H

/* ----------------------------------------------------------------------------
 * If building with a C++ compiler, make all of the definitions in this header
 * have a C binding.
 * ------------------------------------------------------------------------- */
#ifdef __cplusplus
extern "C"
{
#endif    /* ifdef __cplusplus */

/* ----------------------------------------------------------------------------
 * Include files
 * --------------------------------------------------------------------------*/
#include <rsl10.h>
#include <rsl10_ke.h>
#include <rsl10_ble.h>
#include <rsl10_profiles.h>
#include <rsl10_map_nvr.h>
#include <stdbool.h>
#include <rsl10_flash_rom.h>
#include <rsl10_protocol.h>
#include <rsl10_hw_cid101.h>
#include <rsl10_sys_spi.h>
#include "ble_std.h"
#include "ble_custom.h"
#include "ble_bass.h"
#include "spi_interface.h"

/* ----------------------------------------------------------------------------
 * Defines
 * --------------------------------------------------------------------------*/

/* DIO number that is used for easy re-flashing (recovery mode) */
#define RECOVERY_DIO                    12

/* DIO number that is connected to LED of EVB */
#define LED_DIO_NUM                     6

/* Output power */
#define OUTPUT_POWER_DBM                0

/* Minimum and maximum VBAT measurements */
#define VBAT_1p1V_MEASURED              0x1200
#define VBAT_1p4V_MEASURED              0x16cc

/* Maximum battery level */
#define BAT_LVL_MAX                     100

/* Set timer to 200 ms (20 times the 10 ms kernel timer resolution) */
#define TIMER_200MS_SETTING             20

/* Set timer to 2s (200 times the 10 ms kernel timer resolution) */
#define TIMER_2S_SETTING                200

typedef void (*appm_add_svc_func_t)(void);
#define DEFINE_SERVICE_ADD_FUNCTION(func) (appm_add_svc_func_t)func
#define DEFINE_MESSAGE_HANDLER(message, handler) { message, \
                                                   (ke_msg_func_t)handler }

/* List of message handlers that are used by the different profiles/services */
#define APP_MESSAGE_HANDLER_LIST                       \
    DEFINE_MESSAGE_HANDLER(APP_TEST_TIMER, APP_Timer)

/* List of functions used to create the database */
#define SERVICE_ADD_FUNCTION_LIST                        \
    DEFINE_SERVICE_ADD_FUNCTION(Batt_ServiceAdd_Server), \
    DEFINE_SERVICE_ADD_FUNCTION(CustomService_ServiceAdd)

typedef void (*appm_enable_svc_func_t)(uint8_t);
#define DEFINE_SERVICE_ENABLE_FUNCTION(func) (appm_enable_svc_func_t)func

/* List of functions used to enable client services */
#define SERVICE_ENABLE_FUNCTION_LIST \
    DEFINE_SERVICE_ENABLE_FUNCTION(Batt_ServiceEnable_Server)

/* ----------------------------------------------------------------------------
 * Global variables and types
 * --------------------------------------------------------------------------*/
extern const struct ke_task_desc TASK_DESC_APP;

/* APP Task messages */
enum appm_msg
{
    APPM_DUMMY_MSG = TASK_FIRST_MSG(TASK_ID_APP),

    /* Timer used to have a tick periodically for application */
    APP_TEST_TIMER,

    /* Timer used to control the behavior of the LED_DIO_NUM according to
     * the connection states  */
    LED_TIMER,
};

struct app_env_tag
{
    /* Battery service */
    uint8_t batt_lvl;
    uint32_t sum_batt_lvl;
    uint16_t num_batt_read;
    uint8_t spi1_rx_value[60];
    uint8_t spi1_tx_value[60];
    bool send_batt_ntf[NUM_MASTERS];
};

/* Support for the application manager and the application environment */
extern struct app_env_tag app_env;

/* List of functions used to create the database */
extern const appm_add_svc_func_t appm_add_svc_func_list[];

/* ---------------------------------------------------------------------------
* Function prototype definitions
* --------------------------------------------------------------------------*/
extern void App_Initialize(void);

extern void App_Env_Initialize(void);

extern int APP_Timer(ke_msg_id_t const msg_id, void const *param,
                     ke_task_id_t const dest_id,
                     ke_task_id_t const src_id);

extern int LED_Timer(ke_msg_id_t const msg_id, void const *param,
                     ke_task_id_t const dest_id,
                     ke_task_id_t const src_id);

extern int Msg_Handler(ke_msg_id_t const msgid, void *param,
                       ke_task_id_t const dest_id,
                       ke_task_id_t const src_id);

/* ----------------------------------------------------------------------------
 * Close the 'extern "C"' block
 * ------------------------------------------------------------------------- */
#ifdef __cplusplus
}
#endif    /* ifdef __cplusplus */

#endif    /* APP_H */
