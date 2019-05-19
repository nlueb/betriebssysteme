#include "baeckerei.h"

baker_t* stock = NULL;
queue_t* queue = NULL;

int main(int argc, char* argv[])
{
	init_defaults();

	parse_args(argc, argv);
	print_parameters();

	/* Init the random number generator with the current time */
	srandom((unsigned int) time(NULL));

	stock = baker_new(b, r);
	queue = queue_new((size_t) l);

	pthread_t baker_thread;
	pthread_create(&baker_thread, NULL, &baker_thread_main, (void*) stock);

	for(int i = 0; i < m; i++)
	{
		pthread_t customer_thread;
		pthread_create(&customer_thread, NULL, &customer_thread_main, (void*) customer_new());
	}
	for(int i = 0; i < n; i++)
	{
		pthread_t vendor_thread;
		pthread_create(&vendor_thread, NULL, &vendor_thread_main, (void*) NULL);
	}

	printf("starting: main\n");

	for(int i = 1; i < 20; i++) {
		sleep(1);
		printf("breads: %u after %d seconds\n", baker_get_breads(stock), i);
	}

	pthread_join(baker_thread, NULL);
	baker_destroy(stock);

	return 0;
}
