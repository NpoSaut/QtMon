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


#define IFACE_NAME "vcan0"


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
	}

	errno = 0;
	int bytes_sent = write(s, frame, sizeof(struct can_frame));
	if(bytes_sent < 0)
	{
		int errsv = errno;
		fprintf(stderr, "send_can_frame: ошибка при отправке: %d\n", errsv);
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
	}

	errno = 0;
	int bytes_read = read(s, frame, sizeof(struct can_frame));
	if(bytes_read < 0)
	{
		int errsv = errno;
		fprintf(stderr, "read_can_frame: ошибка при чтении: %d\n", errsv);
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

// IPD_STATE_A
int cfd_passed_distance(struct can_frame* frame, int* passed_distance)
{
	if ((*frame).can_id != 0x0C4) return -1;

	(*passed_distance) = (((int) (*frame).data[5]) << 16) + (((int) (*frame).data[3]) << 8) + ((int) (*frame).data[4]);

	return 1;
}



// TEMP===============================================================

double c_speed = 0;
int c_speed_limit = 0;
int c_passed_distance = 0;

void (*cbk_speed)(double* speed);
void (*cbk_speed_limit)(int* speed_limit);
void (*cbk_passed_distance)(int* passed_distance);

void set_callbacks(void (*f_speed)(double* speed), void (*f_speed_limit)(int* speed_limit), void (*f_passed_distance)(int* passed_distance))
{
	cbk_speed = f_speed;
	cbk_speed_limit = f_speed_limit;
	cbk_passed_distance = f_passed_distance;
}

int init()
{
	char* iface_name = IFACE_NAME;

	// Подготавливаем сокет
	printf("Инициализация SocketCAN\n");
	read_socket = getSocket(iface_name);
	if(!read_socket)
		return 0;
	printf("Сокет чтения готов\n");
	return 1;
}

void read_can_msg()
{
	read_can_frame(read_socket, &read_frame);

	double prev_c_speed = c_speed;
	int prev_c_speed_limit = c_speed_limit;
	int prev_c_passed_distance = c_passed_distance;

	if (cfd_speed(&read_frame, &c_speed) == 1)
	{
		if (cbk_speed != NULL && prev_c_speed != c_speed)
		{
			cbk_speed(&c_speed);
		}
		printf("Скорость: %f\n", c_speed);
	}
	else if (cfd_passed_distance(&read_frame, &c_passed_distance) == 1)
	{
		if (cbk_passed_distance != NULL && prev_c_passed_distance != c_passed_distance)
		{
			cbk_passed_distance(&c_passed_distance);
		}
		printf("Пройденный путь: %d\n", c_passed_distance);
	}
	else if (cfd_speed_limit(&read_frame, &c_speed_limit) == 1)
	{
		if (prev_c_speed_limit != c_speed_limit)
		{
			cbk_speed_limit(&c_speed_limit);
		}
		printf("Ограничение скорости: %d\n", c_speed_limit);
	}
}

