#include "../models/models.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <thread>
#include <chrono>
void delay() {
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
}
void clearScreen(){
    for (int i = 0; i < 50; i++){
        puts("");
    }
}
const int MAX_ELEMENT = 26;
unsigned long DJB2(char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash % MAX_ELEMENT;
}
const char* detectOS() {
    #ifdef _WIN32
    return "Windows 32-bit";
    #elif _WIN64
    return "Windows 64-bit";
    #elif __APPLE__ || __MACH__
    return "Mac OSX";
    #elif __linux__
    return "Linux";
    #elif __FreeBSD__
    return "FreeBSD";
    #elif __unix || __unix__
    return "Unix";
    #else
    return "Other";
    #endif
}
void printSpace(char *a){
    int len = strlen(a);
    len = 20 - len;
    int len1 = len;
    if (len % 2 == 1){
        len1 += 1;
    }
    for (int i = 0; i < len/2; i++){
        printf(" ");
    }
    printf("%s", a);
    for (int i = 0; i < len1/2; i++){
        printf(" ");
    }
}
Order *createOrder (char *name, int price, int quantity){
    newOrder = (Order*)malloc(sizeof(Order));
    strcpy(newOrder->name, name);
    newOrder->next = NULL;
    newOrder->prev = NULL;
    newOrder->price = price;
    newOrder->quantity = quantity;
    return newOrder;
}
Customer *createCustomer (char *name){
    newCustomer = (Customer*)malloc(sizeof(Customer));
    strcpy(newCustomer->name, name);
    newCustomer->next = NULL;
    newCustomer->prev = NULL;
    newCustomer->headOrder = NULL;
    newCustomer->tailOrder = NULL;
    return newCustomer;
}
Dish *createDish(char *name, int price, int quantity){
    newDish = (Dish*)malloc(sizeof(Dish));
    strcpy(newDish->name, name);
    newDish->price = price;
    newDish->quantity = quantity;
    newDish->next = NULL;
    newDish->prev = NULL;
    return newDish;
}
void pushDish(char *name, int price, int quantity){
    if (headDish == NULL){
        currDish = createDish(name, price, quantity);
        headDish = tailDish = currDish;
    }
    else if (strcmp(name, headDish->name) < 0){
        currDish = createDish(name, price, quantity);
        currDish->next = headDish;
        headDish->prev = currDish;
        headDish = currDish;
    }
    else if (strcmp(name, headDish->name) >= 0){
        currDish = createDish(name, price, quantity);
        currDish->prev = tailDish;
        tailDish->next = currDish;
        tailDish = currDish;
    }
    else {
        tempDish = createDish(name, price, quantity);
        currDish = headDish;
        while (strcmp(currDish->next->name, name) <= 0){
            currDish = currDish->next;
        }
        currDish->next->prev = tempDish;
        tempDish->next = currDish->next;
        tempDish->prev = currDish;
        currDish->next = tempDish;
    }
}
void popDish(char *name){
    currDish = headDish;
    if (currDish == NULL){
        return;
    }
    else if (headDish == tailDish){
        free(headDish);
        headDish = tailDish = NULL;
    }
    else if (strcmp(headDish->name, name) == 0){
        tempDish = headDish->next;
        headDish->next = NULL;
        headDish = tempDish;
        free(currDish);
        headDish->prev = NULL;
    }
    else if (strcmp(tailDish->name, name) == 0){
        tempDish = tailDish->prev;
        tailDish->prev = NULL;
        tailDish = tempDish;
        free(currDish);
        tailDish->next = NULL;
    }
    else {
        while (currDish != tailDish && strcmp(currDish->next->name, name) != 0){
            currDish = currDish->next;
        }
        if (currDish == tailDish){
            return;
        }
        else {
            tempDish = currDish->next->next;
            currDish->next->next = NULL;
            currDish->next->prev = NULL;
            free(currDish->next);
            currDish->next = tempDish;
            tempDish->prev = currDish;
        }
    }
}
int checkDish(char *name){
    currDish = headDish;
    while (currDish != NULL){
        if (strcmp(currDish->name, name) == 0){
            return 0;
        }
        currDish = currDish->next;
    }
    return 1;
}
void printDish(){
    int count = 1;
    currDish = headDish;
    while (currDish != NULL){
        printf("%-3d.", count);
        printSpace(currDish->name);
        printf("   %03d        Rp%-5d\n", currDish->quantity, currDish->price);
        currDish = currDish->next;
        count++;
    }
}
void pushCustomer(char *name){
    int index = DJB2(name);
    if (headCustomer[index] == NULL){
        currCustomer = createCustomer(name);
        headCustomer[index] = tailCustomer[index] = currCustomer;
    }
    else {
        currCustomer = createCustomer(name);
        currCustomer->prev = tailCustomer[index];
        tailCustomer[index]->next = currCustomer;
        tailCustomer[index] = currCustomer;
    }
}
int searchCustomer(char *name){
    int index = DJB2(name);
    if (headCustomer[index] == NULL){
        return 0;
    }
    else {
        currCustomer = headCustomer[index];
        while (currCustomer != NULL){
            if (strcmp(currCustomer->name, name) == 0){
                return 1;
            }
            currCustomer = currCustomer->next;
        }
    }
    return 0;
}
void printCustomer(){
    for (int i = 0; i < 26; i++){
        currCustomer = headCustomer[i];
        if (currCustomer != NULL){
            printf("%d ", i+1);
            printf("%s ", currCustomer->name);
            currCustomer = currCustomer->next;
            while (currCustomer != NULL){
                printf("-> %s", currCustomer->name);
                currCustomer = currCustomer->next;
            }
            puts("");
        }
    }
}
void pushOrder(Customer *currCustomer, char *name, int quantity, int price){
    if (currCustomer->headOrder == NULL){
        currOrder = createOrder(name, price, quantity);
        currCustomer->headOrder = currCustomer->tailOrder = currOrder;
    }
    else {
        currOrder = createOrder(name, price, quantity);
        currCustomer->tailOrder->next = currOrder;
        currOrder->prev = currCustomer->tailOrder;
        currCustomer->tailOrder = currOrder;
    }
}
void popCustomer(int index){
    if (headCustomer[index] == NULL){
        return;
    }
    else if (headCustomer[index] == tailCustomer[index]){
        headCustomer[index] = tailCustomer[index] = NULL;
    }
    else {
        headCustomer[index] = headCustomer[index]->next;
        headCustomer[index]->prev->next = NULL;
        free(headCustomer[index]->prev);
        headCustomer[index]->prev = NULL;
    }
}