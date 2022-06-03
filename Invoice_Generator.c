
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <stdbool.h>
#include <unistd.h>
#define WAITINGTIME 1



struct items{
    char item[30];
    float price;
    int quantity;
};
struct orders{
    char client[40];
    char date[10];
    int numOfItems;
    struct items itm[50];
};

void loading(){
    printf("\nLoading...\n");
    printf("||||||");
    sleep(WAITINGTIME);
    printf("|||||||");
    sleep(WAITINGTIME);
    printf("||||||");
    sleep(WAITINGTIME);
    printf("||||||");


}
void createHeader(char client_name[40], char date[10]){
    printf("\n\n");
    printf("\t        C Restaurant");
    printf("\n\t      ----------------");
    printf("\n Client's name: %s", client_name);
    printf("\n Date: %s", date);
    printf("\n");
    printf("---------------------------------------------\n");
    printf("Items\t\t");
    printf("Quantity\t\t");
    printf("Total\t\t\n");
    printf("---------------------------------------------\n");
    printf("\n");

}

void createBody(char item[30], int quantity, float price){
    printf("%s\t\t   ", item);
    printf("%d\t\t       ", quantity);
    printf("%.2f\t\t", quantity * price);
    printf("\n\n");
}


void createFooter(float total){
    float tips = 0.05 * total;
    float tax = 0.1 * total;
    float total_total = total + tips + tax;
    printf("---------------------------------------------\n");
    printf("Total\t\t\t\t       %.2f", total);
    printf("\nTips\t\t\t\t       %.2f", tips);
    printf("\nTax\t\t\t\t       %.2f", tax);
    printf("\n---------------------------------------------\n");
    printf("Grand Total\t\t\t       %.2f", total_total);
    printf("\n---------------------------------------------\n");
}

void saveBill(FILE *fp, struct orders ord, float total){
    fp = fopen("bills.txt", "a+");
    fprintf(fp, "\n\n");
    fprintf(fp, "\t        C Restaurant");
    fprintf(fp, "\n\t      ----------------");
    fprintf(fp, "\n Client's name: %s", ord.client);
    fprintf(fp, "\n Date: %s", ord.date);
    fprintf(fp, "\n");
    fprintf(fp, "-----------------------------------------------\n");
    fprintf(fp, "Items\t\t     ");
    fprintf(fp, "Quantity\t\t        ");
    fprintf(fp, "Total\t\t\n");
    fprintf(fp, "-----------------------------------------------\n");
    fprintf(fp, "\n");

    for(int i = 0; i < ord.numOfItems; i++){
        fprintf(fp, "%s                 ", ord.itm[i].item);
        fprintf(fp, "%d                  ",  ord.itm[i].quantity);
        fprintf(fp, "%.2f", ord.itm[i].quantity * ord.itm[i].price);
        fprintf(fp, "\n\n");
    
    }
    float tips = 0.05 * total;
    float tax = 0.1 * total;
    float total_total = total + tips + tax;
    fprintf(fp, "-----------------------------------------------\n");
    fprintf(fp, "Total                                  %.2f", total);
    fprintf(fp, "\nTips                                   %.2f", tips);
    fprintf(fp, "\nTax                                    %.2f", tax);
    fprintf(fp, "\n-----------------------------------------------\n");
    fprintf(fp, "Grand Total                             %.2f", total_total);
    fprintf(fp, "\n-----------------------------------------------\n");


}
int main(){
    float total;
    int option, n;
    struct orders ord;
    FILE *fp;
    char save = 'y';
    printf("\t==============C RESTAURANT==============");
    printf("\n\n Please select your prefered operation");
    printf("\n\n1. Create new bill");
    printf("\n2. Exit\n");
    printf("Your option: ");
    scanf("%d", &option);
    fgetc(stdin);
    loading();
    switch(option){
        case 1:
        printf("\nPlease entrer client's name:  ");
        fgets(ord.client, 40, stdin);
        ord.client[strlen(ord.client)-1] = 0;
        strcpy(ord.date, __DATE__);
        printf("\nPlease entrer the number of items:  ");
        scanf("%d", &n);
        ord.numOfItems = n;
        for(int i=0; i<n;i++){
            fgetc(stdin);
            printf("\n\n");
            printf("Please enter the item No %d: ", i+1);
            fgets(ord.itm[i].item,30, stdin);
            ord.itm[i].item[strlen(ord.itm[i].item)-1] = 0;
            printf("\nPlease enter the quantity:  ");
            scanf("%d", &ord.itm[i].quantity);
            printf("\nPlease enter the unit price:  ");
            scanf("%f", &ord.itm[i].price);
            total += ord.itm[i].quantity * ord.itm[i].price;
        }
        createHeader(ord.client, ord.date);
        for(int i=0; i<ord.numOfItems; i++){
            createBody(ord.itm[i].item, ord.itm[i].quantity, ord.itm[i].price);   
        }
        createFooter(total);
        printf("\nWould you like to save the bill? [y/n]  ");
        scanf("%s", &save);
        if(save != 'n'){
            saveBill(fp, ord, total);
            printf("\nThe bill successfully has been saved");
        }
        printf("\n\nThank you!");
        break;


        case 2:
        printf("\n\nBye!");
        break;

    }
    return 0;
}
