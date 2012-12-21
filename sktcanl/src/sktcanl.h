/*
 * sktcanl.h
 *
 *  Created on: Dec 11, 2012
 *      Author: Yuri Zabaznov
 */

#ifndef SKTCANL_H_
#define SKTCANL_H_

void sktcanl_set_callbacks(
		void (*f_speed)(double* speed),
		void (*f_speed_limit)(int* speed_limit),
		void (*f_stop_flag)(int* stop_flag),
		void (*f_movement_direction)(int* movement_direction),
		void (*f_trafficlight_light)(int* trafficlight_light),
		void (*f_trafficlight_freq)(int* trafficlight_freq),
		void (*f_passed_distance)(int* passed_distance),
		void (*f_epv_state)(int* epv_state),
		void (*f_epv_key)(int* epv_key),
		void (*f_mm_lat_lon)(double* mm_lat, double* mm_lon),
		void (*f_ipd_datetime)(int* ipd_hours, int* ipd_min, int* ipd_sec));
int sktcanl_init();
void sktcanl_read_can_msg();

#endif /* SKTCANL_H_ */
