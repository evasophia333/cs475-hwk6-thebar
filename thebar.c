/*
 * TheBar.c
 *
 *  Created on: Dec 26, 2015
 *      Author: dchiu
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include "globals.h"
#include "customer.h"
#include "bartender.h"

void printBanner();
void init();
void cleanup();

/**
 * Main function
 */
int main(int argc, char **argv)
{
	if(atoi(argv[1]) > 0 && atoi(argv[1]) < 3){

	
	printBanner();
	init(); // initialize semaphores
	//fire off customer thread
	int numThreads = atoi(argv[1]);
	//For customers
	pthread_t threadsForCust[numThreads];
	for(int i=0; i<numThreads;i++){
		pthread_create(&threadsForCust[i], NULL, customer, (void *)&i);
	}

	//for bartneder 
	pthread_t barThread;
	pthread_create(&barThread, NULL, bartender, NULL);


	//wait for all threads to finish
	for(int i=0; i<num_threads;i++){ 
		pthread_join(threadsForCust[i], NULL);
	}
	// joining bartender thread
	pthread_join(barThread, NULL); 
	cleanup(); // cleanup and destroy semaphores
	}else if(atoi(argv[1]) < 0){
		printf("Negative Customers Not Possible! Please try again!!\n");

	}else{
		printf("Uh oh! The bar only has room for two customers MAX! Try with fewer customers.");
	}
	return 0;
}

/**
 * Prints the activity banner.
 * Do not touch.
 */
void printBanner()
{
	printf("Customer:\t\t\t\t\t\t\t\t\t\t| Employee:\n");
	printf("Traveling\tArrived\t\tOrdering\tBrowsing\tAt Register\tLeaving");
	printf("\t| Waiting\tMixing Drinks\tAt Register\tPayment Recv\n");
	printf("----------------------------------------------------------------------------------------+");
	printf("-----------------------------------------------------------\n");
}

/**
 * Create and initialize semaphores
 */
void init()
{
	// unlink semaphores
	sem_unlink("/custToBar");
	sem_unlink("/custArrAtBar");
	sem_unlink("/custOrdering");
	sem_unlink("/custBrowsing");
	sem_unlink("/payForDrink");
	sem_unlink("/custLeavesBar");

	sem_unlink("/paymentSucessful");
	sem_unlink("/makingDrinks");
	sem_unlink("/bartenderWaitsInCloset");
	
	//create semaphores
	custToBar = sem_open("/custToBar",  O_CREAT, 0600, 0);
	custArrAtBar = sem_open("/custArrAtBar",  O_CREAT, 0600, 0);
	custOrdering = sem_open("/custOrdering",  O_CREAT, 0600, 0);
	custBrowsing = sem_open("/custBrowsing",  O_CREAT, 0600, 0);
	payForDrink = sem_open("/payForDrink",  O_CREAT, 0600, 0);
	custLeavesBar = sem_open("/custLeavesBar",  O_CREAT, 0600, 0);

	paymentSucessful = sem_open("/paymentSucessful",  O_CREAT, 0600, 0);
	makingDrinks = sem_open("/makingDrinks",  O_CREAT, 0600, 0);
	bartenderWaitsInCloset = sem_open("/bartenderWaitsInCloset",  O_CREAT, 0600, 0);
}	

/**
 * Cleanup and destroy semaphores
 */
void cleanup()
{
	//close semaphores
	sem_close(custToBar);
	sem_close(custArrAtBar);
	sem_close(custOrdering);
	sem_close(custBrowsing);
	sem_close(payForDrink);
	sem_close(custLeavesBar);

	sem_close(paymentSucessful);
	sem_close(makingDrinks);
	sem_close(bartenderWaitsInCloset);
}
