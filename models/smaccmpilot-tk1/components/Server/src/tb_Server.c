/**************************************************************************
  Copyright (c) 2013-2016 Rockwell Collins and the University of
  Minnesota. Developed with the sponsorship of the Defense Advanced
  Research Projects Agency (DARPA).

  Permission is hereby granted, free of charge, to any person
  obtaining a copy of this data, including any software or models
  in source or binary form, as well as any drawings,
  specifications, and documentation (collectively "the Data"), to
  deal in the Data without restriction, including without
  limitation the rights to use, copy, modify, merge, publish,
  distribute, sublicense, and/or sell copies of the Data, and to
  permit persons to whom the Data is furnished to do so, subject to
  the following conditions:

  The above copyright notice and this permission notice shall be
  included in all copies or substantial portions of the Data.

  THE DATA IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS, SPONSORS,
  DEVELOPERS, CONTRIBUTORS, OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
  CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
  CONNECTION WITH THE DATA OR THE USE OR OTHER DEALINGS IN THE
  DATA.
 **************************************************************************/

/**************************************************************************

  ***AUTOGENERATED CODE: DO NOT MODIFY***

This C file contains the implementations of the AADL primitives
used by user-level declarations for thread Server.

The user code runs in terms of "dispatchers", which cause
dispatch user-level handlers to execute.  These handlers can
communicate using the standard AADL primitives, which are mapped
to C functions.

The send/receive handlers are not thread safe in CAmkES; it is
assumed that this is handled by the CAmkES sequentialized access
to the dispatch handler.  There is only one dispatch interface
for the component containing all of the dispatch points.

They are thread safe for eChronos.

The read/write handlers are thread safe because the writer comes
through a dispatch interface but the reader is "local" on a dispatch
interface and so contention may occur.

 **************************************************************************/

#include "tb_Server.h"
#include <string.h>
#include <camkes.h>

/************************************************************************
 * periodic_dispatcher Declarations
 *
 ************************************************************************/

static bool tb_occurred_periodic_dispatcher;
static int64_t tb_time_periodic_dispatcher;

/************************************************************************
 * periodic_dispatcher_write_int64_t
 * Invoked from remote periodic dispatch thread.
 *
 * This function records the current time and triggers the active thread
 * dispatch from a periodic event.  Note that the periodic dispatch
 * thread is the *only* thread that triggers a dispatch, so we do not
 * mutex lock the function.
 *
 ************************************************************************/

bool periodic_dispatcher_write_int64_t(const int64_t * arg) {
    tb_occurred_periodic_dispatcher = true;
    tb_time_periodic_dispatcher = *arg;
    MUTEXOP(tb_dispatch_sem_post())
    return true;
}
void tb_timer_complete_callback(void *_ UNUSED) {
   // we want time in microseconds, not nanoseconds, so we divide by 1000.
   int64_t tb_time_periodic_dispatcher = tb_timer_time() / 1000LL;
   (void)periodic_dispatcher_write_int64_t(&tb_time_periodic_dispatcher);
   CALLBACKOP(tb_timer_complete_reg_callback(tb_timer_complete_callback, NULL));
}
/************************************************************************
 *  tb_Server_write_self2encrypt:
 * Invoked from user code in the local thread.
 *
 * This is the function invoked by the local thread to make a
 * call to write to a remote data port.
 *
 * XXX: When simulating fan out, the caller of this function will only 
 * receive a positive response when all enqueues are successful. When a
 * negative response is received it only indicates that at least one
 * enqueue attempt failed.
 *
 ************************************************************************/
bool tb_Server_write_self2encrypt
(const SMACCM_DATA__GIDL * tb_self2encrypt) {
    bool tb_result = true ; 

    tb_result &= tb_self2encrypt_enqueue((tb_SMACCM_DATA__GIDL_container *)tb_self2encrypt);

    return tb_result;
}
/************************************************************************
 *  tb_Server_write_self2framing:
 * Invoked from user code in the local thread.
 *
 * This is the function invoked by the local thread to make a
 * call to write to a remote data port.
 *
 * XXX: When simulating fan out, the caller of this function will only 
 * receive a positive response when all enqueues are successful. When a
 * negative response is received it only indicates that at least one
 * enqueue attempt failed.
 *
 ************************************************************************/
