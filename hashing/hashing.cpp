// hashing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<stdio.h>
using namespace std;

struct Node {
	int data;
	struct Node* next;
};

struct Hash {
	Node **arr;
	int hashNo;
};
int hashFunction(int key){
	int index = key%10;
	return index;
};

int linearProbing(struct Hash* h, int key){
	int index = hashFunction(key);
	int i=1;
	int newindex=index;
	while(h->arr[newindex]!=NULL){
		newindex = (index + i)%h->hashNo;
		if(h->arr[newindex]==NULL){
			return newindex;
		}
		i++;
	}
	return index;
}

int quadraticProbing(struct Hash* h, int key){
	int index = hashFunction(key);
	int i=1;
	int newindex=index;
	while(h->arr[newindex]!=NULL){
		newindex = (index + (i*i))%h->hashNo;
		if(h->arr[newindex]==NULL){
			return newindex;
		}
		i++;
	}
	return index;


}

struct Hash* initialiseHash(struct Hash* h){
	for(int i =0; i<h->hashNo; i++){
		h->arr[i] = NULL;
	}
	return h;
}

struct Node* newNode(int data){
	struct Node* n;
	n =(Node*)malloc(sizeof(Node));
	n->data=data;
	n->next = NULL;
	return n;
}

struct Node* sortList(struct Node* n){
	static struct Node* head=n;

	
	if(n==NULL || n->next==NULL){
	return head;
	}

	if(n->data > n->next->data)
		{
			int temp = n->data;
			n->data= n->next->data;
			n->next->data = temp;	
		}
	n = sortList(n->next);

	
	

}

struct Hash* createHash(int keys[], int len, int hashNo){
	struct Hash* hashTable = (Hash*)malloc(sizeof(Hash));
	hashTable->hashNo = hashNo;
	//allocating memory for hashtable arr
	hashTable->arr = (Node**)malloc(sizeof(Node*)*hashTable->hashNo);
	int index,i=0;
	//setting all values of hash table to Null
	hashTable = initialiseHash(hashTable);
	while(i<len){
		//finding value at which to place keys[] in hashtable
		//index = hashFunction(keys[i]);
		//index = linearProbing(hashTable,keys[i]);
		index = quadraticProbing(hashTable,keys[i]);

		//creating new node with key[i] as data
		struct Node* temp = newNode(keys[i]); 

		struct Node* head = hashTable->arr[index];
		//inserting node into hashtable
		if(head==NULL)
		head = temp;
		else{
			struct Node* end;
			end=head;
			while(end->next!=NULL){
				end = end->next;
			}

			end->next = temp;
			head = sortList(head);
		}
		hashTable->arr[index] = head;
		//iterating while loop
		i++;	
	}
	return hashTable;
}

void printHash(struct Hash* h){
	int i =0;
	while(i<h->hashNo){
		if(!h->arr[i]){
			cout<<"None\n";
		
		}
		else{
			while(h->arr[i]!=NULL){
			cout<<h->arr[i]->data<<" ";
			h->arr[i] = h->arr[i]->next;
			}
			cout<<"\n";
		}
		i++;
	}
	cout<<"\n";


}

void searchHash(struct Hash* h, int key){
	int i = hashFunction(key);	

		if(h->arr[i]!=NULL){
			if(h->arr[i]->data == key){
				cout<<"the number "<<key<<" is present";
				return;
			}		
		}
		if(h->arr[i]->next!=NULL){
			while(h->arr[i]!=NULL){
				if(h->arr[i]->data == key)
				{cout<<"the number "<<key<<"is present";
				return;}
				h->arr[i] = h->arr[i]->next;
			}
		}
		cout<<"the key is not present";
	
}


int _tmain(int argc, _TCHAR* argv[])
{
	int keys[10]={32,45,67,73,80,21,11,61,98,31};
	struct Hash* hashTable= (Hash*)malloc(sizeof(Hash));
	hashTable = createHash(keys,10,10);
	printHash(hashTable);
	//searchHash(hashTable,11);
	return 0;
}

