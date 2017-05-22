#include <hellfire.h>
#include <noc.h>

/*
name port   cpu
t1 - 1111 -  0
t2 - 1222 -  1
t3 - 1333 -  1
t4 - 1444 -  2
t5 - 1555 -  2
t6 - 1666 -  3
t7 - 1777 -  3
t8 - 1888 -  4
t9 - 1999 -  5

*/

//t1 is a sender only
void t1(void)
{
	int32_t i, msg = 0;
	int8_t buf[500];
	uint16_t val;
	
	if (hf_comm_create(hf_selfid(), 1111, 0))
		panic(0xff);
	
	while (1){
		for (i = 0; i < hf_ncores(); i++, msg++){
			if (hf_cpuid() != i){
				//to cpu 1
				if(i == 1){
					sprintf(buf, "hello from cpu %d thread %d msg %d\n", hf_cpuid(), hf_selfid(), msg);
					//send to t2
					val = hf_sendack(i, 1222, buf, sizeof(buf), 0, 256);
					if (val) printf("t1, hf_sendack(): error %d\n", val);
					//send to t3
					val = hf_sendack(i, 1333, buf, sizeof(buf), 0, 64);
					if (val) printf("t1, hf_sendack(): error %d\n", val);
				}
				//to cpu 2
				if(i == 2){
					sprintf(buf, "hello from cpu %d thread %d msg %d\n", hf_cpuid(), hf_selfid(), msg);
					//send to t4
					val = hf_sendack(i, 1444, buf, sizeof(buf), 0, 64);
					if (val) printf("t1, hf_sendack(): error %d\n", val);
					//send to t5
					val = hf_sendack(i, 1555, buf, sizeof(buf), 0, 64);
					if (val) printf("t1, hf_sendack(): error %d\n", val);
				}
				//to cpu 3
				if(i == 3){
					sprintf(buf, "hello from cpu %d thread %d msg %d\n", hf_cpuid(), hf_selfid(), msg);
					//send to t7
					val = hf_sendack(i, 1777, buf, sizeof(buf), 0, 1280);
					if (val) printf("t1, hf_sendack(): error %d\n", val);
				}
			}
		}
		delay_ms(10);
	}
}

//t2 sends and receives
void t2(void)
{
	int32_t i, msg = 0;
	int8_t buf[500];
	uint16_t val;
	
	if (hf_comm_create(hf_selfid(), 1222, 0))
		panic(0xff);
	
	while (1){
		for (i = 0; i < hf_ncores(); i++, msg++){
			//first try to get message
			val = hf_recvack(&cpu, &task, buf, &size, 0);
			if (val)
				printf("error %d\n", val);
			else
				printf("%s", buf);
			//then send messages
			if (hf_cpuid() != i){
				//to cpu 3
				if(i == 3){
					sprintf(buf, "hello from cpu %d thread %d msg %d\n", hf_cpuid(), hf_selfid(), msg);
					//send to t6
					val = hf_sendack(i, 1666, buf, sizeof(buf), 0, 64);
					if (val) printf("t2, hf_sendack(): error %d\n", val);
					//send to t7
					val = hf_sendack(i, 1777, buf, sizeof(buf), 0, 320);
					if (val) printf("t2, hf_sendack(): error %d\n", val);
				}
				//to cpu 4
				if(i == 4){
					sprintf(buf, "hello from cpu %d thread %d msg %d\n", hf_cpuid(), hf_selfid(), msg);
					//send to t8
					val = hf_sendack(i, 1888, buf, sizeof(buf), 0, 320);
					if (val) printf("t2, hf_sendack(): error %d\n", val);
				}
			}
		}
		delay_ms(10);
	}
}

//t3 sends and receives
void t3(void)
{
	int32_t i, msg = 0;
	int8_t buf[500];
	uint16_t val;
	
	if (hf_comm_create(hf_selfid(), 1333, 0))
		panic(0xff);
	
	while (1){
		for (i = 0; i < hf_ncores(); i++, msg++){
			//first try to get message
			val = hf_recvack(&cpu, &task, buf, &size, 0);
			if (val)
				printf("error %d\n", val);
			else
				printf("%s", buf);
			//then send messages
			if (hf_cpuid() != i){
				//to cpu 3
				if(i == 3){
					sprintf(buf, "hello from cpu %d thread %d msg %d\n", hf_cpuid(), hf_selfid(), msg);
					//send to t7
					val = hf_sendack(i, 1777, buf, sizeof(buf), 0, 320);
					if (val) printf("t3, hf_sendack(): error %d\n", val);
				}
				//to cpu 4
				if(i == 4){
					sprintf(buf, "hello from cpu %d thread %d msg %d\n", hf_cpuid(), hf_selfid(), msg);
					//send to t8
					val = hf_sendack(i, 1888, buf, sizeof(buf), 0, 64);
					if (val) printf("t3, hf_sendack(): error %d\n", val);
				}
			}
		}
		delay_ms(10);
	}
}

//t4 sends and receives
void t4(void)
{
	int32_t i, msg = 0;
	int8_t buf[500];
	uint16_t val;
	
	if (hf_comm_create(hf_selfid(), 1444, 0))
		panic(0xff);
	
	while (1){
		for (i = 0; i < hf_ncores(); i++, msg++){
			//first try to get message
			val = hf_recvack(&cpu, &task, buf, &size, 0);
			if (val)
				printf("error %d\n", val);
			else
				printf("%s", buf);
			//then send messages
			if (hf_cpuid() != i){
				//to cpu 4
				if(i == 4){
					sprintf(buf, "hello from cpu %d thread %d msg %d\n", hf_cpuid(), hf_selfid(), msg);
					//send to t8
					val = hf_sendack(i, 1888, buf, sizeof(buf), 0, 64);
					if (val) printf("t4, hf_sendack(): error %d\n", val);
				}
			}
		}
		delay_ms(10);
	}
}

