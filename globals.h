/*
 * globals.h
 *
 *  Created on: Dec 26, 2015
 *      Author: dchiu
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

int num_threads;	// number of customer threads
int now_serving;	// customer's ID who is being served

//semaphores
sem_t* custToBar;
sem_t* custArrAtBar;
sem_t* custOrdering;
sem_t* custBrowsing;
sem_t* payForDrink;
sem_t* custLeavesBar;

sem_t* paymentSucessful;
sem_t* makingDrinks;
sem_t* bartenderWaitsInCloset;

#endif /* GLOBALS_H_ */
