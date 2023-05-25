/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node **h);

/* functions that you have to implement */
void inorderTraversal(Node *ptr);			/* recursive inorder traversal */
void preorderTraversal(Node *ptr);			/* recursive preorder traversal */
void postorderTraversal(Node *ptr);			/* recursive postorder traversal */
int insert(Node *head, int key);			/* insert a node to the tree */
int deleteLeafNode(Node *head, int key);	/* delete the leaf node for the key */
Node *searchRecursive(Node *ptr, int key);	/* search the node for the key */
Node *searchIterative(Node *head, int key); /* search the node for the key */
int freeBST(Node *head);					/* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */
void freetree(Node *p);
int main()
{
	char command;
	int key;
	Node *head = NULL;
	Node *ptr = NULL; /* temp */

	do
	{
		printf("\n[----- [Hyaejun mun] [2019015035] -----]\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command)
		{
		case 'z':
		case 'Z':
			initializeBST(&head);
			break;
		case 'q':
		case 'Q':
			freeBST(head);
			break;
		case 'n':
		case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd':
		case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f':
		case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's':
		case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i':
		case 'I':
			inorderTraversal(head->left);
			break;
		case 'p':
		case 'P':
			preorderTraversal(head->left);
			break;
		case 't':
		case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node **h)
{

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node *)malloc(sizeof(Node));
	(*h)->left = NULL; /* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}

void inorderTraversal(Node *ptr) // 배열을 좌 -> 중앙 -> 우 방식으로 확인하기.
{								 // recursive(재귀) 방식으로 만들어야 함!
	if (ptr != NULL)
	{
		inorderTraversal(ptr->left);  // 왼쪽 탐색,
		printf(" [%d] ", ptr->key);	  // 가운데 출력,
		inorderTraversal(ptr->right); // 오른쪽 탐색 순으로 진행한다.
	}
}

void preorderTraversal(Node *ptr) // 배열을 중앙 -> 좌 -> 우 방식으로 확인하기.
{								  // 미리 설명한 대로, 재귀 방식으로 만들어야 함.
	if (ptr != NULL)
	{
		printf(" [%d] ", ptr->key);	   // 가운데 출력,
		preorderTraversal(ptr->left);  // 왼쪽 탐색,
		preorderTraversal(ptr->right); // 오른쪽 탐색 순으로 진행한다.
	}
}

void postorderTraversal(Node *ptr) // 배열을 좌 -> 우 -> 중앙 방식으로 확인하기.
{								   // 재귀 방식으로 만들어야 함!
	if (ptr != NULL)
	{
		postorderTraversal(ptr->left);	// 왼쪽 탐색,
		postorderTraversal(ptr->right); // 오른쪽 탐색,
		printf(" [%d] ", ptr->key);		// 가운데 출력 순으로 진행한다.
	}
}

int insert(Node *head, int key) // tree의 형식을 유지하면서 노드를 삽입해야 한다.
{
	if (head == NULL) // 트리가 생성되지 않았으면,
	{
		printf("There is no tree.\n"); // 아무것도 실행하지 않고 종료한다.
		return 1;
	}
	Node *p = (Node *)malloc(sizeof(Node));
	p->key = key;
	p->left = NULL;
	p->right = NULL;
	if (head->left == NULL) // 트리에 노드가 하나도 없으면,
	{
		head->left = p; // 트리의 루트로 삽입한다.
		return 0;
	}
	Node *find = head->left; // 트리를 탐색하는 노드.
	Node *parent = NULL;	 // find의 부모. find를 이용해 노드를 입력할 위치를 알아냄.
	while (find != NULL)
	{
		parent = find;
		if (find->key == key) // 같은 key를 가진 노드가 있을 경우, 그냥 종료한다.
			return 1;
		if (find->key > key) // key가 더 작으면, 탐색 노드를 왼쪽으로 이동시킨다.
			find = find->left;
		else // key가 더 크면, 탐색 노드를 오른쪽으로 이동시킨다.
			find = find->right;
	}					   // 이제, parent 노드는 입력할 위치의 부모 노드가 됨.
	if (parent->key > key) // 왼쪽에 넣을지, 오른쪽에 넣을지만 결정하면 됨.
		parent->left = p;
	else
		parent->right = p;
	return 0;
}

int deleteLeafNode(Node *head, int key)
{
	if (head == NULL) // 트리가 생성되지 않았으면,
	{
		printf("There is no tree.\n"); // 아무것도 실행하지 않고 종료한다.
		return 1;
	}
	if (head->left == NULL) // 트리에 노드가 하나도 없으면,
	{
		printf("Tree is empty.\n"); // 아무것도 실행하지 않고 종료한다.
		return 1;
	}
	Node *p = head->left;
	Node *parent = head;
	while (p != NULL)
	{
		if (p->key == key) // 노드를 찾는다.
		{
			if (p->left == NULL && p->right == NULL) // 조건을 만족하면서, 리프 노드여야 한다.
			{
				if (parent == head) // 지울 노드가 루트인 경우
					head->left = NULL;
				if (parent->left == p) // 지울 노드의 위치 찾기(부모 노드의 링크 제거 위함)
					parent->left = NULL;
				else
					parent->right = NULL;
				free(p); // 링크 제거했으면, p 제거
			}
			else // 리프 노드가 아닌 경우
				printf("That node is not leaf node.\n");
			return 0; // key가 같은 다른 노드는 없으므로, 이제 종료한다.
		}
		parent = p;
		if (p->key > key)
			p = p->left;
		else
			p = p->right;
	}
	printf("There is no key.\n");
	return 1;
}

Node *searchRecursive(Node *ptr, int key)
{
	if (ptr == NULL) // 트리가 생성되지 않았으면,
		return NULL;
	if (ptr->key > key) // 트리가 오름차순임을 이용!
		ptr = searchRecursive(ptr->left, key);
	if (ptr->key < key)
		ptr = searchRecursive(ptr->right, key);
	if (ptr->key == key) // 위치를 찾았으면, 그 위치를 리턴한다.
		return ptr;
}

Node *searchIterative(Node *head, int key)
{
	if (head == NULL) // 트리가 생성되지 않았으면,
	{
		printf("There is no tree.\n"); // 아무것도 실행하지 않고 종료한다.
		return NULL;
	}
	if (head->left == NULL) // 트리에 노드가 하나도 없으면,
	{
		printf("Tree is empty.\n"); // 아무것도 실행하지 않고 종료한다.
		return NULL;
	}
	Node *find = head->left; // 트리를 탐색하기 위한 노드
	while (find != NULL)
	{
		if (find->key > key)	// 트리의 원소가 더 크면,
			find = find->left;	// key는 트리의 왼쪽에 있을 확률이 크다.
		if (find->key < key)	// 트리의 원소가 더 크면,
			find = find->right; // key는 트리의 왼쪽에 있을 확률이 크다.
		if (find->key == key)	// 원하는 위치에 도달했으면,
			return find;		// 그 위치를 리턴한다.
	}
	return NULL; // 찾지 못했으면, NULL을 리턴한다.
}

void freetree(Node *p)
{
	if (p == NULL) // p가 비어있을 경우, 그냥 종료.
		return;
	freetree(p->left); // p의 왼쪽, 오른쪽을 모두 할당 해제해주면
	freetree(p->right);
	free(p); // 자기 자신도 풀어준다.
}

int freeBST(Node *head)
{
	if (head == NULL) // 아무 실행도 안하고 종료할 경우
	{
		return 1;
	}
	if (head->left == NULL) // 헤드 생성(z)만 하고 종료할 경우
	{
		free(head);
		return 1;
	}
	Node *p = head->left; // 트리 돌아다니면서 할당 해제할 포인터.
	freetree(p);		  // 제거 함수를 재귀로 구현하기 위해 따로 함수를 만든다.
	free(head);
	return 0;
}