/*
 * sktcanl.h
 *
 *  Created on: Dec 11, 2012
 *      Author: Yuri Zabaznov
 */

#ifndef SKTCANL_H_
#define SKTCANL_H_

void set_callbacks(void (*f_speed)(double* speed), void (*f_speed_limit)(int* speed_limit), void (*f_passed_distance)(int* passed_distance));
int init();
void read_can_msg();

#endif /* SKTCANL_H_ */
