#include "utilities.h"

int unstable = 0;

int char_num_to_interge(char c)
{
	if (int(c) >= 48 && int(c) <= 57)
	{
		return int(c) - 48;
	}
	else
	{
		return -1;
	}
}

char* trim(char* strIn) 
{

//	char* strOut = {};
	int i, j;

	i = 0;

	j = strlen(strIn) - 1;

	//while (strIn[i] == ' ')
	//	++i;

	while (strIn[j] == '\n')
		--j;
	strncpy(strIn, strIn, j+ 1);
	strIn[j + 1] = '\0';
	return strIn;
}

int numlen(int n)
{
	if (n < 10)
		return 1;
	if (n < 100)
		return 2;
	return -1;
}

int gettime(char* buff)
{
	int time = 0;
	int temp;
	char* ptime = strstr(buff, "时间=");
	if (ptime != NULL)
	{
		temp = char_num_to_interge(ptime[5]);
		if (temp != -1)
		{
			time = temp;
		}
		temp = char_num_to_interge(ptime[6]);
		if (temp != -1)
		{
			time = time * 10 + temp;
		}
		temp = char_num_to_interge(ptime[7]);
		if (temp != -1)
		{
			time = time * 10 + temp;
		}
		printf("%dms ", time);
		if (time >= 10)
			unstable++;
		//delete ptime;
		return time;
	}
	else
		return -1;
}

int getmax(char* buff)
{
	int time = 0;
	int temp;
	char* ptime = strstr(buff, "最长");
	if (ptime != NULL)
	{
		temp = char_num_to_interge(ptime[7]);
		if (temp != -1)
		{
			time = temp;
		}
	}
	return time;
}

int getaverage(char* buff)
{
	int time = 0;
	int temp;
	char* ptime = strstr(buff, "平均");
	if (ptime != NULL)
	{
		temp = char_num_to_interge(ptime[7]);
		if (temp != -1)
		{
			time = temp;
		}
	}
	return time;
}

char* getip(char* buff)
{
	int i = 0;
	char* ip = buff;
	for (i = 0; i < 3; i++)
	{
		ip = strstr(ip, "ms");
		ip = strcpy(ip, ip + 2);
	}
	//printf("%d", strlen(ip));
	ip = strcpy(ip, ip + 2);
	ip = trim(ip);
	return ip;
}