int totalPatient, totalCure;
char name[255], month[255];
int day, year;
struct patient{
    int day;
    char month[255];
    int year;
    char name[255];
    patient *next, *prev;
}*curr;