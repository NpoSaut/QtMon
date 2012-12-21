/*
 * sktcanl.c
 *
 *  Created on: Dec 11, 2012
 *      Author: Yuri Zabaznov
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>

#include <linux/can.h>
#include <linux/can/raw.h>
#include <string.h>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <errno.h>


#define IFACE_NAME "can0"


// Interface section
struct iparameters
{
	int gps_year;
	int gps_month;
	int gps_day;
	int gps_hour;
	int gps_min;
	int gps_sec;
	double gps_lat;
	double gps_lon;

	double speed;
	int speed_limit;
	int stop_flag;
	int movement_direction;
	int trafficlight_light;
	int trafficlight_freq;
	double passed_distance;
	int epv_state;
	int epv_readiness;
	int epv_breakage_cause;
	//double pressure;

	int operator_alertness;
}
g_iparameters;


// getSocket создает и настраивает сокет на CAN-интерфейсе iface_name
int getSocket(char* iface_name)
{
	int errsv = 0;

	// Создаем сокет
	errno = 0;
	int s = socket(PF_CAN, SOCK_RAW, CAN_RAW);
	if(s < 0)
	{
		errsv = errno;
		fprintf(stderr, "Ошибка при открытии сокета: %d\n", errsv);
		fflush(stderr);
		return 0;
	}

	// Определяем индекс интерфейса
	struct ifreq ifr;
	strcpy(ifr.ifr_name, iface_name);
	// Полученный индес будет записан в поле ifr.ifr_ifindex
	errno = 0;
	ioctl(s, SIOCGIFINDEX, &ifr);
	if(ifr.ifr_ifindex < 0)
	{
		errsv = errno;
		fprintf(stderr,"Не найден интерфейс %s, ошибка: %d\n", iface_name, errno);
		fflush(stderr);
		return 0;
	}
	printf("Найден CAN интерфейс: %d\n", ifr.ifr_ifindex);

	// Биндим сокет на нужный интерфейс
	struct sockaddr_can addr;
	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;
	bind(s, (struct sockaddr*)&addr, sizeof(addr));

	return s;
}

int send_can_frame(int s, struct can_frame* frame)
{
	if (!s)
	{
		printf("send_can_frame: сокет не существует\n");
		fflush(stdout);
	}

	errno = 0;
	int bytes_sent = write(s, frame, sizeof(struct can_frame));
	if(bytes_sent < 0)
	{
		int errsv = errno;
		fprintf(stderr, "send_can_frame: ошибка при отправке: %d\n", errsv);
		fflush(stderr);
		return 0;
	}
/*
//#ifdef DEBUG
	//printf("Успешно отправлено %d байт на %s\n", bytes_sent, iface_name);
	printf("send_can_frame: успешно отправлено %d байт\n", bytes_sent);
//#endif // DEBUG
*/
	return 1;
}

int read_can_frame(int s, struct can_frame* frame)
{
	if (!s)
	{
		printf("read_can_frame: сокет не существует\n");
		fflush(stdout);
	}

	errno = 0;
	int bytes_read = read(s, frame, sizeof(struct can_frame));
	if(bytes_read < 0)
	{
		int errsv = errno;
		fprintf(stderr, "read_can_frame: ошибка при чтении: %d\n", errsv);
		fflush(stderr);
		return 0;
	}
/*
//#ifdef DEBUG
	printf("read_can_frame: принято сообщение:\n");
	printf("длина: %d\n", (*frame).can_dlc);
	printf("id: %d\n", (*frame).can_id);
	printf("data: [");
	int i;
	for(i = 0; i < (*frame).can_dlc; i++)
		printf("0x%02x, ", (*frame).data[i]);
	printf("]\n");
//#endif // DEBUG
*/
	return 1;
}

int read_socket = -1;
int write_socket = -1;

struct can_frame read_frame;


//======================================

// -1 - incorrect frame ID
// 0 - A != B
// 1 - success

// SAUT_INFO_A
int cfd_speed(struct can_frame* frame, double* speed)
{
	if ((*frame).can_id != 0x233) return -1;

	double s1 = (double)((*frame).data[0]);
	double s2 = ( (double)( (*frame).data[1] >> 1 ) ) / 128;
	double s3 = (double)( ((*frame).data[1] & 0b00000001 ) == 0 ? 0 : 256 );

	(*speed) = s1 + s2 + s3;
	return 1;
}

// MCO_STATE_A
int cfd_speed_limit(struct can_frame* frame, int* speed_limit)
{
	if ((*frame).can_id != 0x050) return -1;

	(*speed_limit) = ( ((int)( (*frame).data[3] & 0b10000000 )) << 8 ) + (int)((*frame).data[1]);

	return 1;
}

// SAUT_INFO_A
int cfd_stop_flag(struct can_frame* frame, int* stop_flag)
{
	if ((*frame).can_id != 0x233) return -1;

	(*stop_flag) = (int) (( (*frame).data[7] >> 2 ) & 0b00000001 );

	return 1;
}

