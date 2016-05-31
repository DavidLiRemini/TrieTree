/*
 * trie.h
 *
 *  Created on: 2016年3月30日
 *      Author: mysql
 */

#ifndef TRIE_H_
#define TRIE_H_
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define TRANSFORM
#define MAXDIGIT 26
#define PERSISTENTTEST
//#define AUTODESTROY
struct TrieNode{
	int counter;
	bool IsLeaf;
#ifdef TRANSFORM
	char trans[11];
#endif
	TrieNode* Next[MAXDIGIT];
	TrieNode();
};

class TrieTree{
private:
	TrieNode* _root;
private:
	TrieNode* CreateNode();
	int search(TrieNode*, char*);
	char* search_trans(TrieNode*, char*);
	void Insert(TrieNode*, char*, bool* flag);
	void DestroyTree(TrieNode*);
	void Insert(TrieNode*, char*, char*);
	void DeleteString(char*, TrieNode*);
public:
	TrieTree();
	int search(char*);
	char* search_trans(char*);
	void insert(char*, bool* flag = NULL);
	void insert(char*, char*);
	void DeleteString(char*);
	void DestroyTree();
	~TrieTree();
};



#endif /* TRIE_H_ */
