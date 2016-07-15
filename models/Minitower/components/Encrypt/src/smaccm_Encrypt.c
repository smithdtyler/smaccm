/**************************************************************************
  Copyright (c) 2013, 2014, 2015 Rockwell Collins and the University of Minnesota.
  Developed with the sponsorship of the Defense Advanced Research Projects Agency (DARPA).

  Permission is hereby granted, free of charge, to any person obtaining a copy of this data,
  including any software or models in source or binary form, as well as any drawings, specifications, 
  and documentation (collectively "the Data"), to deal in the Data without restriction, including 
  without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
  and/or sell copies of the Data, and to permit persons to whom the Data is furnished to do so, 
  subject to the following conditions: 

  The above copyright notice and this permission notice shall be included in all copies or
  substantial portions of the Data.

  THE DATA IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT 
  LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
  IN NO EVENT SHALL THE AUTHORS, SPONSORS, DEVELOPERS, CONTRIBUTORS, OR COPYRIGHT HOLDERS BE LIABLE 
  FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
  ARISING FROM, OUT OF OR IN CONNECTION WITH THE DATA OR THE USE OR OTHER DEALINGS IN THE DATA. 

 **************************************************************************/


/**************************************************************************

   File: /home/ajgacek/minitower/june/apps/smaccmpilot/components/Encrypt/src/smaccm_Encrypt.c
   Created on: 2016/07/18 12:07:37
   using Dulcimer AADL system build tool suite 

   ***AUTOGENERATED CODE: DO NOT MODIFY***

  This C file contains the implementations of the AADL primitives
  used by user-level declarations for thread Encrypt.   

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
#include "smaccm_Encrypt.h"
#include <string.h>
#include <Encrypt.h>

///////////////////////////////////////////////////////////////////////////
//
// Local prototypes for AADL dispatchers
//
///////////////////////////////////////////////////////////////////////////
static void 
smaccm_Encrypt_periodic_dispatcher_dispatcher(int64_t * periodic_dispatcher); 
static void 
smaccm_Encrypt_Encrypt_initializer_dispatcher(int64_t * Encrypt_initializer); 
static void 
smaccm_Encrypt_server2self_dispatcher(SMACCM_DATA__GIDL server2self); 
static void 
smaccm_Encrypt_uart2self_dispatcher(bool * uart2self); 
 
 



/************************************************************************
 * 
 * Static variables and queue management functions for port:
 * 	server2self
 * 
 ************************************************************************/

static SMACCM_DATA__GIDL smaccm_queue_server2self [1];
static bool smaccm_queue_full_server2self  = false;
static uint32_t smaccm_queue_front_server2self  = 0;
static uint32_t smaccm_queue_back_server2self  = 0;

bool smaccm_queue_is_full_server2self() {
	return (smaccm_queue_front_server2self == smaccm_queue_back_server2self) && (smaccm_queue_full_server2self);
}

bool smaccm_queue_is_empty_server2self() {
	return (smaccm_queue_front_server2self == smaccm_queue_back_server2self) && (!smaccm_queue_full_server2self); 
}

bool smaccm_queue_read_server2self(SMACCM_DATA__GIDL server2self) {
	if (smaccm_queue_is_empty_server2self()) {
		return false;
	} else {
		memcpy(server2self, smaccm_queue_server2self[smaccm_queue_back_server2self], sizeof(SMACCM_DATA__GIDL));

		smaccm_queue_back_server2self = (smaccm_queue_back_server2self + 1) % 1; 
		smaccm_queue_full_server2self = false ; 
		return true;
	}
}

bool smaccm_queue_write_server2self(const SMACCM_DATA__GIDL server2self) {
	if (smaccm_queue_is_full_server2self()) {
		return false;
	} else {
		memcpy(smaccm_queue_server2self[smaccm_queue_front_server2self], server2self, sizeof(SMACCM_DATA__GIDL));

		smaccm_queue_front_server2self = (smaccm_queue_front_server2self + 1) % 1; 		
		if (smaccm_queue_back_server2self == smaccm_queue_front_server2self) { 
			smaccm_queue_full_server2self = true ; 
		}
		return true;
	}
}