// IPD_STATE_A
int cfd_movement_direction(struct can_frame* frame, int* movement_direction)
{
	if ((*frame).can_id != 0x0C4) return -1;

	(*movement_direction) = (int) (( (*frame).data[1] >> 7 ) & 0b00000001 );

	return 1;
}

// MCO_STATE_A
int cfd_trafficlight_light(struct can_frame* frame, int* trafficlight_light)
{
	if ((*frame).can_id != 0x050) return -1;

	(*trafficlight_light) = (int) ( (*frame).data[5] & 0b00001111 );

	return 1;
}

// MP_STATE_A
int cfd_trafficlight_freq(struct can_frame* frame, int* trafficlight_freq)
{
	if ((*frame).can_id != 0x08F) return -1;

    (*trafficlight_freq) = (int) (( (*frame).data[4] & 0b00110000 ) >> 4);

	return 1;
}

// IPD_STATE_A
int cfd_passed_distance(struct can_frame* frame, int* passed_distance)
{
	if ((*frame).can_id != 0x0C4) return -1;

	(*passed_distance) = (((int) (*frame).data[5]) << 16) + (((int) (*frame).data[3]) << 8) + ((int) (*frame).data[4]);

	return 1;
}

// MCO_STATE_A
int cfd_epv_state(struct can_frame* frame, int* epv_state)
{
	if ((*frame).can_id != 0x050) return -1;

	(*epv_state) = (int) ( ( (*frame).data[5] >> 5 ) & 0b00000001 );

	return 1;
}

// MCO_STATE_A
int cfd_epv_key(struct can_frame* frame, int* epv_key)
{
	if ((*frame).can_id != 0x050) return -1;

	(*epv_key) = (int) ( ( (*frame).data[0] >> 6 ) & 0b00000001 );

	return 1;
}


// MM_ALT_LONG
int cfd_mm_lat_lon(struct can_frame* frame, double* lat, double* lon)
{
	if ((*frame).can_id != 0x213) return -1;

	int lat_i =((int) (*frame).data[0]) + (((int) (*frame).data[1]) << 8) + (((int) (*frame).data[2]) << 16) + (((int) (*frame).data[3]) << 24);
    *lat = (double)lat_i * 10e-9 * 180 / 3.14159265359;

	int lon_i =((int) (*frame).data[4]) + (((int) (*frame).data[5]) << 8) + (((int) (*frame).data[6]) << 16) + (((int) ((*frame).data[7]) & 0b01111111 ) << 24);
    *lon = (double)lon_i * 10e-9 * 180 / 3.14159265359;

	return 1;
}

// IPD_DATE
int cfd_ipd_datetime(struct can_frame* frame, int* ipd_hours, int* ipd_min, int* ipd_sec)
{
	if ((*frame).can_id != 0x0C7) return -1;

	*ipd_hours = (int) (*frame).data[4];
	*ipd_min = (int) (*frame).data[5];
	*ipd_sec = (int) (*frame).data[6];

	return 1;
}


// TEMP===============================================================

double c_speed;
int c_speed_limit;
int c_stop_flag;
int c_movement_direction;
int c_trafficlight_light;
int c_trafficlight_freq;
int c_passed_distance;
int c_epv_state;
int c_epv_key;
double c_mm_lat; double c_mm_lon;
int c_ipd_hours; int c_ipd_min; int c_ipd_sec;

void (*cbk_speed)(double* speed);
void (*cbk_speed_limit)(int* speed_limit);
void (*cbk_stop_flag)(int* stop_flag);
void (*cbk_movement_direction)(int* movement_direction);
void (*cbk_trafficlight_light)(int* trafficlight_light);
void (*cbk_trafficlight_freq)(int* trafficlight_freq);
void (*cbk_passed_distance)(int* passed_distance);
void (*cbk_epv_state)(int* epv_state);
void (*cbk_epv_key)(int* epv_key);
void (*cbk_mm_lat_lon)(double* mm_lat, double* mm_lon);
void (*cbk_ipd_datetime)(int* ipd_hours, int* ipd_min, int* ipd_sec);


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
		void (*f_ipd_datetime)(int* ipd_hours, int* ipd_min, int* ipd_sec))
{
	cbk_speed = f_speed;
	cbk_speed_limit = f_speed_limit;
	cbk_stop_flag = f_stop_flag;
	cbk_movement_direction = f_movement_direction;
	cbk_trafficlight_light = f_trafficlight_light;
	cbk_trafficlight_freq = f_trafficlight_freq;
	cbk_passed_distance = f_passed_distance;
	cbk_epv_state = f_epv_state;
	cbk_epv_key = f_epv_key;
	cbk_mm_lat_lon = f_mm_lat_lon;
	cbk_ipd_datetime = f_ipd_datetime;
}

