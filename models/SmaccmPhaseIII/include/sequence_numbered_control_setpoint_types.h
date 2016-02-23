/* This file has been autogenerated by Ivory
 * Compiler version  0.1.0.2
 */
#ifndef __SEQUENCE_NUMBERED_CONTROL_SETPOINT_TYPES_H__
#define __SEQUENCE_NUMBERED_CONTROL_SETPOINT_TYPES_H__
#ifdef __cplusplus
extern "C" {
#endif
#include "control_setpoint_types.h"
#include "ivory.h"
#include "ivory_serialize.h"
#include "sequence_num_types.h"
typedef struct sequence_numbered_control_setpoint { uint32_t seqnum;
                                                    struct control_setpoint val;
} sequence_numbered_control_setpoint;
void sequence_numbered_control_setpoint_get_le (const uint8_t * n_var0, uint32_t n_var1, struct sequence_numbered_control_setpoint * n_var2);
void sequence_numbered_control_setpoint_get_be (const uint8_t * n_var0, uint32_t n_var1, struct sequence_numbered_control_setpoint * n_var2);
void sequence_numbered_control_setpoint_set_le (uint8_t * n_var0, uint32_t n_var1, const struct sequence_numbered_control_setpoint * n_var2);
void sequence_numbered_control_setpoint_set_be (uint8_t * n_var0, uint32_t n_var1, const struct sequence_numbered_control_setpoint * n_var2);

#ifdef __cplusplus
}
#endif
#endif /* __SEQUENCE_NUMBERED_CONTROL_SETPOINT_TYPES_H__ */