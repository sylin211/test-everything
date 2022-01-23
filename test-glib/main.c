#include <stdio.h>
#include <glib.h>
#include "test-mutex.h"
int main() {
	
	write_num_to_queue_multi_thread();

	return 0;
}