/************************************************************************
 *  server2self_write_SMACCM_DATA__GIDL: 
 * Invoked by: remote interface.
 * 
 * This is the function invoked by a remote RPC to write to an active-thread
 * input event data port.  It queues the input message into a circular buffer.
 * 
 ************************************************************************/

bool server2self_write_SMACCM_DATA__GIDL(const smaccm_SMACCM_DATA__GIDL_container * arg) {
	bool result;
	smaccm_encrypt_server2self_mut_lock(); 
	result = smaccm_queue_write_server2self((uint8_t *) arg);
	smaccm_encrypt_server2self_mut_unlock(); 
	return result;
}


/************************************************************************
 *  Encrypt_read_server2self: 
 * Invoked from local active thread.
 * 
 * This is the function invoked by the active thread to read from the 
 * input event data queue circular buffer.
 * 
 ************************************************************************/

bool Encrypt_read_server2self(SMACCM_DATA__GIDL arg) {
	bool result; 
	smaccm_encrypt_server2self_mut_lock(); 
	result = smaccm_queue_read_server2self(arg);
	smaccm_encrypt_server2self_mut_unlock(); 
	return result;
}


/************************************************************************
 * 
 * Static variables and queue management functions for port:
 * 	uart2self
 * 
 ************************************************************************/

static bool smaccm_queue_uart2self [1];
static bool smaccm_queue_full_uart2self  = false;
static uint32_t smaccm_queue_front_uart2self  = 0;
static uint32_t smaccm_queue_back_uart2self  = 0;

bool smaccm_queue_is_full_uart2self() {
	return (smaccm_queue_front_uart2self == smaccm_queue_back_uart2self) && (smaccm_queue_full_uart2self);
}

bool smaccm_queue_is_empty_uart2self() {
	return (smaccm_queue_front_uart2self == smaccm_queue_back_uart2self) && (!smaccm_queue_full_uart2self); 
}

bool smaccm_queue_read_uart2self(bool * uart2self) {
	if (smaccm_queue_is_empty_uart2self()) {
		return false;
	} else {
		*uart2self = smaccm_queue_uart2self[smaccm_queue_back_uart2self] ;

		smaccm_queue_back_uart2self = (smaccm_queue_back_uart2self + 1) % 1; 
		smaccm_queue_full_uart2self = false ; 
		return true;
	}
}

bool smaccm_queue_write_uart2self(const bool * uart2self) {
	if (smaccm_queue_is_full_uart2self()) {
		return false;
	} else {
		smaccm_queue_uart2self[smaccm_queue_front_uart2self] = *uart2self ;

		smaccm_queue_front_uart2self = (smaccm_queue_front_uart2self + 1) % 1; 		
		if (smaccm_queue_back_uart2self == smaccm_queue_front_uart2self) { 
			smaccm_queue_full_uart2self = true ; 
		}
		return true;
	}
}

/************************************************************************
 *  uart2self_write_bool: 
 * Invoked by: remote interface.
 * 
 * This is the function invoked by a remote RPC to write to an active-thread
 * input event data port.  It queues the input message into a circular buffer.
 * 
 ************************************************************************/

bool uart2self_write_bool(const bool * arg) {
	bool result;
	smaccm_encrypt_uart2self_mut_lock(); 
	result = smaccm_queue_write_uart2self( arg);
	smaccm_encrypt_uart2self_mut_unlock(); 
	return result;
}


/************************************************************************
 *  Encrypt_read_uart2self: 
 * Invoked from local active thread.
 * 
 * This is the function invoked by the active thread to read from the 
 * input event data queue circular buffer.
 * 
 ************************************************************************/

bool Encrypt_read_uart2self(bool * arg) {
	bool result; 
	smaccm_encrypt_uart2self_mut_lock(); 
	result = smaccm_queue_read_uart2self(arg);
	smaccm_encrypt_uart2self_mut_unlock(); 
	return result;
}



// NOT writing dispatch variables for port self2uart


