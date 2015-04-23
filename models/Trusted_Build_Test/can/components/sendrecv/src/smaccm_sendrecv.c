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

   File: /home/ajgacek/smaccm/models/Trusted_Build_Test/can/components/sendrecv/src/smaccm_sendrecv.c
   Created on: 2015/04/23 10:06:50
   using Dulcimer AADL system build tool suite 

   ***AUTOGENERATED CODE: DO NOT MODIFY***

  This C file contains the implementations of the AADL primitives
  used by user-level declarations for thread sendrecv.   

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


#include <string.h>
#include <smaccm_sendrecv.h>
#include <sendrecv.h>

///////////////////////////////////////////////////////////////////////////
//
// Local prototypes for AADL dispatchers
//
///////////////////////////////////////////////////////////////////////////
void 
smaccm_sendrecv_input_dispatcher(can__can_frame_i * input); 
void 
smaccm_dispatcher_periodic_1000_ms(uint64_t * periodic_1000_ms); 
 



/************************************************************************
 * 
 * Static variables and queue management functions for port:
 * 	input
 * 
 ************************************************************************/

can__can_frame_i smaccm_queue_input [1];
bool smaccm_queue_full_input  = false;
uint32_t smaccm_queue_front_input  = 0;
uint32_t smaccm_queue_back_input  = 0;

bool smaccm_queue_is_full_input() {
	return (smaccm_queue_front_input == smaccm_queue_back_input) && (smaccm_queue_full_input);
}

bool smaccm_queue_is_empty_input() {
	return (smaccm_queue_front_input == smaccm_queue_back_input) && (!smaccm_queue_full_input); 
}

bool smaccm_queue_read_input(can__can_frame_i * input) {
	if (smaccm_queue_is_empty_input()) {
		return false;
	} else {
		memcpy(input, &smaccm_queue_input[smaccm_queue_back_input], sizeof(can__can_frame_i));

		smaccm_queue_back_input = (smaccm_queue_back_input + 1) % 1; 
		smaccm_queue_full_input = false ; 
		return true;
	}
}

bool smaccm_queue_write_input(const can__can_frame_i * input) {
	if (smaccm_queue_is_full_input()) {
		return false;
	} else {
		memcpy(&smaccm_queue_input[smaccm_queue_front_input], input, sizeof(can__can_frame_i));

		smaccm_queue_front_input = (smaccm_queue_front_input + 1) % 1; 		
		if (smaccm_queue_back_input == smaccm_queue_front_input) { 
			smaccm_queue_full_input = true ; 
		}
		return true;
	}
}

/************************************************************************
 *  input_write_can__can_frame_i: 
 * Invoked by: remote interface.
 * 
 * This is the function invoked by a remote RPC to write to an active-thread
 * input event data port.  It queues the input message into a circular buffer.
 * 
 ************************************************************************/

bool input_write_can__can_frame_i(const can__can_frame_i * arg) {
	bool result;
	smaccm_sendrecv_input_mut_lock(); 
	result = smaccm_queue_write_input( arg);
	smaccm_sendrecv_input_mut_unlock(); 
	smaccm_dispatch_sem_post();

	return result;
}


/************************************************************************
 *  sendrecv_read_input: 
 * Invoked from local active thread.
 * 
 * This is the function invoked by the active thread to read from the 
 * input event data queue circular buffer.
 * 
 ************************************************************************/

bool sendrecv_read_input(can__can_frame_i * arg) {
	bool result; 
	smaccm_sendrecv_input_mut_lock(); 
	result = smaccm_queue_read_input(arg);
	smaccm_sendrecv_input_mut_unlock(); 
	return result;
}



can__can_frame_i * smaccm_tmp_array_output; 
uint32_t * smaccm_tmp_used_output;
uint32_t smaccm_max_tmp_array_output; 	


/************************************************************************
 * periodic_1000_ms Declarations
 * 
 ************************************************************************/

bool smaccm_occurred_periodic_1000_ms;
uint64_t smaccm_time_periodic_1000_ms;

/************************************************************************
 * sendrecv_periodic_1000_ms_write_uint64_t
 * Invoked from remote periodic dispatch thread.
 * 
 * This function records the current time and triggers the active thread 
 * dispatch from a periodic event.
 * 
 ************************************************************************/

bool sendrecv_periodic_1000_ms_write_uint64_t(const uint64_t * arg) {
	smaccm_occurred_periodic_1000_ms = true;
	smaccm_time_periodic_1000_ms = *arg;
	smaccm_dispatch_sem_post();

	return true;
}



/************************************************************************
 *  dispatch_dispatch_periodic_1000_ms: 
 * Invoked by remote RPC (or, for active thread, local dispatcher).
 * 
 * This is the function invoked by an active thread dispatcher to 
 * call to a user-defined entrypoint function.  It sets up the dispatch
 * context for the user-defined entrypoint, then calls it.
 * 
 ************************************************************************/

