#include "customer.h"

void* customer_thread_main(void* data)
{
	printf("starting: customer\n");
	customer_t* self = (customer_t*) data;

	while(true)
	{
		customer_stroll();
		if (!baker_has_breads(stock)) continue;
		if (queue_full(queue)) continue;
		if (!queue_enqueue(queue, (void*) self)) continue;
		break;
	}

	sem_wait(&self->sem);

	printf("Thread %lu got %u breads\n", pthread_self(), self->gotten_breads);

	customer_destroy(self);
	return NULL;
}

void customer_stroll(void)
{
	sleep((unsigned int)((random() % 12) + 1));
}

void customer_init(customer_t* customer)
{
	customer->wanted_breads = (int)((random() % 5) + 1);
	customer->gotten_breads = 0;
	sem_init(&customer->sem, 0, 0);
}

customer_t* customer_new()
{
	customer_t* customer = malloc(sizeof(customer_t));
	customer_init(customer);
	return customer;
}

void customer_destroy(customer_t* customer)
{
	sem_destroy(&customer->sem);
	free(customer);
}

void customer_give_breads(customer_t* customer, int breads)
{
	customer->gotten_breads = breads;
}
