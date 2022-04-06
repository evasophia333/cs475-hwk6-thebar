/*
 * bartender.c
 *
 *  Created on: Dec 26, 2015
 *      Author: dchiu
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include "globals.h"
#include "bartender.h"

/**
 * Code for bartender thread.
 * Do not touch.
 */
void* bartender(void* args)
{
	int i;
	for (i = 0; i<num_threads; i++)
	{
		waitForCustomer();
		makeDrink();
		receivePayment();
	}
	return NULL;
}

/**
 * Waits in a closet until a customer enters.
 */
void waitForCustomer()
{
	sem_wait(custToBar);
	sem_post(bartenderWaitsInCloset);
	printf("\t\t\t\t\t\t\t\t\t\t\t| Bartender\n");
}


/**
 * When a customer places an order it takes the Bartender
 * a random amount of time between 5 ms and 1000 ms to make the drink.
 */
void makeDrink()
{
	sem_wait(custOrder);
	int randTime = (rand() % (1000 - 5 + 1)) + 5;
	usleep(randTime);
	printf("\t\t\t\t\t\t\t\t\t\t\t| \t\tBartender\n");
	sem_post(makingDrinks);
}


/**
 * Gets payment from the correct customer
 */
void receivePayment()
{
	sem_wait(payForDrink);
	//at the register waiting for customer to pay
	printf("\t\t\t\t\t\t\t\t\t\t\t| \t\t\t\tBartender\n");

	//got the payment from the right customer!
	sem_post(paymentSucessful);
	printf("\t\t\t\t\t\t\t\t\t\t\t| \t\t\t\t\t\tBartender\n");
}
