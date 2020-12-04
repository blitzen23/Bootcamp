#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../controllers/controllers.h"
void MenuAddDish(){
    // menu untuk add dish
    while (1){
        int flag = 1;
        printf("Insert the name of the dish [Lowercase letters]: "); 
        scanf("%[^\n]", name);
        getchar();
        int len = strlen(name);
        // validasi lowercase dan tidak boleh ada karakter lain selain lowercase dan spasi
        for (int i = 0; i < len; i++){
            if (!(name[i] >= 'a' && name[i] <= 'z') && name[i] != ' '){
                flag = 0;
                break;
            }
        }
        if(flag && checkDish(name)){
            break;
        }
    }
    while (1){
        printf("Insert the price of dish [1000..50000]: ");
        scanf("%d", &price);
        getchar();
        // validasi harga agar berada di antara 1000 dan 50000
        if (price >= 1000 && price <= 50000){
            break;
        }
    }
    while (1){
        printf("Insert the quantity of dish [1..999]: ");
        scanf("%d", &quantity);
        getchar();
        // validasi quantity agar berada di antara 1 dan 999
        if (quantity >= 1 && quantity <= 999){
            break;
        }
    }
    // memasukkan dish yang telah di input ke dalam linked list
    pushDish(name, price, quantity);
    printf("The dish has been added\n");
    printf("Press enter to continue\n");
    getchar();
}
void MenuRemoveDish(){
    // menu untuk remove dish
    // ketika tidak ada dish maka akan mengeluarkan no dish found
    if (headDish == NULL){
        printf("No dish found\n");
    }
    else {
        // jika ada dish maka akan di print
        printf("\tBude's Menu\n");
        printf("===========================================\n");
        printf("No .        Name        Quantity       Price\n");
        printDish();
        printf("===========================================\n");
        while (1){
            int flag = 1;
            printf("Insert dish's name to be deleted: ");
            scanf("%[^\n]", name);
            getchar();
            int len = strlen(name);
            // untuk validasi bahwa nama dish hanya bisa lowercase dan karakternya hanya bisa spasi
            for (int i = 0; i < len; i++){
                if (!(name[i] >= 'a' && name[i] <= 'z') && name[i] != ' '){
                    flag = 0;
                    break;
                }
            }
            // validasi apakah nama dishnya ada, jika tidak maka akan diminta terus, jika ada maka akan break
            if(flag && !checkDish(name)){
                break;
            }
        }
        // menghapus nama dish yang telah diinput
        popDish(name);
        printf("The dish has been removed!\n");
    }
    printf("Press enter to continue\n");
    getchar();
}
void MenuAddCustomer(){
    // menu untuk add customer
    while (1){
        int flag = 1;
        printf("Insert the customer's name [Without space]: ");
        scanf("%[^\n]", name);
        getchar();
        int len = strlen(name);
        // validasi nama agar hanya bisa A-Z atau a-z, selain dari itu maka akan diminta inputan terus
        for (int i = 0; i < len; i++){
            if (!(name[i] >= 'a' && name[i] <= 'z') && !(name[i] >= 'A' && name[i] <= 'Z')){
                flag = 0;
                break;
            }
        }
        // jika sudah sesuai dgn validasi maka akan break
        if (flag){
            break;
        }
    }
    // memasukkan nama customer sesuai dengan yang di input
    pushCustomer(name);
    printf("Customer has been added!\n");
    printf("Press enter to continue\n");
    getchar();
}
void MenuViewWarteg(){
    // menu untuk melihat warteg
    int flag = 0;
    // untuk mengecek apakah ada customer, jika ada maka akan printCustomer() sedangkan jika tidak ada akan print No costumer
    for (int i = 0; i < 26; i++){
        if (headCustomer[i] != NULL){
            flag = 1;
            break;
        }
    }
    if (flag){
        printf("Customer's List\n");
        printCustomer();
    }
    else {
        printf("No costumer\n");
    }
    printf("Press enter to continue\n");
    getchar();
}
void MenuSearchCustomer(){
    // menu untuk mencari customer
    int flag = 0;
    // untuk mengecek apakah ada customer
    for (int i = 0; i < 26; i++){
        if (headCustomer[i] != NULL){
            flag = 1;
            break;
        }
    }
    // jika ada customer akan meminta nama customer yang ingin dicari
    if (flag){
        while (1){
            int flag = 1;
            printf("Insert the customer's name to be searched: ");
            scanf("%[^\n]", name);
            getchar();
            int len = strlen(name);
            // untuk validasi nama customer hanya bisa a-z dan A-Z
            for (int i = 0; i < len; i++){
                if (!(name[i] >= 'a' && name[i] <= 'z') && !(name[i] >= 'A' && name[i] <= 'Z')){
                    flag = 0;
                    break;
                }
            }
            // jika validasi nama sesuai maka akan break
            if (flag){
                break;
            }
        }
        // jika nama ditemukan
        if (searchCustomer(name)){
            printf("%s is present\n", name);
        }
        // jika nama tidak ditemukan
        else {
            printf("%s is not present\n", name);
        }
    }
    // jika tidak ada customer
    else {
        printf("No costumer\n");
    }
    printf("Press enter to continue\n");
    getchar();
}
void MenuOrder(){
    // menu untuk order
    int flag = 0;
    // cek apakah ada customer
    for (int i = 0; i < 26; i++){
        if (headCustomer[i] != NULL){
            flag = 1;
            break;
        }
    }
    // jika ada customer
    if (flag){
        // jika ada dish
        if (headDish != NULL){
            while (1){
                // validasi customer name sampai ada
                printf("Insert the customer's name: ");
                scanf("%[^\n]", name);
                getchar();
                if (searchCustomer(name)){
                    break;
                }
            }
            printf("Insert the amount of dish: ");
            scanf("%d", &amount);
            getchar();
            for (int i = 1; i <= amount; i++){
                orderQty = 0;
                printf("[%d]Insert the dish's name and quantity: ", i);
                // validasi order
                scanf("%[^\n]", order);
                getchar();
                int j = 0;
                for (j = 0; order[j+1] != 'x'; j++){
                    orderName[j] = order[j];
                }
                orderName[j] = '\0';
                j += 2;
                for (j = j; order[j] != '\0'; j++){
                    orderQty = (orderQty*10) + (order[j]-'0');
                }
                int result = checkDish(orderName);
                // jika dish name tidak ada maka akan diminta terus hingga ada
                if (result == 1){
                    i--;
                }
                if (result == 0){
                    // jika nama dish ada tapi quantitynya < 1 ataupun melebihi quantity dari dish yang tersedia
                    if (orderQty < 1 || orderQty > currDish->quantity){
                        i--;
                    }
                    // jika semua kondisi terpenuhi
                    else {
                        pushOrder(currCustomer, orderName, orderQty, currDish->price);
                        currDish->quantity -= orderQty;
                        // jika quantity dish 0 maka akan dihapus dari menu dish
                        if (currDish->quantity == 0){
                            popDish(currDish->name);
                        }
                    }
                }
            }
            printf("Order success!\n");
        }
        // jika tidak ada dish
        else {
            printf("No dish\n");
        }
    }
    // jika tidak ada cusomter
    else {
        printf("No costumer\n");
    }
    printf("Press enter to continue\n");
    getchar();

}
void MenuPayment(){
    // menu untuk payment
    int flag = 0;
    // untuk mengecek apakah ada customer
    for (int i = 0; i < 26; i++){
        if (headCustomer[i] != NULL){
            flag = 1;
            break;
        }
    }
    // jika ada customer
    if (flag){
        int index;
        while (1){
            int flag = 0;
            printf("Insert the customer's index: ");
            scanf("%d", &index);
            // jika indexnya ada isi baru masuk ke dalam if
            if (headCustomer[index-1] != NULL){
                // jika customer di index itu tidak melakukan order maka akan print No order
                if (headCustomer[index-1]->headOrder == NULL){
                    printf("No order\n");
                }
                // jika customer di index itu telah melakukan order maka akan print biaya dan dish yang diorder
                else {
                    printf("%s\n", headCustomer[index-1]->name);
                    int count = 1;
                    int sum = 0;
                    currOrder = headCustomer[index-1]->headOrder;
                    while (currOrder != NULL){
                        printf("[%d] %s x%d\n", count, currOrder->name, currOrder->quantity);
                        sum += (currOrder->quantity*currOrder->price);
                        currOrder = currOrder->next;
                    }
                    printf("Total: Rp%d\n", sum);
                    printf("Press enter to continue\n");
                    getchar();
                    popCustomer(index-1);
                    break;
                }
            }
        }
    }
    // jika tidak ada customer
    else {
        printf("No costumer\n");
    }
    getchar();
}
void splashScreen(){
    // menu exit
    char *splash = 
    R"(
                                                                                                        
                                                      ..`                                           
                  .//.                               /+++-   `    :/:                               
                  /MM:                               -/+/` .hm/   dMd                               
         :osso/`  /MM:   `+ss+:ss-  `/osso:   /so:sy: ss/ +yMMhs: dMd/sso:   +s+/sso-.+sso:         
        hMdo+dMm. /MM:  .NMNyyNMM/ .NMmsyNMh  yMMmss- MMy :oMMy/- dMMdshMMo  mMMdsdMMMdshMMs        
        .-:--+MM/ /MM:  +MM-  /MM/ sMM`  +MM- yMM`    MMy  -MM+   dMm   dMm  mMm   mMm   hMN        
       `hMmhyhMM/ /MM:  +MM-  /MM/ sMM   /MM: yMM     MMy  -MM+   dMd   dMm  mMd   dMm   yMM        
       :MM+  +MM/ :MMo. .NMmsyNMM/ +MM+..yMM. yMM     MMy  -MMs`  dMd   dMm  mMd   dMm   yMM        
        sNMMNdMM/  smMM- `+syo+MM/  omMMMNh:  yMM     MMs   omMM: dMd   hMm  dMd   dMm   yMN        
         ``.` ``     `` .dds::hMm`  `..-..`````..`````...````....`...```...``...............        
                         -shhhyo`  `..............------------------------------------------        
                                   .+-/`   /::/    :::/`  .-o-`  `/::    -/    -o  :+   -/::        
                                   .s:s`  -+  /:  .o  :/    s    s`     `y+/   :++./s   //-+        
                                   .o-+.  `+--+`   +--/.    o    -/--   +.`+`  :-/+ o   :-`         
                                    ```     ``      ``      `     ```   `         ` `                
                                                                                                        
    
    )";
    printf("%s\n", splash);
}
int main(){
    int choose;
    while (1){
        clearScreen();
        time_t t;
        time(&t);
        printf("System: %s\n", detectOS());
        printf("%s\n", ctime(&t));
        puts("1. Add Dish");
        puts("2. Remove Dish");
        puts("3. Add Customer");
        puts("4. Search Customer");
        puts("5. View Warteg");
        puts("6. Order");
        puts("7. Payment");
        puts("8. Exit Warteg");
        while (1){
            printf(">> ");
            scanf("%d", &choose);
            getchar();
            if (choose >= 1 && choose <= 8){
                break;
            }
        }
        if (choose == 1){
            clearScreen();
            MenuAddDish();
        }
        else if (choose == 2){
            clearScreen();
            MenuRemoveDish();
        }
        else if (choose == 3){
            clearScreen();
            MenuAddCustomer();
        }
        else if (choose == 4){
            clearScreen();
            MenuSearchCustomer();
        }
        else if (choose == 5){
            clearScreen();
            MenuViewWarteg();
        }
        else if (choose == 6){
            clearScreen();
            MenuOrder();
        }
        else if (choose == 7){
            clearScreen();
            MenuPayment();
        }
        else {
            clearScreen();
            splashScreen();
            break;
        }
    }
    return 0;
}