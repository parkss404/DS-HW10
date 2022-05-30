#include <stdio.h>
#include <stdlib.h>

 

#define MAX_VERTEX 10

#define MAX_QUEUE MAX_VERTEX+1

int check[MAX_VERTEX];

 

//구조체 정의 

typedef struct LIST {

   int vx;

   struct LIST* link;

}List;

 

typedef struct GRAPH {

   int n;

   List* adj_list[MAX_VERTEX];

}Graph;



 

//사용 함수 정리

Graph* Init_Graph(void);

void Add_Vertex(Graph* g);

void Add_Edge(Graph* g, int u, int v);

void DFS(Graph *g, int n);

void Depth_First_Search(Graph* g, int n);

void BFS(Graph *g, int n);

void Breath_First_Search(Graph* g, int n);

void Add_Queue(int n);

void Print_Graph(Graph* g);

int Delete_Queue(void);


/*---------------------------*/

 

//큐 설정

int front   = 0;

int rear    = 0;

int queue[MAX_QUEUE];

/*---------------------------*/

 

 

int main(void) {
  //변수 설정
  char command;
  int num,n,m;
  Graph* g;
  do{
		printf("\n\n");
		printf("[----- [박성준] [2021040026] -----]\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Graph Searches                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph       = z                                       \n");
		printf(" Insert vertex         = v      Insert Edge           = e \n");
		printf(" Depth First Search    = d      Breath First Search   = b \n");
		printf(" Print Graph           = p      Quit                  = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

    //스위치 문으로 각 키값과 내용설정
		switch(command) {
    
		case 'z': case 'Z':
      g = Init_Graph();
			break;
      
		case 'v': case 'V':
			printf("insert vertex num = ");
			scanf("%d", &num);
      
      if(num > 10){
        printf("smaller than 11");
        break;
      }
      
			for(int i = 0; i < num; i++){
        Add_Vertex(g);
    }
			break;
    
		case 'e': case 'E':
			printf("insert edge = ");
      scanf("%d %d",&n,&m);
      Add_Edge(g,n,m);
      
			break;
      
    case 'q': case 'Q':
			break;
      
		case 'd': case 'D':
			DFS(g, 0);
			break;
    
		case 'b': case 'B':
			BFS(g, 0);
			break;


		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

 
//그래프 초기 설정
Graph* Init_Graph(void){
    //메모리 할당
    Graph* g = (Graph*)malloc(sizeof(Graph));

    g->n = 0;

    //최대 크기만큼 adj_list 만듦 비어있는 상태로
    for(int i = 0; i < MAX_VERTEX; i++)

        g->adj_list[i] = NULL;

    
    
    return g;

}

 
//정점 추가
void Add_Vertex(Graph* g){
    //메모리 할당
    g->adj_list[g->n] = (List*)malloc(sizeof(List));
    //vx는 -1fh
    g->adj_list[g->n]->vx = -1;
    //해당 주소값은 비어있는 상태로
    g->adj_list[g->n]->link = NULL;

    
    //수 증가
    g->n++;

}

 
//간선 연결
void Add_Edge(Graph* g, int u, int v){
  
    //오류 처리
    if(u >= g->n || v >= g->n){

        printf("Out of Graph.\n\n");

    }
  
    else{
        //메모리 할당
        List* tmp_u = (List*)malloc(sizeof(List));

        List* tmp_v = (List*)malloc(sizeof(List));

        
        //값을 짐어넣기
        tmp_u->vx = u;

        tmp_v->vx = v;

        
        //두 부분을 서로 이어준다.
        tmp_v->link = g->adj_list[u]->link;

        g->adj_list[u]->link = tmp_v;

        
        //두 부분을 서로 이어준다.
        tmp_u->link = g->adj_list[v]->link;
        
        g->adj_list[v]->link = tmp_u;

 

    }

}

 
//깊이우선탐색 
void DFS(Graph *g, int n){
    //마킹으로 사용 할 check 
    for(int i = 0; i < MAX_VERTEX; i++){

        check[i] = 0;

    }

    
    
    Depth_First_Search(g, n);

    

    printf("\n");

}

 
//DFS와 분리 
void Depth_First_Search(Graph* g, int n){
    //0일 경우 
    if(check[n] == 0){
        
        List* cur;
        List* tmp;

        
        // cur값 업데이트
        cur =  g->adj_list[n]->link;

        
        //n 출력
        printf("%2d  ", n);

        
        //마킹 변경
        check[n] = 1;

        
        //cur이 비어있을 경우
        while(cur != NULL){
            //tmp를 cur->link로
            tmp = cur->link;

            
            //check의 cur->vx 인덱스가 0일 때
            if(check[cur->vx] == 0)
                //재귀함수 이용해서 다시 진행 
                Depth_First_Search(g, cur->vx);

            
            //cur을 tmp로
            cur = tmp;

        }

    }

}

 
//너비우선탐색
void BFS(Graph *g, int n){
    //마찬가지로 마킹 리스트
    for(int i = 0; i < MAX_VERTEX; i++){

        check[i] = 0;

    }

    
    //큐를 이용함으로 front rear
    front   = 0;
    rear    = 0;

    
    Breath_First_Search(g, n);

    

    printf("\n");

}

 

void Breath_First_Search(Graph* g, int n){

    List* cur;
    List* tmp;

    
    
    int queue_out;

    
    //cur값 업데이트
    cur = g->adj_list[n]->link;

    
    //마킹값이 0일 때
    if(check[n] == 0){
        //프린트 n
        printf("%2d  ", n);
        //마킹표시 변경
        check[n] = 1;

    }

    
    //cur이 비어있지 않을 때까지
    while(cur != NULL){
        //tmp는 cur->link로 계속 변경
        tmp = cur->link;

        
        //cur->vx의 마킹값이 0이면
        if(check[cur->vx] == 0){
            //프린트하고
            printf("%2d  ", cur->vx);
            //1로 변경
            check[cur->vx] = 1;
            //큐에 추가
            Add_Queue(cur->vx);

        }

        
        
        cur = tmp;

    }

    
    //큐아웃 업데이트
    queue_out = Delete_Queue();

    
    //queue_out이 -1이 아닐때까지
    while(queue_out != -1){
        //재귀 반복
        Breath_First_Search(g, queue_out);
        //큐아웃 업데이트
        queue_out = Delete_Queue();

    }

}

 
//큐 추가
void Add_Queue(int n){
    //큐가 가득 찬 경우
    if((rear+1)%MAX_QUEUE == front){

        puts("Queue is full.");

    }
    
    else{
        //rear값 변경
        rear = (rear+1)%MAX_QUEUE;

        queue[rear] = n; // 1번부터 찬다.

    }

}

 
//큐 삭제
int Delete_Queue(void){
    //tmp를 -1로
    int tmp = -1;

    
    //비어있을 경우
    if(front == rear){

//        puts("Queue is empty.");

    }

    else{
        
        front = (front+1)%MAX_QUEUE;
        // tmp값 변경
        tmp = queue[front];

    }

    return tmp;

}
