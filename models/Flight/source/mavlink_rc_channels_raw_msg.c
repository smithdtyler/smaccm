/* This file has been autogenerated by Ivory
 * Compiler version  0.1.0.0
 */
#include "mavlink_rc_channels_raw_msg.h"

void mavlink_rc_channels_raw_msg_send(const struct rc_channels_raw_msg* n_var0,
                                      uint8_t* n_var1, uint8_t n_var2[80U])
{
    uint8_t n_local0[22U] = {};
    uint8_t* n_ref1 = n_local0;
    uint32_t n_deref2 = n_var0->time_boot_ms;
    
    mavlink_pack_uint32_t((uint8_t*) n_ref1, 0U, n_deref2);
    
    uint16_t n_deref3 = n_var0->chan1_raw;
    
    mavlink_pack_uint16_t((uint8_t*) n_ref1, 4U, n_deref3);
    
    uint16_t n_deref4 = n_var0->chan2_raw;
    
    mavlink_pack_uint16_t((uint8_t*) n_ref1, 6U, n_deref4);
    
    uint16_t n_deref5 = n_var0->chan3_raw;
    
    mavlink_pack_uint16_t((uint8_t*) n_ref1, 8U, n_deref5);
    
    uint16_t n_deref6 = n_var0->chan4_raw;
    
    mavlink_pack_uint16_t((uint8_t*) n_ref1, 10U, n_deref6);
    
    uint16_t n_deref7 = n_var0->chan5_raw;
    
    mavlink_pack_uint16_t((uint8_t*) n_ref1, 12U, n_deref7);
    
    uint16_t n_deref8 = n_var0->chan6_raw;
    
    mavlink_pack_uint16_t((uint8_t*) n_ref1, 14U, n_deref8);
    
    uint16_t n_deref9 = n_var0->chan7_raw;
    
    mavlink_pack_uint16_t((uint8_t*) n_ref1, 16U, n_deref9);
    
    uint16_t n_deref10 = n_var0->chan8_raw;
    
    mavlink_pack_uint16_t((uint8_t*) n_ref1, 18U, n_deref10);
    
    uint8_t n_deref11 = n_var0->port;
    
    mavlink_pack_uint8_t((uint8_t*) n_ref1, 20U, n_deref11);
    
    uint8_t n_deref12 = n_var0->rssi;
    
    mavlink_pack_uint8_t((uint8_t*) n_ref1, 21U, n_deref12);
    for (int32_t n_ix13 = 0; n_ix13 <= 21; n_ix13++) {
        ASSERTS(n_ix13 > 0 && 2147483647 - n_ix13 >= 6 || n_ix13 <= 0);
        if (n_ix13 + 6 >= 80) { } else {
            uint8_t n_deref14 = n_ref1[n_ix13];
            
            ASSERTS(n_ix13 > 0 && 2147483641 >= n_ix13 || n_ix13 <= 0);
            ASSERTS(0 <= 6 + n_ix13 && 6 + n_ix13 < 80);
            *&n_var2[(6 + n_ix13) % 80] = n_deref14;
        }
    }
    mavlinkSendWithWriter(35U, 244U, 22U, n_var1, n_var2);
    for (int32_t n_ix15 = 0; n_ix15 <= 49; n_ix15++) {
        ASSERTS(n_ix15 > 0 && 2147483647 - n_ix15 >= 30 || n_ix15 <= 0);
        ASSERTS(0 <= n_ix15 + 30 && n_ix15 + 30 < 80);
        *&n_var2[(n_ix15 + 30) % 80] = 0U;
    }
    return;
}

void mavlink_rc_channels_raw_unpack(struct rc_channels_raw_msg* n_var0, const
                                    uint8_t* n_var1)
{
    uint32_t n_r0 = mavlink_unpack_uint32_t(n_var1, 0U);
    
    *&n_var0->time_boot_ms = n_r0;
    
    uint16_t n_r1 = mavlink_unpack_uint16_t(n_var1, 4U);
    
    *&n_var0->chan1_raw = n_r1;
    
    uint16_t n_r2 = mavlink_unpack_uint16_t(n_var1, 6U);
    
    *&n_var0->chan2_raw = n_r2;
    
    uint16_t n_r3 = mavlink_unpack_uint16_t(n_var1, 8U);
    
    *&n_var0->chan3_raw = n_r3;
    
    uint16_t n_r4 = mavlink_unpack_uint16_t(n_var1, 10U);
    
    *&n_var0->chan4_raw = n_r4;
    
    uint16_t n_r5 = mavlink_unpack_uint16_t(n_var1, 12U);
    
    *&n_var0->chan5_raw = n_r5;
    
    uint16_t n_r6 = mavlink_unpack_uint16_t(n_var1, 14U);
    
    *&n_var0->chan6_raw = n_r6;
    
    uint16_t n_r7 = mavlink_unpack_uint16_t(n_var1, 16U);
    
    *&n_var0->chan7_raw = n_r7;
    
    uint16_t n_r8 = mavlink_unpack_uint16_t(n_var1, 18U);
    
    *&n_var0->chan8_raw = n_r8;
    
    uint8_t n_r9 = mavlink_unpack_uint8_t(n_var1, 20U);
    
    *&n_var0->port = n_r9;
    
    uint8_t n_r10 = mavlink_unpack_uint8_t(n_var1, 21U);
    
    *&n_var0->rssi = n_r10;
}