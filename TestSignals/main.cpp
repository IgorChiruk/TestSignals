#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void term_handler(int i) // �������-���������� �������
{
	printf("Terminating\n");
	exit(EXIT_SUCCESS);
}
int main(int argc, char ** argv)
{
	struct sigaction sa; /* ����. ��������� ������������ � �������� ��������� ���������� ������ sigaction() */
	sigset_t newset; // ����� ��������
	sigemptyset(&newset); // �������������� ����� ��������, ��������� � newset, � "�������" ��� �� ���� ��������
	sigaddset(&newset, SIGHUP); // ��������� ������ SIGHUP � ��� �����  
	sigprocmask(SIG_BLOCK, &newset, 0); // ��������� ����� newset � ������ ��������������� 
	sa.sa_handler = term_handler; // ��������� � ��������� ����  sigaction ��������� �� ������� ���������� �������
	sigaction(SIGTERM, &sa, 0); /* ���� ������� � ������ ���� ���������� ��������
					�� ��������� ������ �������� ���������� term_handler �� ������ ��������� ������� SIGTERM
					- �.�. ������� "����������� �����������"*/

	printf("My pid is %i\n", getpid()); // ������� pid ��������
	printf("Waiting...\n");

	while (1) sleep(1); // ����������� ���� � ��������� �� ���� ������� ������������ �� ������ �����

	return EXIT_FAILURE;
}