int sktcanl_init()
{
	char* iface_name = IFACE_NAME;

	// Подготавливаем сокет
	printf("Инициализация SocketCAN\n");
	fflush(stdout);
	read_socket = getSocket(iface_name);
	if(!read_socket)
		return 0;
	printf("Сокет чтения готов\n");
	fflush(stdout);
	return 1;
}

void sktcanl_read_can_msg()
{
	read_can_frame(read_socket, &read_frame);

	double prev_c_speed = c_speed;
	int prev_c_speed_limit = c_speed_limit;
	int prev_c_stop_flag = c_stop_flag;
	int prev_c_movement_direction = c_movement_direction;
	int prev_c_trafficlight_light = c_trafficlight_light;
	int prev_c_trafficlight_freq = c_trafficlight_freq;
	int prev_c_passed_distance = c_passed_distance;
	int prev_c_epv_state = c_epv_state;
	int prev_c_epv_key = c_epv_key;
	double prev_c_mm_lat = c_mm_lat; double prev_c_mm_lon = c_mm_lon;
	int prev_c_ipd_hours = c_ipd_hours; int prev_c_ipd_min = c_ipd_min; int prev_c_ipd_sec = c_ipd_sec;

	if (cfd_speed(&read_frame, &c_speed) == 1)
	{
		if (cbk_speed != NULL && prev_c_speed != c_speed)
		{
			cbk_speed(&c_speed);
		}
		printf("Скорость: %f\n", c_speed);
		fflush(stdout);
	}
	if (cfd_passed_distance(&read_frame, &c_passed_distance) == 1)
	{
		if (cbk_passed_distance != NULL && prev_c_passed_distance != c_passed_distance)
		{
			cbk_passed_distance(&c_passed_distance);
		}
		printf("Пройденный путь: %d\n", c_passed_distance);
		fflush(stdout);
	}
	if (cfd_speed_limit(&read_frame, &c_speed_limit) == 1)
	{
		if (prev_c_speed_limit != c_speed_limit)
		{
			cbk_speed_limit(&c_speed_limit);
		}
		printf("Ограничение скорости: %d\n", c_speed_limit);
		fflush(stdout);
	}
	if (cfd_trafficlight_light(&read_frame, &c_trafficlight_light) == 1)
	{
		if (prev_c_trafficlight_light != c_trafficlight_light)
		{
			cbk_trafficlight_light(&c_trafficlight_light);
		}
		printf("Светофор: %d\n", c_trafficlight_light);
		fflush(stdout);
	}
    if (cfd_trafficlight_freq(&read_frame, &c_trafficlight_freq) == 1)
    {
        if (prev_c_trafficlight_freq != c_trafficlight_freq)
        {
            cbk_trafficlight_freq(&c_trafficlight_freq);
        }
        printf("Частота светофора: %d\n", c_trafficlight_freq);
        fflush(stdout);
    }
	if (cfd_epv_state(&read_frame, &c_speed_limit) == 1)
	{
		if (prev_c_epv_state != c_epv_state)
		{
			cbk_epv_state(&c_epv_state);
		}
		printf("Состояние ЭПК: %d\n", c_epv_state);
		fflush(stdout);
	}
	if (cfd_epv_key(&read_frame, &c_epv_key) == 1)
	{
		if (prev_c_epv_key != c_epv_key)
		{
			cbk_speed_limit(&c_epv_key);
		}
		printf("Ключ ЭПК: %d\n", c_epv_key);
		fflush(stdout);
	}
	if (cfd_epv_key(&read_frame, &c_epv_key) == 1)
	{
		if (prev_c_epv_key != c_epv_key)
		{
			cbk_speed_limit(&c_epv_key);
		}
		printf("Ключ ЭПК: %d\n", c_epv_key);
		fflush(stdout);
	}
	if (cfd_mm_lat_lon(&read_frame, &c_mm_lat, &c_mm_lon) == 1)
	{
		if (prev_c_mm_lat != c_mm_lat || prev_c_mm_lon != c_mm_lon)
		{
			cbk_mm_lat_lon(&c_mm_lat, &c_mm_lon);
		}
		printf("Широта: %f, долгота: %f\n", c_mm_lat, c_mm_lon);
		fflush(stdout);
	}
	if (cfd_ipd_datetime(&read_frame, &c_ipd_hours, &c_ipd_min, &c_ipd_sec) == 1)
	{
		if (prev_c_ipd_hours != c_ipd_hours || prev_c_ipd_min != c_ipd_min || prev_c_ipd_sec != c_ipd_sec)
		{
			cbk_ipd_datetime(&c_ipd_hours, &c_ipd_min, &c_ipd_sec);
		}
		printf("Время: %d:%d:%d\n", c_ipd_hours, c_ipd_min, c_ipd_sec);
		fflush(stdout);
	}
}

