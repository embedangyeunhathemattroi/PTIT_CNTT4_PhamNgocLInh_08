#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>


#define MAX_URL 100
#define RECENT_LIMIT 5

typedef struct Operation{
char url[MAX_URL];
char timeStamp[30];
struct Operation * next;
}Operation;

typedef struct Stack{
Operation * top;
}Stack;

typedef struct HistoryNode {
    char url[MAX_URL];
    char timeStamp[30];
  struct HistoryNode*prev;
    struct HistoryNode*next;
}HistoryNode;

typedef struct HistoryList {
    HistoryNode *head;
    HistoryNode* tail;


}HistoryList;

typedef struct ReccentQueue{
    Operation reccent[RECENT_LIMIT];
    int front;
    int rear;
    int size;
}ReccentQueue;

//lay thoi gian hien tai duoi dang chuoi
char*getCurrentTime() {
    static char buffer[30];
    time_t t =time(NULL);
    struct tm*now =localtime(&t);
    strftime(buffer,sizeof(buffer),"%Y -%m -%d %H:%:%M:%S",now);
    return buffer;
}

//tao 1 ope moi
Operation *createOperation( const char *url) {
    Operation * op=(Operation*)malloc(sizeof(Operation));
    strcpy(op->url,url);
    strcpy(op->timeStamp,getCurrentTime());
    op-> next= NULL;
    return op;
}

HistoryNode* createHistoryNode(const char *url) {
   HistoryNode * node=(HistoryNode*)malloc(sizeof(HistoryNode));
    strcpy(node ->url,url);
    strcmp(node -> timeStamp, getCurrentTime());
    node -> next =node -> prev =NULL;
    return node;

}

void push(Stack * stack,Operation * op) {
    op -> next = stack -> top;
    stack -> top =op;
}

Operation * pop(Stack * stack) {
    if (!stack -> top)
    return NULL;
    Operation * temp =stack -> top;
    stack -> top = temp -> next;
    temp -> next =NULL;
    return temp;

}

void clearStack (Stack * stack ) {
    while (stack -> top) {
        Operation * temp =pop(stack);
        free(temp);
    }
}


void addRecent(ReccentQueue*q, const char *url) {
    q-> rear=(q-> rear +1) %RECENT_LIMIT;
  strcpy(q -> reccent[q->rear].url,url);
    strcpy(q -> reccent[q->rear].timeStamp,getCurrentTime());

    if (q->size <RECENT_LIMIT)
        q->size++;
    else
        q->front =(q -> front +1) %RECENT_LIMIT;

}

void printRecent(ReccentQueue*q) {
    printf("=====Recent PAge=====\n");
    int count =q-> size;
    int index=q->front;
    for (int i=0;i<count;i++) {
        printf("(%s) %s \n",q->reccent[index].url,q->reccent[index].timeStamp);
        index =(index +1)%RECENT_LIMIT;
    }
}

void addHistory(HistoryList *list, const char *url) {
    HistoryNode*node =createHistoryNode(url);
    if (list -> tail ==NULL) {
        list -> head =list ->tail =node;

    }else {
        list->tail -> next=node;
        node -> prev =list -> tail;
        list-> tail=node;
    }
}

void printHistory(HistoryList *list) {
    printf("====Web History====\n");
    HistoryNode*current=list->head;
    while (current!=NULL) {
        printf("%s (%s)\n",current -> url,current ->timeStamp);
        current =current-> next;

    }

}

void clearHistory(HistoryList*list) {
   HistoryNode * current =list-> head;
    while (current) {
        HistoryNode *temp=current;
        current =current -> next;
        free(temp);

    }

    list->head=list->tail=NULL;

}



int main(){
    Stack back={NULL};
    Stack forward={NULL};
    ReccentQueue reccent ={0};
    HistoryList history ={0};
    Operation *current =NULL;


int choice ;
    char url[MAX_URL];

do{
printf("================MENU==================\n");
printf("1: Visit URL:\n");
printf("2:BackWard:\n");
printf("3: ForWard:\n");
printf("4:Current:\n");
printf("5:History:\n");
printf("6:Clear History:\n");
printf("7:Exit:\n");
printf("moi ban nhap vao lua chon :");
scanf("%d",&choice);
    getchar();
switch (choice){
case 1:
        printf("ban hay nhap vao 1 ma url:\n");
        fgets(url,sizeof(url),stdin);
        url[strcspn(url,"\n")]=0;

        if (current !=NULL)  push(&back, current);
        clearStack(&forward);
        current =createOperation(url);
        addRecent(&reccent,url);
        addHistory(&history,url);
        printf("truy cap vao:%s \n",url);

break;
case 2:
        if (!back.top) {
            printf("khong the quay lui \n");

        }else {
            push(&forward,current);
            current =pop(&back);
            printf("back den :%s \n",current -> url);

        }

break;
case 3:
        if (!forward.top) {
            printf("khong the forward \n");

        }else {
            push(&back,current);
            current =pop(&forward);
            printf("forward den :%s \n",current -> url);

        }
break;
case 4:
        if (current)
            printf("trang hien tai:%s (%s) \n",current -> url,current->timeStamp);
        else
            printf("chua the truy cap vao trang nao \n");
break;
case 5:
        printHistory(&history);
break;
case 6:
        clearHistory(&history);
        clearStack(&back);
        clearStack(&forward);
        reccent.front =0;
        reccent.rear=-1;
        reccent.size=0;
        if (current) {
            free(current);
            current=NULL;

        }
        printf("da xoa toan bo lich su truy cap \n");

break;
case 7:
printf(" cam on ban da su dung chuong trinh nay \n");
break;

default:
printf("lua chon khong hop le \n");
break;
}
}while(choice !=7);
    clearHistory(&history);
    clearStack(&back);
    clearStack(&forward);
    if (current)  free(current);
return 0;
}