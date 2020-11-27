#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../Controllers/controllers.h"
int main (){
    scanf("%d %d", &totalPatient, &totalCure);
    for (int i = 0; i < totalPatient; i++){
        scanf("%d %s %d - %[^\n]", &day, month, &year, name);
        pushMid(name, day, month, year);
    }
    for (int i = 0; i < totalCure; i++){
        popHead();
    }
    if (totalPatient <= totalCure){
        printf("All patients get the cure, %d cure left\n", totalCure-totalPatient);
    }
    else {
        printf("Need %d more cure\n", totalPatient-totalCure);
        printAll();
        for (int i = 0; i < totalPatient-totalCure; i++){
            popHead();
        }
    }
    return 0;
}