/************************************************************************
 * periodic_dispatcher Declarations
 * 
 ************************************************************************/

static bool smaccm_occurred_periodic_dispatcher;
static int64_t smaccm_time_periodic_dispatcher;

/************************************************************************
 * Encrypt_periodic_dispatcher_write_int64_t
 * Invoked from remote periodic dispatch thread.
 * 
 * This function records the current time and triggers the active thread 
 * dispatch from a periodic event.  Note that the periodic dispatch 
 * thread is the *only* thread that triggers a dispatch, so we do not
 * mutex lock the function.
 * 
 ************************************************************************/

bool Encrypt_periodic_dispatcher_write_int64_t(const int64_t * arg) {
	smaccm_occurred_periodic_dispatcher = true;
	smaccm_time_periodic_dispatcher = *arg;
	smaccm_dispatch_sem_post();

	return true;
}

 
 
 

/************************************************************************
 *  dispatch_dispatch_periodic_dispatcher: 
 * Invoked by remote RPC (or, for active thread, local dispatcher).
 * 
 * This is the function invoked by an active thread dispatcher to 
 * call to a user-defined entrypoint function.  It sets up the dispatch
 * context for the user-defined entrypoint, then calls it.
 * 
 ************************************************************************/

void dispatch_dispatch_periodic_dispatcher(
  const int64_t * in_arg ,
  smaccm_Encrypt_periodic_dispatcher_struct *out_arg) {
	 
	component_entry( in_arg); 

	 
}	


/************************************************************************
 *  dispatch_dispatch_Encrypt_initializer: 
 * Invoked by remote RPC (or, for active thread, local dispatcher).
 * 
 * This is the function invoked by an active thread dispatcher to 
 * call to a user-defined entrypoint function.  It sets up the dispatch
 * context for the user-defined entrypoint, then calls it.
 * 
 ************************************************************************/

void dispatch_dispatch_Encrypt_initializer(
  const int64_t * in_arg ,
  smaccm_Encrypt_Encrypt_initializer_struct *out_arg) {
	 
	component_init( in_arg); 

	 
}	


/************************************************************************
 *  dispatch_dispatch_server2self: 
 * Invoked by remote RPC (or, for active thread, local dispatcher).
 * 
 * This is the function invoked by an active thread dispatcher to 
 * call to a user-defined entrypoint function.  It sets up the dispatch
 * context for the user-defined entrypoint, then calls it.
 * 
 ************************************************************************/

void dispatch_dispatch_server2self(
  const smaccm_SMACCM_DATA__GIDL_container * in_arg ,
  smaccm_Encrypt_server2self_struct *out_arg) {
	 
	 
}	


/************************************************************************
 *  dispatch_dispatch_uart2self: 
 * Invoked by remote RPC (or, for active thread, local dispatcher).
 * 
 * This is the function invoked by an active thread dispatcher to 
 * call to a user-defined entrypoint function.  It sets up the dispatch
 * context for the user-defined entrypoint, then calls it.
 * 
 ************************************************************************/

void dispatch_dispatch_uart2self(
  const bool * in_arg ,
  smaccm_Encrypt_uart2self_struct *out_arg) {
	 
	 
}	



/************************************************************************
 * Encrypt_write_self2uart 
 * Invoked from local active or passive thread.
 * 
 * This is the comm function invoked by a user-level thread to send a message 
 * to another thread.  If the target is an active thread, it calls an 
 * RPC on the target thread to queue the data.  If it is a passive thread, 
 * it locally enqueues the request to be sent when the user thread
 * completes execution.
 * 
 ************************************************************************/

bool Encrypt_write_self2uart(const SMACCM_DATA__UART_Packet_i * self2uart) {
	bool result = true;
	result &= Encrypt_self2uart_write_SMACCM_DATA__UART_Packet_i(self2uart);			


	return result;
}


/************************************************************************
 * 
smaccm_Encrypt_periodic_dispatcher_dispatcher
 * Invoked from local active thread.
 * 
 * This is the dispatcher function invoked to respond to an incoming thread 
 * stimulus: an ISR, a periodic dispatch, or a queued event.
 * 
 ******************************************************************************/
