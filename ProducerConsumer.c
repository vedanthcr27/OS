#include<stdio.h>

int mutex=1,full=0,empty=3,x=0;

int wait(int *s)
{
    return(--(*s));
}

int signal(int *s)
{
    return(++(*s));
}

void producer(){
    wait(&mutex);
    signal(&full);
    wait(&empty);
    x++;
    printf("The item produced is %d\n",x);
    signal(&mutex);
}

void consumer(){
    wait(&mutex);
    wait(&full);
    signal(&empty);
    printf("Consumed item %d\n",x);
    x--;
    signal(&mutex);
}

int main()
{
    int choice;
    do{
    printf("Enter choice:\n");
    scanf("%d",&choice);
    switch(choice){
        case 1:
            if((mutex==1)&&(empty!=0))
            {
                producer();
            }
            else
            {
                printf("The print buffer is full\n");
            }
            break;
        case 2:
            if((mutex==1)&&(full!=0))
            {
                consumer();
            }
            else
            {
                printf("The print buffer is empty\n");
            }
            break;
        case 3:
            {
                printf("Exiting.\n");
            }
            break;
            }
    }while(choice!=3);
    return 0;
}
