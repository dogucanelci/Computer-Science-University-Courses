#include "data_structs.h"


//Queue Functions
void Queue::init(){
head = NULL; tail = NULL;
}

bool Queue::isEmpty() {
return head == NULL;
}

void Queue::close(){
Process *p;
while (head) {
p = head;
head = head->next;
delete p;
}
}

void Queue::queue(Process *newdata){
Process *newnode = new Process;
//newnode->data = newdata;
newnode->task_stack = newdata->task_stack;
newnode->task_count = newdata->task_count;
newnode->arrival_time=newdata->arrival_time;
newnode->deadline = newdata->deadline;
newnode->name = newdata->name;
newnode->priority = newdata->priority;
newnode->next = NULL;
if ( isEmpty() ) { // first element
tail = newnode;
head = tail;
}
else {
tail->next = newnode;
tail = newnode;
}
}


Process* Queue::dequeue() {
Process *topnode;
Process *temp=new Process;
topnode = head;
head = head->next;
temp->task_stack = topnode->task_stack;
temp->task_count = topnode->task_count;
temp->arrival_time= topnode->arrival_time;
temp->deadline = topnode->deadline;
temp->name = topnode->name;
temp->priority = topnode->priority;
delete topnode;
return temp;
}

Process* Queue::front(){
    return (head);
}


// finish line of Queue functions

//MultiQueue Functions
void MultiQueue::init(int i){
   
    queues[i].head = NULL;
    queues[i].tail = NULL;    
    
}

bool MultiQueue::isEmpty(int i) {
return queues[i].head == NULL;
}


void MultiQueue::close(int i){

Process *p;
while (queues[i].head) {
p = queues[i].head;
queues[i].head = queues[i].head->next;
delete p;
}
}

void MultiQueue::queue(Process *newdata,int i){
Process *newnode = new Process;
//newnode->data = newdata;
newnode->task_stack = newdata->task_stack;
newnode->task_count = newdata->task_count;
newnode->arrival_time=newdata->arrival_time;
newnode->deadline = newdata->deadline;
newnode->name = newdata->name;
newnode->priority = newdata->priority;
newnode->next = NULL;
if ( queues[i].isEmpty() ) { // first element
queues[i].tail = newnode;
queues[i].head = queues[i].tail;
}
else {
queues[i].tail->next = newnode;
queues[i].tail = newnode;
}
}


Process* MultiQueue::dequeue(int i) {
Process *topnode;
Process *temp=new Process;
topnode = queues[i].head;
queues[i].head = queues[i].head->next;
temp->task_stack = topnode->task_stack;
temp->task_count = topnode->task_count;
temp->arrival_time= topnode->arrival_time;
temp->deadline = topnode->deadline;
temp->name = topnode->name;
temp->priority = topnode->priority;
delete topnode;
return temp;
}

Process* MultiQueue::front(int i){
    return (queues->head);
}


// finish line of MultiQueue functions



//Stack Functions
void Stack::init()
{
    head = NULL;
}

void Stack::close()
{
    Subtask *p;
    while (head->duration)
    {
        p = head;
        head = head->next;
        delete p;
    }

}

void Stack::push(Subtask *newdata)
{
    Subtask *newnode = new Subtask;
    newnode->duration = newdata->duration;
    newnode->name = newdata->name;
    newnode->next = head;
    head = newnode;
}

Subtask* Stack::pop()
{
    Subtask *topnode;
    Subtask *temp=new Subtask;
    topnode = head;
    head = head->next;
    temp->duration=topnode->duration;
    temp->name=topnode->name;
    delete topnode;
    return temp;
}

bool Stack::isEmpty()
{
    return head == NULL;
}
//finish line of Stack Functions