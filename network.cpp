#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "utilities.h"
//#define DEBUG 1
#define MAXMUN 99

extern int unstable;
int time[MAXMUN];
char* buff = (char*)malloc(80 * sizeof(char));

char* router = (char*)malloc(16 * sizeof(char));
char* gateway = (char*)malloc(16 * sizeof(char));;

int ping(char* target, int n)
{
	char command[] = "ping ";
	char segment[] = " -n ";
	//char number[2] = { char(n+48), '\0' };
//	printf("%d\n", sizeof(n));
	
	char* cmd = (char*)malloc(strlen(command) + strlen(segment) + strlen(target) + numlen(n));
	sprintf(cmd, "%s%s%s%d", command, target, segment, n);
//	printf("%d", sizeof(cmd));

	FILE* pFileWrite = freopen("outfile.txt", "w", stdout);
	system(cmd);
	fclose(pFileWrite);
	freopen("CON", "w", stdout);
	
	return 1;
}

int tracert()
{	

#ifndef DEBUG
	printf("\n\n���ڲ���·����ip����Ӫ������ip...\n");

	FILE* pFileWrite = freopen("outfile.txt", "w", stdout);
	system("tracert -h 5 baidu.com");
	fclose(pFileWrite);
	freopen("CON", "w", stdout);

	printf("������ɣ�\n\n");
#endif
	FILE* fp = fopen("outfile.txt", "r");
	int i = 0;

	for(i=0;i<5;i++)
		fgets(buff, 80, fp);
	
	strcpy(router, getip(buff));
	printf("·������ip��ַΪ��%s\n", router);
	fgets(buff, 80, fp);
	fgets(buff, 80, fp);
	strcpy(gateway, getip(buff));
	printf("��Ӫ�����ص�ip��ַΪ��%s\n", gateway);

	return 1;
}

int routertest(int require)
{
	printf("\n\n���ڲ�����·����֮���ͨ�ţ����Ժ�...\n");
	int lost = 0;
//	char router[] = "192.168.1.1 ";
	ping(router, require);

	//system("CLS");
	printf("������ɣ������ܹ���·����������%d��ͨѶ\n", require);
	printf("��ÿ�ε��ӳٷֱ�Ϊ��");

	FILE* fp = fopen("outfile.txt", "r");
	int i = 0;

	//	fprintf(fp, "%s", buff);
	fgets(buff, 80, fp);
	fgets(buff, 80, fp);
	for (i = 0; i < require; i++)
	{
		fgets(buff, 80, fp);
		time[i] = gettime(buff);
		if (time[i] == -1)
		{
			lost++;
			continue;
		}
	}

	for (i = 0; i < 5; i++)
		fgets(buff, 80, fp);

	int max = getmax(buff);
	int avr = getaverage(buff);
	printf("\n��������ӳ�Ϊ��%dms\n", max);
	printf("����ƽ���ӳ�Ϊ��%dms\n", avr);

	printf("�ڱ��β����У���%d���ӳٳ���10ms��ռ������%.2f\n", unstable, unstable / require);
	printf("�ڱ��β����У���%d�ζ�����ռ������%.2f\n", lost, lost / require);

	return 1;
}

int gatewaytest(int require)
{
	printf("\n\n���ڲ�������Ӫ������֮���ͨ�ţ����Ժ�...\n");
	int lost = 0;
	//	char router[] = "192.168.1.1 ";
	ping(router, require);

	//system("CLS");
	printf("������ɣ������ܹ������ؽ�����%d��ͨѶ\n", require);
	printf("��ÿ�ε��ӳٷֱ�Ϊ��");

	FILE* fp = fopen("outfile.txt", "r");
	int i = 0;

	//	fprintf(fp, "%s", buff);
	fgets(buff, 80, fp);
	fgets(buff, 80, fp);
	for (i = 0; i < require; i++)
	{
		fgets(buff, 80, fp);
		time[i] = gettime(buff);
		if (time[i] == -1)
		{
			lost++;
			continue;
		}
	}

	for (i = 0; i < 5; i++)
		fgets(buff, 80, fp);

	int max = getmax(buff);
	int avr = getaverage(buff);
	printf("\n��������ӳ�Ϊ��%dms\n", max);
	printf("����ƽ���ӳ�Ϊ��%dms\n", avr);

	printf("�ڱ��β����У���%d���ӳٳ���10ms��ռ������%.2f\n", unstable, unstable / require);
	printf("�ڱ��β����У���%d�ζ�����ռ������%.2f\n", lost, lost / require);

	return 1;
}

int main(void)
{
	
	int require = 0;
#ifndef DEBUG
	while(1)
	{
		printf("��������Ҫping�Ĵ���(0-99)��");
		scanf("%d", &require);
		if (require < 99 && require>0)
			break;
		else
			printf("������������������\n");
	}
#endif
#ifdef DEBUG
	require = 10;
#endif

	tracert();
	routertest(require);
	gatewaytest(require);

	free(buff);
	free(router);
	free(gateway);

	int t=remove("outfile.txt");
//	printf("%d", t);

	system("pause");
	return 0;
}