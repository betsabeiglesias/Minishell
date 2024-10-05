// PROBANDO SEÑALES
//      SIGINT
//      SIGQUIT

#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>
#include <unistd.h>

#define BUFFER_SIZE 5

void ft_prompt()
{
    printf("esto es el segundo prompt\n");
}

void own_function(void)
{
	//static char buffer[1000];
	printf("\nexecuting OWN_FUNCTION\n");
	//read(0, buffer, BUFFER_SIZE);
}

void exe_c(int num)
{
	num = num;
    //printf("Escribe CNTRL+C, num: %d\n", num);
}
void exe_d(int num)
{
	num = num;
    //printf("Escribe CNTRL+\, num: %d\n", num);
}

int main()
{
	int a = 1;
    signal(SIGINT, &exe_c);
	//signal(SIGQUIT, &exe_d);
	while(1)
	{
		if (a == 1)
		{
			printf("dentro de while\n");
			a = 0;
		}
		own_function();
		sleep(10);
	}
    return (0);
}
///////////