//t5 sends and receives
void t5(void)
{
	int32_t i, msg = 0;
	int8_t buf[640];
	uint16_t val;
	
	if (hf_comm_create(hf_selfid(), 1555, 0))
		panic(0xff);
	
	while (1){
		for (i = 0; i < hf_ncores(); i++, msg++){
			//first try to get message
			val = hf_recvack(&cpu, &task, buf, &size, 0);
			if (val)
				printf("error %d\n", val);
			else
				printf("%s", buf);
			//then send messages
			if (hf_cpuid() != i){
				//to cpu 4
				if(i == 4){
					sprintf(buf, "hello from cpu %d thread %d msg %d\n", hf_cpuid(), hf_selfid(), msg);
					//send to t8
					val = hf_sendack(i, 1888, buf, sizeof(buf), 0, 640);
					if (val) printf("t5, hf_sendack(): error %d\n", val);
				}
			}
		}
		delay_ms(10);
	}
}

//t6 sends and receives
void t6(void)
{
	int32_t i, msg = 0;
	int8_t buf[640];
	uint16_t val;
	
	if (hf_comm_create(hf_selfid(), 1666, 0))
		panic(0xff);
	
	while (1){
		for (i = 0; i < hf_ncores(); i++, msg++){
			//first try to get message
			val = hf_recvack(&cpu, &task, buf, &size, 0);
			if (val)
				printf("error %d\n", val);
			else
				printf("%s", buf);
			//then send messages
			if (hf_cpuid() != i){
				//to cpu 5
				if(i == 5){
					sprintf(buf, "hello from cpu %d thread %d msg %d\n", hf_cpuid(), hf_selfid(), msg);
					//send to t9
					val = hf_sendack(i, 1999, buf, sizeof(buf), 0, 640);
					if (val) printf("t6, hf_sendack(): error %d\n", val);
				}
			}
		}
		delay_ms(10);
	}
}

//t7 sends and receives
void t7(void)
{
	int32_t i, msg = 0;
	int8_t buf[1280];
	uint16_t val;
	
	if (hf_comm_create(hf_selfid(), 1777, 0))
		panic(0xff);
	
	while (1){
		for (i = 0; i < hf_ncores(); i++, msg++){
			//first try to get message
			val = hf_recvack(&cpu, &task, buf, &size, 0);
			if (val)
				printf("error %d\n", val);
			else
				printf("%s", buf);
			//then send messages
			if (hf_cpuid() != i){
				//to cpu 5
				if(i == 5){
					sprintf(buf, "hello from cpu %d thread %d msg %d\n", hf_cpuid(), hf_selfid(), msg);
					//send to t9
					val = hf_sendack(i, 1999, buf, sizeof(buf), 0, 640);
					if (val) printf("t7, hf_sendack(): error %d\n", val);
				}
			}
		}
		delay_ms(10);
	}
}

//t8 sends and receives
void t8(void)
{
	int32_t i, msg = 0;
	int8_t buf[640];
	uint16_t val;
	
	if (hf_comm_create(hf_selfid(), 1777, 0))
		panic(0xff);
	
	while (1){
		for (i = 0; i < hf_ncores(); i++, msg++){
			//first try to get message
			val = hf_recvack(&cpu, &task, buf, &size, 0);
			if (val)
				printf("error %d\n", val);
			else
				printf("%s", buf);
			//then send messages
			if (hf_cpuid() != i){
				//to cpu 5
				if(i == 5){
					sprintf(buf, "hello from cpu %d thread %d msg %d\n", hf_cpuid(), hf_selfid(), msg);
					//send to t9
					val = hf_sendack(i, 1999, buf, sizeof(buf), 0, 640);
					if (val) printf("t8, hf_sendack(): error %d\n", val);
				}
			}
		}
		delay_ms(10);
	}
}

//t9 receives only
void t9(void)
{
	int8_t buf[640];
	uint16_t cpu, task, size, val;
	
	if (hf_comm_create(hf_selfid(), 1999, 0))
		panic(0xff);
	
	while (1){
		val = hf_recvack(&cpu, &task, buf, &size, 0);
		if (val)
			printf("error %d\n", val);
		else
			printf("%s", buf);
	}
}

void app_main(void)
{
	if (hf_cpuid() == 0){
		hf_spawn(t1, 0, 0, 0, "t1", 2048);
	}
	if (hf_cpuid() == 1){
		hf_spawn(t2, 0, 0, 0, "t2", 2048);
		hf_spawn(t3, 0, 0, 0, "t3", 2048);
	}
	if (hf_cpuid() == 2){
		hf_spawn(t4, 0, 0, 0, "t4", 2048);
		hf_spawn(t5, 0, 0, 0, "t5", 2048);
	}
	if (hf_cpuid() == 3){
		hf_spawn(t6, 0, 0, 0, "t6", 2048);
		hf_spawn(t7, 0, 0, 0, "t7", 2048);
	}
	if (hf_cpuid() == 4){
		hf_spawn(t8, 0, 0, 0, "t8", 2048);
	}
	if (hf_cpuid() == 5){
		hf_spawn(t9, 0, 0, 0, "t9", 2048);
	}
}
