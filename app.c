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
 * app.c
 * - Main application file
 * ----------------------------------------------------------------------------
 * $Revision: 1.30 $
 * $Date: 2018/02/21 18:46:05 $
 * ------------------------------------------------------------------------- */

#include "app.h"

int main(void)
{
    App_Initialize();

    /* Main application loop:
     * - Run the kernel scheduler
     * - Send notifications for the battery voltage and RSSI values
     * - Refresh the watchdog and wait for an interrupt before continuing */
    while (1)
    {
        Kernel_Schedule();

        for (unsigned int i = 0; i < NUM_MASTERS; i++)
        {
            if (ble_env[i].state == APPM_CONNECTED)
            {
                /* Send battery level if battery service is enabled */
                if (app_env.send_batt_ntf[i] && bass_support_env[i].enable)
                {
                    app_env.send_batt_ntf[i] = 0;
                    Batt_LevelUpdateSend(ble_env[i].conidx,
                                         app_env.batt_lvl, 0);
                }

                /* Update custom service characteristics, send notifications if
                 * notification is enabled */
                /*
                if (cs_env[i].tx_value_changed && cs_env[i].sent_success)
                {
                    cs_env[i].tx_value_changed = false;
                    (cs_env[i].val_notif)++;

                    if (cs_env[i].tx_cccd_value & ATT_CCC_START_NTF)
                    {
                        memset(cs_env[i].tx_value, cs_env[i].val_notif,
                               CS_TX_VALUE_MAX_LENGTH);
                        CustomService_SendNotification(ble_env[i].conidx,
                                                       CS_IDX_TX_VALUE_VAL,
                                                       &cs_env[i].tx_value[0],
                                                       CS_TX_VALUE_MAX_LENGTH);
                    }
                }
				*/
                /* Update TX long characteristic if new RX long characteristic was received.
                 * Write the inverted version of RX characteristic into TX */
                if (cs_env[i].rx_long_value_changed == true)
                {
                    for (unsigned int j = 0; j < CS_RX_LONG_VALUE_MAX_LENGTH; j++)
                    {
                        cs_env[i].tx_long_value[j] = 0xFF ^ cs_env[i].rx_long_value[j];
                    }
                    cs_env[i].rx_long_value_changed = false;
                }

                if (cs_env[i].tx_value_changed)
                {
                    cs_env[i].tx_value_changed = false;

                    CustomService_SendNotification(ble_env[i].conidx,
                                                       CS_IDX_TX_VALUE_VAL,
                                                       &cs_env[i].tx_value[0],
                                                       cs_env[i].tx_size);

                }

                /*  SPI_IF */
                // Set new message to be sent to Master.
                // If received message is available && there is no message being sent.
                if (cs_env[i].rx_value_changed != 0 && SPI_IF_MessagePending() == 0)
                {
                    if (cs_env[i].rx_size > 0 && SPI_IF_MessagePending() == 0)
                    {
                        SPI_IF_SetMessage((const char*)cs_env[i].rx_value, cs_env[i].rx_size);
                        cs_env[i].rx_size = 0;
                    }
                    cs_env[i].rx_value_changed = 0;
                }

                // Set new message to be transmitted over BLE.
                // If there is no message being processed and there is new message available.
                if (cs_env[i].tx_value_changed == 0 &&
                    SPI_IF_GetMessage(cs_env[i].tx_value, &cs_env[i].tx_size) != 0)
                {
                    cs_env[i].tx_value_changed = 1;
                }

                /* SPI_IF END */
            }
        }

        /* Refresh the watchdog timer */
        Sys_Watchdog_Refresh();

        /* Wait for an event before executing the scheduler again */
        SYS_WAIT_FOR_EVENT;
    }
}
