#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;//구조체 변수 선언

//스택
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;
//pop과 push
Node* pop();
void push(Node* aNode);

//큐
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;
//dequeue & enqueue
Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */
void printStack();



int main()
{
	char command;
	int key;
	Node* head = NULL; 

	do{
		printf("\n\n");
		printf("[----- [박성준] [2021040026] -----]\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		case 'p': case 'P':
			printStack();
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	//비어있을 경우에, free
	if(*h != NULL)
		freeBST(*h);

	//헤드노드 메모리할당
	*h = (Node*)malloc(sizeof(Node));
	//초기설정
	(*h)->left = NULL;	
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)
{
	if(ptr) {
		//있을 경우, 왼쪽주소 재귀함수 반복 
		recursiveInorder(ptr->left);
		//프린트
		printf(" [%d] ", ptr->key);
		//오른쪽 재귀함수 반복
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224
 */

void iterativeInorder(Node* node)
{
	for(;;)
	{
		for(; node; node = node->left)
			//node 푸쉬
			push(node);
		//반복문 종료 후 팝 
		node = pop();
		
		//노드에 없을 경우,끝내기 
		if(!node) break;
		//키 값을 꺼내기
		printf(" [%d] ", node->key);
		//node 변경
		node = node->right;
	}
}


void levelOrder(Node* ptr)
{
	// int front = rear = -1; 이미 설정되어 있음
	
	//비어있을경우
	if(!ptr) return;
	
	//enqueue
	enQueue(ptr);
	
	for(;;)
	{
		
		ptr = deQueue();
		if(ptr) {
			//프린트 키값
			printf(" [%d] ", ptr->key);
			//왼쪽주소일때
			if(ptr->left)
				//enqueue에 ptr->left
				enQueue(ptr->left);
			//오른쪽주소일때
			if(ptr->right)
				//enQueue에 ptr->right
				enQueue(ptr->right);
		}
		else
			break;

	}

}


int insert(Node* head, int key)
{	//newNode 메모리 할당
	Node* newNode = (Node*)malloc(sizeof(Node));
	//값 설정
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;
	//왼쪽주소가 비어있을경우에 
	if (head->left == NULL) {
		//newNode와 연결
		head->left = newNode;
		return 1;
	}
	
	//왼쪽 주소가 시작중심
	Node* ptr = head->left;
	//부모노드 null
	Node* parentNode = NULL;
	while(ptr != NULL) {
		
		//이미 해당 키가 있을 경우에 끝
		if(ptr->key == key) return 1;
		
		//부모노드에 ptr 넣기 
		parentNode = ptr;

		//ptr의 키 값이 입력한 수보다 작을때
		if(ptr->key < key)
			//오른쪽에다가
			ptr = ptr->right;
		//ptr의 키 값이 입력한 수보다 클때
		else
			//왼쪽에다가
			ptr = ptr->left;
	}

	//부모노드의 키 값이 입력한 수보다 클때
	if(parentNode->key > key)
		//왼쪽
		parentNode->left = newNode;
	//부모노드의 키 값이 입력한 수보다 클때
	else
		//오른쪽
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{
	//헤드가 비어있을때 
	if (head == NULL) {
		//프린트
		printf("\n Nothing to delete!!\n");
		return -1;
	}
	//헤드의 왼쪽이 비어있을때
	if (head->left == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	//헤드의 왼쪽이 루트
	Node* root = head->left;


	//부모노드 널
	Node* parent = NULL;
	//ptr 널 
	Node* ptr = root;
	
	//ptr이 널이며 키값이 중복되지 않을 동안,
	while((ptr != NULL)&&(ptr->key != key)) {
		//키값이 중복되지 않을 경우,
		if(ptr->key != key) {
			//부모노드 = ptr
			parent = ptr;	/* save the parent */
			//ptr의 키 값이 입력한 수보다 작을 때
			if(ptr->key > key)
				ptr = ptr->left;
			//ptr의 키 값이 입력한 수보다 클 때
			else
				ptr = ptr->right;
		}
	}

	//널 일때
	if(ptr == NULL)
	{
		//없음 프린트
		printf("No node for key [%d]\n ", key);
		return -1;
	}


	//삭제 해당 노드가 리프노드일때
	
	//왼쪽주소와 오른쪽 주소의 값이 널일 때,
	if(ptr->left == NULL && ptr->right == NULL)
	{
		//부모노드가 널일 때
		if(parent != NULL) {
			//부모의 왼쪽주소가 ptr일때
			if(parent->left == ptr)
				//왼쪽 널값으로
				parent->left = NULL;
			else
				//오른쪽 널값으로
				parent->right = NULL;
		} else { 
			//부모노드가 널이 아닐 때, 헤드의 왼쪽 널로
			head->left = NULL;

		}
		//ptr을 프리
		free(ptr);
		return 1;
	}

	
	//하나의 자식노드가 존재할 경우
	//ptr왼쪽 주소가 널이거나 ptr 오른쪽 주소가 널일경우
	if ((ptr->left == NULL || ptr->right == NULL))
	{
		//자식노드에서 
		Node* child;
		//만약 ptr의 왼쪽이 널일 경우
		if (ptr->left != NULL)
			//왼쪽주소를 값으로
			child = ptr->left;
		//만약 ptr의 왼쪽이 널이 아닐 경우
		else
			//오른쪽주소를 값으로 
			child = ptr->right;
		
		//부모노드가 널일경우 
		if(parent != NULL)
		{
			//parent의 왼쪽주소가 ptr과 같을 경우 
			if(parent->left == ptr)
				//자식노드를 부모노드 왼쪽 주소 값으로 
				parent->left = child;
			else
				//자식노드를 부모노드 오른쪽 주소 값으로 
				parent->right = child;
		} else {
			
			//부모노드가 널일 경우, 루트 값으로 그때의 자식노드가 되어야 한다.
			root = child;
		}
		//프리 
		free(ptr);
		return 1;
	}

	
	//노드에 두개의 자식이 있을 경우, 자식노드 중 작은 노드를 오른쪽 하위노드에서 찾는다.
	
	Node* candidate;
	parent = ptr;


	candidate = ptr->right;

	
	//왼쪽의 주소가 비어있지 않을 때까지 
	while(candidate->left != NULL)
	{
		//부모값 변화
		parent = candidate;
		//candidate값 변화
		candidate = candidate->left;
	}

	
	//부모노드 오른쪽이 candidate일 때
	if (parent->right == candidate)
		//candidate->right로 값 변경
		parent->right = candidate->right;
	else
		///부모노드 오른쪽이 candidate아닐 때,부모의 왼쪽을 candidate->right로 값 변경
		parent->left = candidate->right;

	
	//키값을 candidate->key으로
	ptr->key = candidate->key;

	free(candidate);
	return 1;
}


void freeNode(Node* ptr)
{
	if(ptr) { 
		//재귀 이용해 노드 초기화
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{
	//헤드의 왼쪽이 헤드값과 같다면
	if(head->left == head)
	{
		//헤드 프리
		free(head);
		return 1;
	}
	
	//노드 p의 값을 head의 왼쪽으로 
	Node* p = head->left;
	
	//프리노드
	freeNode(p);
	
	free(head);
	return 1;
}



Node* pop()
{
	//탑이 음수면 리턴
	if (top < 0) return NULL;
	//스택 줄이기
	return stack[top--];
}

void push(Node* aNode)
{
	//스택 늘리기 그리고 그 값을 받아온 값으로
	stack[++top] = aNode;
}


void printStack()
{
	int i = 0;
	printf("--- stack ---\n");
	//스택안에 있는것들 프린트
	while(i <= top)
	{
		printf("stack[%d] = %d\n", i, stack[i]->key);
	}
}


Node* deQueue()
{
	//비어있을경우
	if (front == rear) {
		printf("\n....Now Queue is empty!!\n" );
		return NULL;
	}
	//front 값 변경
	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[front];

}

void enQueue(Node* aNode)
{
	//rear값 변경
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	//비어있을 경우
	if (front == rear) {
		printf("\n....Now Queue is full!!\n");
		return;
	}
	queue[rear] = aNode;
}




