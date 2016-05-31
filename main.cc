/*
 * main.cc
 *
 *  Created on: 2016年3月30日
 *      Author: mysql
 */
#include "trie.h"
#include <stdio.h>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>

void test1()
{
	char str1[3000] = {0};
	char str2[3000] = {0};
	char str3[3000] = {0};
	TrieTree tree;
	scanf("%s", str1);
	while(scanf("%s", str1) && strcmp(str1, "END"))
	{
		scanf("%s", str2);
		tree.insert(str2, str1);
	}

	int index = 0;
	getchar();
	gets(str1);
	while(gets(str1))
	{
		if(!strcmp(str1, "END"))
		{
			break;
		}

		for(int i = 0; str1[i] != '\0'; ++i)
		{
			if(str1[i] >= 'a' && str1[i] <= 'z')
			{
				str3[index++] = str1[i];
			}
			else
			{
				str3[index] = '\0';
				char* p = tree.search_trans(str3);
				if(p)
					printf("%s", p);
				else
					printf("%s", str3);
				index = 0;
				printf("%c", str1[i]);
			}
		}
		printf("\n");
	}
}

void test2()
{
	TrieTree tree;
	char str1[300] = {0};
	char str2[300] = {0};

	while(gets(str1))
	{
		if(*str1 == '\0')
			break;
		tree.insert(str1);
	}

	while(gets(str2))
	{
		int result = tree.search(str2);
		printf("%d\n", result);
	}
}

void test3()
{
	int testcasenum;
	int datanum;
	TrieTree tree;
	char str[300] = {0};
	scanf("%d", &testcasenum);
	bool flag = false;
	for(int i = 0; i < testcasenum; i++)
	{
		scanf("%d", &datanum);
		getchar();
		while(gets(str))
		{
//			if(*str=='\0')
//				break;
			if(strlen(str) == 1)
			{
				i++;
				datanum = *str - '0';
				flag = false;
				continue;
			}
			tree.insert(str, &flag);
		}
		if(!flag)
			printf("YES\n");
	}
}
int main()
{
	int fd = open("/home/mysql/fork.cc", O_RDONLY);
	TrieNode* trie = new TrieNode();
	delete trie;
	close(fd);
	TrieTree treeroot;
	treeroot.insert("ABC");
	treeroot.insert("abc");
	treeroot.insert("bdaa");
	treeroot.insert("bcd");
	treeroot.DeleteString("abc");
	treeroot.DeleteString("bcd");
	printf("end\n");
//	test2();
}



