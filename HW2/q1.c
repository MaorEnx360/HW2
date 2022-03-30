#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct Worker {
	unsigned long int id;
	char* name;
	unsigned long int salary;
	union year {
		char heb[6];
		unsigned long int grg;
	}year;
	}Worker;
typedef struct WorkerList
{
	Worker * data;
	struct WorkerList* next;
} WorkerList;

//Private Methods
bool isEmpty(WorkerList* head);
//

//Public Methods
Worker* CreateWorker();
void PrintWorker(Worker* worker);
WorkerList * addWorker(WorkerList *head, Worker * w);
void update_worker(WorkerList *head, float percent);
int index(WorkerList *head, long unsigned id);
int indexR(WorkerList * head, long unsigned id);
WorkerList* deleteWorstWorker(WorkerList *head);
WorkerList* reverse(WorkerList *head);
void freeWorkers(WorkerList *head);




void main() {
	WorkerList* dummy = { NULL };
	Worker* w1 = CreateWorker();
	//Worker* w2 = CreateWorker();
	//Worker* w3 = CreateWorker();
	Worker w4 = {189654,"Maor",24000};
	w4.year.grg = 2000;
	Worker w5 = { 296461,"Roea",32000};
	w5.year.grg = 2000;
	Worker w6 = { 616651,"Worker6",15000};
	w6.year.grg = 2000;

	//PrintWorker(w2);
	//dummy = addWorker(dummy,w2);
	dummy = addWorker(dummy, &w5);
	dummy = addWorker(dummy, &w6);
	dummy = addWorker(dummy, &w4);
	dummy = addWorker(dummy, w1);
	//dummy = addWorker(dummy, w3);
	dummy = reverse(dummy);
	int id = 189654;
	int srch = indexR(dummy,id);
	srch = index(dummy, id);
	update_worker(dummy, 0.5);
	
	freeWorkers(dummy);

}

Worker* CreateWorker()
{
	Worker* tmp = (Worker*)malloc(sizeof(Worker)*1);
	tmp->name = (char*)calloc(1,sizeof(char));
	int yeartype = 2;
	puts("Please Enter id");
	scanf("%u", &tmp->id);
	printf("Enter a name : ");
	scanf("%s",tmp->name);
	puts("Please salary");
	scanf("%u", &tmp->salary);
	while (yeartype < 0 || yeartype>1) {
	puts("Enter 0 for Hebrew year or 1 for gregorian year");
		scanf("%d", &yeartype);
	}
	if (yeartype == 1) {
		puts("please enter a gregorian year");
		scanf("%u", &(tmp->year.grg));
}
	else {
		puts("please enter a hebrew year");
		scanf("%s", tmp->year.heb);
	}
	return tmp;

}

void PrintWorker(Worker* worker)
{
	printf("Id : %d \n", worker->id);
	printf("Name : %s \n", worker->name);
	printf("Salary : %u \n", worker->salary);
	printf("Year : %u \n", worker->year.grg);
}

void update_worker(WorkerList * head, float percent)
{
	while (!isEmpty(head)) {
		head->data->salary = head->data->salary + percent*(head->data->salary);
		head = head->next;
	}
}


int index(WorkerList * head, long unsigned id)
{
	if(isEmpty(head)){ //if The list is empty //start condition
		return -1;
	}
		int cout = 1;
	while (head->next != NULL) {
		if (head->data->id == id) {
			return cout;
		}
		head = head->next;
		cout++;
	}
	return -1;
}
int indexR(WorkerList * head, long unsigned id) {
	static int cout = 1;
	if (isEmpty(head)) //if The list is empty //stop condition
		return -1;
	if (head->data->id == id)
		return cout;
		cout++;
	return indexR(head->next, id);
}
WorkerList * deleteWorstWorker(WorkerList * head)
{
	WorkerList* cur = head;
	WorkerList* prv = (WorkerList*)calloc(1, sizeof(WorkerList));

	if (isEmpty(head)) {  //if The list is empty 
		return head;
	}
	else {
		while (!isEmpty(cur->next)) { //Go through all the nodes in the list

			prv = cur;
			cur = cur->next;
		}
		
		prv->next = NULL;
		cur->data = NULL; //for security 
		free(&cur->data); 
		cur = NULL;
		return head;
	}
}
WorkerList *reverse(WorkerList *head)
	{
	 WorkerList* temp = head;
	 WorkerList* prv = NULL;
	 WorkerList* cur = head;
	 WorkerList* nxt = head;

	while (!isEmpty(cur))
	{
		nxt = cur->next;
		cur->next = prv;
		prv = cur;
		cur = nxt;
	}
	head = prv;
	return head;
}
void freeWorkers(WorkerList * head)
{
	WorkerList* tmp = head;
	while (!isEmpty(tmp->next)) {
		tmp->data = NULL; //for security 
		free(tmp->data);
		tmp = tmp->next;
	}
	free(head); //free the list
	free(tmp);

}
bool isEmpty(WorkerList* head) {
	if (head == NULL) {
		return true;
	}
	else {
		return false;
	}
}
WorkerList * addWorker(WorkerList * head, Worker * w)
{
	WorkerList* new = (WorkerList*)calloc(1, sizeof(WorkerList));
	WorkerList* tmp = (WorkerList*)calloc(1, sizeof(WorkerList));
	WorkerList* cur = head;
	new->data = w;
	if (isEmpty(head)) {
		head = new;
	}
	else {
		if (isEmpty(head->next)) {
			if (new->data->salary > cur->data->salary) {
				tmp = head;
				head = new;
				head->next = tmp;
			}
			else {
				head->next = new;
			}
		}
		else if (w->salary > head->data->salary) {
			  {
				tmp = head;
				head = new;
				head->next = tmp;
			}
		}
		else {
			while (!isEmpty(cur->next)) {
				if (w->salary < cur->data->salary && w->salary > cur->next->data->salary) {
					tmp = cur->next;
					new->next = tmp;
					cur->next = new;
					break;
				}
				cur = cur->next;
			}
			if (isEmpty(cur->next)) {
				cur->next = new;
			}
		}
	}
	return head;
}

