#include "ht.h"
#include "node.h"

unsigned int hash_function (const void *key)
{
	size_t i;
	unsigned int hash = 0;

	size_t strlen_key = strnlen(key,16);

	for (i = 0; i < strlen_key; ++i) {
		hash += *((const char *)key + i);
	}

	return (hash * hash + hash) % MAX_HASH;
}

void ht_init (ht *h)
{
	int i;
	for (i = 0; i < MAX_HASH; ++i)
	{
		h->list[i] = (ll *) malloc (sizeof(ll));	

		if (h->list[i] == NULL)
		{
			perror("Malloc failed for h->list[i] !");
			exit (-1);
		}

		h->list[i]->head = NULL;
		h->list[i]->tail = NULL;
	}
}

void ht_insert (ht *h, const char *key, void *value)
{
	unsigned int hash = hash_function (key);

	node *new_node = (node *) malloc (sizeof(node));	
	if (new_node == NULL)
	{
		perror("Malloc failed for new node !");
		exit (-1);
	}

	new_node->key = (char *)strdup(key);
	if (new_node->key == NULL)
	{
		perror("Failed to malloc key !");
		exit(-1);
	}

	new_node->value 	= value; 
	new_node->next 		= h->list[hash]->head;
	h->list[hash]->head	= new_node;
}

void ht_delete(ht *h, const char *key)
{
	node *n 	= NULL;
	node *prev_n 	= NULL;

	node *tmp;

	unsigned int hash;

	if (!h || !key)
		return;

	hash = hash_function (key);

	n = h->list[hash]->head;

	while (n)
	{
		if (strcmp(key, n->key) == 0)
		{
			if (prev_n == NULL)
			{
				h->list[hash]->head = n->next;	
				free(n);
			}
			else
			{
				tmp = n;
				prev_n->next = n->next;
				free(tmp);
			}
			return;
		}

		prev_n = n;
		n = n->next;
	}
}

node* ht_search (ht *h, const char *key)
{
	node *n;
	unsigned int hash = hash_function (key);

	for (n = h->list[hash]->head; n ; n = n->next)
	{
		if (strcmp(key, n->key) == 0)
		{
			return n;
		}
	}
	return NULL;
}