void dispatch_dispatch_periodic_1000_ms(
const uint64_t * periodic_1000_ms ,
  smaccm_can__can_frame_i_struct_1 *output_data, uint32_t * output_index 
) {
	smaccm_max_tmp_array_output = 1;
	smaccm_tmp_used_output = output_index;
	smaccm_tmp_array_output = output_data->f; 
	*smaccm_tmp_used_output = 0; 

	send(periodic_1000_ms); 

}	


/************************************************************************
 *  dispatch_dispatch_input: 
 * Invoked by remote RPC (or, for active thread, local dispatcher).
 * 
 * This is the function invoked by an active thread dispatcher to 
 * call to a user-defined entrypoint function.  It sets up the dispatch
 * context for the user-defined entrypoint, then calls it.
 * 
 ************************************************************************/

void dispatch_dispatch_input(
const can__can_frame_i * input ,
  smaccm_can__can_frame_i_struct_1 *output_data, uint32_t * output_index 
) {
	smaccm_max_tmp_array_output = 1;
	smaccm_tmp_used_output = output_index;
	smaccm_tmp_array_output = output_data->f; 
	*smaccm_tmp_used_output = 0; 

	receive(input); 

}	



/************************************************************************
 * sendrecv_write_output 
 * Invoked from local active or passive thread.
 * 
 * This is the comm function invoked by a user-level thread to send a message 
 * to another thread.  It enqueues the request to be sent when the user thread
 * completes execution.
 * 
 ************************************************************************/

bool sendrecv_write_output(const can__can_frame_i * output) {
	if (smaccm_max_tmp_array_output > 0 && 
		 *smaccm_tmp_used_output < smaccm_max_tmp_array_output) {
		memcpy(&smaccm_tmp_array_output[*smaccm_tmp_used_output], output, sizeof(can__can_frame_i));

		(*smaccm_tmp_used_output)++;
		return true;
	} else {
		return false;
	}
}


/************************************************************************
 * 
smaccm_sendrecv_input_dispatcher
 * Invoked from local active thread.
 * 
 * This is the dispatcher function invoked to respond to an incoming thread 
 * stimulus: an ISR, a periodic dispatch, or a queued event.
 * 
 ******************************************************************************/
void 
smaccm_sendrecv_input_dispatcher(can__can_frame_i * input) {
	smaccm_can__can_frame_i_struct_1 output_data ;
	uint32_t output_index;


	 
	// make the call: 
	dispatch_dispatch_input(  input, 
 		&output_data,
 		&output_index  
	
		); 
	 

	// call the aadl dispatchers for any generated output events.
	// to prevent misuse by malicious clients, we ensure that the number 
	// of dispatches is less than the maximum allowed dispatch count.
	uint32_t smaccm_it; 
	for (smaccm_it = 0; smaccm_it < output_index && smaccm_it < 1; smaccm_it++) {
	   // Calling an active dispatch target.
	   sendrecv_output_write_can__can_frame_i(
	   (&(output_data.f[smaccm_it]))
	   );	

	}

}
/************************************************************************
 * 
smaccm_dispatcher_periodic_1000_ms
 * Invoked from local active thread.
 * 
 * This is the dispatcher function invoked to respond to an incoming thread 
 * stimulus: an ISR, a periodic dispatch, or a queued event.
 * 
 ******************************************************************************/
void 
smaccm_dispatcher_periodic_1000_ms(uint64_t * periodic_1000_ms) {
	smaccm_can__can_frame_i_struct_1 output_data ;
	uint32_t output_index;


	 
	// make the call: 
	dispatch_dispatch_periodic_1000_ms(  periodic_1000_ms, 
 		&output_data,
 		&output_index  
	
		); 
	 

	// call the aadl dispatchers for any generated output events.
	// to prevent misuse by malicious clients, we ensure that the number 
	// of dispatches is less than the maximum allowed dispatch count.
	uint32_t smaccm_it; 
	for (smaccm_it = 0; smaccm_it < output_index && smaccm_it < 1; smaccm_it++) {
	   // Calling an active dispatch target.
	   sendrecv_output_write_can__can_frame_i(
	   (&(output_data.f[smaccm_it]))
	   );	

	}

}
 
/************************************************************************
 * run()
 * Main active thread function.
 * 
 ************************************************************************/

int run() {
	// port initialization routines (if any)... 

	// thread initialization routines (if any)...

	// register interrupt handlers (if any)...
	  

	// initial lock to await dispatch input.
	smaccm_dispatch_sem_wait();

	for(;;) {
		smaccm_dispatch_sem_wait();


		// drain the queues 
		if (smaccm_occurred_periodic_1000_ms) {
			smaccm_occurred_periodic_1000_ms = false;

			smaccm_dispatcher_periodic_1000_ms(&smaccm_time_periodic_1000_ms);
		}

		while (!smaccm_queue_is_empty_input()) {
			can__can_frame_i input ;
			smaccm_queue_read_input(&input);

			smaccm_sendrecv_input_dispatcher(&input); 
		}


	}
	// won't ever get here, but form must be followed
	return 0;
}



/**************************************************************************
  End of autogenerated file: /home/ajgacek/smaccm/models/Trusted_Build_Test/can/components/sendrecv/src/smaccm_sendrecv.c
 **************************************************************************/
