#include <stdio.h>    // Standard input/output definitions
#include <stdlib.h>
#include <string.h>   // String function definitions
#include <unistd.h>   // para usleep()
#include <getopt.h>
#include <math.h>

#include "arduino-serial-lib.h"

float calculateSD(float data[]);
float calculateProm(float data[]);

void error(char* msg)
{
    fprintf(stderr, "%s\n",msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
	int fd = -1;
	int baudrate = 9600;  // default

	fd = serialport_init("/dev/ttyACM0", baudrate);
	
	float temperatura[12]={0};
	float humedad[12]={0};

	if( fd==-1 )
	{
		error("couldn't open port");
		return -1;
	}

	char com1 = 't';
	char com2 = 'h';
	int c = 0;
	while (c<12){
		int temp=0;

		write(fd,&com1,1);
		read(fd,&temp,1);
		temperatura[c]=(float)temp;
		printf("Temperatura: %d\n",temp);
		usleep(500000);
		
		c++;	
	}
	printf("Prom = %.2f\n",calculateProm(temperatura));
	printf("SD = %.2f\n\n",calculateSD(temperatura));

	usleep(2000000);	
	c=0;

	while (c<12){
		int hum=0;

		write(fd,&com2,1);
		read(fd,&hum,1);
		humedad[c]=(float)hum;
		printf("Humedad: %d\n",hum);
		usleep(500000);	
		c++;	
	}
	printf("Prom = %.2f\n",calculateProm(humedad));
	printf("SD = %.2f\n",calculateSD(temperatura));	
	close( fd );
	return 0;	
}

/* Ejemplo para calcular desviacion estandar y media */
float calculateSD(float data[])
{
    float sum = 0.0, mean, standardDeviation = 0.0;

    int i;
	int cero=0;
    for(i = 0; i < 12; ++i)
    {
        if(data[i] != 0)		
		        sum += data[i];
		else
			cero++;
    }

    mean = sum/(12-cero);

    for(i = 0; i < 12; ++i){
	if(data[i] != 0)
	        standardDeviation += pow(data[i] - mean, 2);
	}
    return sqrt(standardDeviation / (12-cero));
}

float calculateProm(float data[])
{
	int cero=0;
	int sum =0;
	for(int i = 0; i < 12; ++i)
	{
		if(data[i] != 0)		
		        sum += data[i];
		else
			cero++;
	
    	}

    	float mean = sum/(12-cero);
	return mean;
}
