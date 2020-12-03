char name[255];
int price;
int quantity;
int amount;
char order[255];
char orderName[255];
int orderQty = 0;
char splash[255][1000];
struct Dish {
    char name[255];
    int price, quantity;
    Dish *prev, *next;
}*headDish, *tailDish, *currDish, *newDish, *delDish, *tempDish;

struct Order {
    char name[255];
    int quantity, price;
    Order *prev, *next;
}*newOrder, *currOrder, *delOrder;

struct Customer {
    char name[255];
    Order *headOrder, *tailOrder;
    Customer *prev, *next;    
}*headCustomer[26], *tailCustomer[26], *currCustomer, *newCustomer, *delCustomer, *tempCustomer;

