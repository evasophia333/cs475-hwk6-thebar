/*
 * customer.c
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
#include "customer.h"

/**
 * This is what the thread will call.
 * Do not touch.
 */
void* customer(void* args)
{
	unsigned int *custID = (unsigned int*) args;
	custTravelToBar(*custID);
	custArriveAtBar(*custID);
	custPlaceOrder();
	custBrowseArt();
	custAtRegister();
	custLeaveBar();
	return NULL;
}


/**
 * Each customer takes a random amount of time between 20 ms and 5000 ms to travel to the bar.
 */
void custTravelToBar(unsigned int custID)
{
	int randTime = (rand() % ((5000 - 20)+ 1)) + 20;
	unsleep(randTime);
	printf("Cust %u\t\t\t\t\t\t\t\t\t\t\t|\n", custID);
	sem_post(custToBar); //sem1
}


/**
 * If there is already another customer in the bar the current customer has
 * to wait until bar is empty before entering.
 */
void custArriveAtBar(unsigned int custID)
{
	//is there already another customer?
	sem_wait(custToBar);
	printf("\t\tCust %u\t\t\t\t\t\t\t\t\t|\n", custID);
	now_serving = custID;
	sem_post(custArrAtBar);   //sem2
}


/**
 * The customer in the bar places an order
 */
void custPlaceOrder()
{
	sem_post(custOrder); //sem3
	sem_post(custBrowsing); //sem4
	printf("\t\t\t\tCust %u\t\t\t\t\t\t\t|\n", now_serving);
}


/**
 * The customer in the bar can browse the wall art for a random amount of time between 3ms and 4000ms.
 */
void custBrowseArt()
{
	sem_wait(custBrowsing);
	int randTime = (rand() % ((4000 - 3)+ 1)) + 3;
	unsleep(randTime);
	printf("\t\t\t\t\t\tCust %u\t\t\t\t\t|\n", now_serving);
}


/**
 * If their drink is not ready by the time they are done admiring the art they must wait
 * until the bartender has finished. When the bartender is finished, the customer pays.
 *
 */
void custAtRegister()
{
	sem_wait(bartenderWaitsInCloset); //sem5
	printf("\t\t\t\t\t\t\t\tCust %u\t\t\t|\n", now_serving);
	sem_post(payForDrink); //sem6
}


/**
 * The customer in the bar leaves the bar.
 */
void custLeaveBar()
{
	sem_wait(paymentSucessful);
	printf("\t\t\t\t\t\t\t\t\t\tCust %u\t|\n", now_serving);
	sem_post(custLeavesBar); //sem7
}