static smaccm_Encrypt_periodic_dispatcher_struct smaccm_Encrypt_periodic_dispatcher_arg;

static void 
smaccm_Encrypt_periodic_dispatcher_dispatcher(int64_t * periodic_dispatcher) {

	// make the call: 
	dispatch_dispatch_periodic_dispatcher( periodic_dispatcher,
  &smaccm_Encrypt_periodic_dispatcher_arg	
		); 

}
/************************************************************************
 * 
smaccm_Encrypt_Encrypt_initializer_dispatcher
 * Invoked from local active thread.
 * 
 * This is the dispatcher function invoked to respond to an incoming thread 
 * stimulus: an ISR, a periodic dispatch, or a queued event.
 * 
 ******************************************************************************/
static smaccm_Encrypt_Encrypt_initializer_struct smaccm_Encrypt_Encrypt_initializer_arg;

static void 
smaccm_Encrypt_Encrypt_initializer_dispatcher(int64_t * Encrypt_initializer) {

	// make the call: 
	dispatch_dispatch_Encrypt_initializer( Encrypt_initializer,
  &smaccm_Encrypt_Encrypt_initializer_arg	
		); 

}
/************************************************************************
 * 
smaccm_Encrypt_server2self_dispatcher
 * Invoked from local active thread.
 * 
 * This is the dispatcher function invoked to respond to an incoming thread 
 * stimulus: an ISR, a periodic dispatch, or a queued event.
 * 
 ******************************************************************************/
static smaccm_Encrypt_server2self_struct smaccm_Encrypt_server2self_arg;

static void 
smaccm_Encrypt_server2self_dispatcher(SMACCM_DATA__GIDL server2self) {

	// make the call: 
	dispatch_dispatch_server2self((smaccm_SMACCM_DATA__GIDL_container *) server2self,
  &smaccm_Encrypt_server2self_arg	
		); 

}
/************************************************************************
 * 
smaccm_Encrypt_uart2self_dispatcher
 * Invoked from local active thread.
 * 
 * This is the dispatcher function invoked to respond to an incoming thread 
 * stimulus: an ISR, a periodic dispatch, or a queued event.
 * 
 ******************************************************************************/
static smaccm_Encrypt_uart2self_struct smaccm_Encrypt_uart2self_arg;

static void 
smaccm_Encrypt_uart2self_dispatcher(bool * uart2self) {

	// make the call: 
	dispatch_dispatch_uart2self( uart2self,
  &smaccm_Encrypt_uart2self_arg	
		); 

}

 
/************************************************************************
 * int run(void)
 * Main active thread function.
 * 
 ************************************************************************/

int run(void) {
	// port initialization routines (if any)... 

	// thread initialization routines (if any)...
	  int64_t dummy_time = 0;

	  smaccm_Encrypt_Encrypt_initializer_dispatcher(&dummy_time);
	// register interrupt handlers (if any)...
	    	

	// initial lock to await dispatch input.
	smaccm_dispatch_sem_wait();

	for(;;) {
		smaccm_dispatch_sem_wait();


		// drain the queues 
		if (smaccm_occurred_periodic_dispatcher) {
			smaccm_occurred_periodic_dispatcher = false;

			smaccm_Encrypt_periodic_dispatcher_dispatcher(&smaccm_time_periodic_dispatcher);
		}

		while (!smaccm_queue_is_empty_server2self()) {
			SMACCM_DATA__GIDL server2self ;
			Encrypt_read_server2self(server2self);

			smaccm_Encrypt_server2self_dispatcher(server2self); 
		}

		while (!smaccm_queue_is_empty_uart2self()) {
			bool uart2self ;
			Encrypt_read_uart2self(&uart2self);

			smaccm_Encrypt_uart2self_dispatcher(&uart2self); 
		}


	}
	// won't ever get here, but form must be followed
	return 0;
}




/**************************************************************************
  End of autogenerated file: /home/ajgacek/minitower/june/apps/smaccmpilot/components/Encrypt/src/smaccm_Encrypt.c
 **************************************************************************/