bool tb_Server_write_self2framing
(const SMACCM_DATA__GIDL * tb_self2framing) {
    bool tb_result = true ; 

    tb_result &= tb_self2framing_enqueue((tb_SMACCM_DATA__GIDL_container *)tb_self2framing);

    return tb_result;
}
/************************************************************************
 *  tb_Server_write_self2vm_reboot:
 * Invoked from user code in the local thread.
 *
 * This is the function invoked by the local thread to make a
 * call to write to a remote data port.
 *
 * XXX: When simulating fan out, the caller of this function will only 
 * receive a positive response when all enqueues are successful. When a
 * negative response is received it only indicates that at least one
 * enqueue attempt failed.
 *
 ************************************************************************/
bool tb_Server_write_self2vm_reboot
(const bool * tb_self2vm_reboot) {
    bool tb_result = true ; 

    tb_result &= tb_self2vm_reboot_enqueue((bool *)tb_self2vm_reboot);

    return tb_result;
}



void pre_init(void) {

    // Pre-initialization statements for periodic_dispatcher
    // Pre-initialization statements for Server_initializer
    // Pre-initialization statements for tb_vm2self
    // Pre-initialization statements for tb_decrypt2self
    // Pre-initialization statements for tb_framing2self

}

/************************************************************************
 *  tb_entrypoint_Server_periodic_dispatcher:
 *
 * This is the function invoked by an active thread dispatcher to
 * call to a user-defined entrypoint function.  It sets up the dispatch
 * context for the user-defined entrypoint, then calls it.
 *
 ************************************************************************/
void tb_entrypoint_Server_periodic_dispatcher(const int64_t * in_arg) {
    component_entry((int64_t *) in_arg);

}

/************************************************************************
 *  tb_entrypoint_Server_Server_initializer:
 *
 * This is the function invoked by an active thread dispatcher to
 * call to a user-defined entrypoint function.  It sets up the dispatch
 * context for the user-defined entrypoint, then calls it.
 *
 ************************************************************************/
void tb_entrypoint_Server_Server_initializer(const int64_t * in_arg) {
    component_init((int64_t *) in_arg);

}

/************************************************************************
 *  tb_entrypoint_tb_Server_decrypt2self:
 *
 * This is the function invoked by an active thread dispatcher to
 * call to a user-defined entrypoint function.  It sets up the dispatch
 * context for the user-defined entrypoint, then calls it.
 *
 ************************************************************************/
void tb_entrypoint_tb_Server_decrypt2self(const SMACCM_DATA__GIDL * in_arg) {
}

/************************************************************************
 *  tb_entrypoint_tb_Server_framing2self:
 *
 * This is the function invoked by an active thread dispatcher to
 * call to a user-defined entrypoint function.  It sets up the dispatch
 * context for the user-defined entrypoint, then calls it.
 *
 ************************************************************************/
void tb_entrypoint_tb_Server_framing2self(const SMACCM_DATA__GIDL * in_arg) {
}


/************************************************************************
 * int run(void)
 * Main active thread function.
 *
 ************************************************************************/

int run(void) {

    // Port initialization routines

    // tb_timer_periodic(0, ((uint64_t)5)*NS_IN_MS);
    CALLBACKOP(tb_timer_complete_reg_callback(tb_timer_complete_callback, NULL));


    {
    int64_t tb_dummy;
    tb_entrypoint_Server_Server_initializer(&tb_dummy);
    }
    // Initial lock to await dispatch input.
    MUTEXOP(tb_dispatch_sem_wait())
    for(;;) {
        MUTEXOP(tb_dispatch_sem_wait())

        // Drain the queues
        if (tb_occurred_periodic_dispatcher) {
            tb_occurred_periodic_dispatcher = false;
            tb_entrypoint_Server_periodic_dispatcher(&tb_time_periodic_dispatcher);
        }

    }

    // Won't ever get here, but form must be followed
    return 0;
}

