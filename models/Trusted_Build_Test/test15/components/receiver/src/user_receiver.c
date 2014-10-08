#include <smaccm_receiver.h>
#include <receiver.h>

void periodic_ping(/* const */uint32_t periodic_1000_ms) {
	printf("receiver: periodic dispatch received at time: %d", periodic_1000_ms); 

	bool result = true; 
	while (result) {
		result = receiver_read_Input1(); 
		if (result) {
   			printf("receiver: event consumed\n");
   		} else {
   			printf("receiver: queue emptied.\n");
   		}
   	}		
}