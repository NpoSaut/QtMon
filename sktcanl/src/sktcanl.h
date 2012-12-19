/*
 * sktcanl.h
 *
 *  Created on: Dec 11, 2012
 *      Author: Yuri Zabaznov
 */

#ifndef SKTCANL_H_
#define SKTCANL_H_

void sktcanl_set_callbacks(void (*f_speed)(double* speed), void (*f_speed_limit)(int* speed_limit), void (*f_passed_distance)(int* passed_distance));
int sktcanl_init();
void sktcanl_read_can_msg();

#endif /* SKTCANL_H_ */
