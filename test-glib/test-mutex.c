#include "test-mutex.h"
#include <stdio.h>
#include <stdlib.h>
typedef struct mydata {
	gint id;
	gint data;
}mydata;

static gint sort_cmp(mydata* d1, mydata* d2) {
	if (d1->id > d2->id)
		return -1;
	else if (d1->id < d2->id)
		return 1;
	else 
		return 0;
}

static void display_queue_elements(gpointer param) {

	mydata* data = (mydata*)param;
	
	printf("%d ", data->id);
}

GQueue* q;

void func(gpointer param) {

	mydata* data = (mydata*)param;
	while (1) {
		
		g_queue_insert_sorted(q, data, (GCompareDataFunc)sort_cmp, NULL);

		g_usleep(1 * 1000);
	}
}

void write_num_to_queue_multi_thread() {
	
	q = g_queue_new();

	for (int i = 0; i < 100; i++) {
		mydata* data = (mydata*)g_malloc0(sizeof(mydata));
		data->id = i;
		gchar threadName[4];
		_itoa_s(i, threadName, 4, 10);
		printf("create thread: %d\n", i);
		GThread* t = g_thread_new(threadName, (GThreadFunc)func, data);
	}

	while (1) {
		g_usleep(10000 * 1000);
		break;
	}

	g_queue_foreach(q, (GFunc)display_queue_elements, NULL);
}