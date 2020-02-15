#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void term_handler(int i) // функция-обработчик сигнала
{
	printf("Terminating\n");
	exit(EXIT_SUCCESS);
}
int main(int argc, char ** argv)
{
	struct sigaction sa; /* спец. структура используемая в качестве параметра системного вызова sigaction() */
	sigset_t newset; // набор сигналов
	sigemptyset(&newset); // инициализирует набор сигналов, указанный в newset, и "очищает" его от всех сигналов
	sigaddset(&newset, SIGHUP); // добавляем сигнал SIGHUP в наш набор  
	sigprocmask(SIG_BLOCK, &newset, 0); // добавляем набор newset в группу заблокированных 
	sa.sa_handler = term_handler; // добавляем в структуру типа  sigaction указатель на функцию обработчик сигнала
	sigaction(SIGTERM, &sa, 0); /* этим вызовом с учётом всех предыдущих действий
					мы назначили нашему процессу обработчик term_handler на случай получения сигнала SIGTERM
					- т.е. сигнала "предложения завершиться"*/

	printf("My pid is %i\n", getpid()); // выводим pid процесса
	printf("Waiting...\n");

	while (1) sleep(1); // бесконечный цикл с задержкой на одну секунду силлисекунду на каждый виток

	return EXIT_FAILURE;
}