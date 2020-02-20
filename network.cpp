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
	printf("\n\n正在查找路由器ip与运营商网关ip...\n");

	FILE* pFileWrite = freopen("outfile.txt", "w", stdout);
	system("tracert -h 5 baidu.com");
	fclose(pFileWrite);
	freopen("CON", "w", stdout);

	printf("查找完成！\n\n");
#endif
	FILE* fp = fopen("outfile.txt", "r");
	int i = 0;

	for(i=0;i<5;i++)
		fgets(buff, 80, fp);
	
	strcpy(router, getip(buff));
	printf("路由器的ip地址为：%s\n", router);
	fgets(buff, 80, fp);
	fgets(buff, 80, fp);
	strcpy(gateway, getip(buff));
	printf("运营商网关的ip地址为：%s\n", gateway);

	return 1;
}

int routertest(int require)
{
	printf("\n\n正在测试与路由器之间的通信，请稍后...\n");
	int lost = 0;
//	char router[] = "192.168.1.1 ";
	ping(router, require);

	//system("CLS");
	printf("测试完成，本次总共与路由器进行了%d次通讯\n", require);
	printf("您每次的延迟分别为：");

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
	printf("\n您的最大延迟为：%dms\n", max);
	printf("您的平均延迟为：%dms\n", avr);

	printf("在本次测试中，有%d次延迟超过10ms，占总数的%.2f\n", unstable, unstable / require);
	printf("在本次测试中，有%d次丢包，占总数的%.2f\n", lost, lost / require);

	return 1;
}

int gatewaytest(int require)
{
	printf("\n\n正在测试与运营商网关之间的通信，请稍后...\n");
	int lost = 0;
	//	char router[] = "192.168.1.1 ";
	ping(router, require);

	//system("CLS");
	printf("测试完成，本次总共与网关进行了%d次通讯\n", require);
	printf("您每次的延迟分别为：");

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
	printf("\n您的最大延迟为：%dms\n", max);
	printf("您的平均延迟为：%dms\n", avr);

	printf("在本次测试中，有%d次延迟超过10ms，占总数的%.2f\n", unstable, unstable / require);
	printf("在本次测试中，有%d次丢包，占总数的%.2f\n", lost, lost / require);

	return 1;
}

int main(void)
{
	
	int require = 0;
#ifndef DEBUG
	while(1)
	{
		printf("请输入需要ping的次数(0-99)：");
		scanf("%d", &require);
		if (require < 99 && require>0)
			break;
		else
			printf("输入有误！请重新输入\n");
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