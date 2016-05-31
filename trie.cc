/*
 * trie.cc
 *
 *  Created on: 2016年3月30日
 *      Author: mysql
 */
#include "trie.h"
#include <assert.h>
#include <stdexcept>

TrieNode::TrieNode()
	:counter(0),
	 IsLeaf(false){
	memset(Next, 0, sizeof(Next));

}

TrieTree::TrieTree()
	:_root(nullptr){
	_root = CreateNode();
}

TrieNode* TrieTree::CreateNode()
{
#ifndef AUTODESTROY
	TrieNode* node = new TrieNode();
	return node;
#else
	std::shared_ptr<TrieNode>nd(new TrieNode());
	TrieNode* p = nd.get();
	return p;
#endif
}

void TrieTree::Insert(TrieNode* root, char* str, bool* flag)
{
	assert(root != NULL);
	if(str == NULL || !strcmp(str, ""))
		return;
	TrieNode* nd = root;
	char* ptr = str;
	int id = 0;
	while(*ptr)
	{
		if(*ptr >= '0' && *ptr <= '9')
			id = *ptr - '0';
		else if(*ptr >= 'a' && *ptr <= 'z')
			id = *ptr - 'a';
		else
			throw std::runtime_error("elements should be in < a ~ z or 0 ~ 9 >\n");
		if(nd->Next[id] == NULL)
		{
			nd->Next[id] = CreateNode();
		}
		nd = nd->Next[id];
		++ptr;
		nd->counter++;
#ifdef PERSISTENTTEST
		if(nd->counter > 1 && nd->IsLeaf)
		{
			printf("NO\n");
			*flag = true;
		}
#endif
	}
	nd->IsLeaf = true;
#ifdef PERSISTENTTEST
	if(nd->counter > 1 && nd->IsLeaf)
	{
		printf("NO\n");
		*flag = true;
	}
#endif
}

void TrieTree::Insert(TrieNode* root, char* str, char* trans)
{
	assert(root != NULL);
	if((str == NULL || !strcmp(str, "")) ||
			(trans == NULL || !strcmp(trans, "")))
		return ;
	TrieNode* nd = root;
	char* ptr = str;
	int id = 0;

	while(*ptr)
	{
		if(*ptr >= '0' && *ptr <= '9')
			id = *ptr - '0';
		else if(*ptr >= 'a' && *ptr <= 'z')
			id = *ptr - 'a';
		else
			throw std::runtime_error("elements not in < a ~ z or 0 ~ 9 >\n");
		if(nd->Next[id] == NULL)
		{
			nd->Next[id] = CreateNode();
		}
		nd = nd->Next[id];
		++ptr;
		nd->counter++;
	}
	nd->IsLeaf = true;
#ifdef TRANSFORM
	strcpy(nd->trans, trans);
#endif
}

int TrieTree:: search(TrieNode* root, char* str)
{
	assert(root != NULL);
	if(str == NULL || !strcmp("", str))
		return -1;
	char* ptr = str;
	int id = 0;
	TrieNode* nd = root;
	while(*ptr)
	{
		if(*ptr >= '0' && *ptr <= '9')
			id = *ptr - '0';
		else if(*ptr >= 'a' && *ptr <= 'z')
			id = *ptr - 'a';
		else
			throw std::runtime_error("elements not in a ~ z or 0 ~ 9\n");
		nd = nd->Next[id];
		if(nd == NULL)
			return 0;
		++ptr;
	}
	return nd->counter;
}

char* TrieTree:: search_trans(TrieNode* root, char* str)
{
	assert(root != NULL);
	if(str == NULL || !strcmp("", str))
		return NULL;
	char* ptr = str;
	int id = 0;
	TrieNode* nd = root;
	while(*ptr)
	{
		if(*ptr >= '0' && *ptr <= '9')
			id = *ptr - '0';
		else if(*ptr >= 'a' && *ptr <= 'z')
			id = *ptr - 'a';
		else
			throw std::runtime_error("elements not in a ~ z or 0 ~ 9\n");
		nd = nd->Next[id];
		if(nd == NULL)
			return NULL;
		++ptr;
	}
	if(nd->IsLeaf)
		return nd->trans;
	else
		return NULL;
}

char* TrieTree::search_trans(char* str)
{
	return search_trans(_root, str);
}
void TrieTree::DestroyTree(TrieNode* root)
{
	assert(root != NULL);
	for(int i = 0; i < MAXDIGIT; i++)
	{
		if(root->Next[i] != NULL)
			DestroyTree(root->Next[i]);
	}
	delete root;
}

void TrieTree::DestroyTree()
{
	DestroyTree(_root);
}
TrieTree::~TrieTree()
{
#ifndef AUTODESTROY
	DestroyTree();
#endif
}

int TrieTree::search(char* str)
{
	return search(_root, str);
}

void TrieTree::insert(char* str, bool* flag)
{
	Insert(_root, str, flag);
}

void TrieTree::insert(char* str, char* trans)
{
	Insert(_root, str, trans);
}

void TrieTree::DeleteString(char* str, TrieNode* tree)
{
	assert(tree != NULL);
	if(*str == '\0')
		return;
	int id = 0;
	char* ptr = str;
	TrieNode* nd = tree;
	if(*ptr >= '0' && *ptr <= '9')
		id = *ptr - '0';
	else if(*ptr >= 'a' && *ptr <= 'z')
		id = *ptr - 'a';
	else
		throw std::runtime_error("elements not in a ~ z or 0 ~ 9\n");

	if(nd->Next[id] != NULL)
	{
		--nd->Next[id]->counter;
		nd = nd->Next[id];
		++ptr;
		if(*ptr == '\0')
			nd->IsLeaf = false;
		DeleteString(ptr, nd);
	}
#ifndef AUTODESTROY
	if(nd->counter == 0 && nd != _root)
	{
		delete nd;
		tree->Next[id] = NULL;
	}
#endif
}

void TrieTree::DeleteString(char* str)
{
	DeleteString(str, _root);
}


