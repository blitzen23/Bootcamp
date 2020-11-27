#include <stdio.h>
#include <stdlib.h>
#include "../Models/models.h"
#include <string.h>
patient *head = NULL;
patient *tail = NULL;
patient *createPatient(char *name, int day, char *month, int year){
    patient *newPatient = (patient*)malloc(sizeof(patient));
    strcpy(newPatient->name, name);
    strcpy(newPatient->month, month);
    newPatient->year = year;
    newPatient->day = day;
    newPatient->next = NULL;
    newPatient->prev = NULL;
    return newPatient;
}
int calculateMonth(char *month){
    if (strcasecmp(month, "January")){
        return 1;
    }
    else if (strcasecmp(month, "February")){
        return 2;
    }
    else if (strcasecmp(month, "March")){
        return 3;
    }
    else if (strcasecmp(month, "April")){
        return 4;
    }
    else if (strcasecmp(month, "May")){
        return 5;
    }
    else if (strcasecmp(month, "June")){
        return 6;
    }
    else if (strcasecmp(month, "July")){
        return 7;
    }
    else if (strcasecmp(month, "August")){
        return 8;
    }
    else if (strcasecmp(month, "September")){
        return 9;
    }
    else if (strcasecmp(month, "October")){
        return 10;
    }
    else if (strcasecmp(month, "November")){
        return 11;
    }
    else {
        return 12;
    }
}
void pushTail(char *name, int day, char *month, int year){
    curr = createPatient(name, day, month, year);
    if (head == NULL){
        head = tail = curr;
    }
    else {
        curr->prev = tail;
        tail->next = curr;
        tail = curr;
    }
}
void pushHead(char *name, int day, char *month, int year){
    curr = createPatient(name, day, month, year);
    if (head == NULL){
        head = tail = curr;
    }
    else {
        curr->next = head;
        head->prev = curr;
        head = curr;
    }
}
void pushMid(char *name, int day, char *month, int year){
    if (head == NULL){
        patient *temp = createPatient(name, day, month, year);
        head = tail = temp;
    }
    else if ((year < head->year) || (year == head->year && calculateMonth(month) < calculateMonth(head->month)) || (year == head->year && calculateMonth(month) == calculateMonth(head->month) && day < head->day)){
        pushHead(name, day, month, year);
    }
    else if ((year >= tail->year) || (year == tail->year && calculateMonth(month) >= calculateMonth(tail->month)) || (year == tail->year && calculateMonth(month) == calculateMonth(tail->month) && day >= tail->day)){
        pushTail(name, day, month, year);
    }
    else {
        patient *temp = createPatient(name, day, month, year);
        curr = head;
        while (curr ->next != NULL && (year >= curr->next->year) || (year == curr->next->year && calculateMonth(month) >= calculateMonth(curr->next->month)) || (year == curr->next->year && calculateMonth(month) == calculateMonth(curr->next->month) && day >= curr->next->day)){
            curr = curr->next;
        }
        curr->next->prev = temp;
        temp->next = curr->next;
        temp->prev = curr;
        curr->next = temp;
    }
}
void popHead(){
    curr = head;
    if (head == NULL){
        return;
    }
    else if (head == tail){
        free(head);
        head = tail = NULL;
    }
    else {
        head = curr->next;
        curr->next = NULL;
        free(curr);
        head->prev = NULL;
    }
}
void printAll(){
    curr = head;
    if (curr == NULL){
        return;
    }
    while (curr != NULL){
        printf("%d %s %d - %s\n", curr->day, curr->month, curr->year, curr->name);
        curr = curr->next;
    }
}