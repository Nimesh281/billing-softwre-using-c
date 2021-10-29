#include<stdio.h>
#include<string.h>
#include<stdlib.h>


struct items
{
    char item[20];
    float price;
    int qty;
};

struct orders
{
    char customerName[50];
    char date[30];
    int noOfItems;
    struct items itm[50];
};

void generateBillHeader(char name[50],char date[30]){
    printf("\n\n");
    printf("\t    RNB. REstaurant");
    printf("\n\t=======================");
    printf("\nDate:%s",date);
    printf("\nInvoice To: %s",name);
    printf("\n");
    printf("======================================");
    printf("\nItem\t\t");
    printf("Qty\t\t");
    printf("Total\t\t");
    printf("\n======================================");
    printf("\n\n");
}

void generateBillBody(char item[20],int Qty,float price ){
     printf("%s\t\t",item);
     printf("%d\t\t",Qty);
     printf("%0.2f\t\t",price);
     printf("\n");
}

void generateBillFooter(float total){
    printf("\n");
    float dis = 0.1*total;
    float netTotal = total-dis;
    printf("======================================");
    printf("\nSub Total \t\t\t%0.2f",total);
    printf("\nDiscount @10%s\t\t\t%0.2f","%",dis);
    printf("\n======================================");
    printf("\nNet Total\t\t\t%0.2f",netTotal);
    printf("\n======================================");
}


int main(){

    int opt,n;
    char saveBill,flag='y';
    char name[50];
    struct orders ord;
    struct orders order;
    FILE *fp;
    
    // Dashboard for user
    while(flag =='y'){
    float total=0;
    int invoiceFound=0;
    system("cls");
    printf("\n");
    printf("\n");
    printf("\t==========RNB. Restaurant==========");
    printf("\n\n Please select your prefered opton: ");
    printf("\n 1.Generate Invoice");
    printf("\n 2.Show All Invoices");
    printf("\n 3.Search Invoice");
    printf("\n 4.Clear all Invoices");
    printf("\n 5.Exit");
    printf("\n");
    printf("\n");
    printf("Your Choice: ");
    scanf(" %d",&opt);
    // fgetc(stdin);


    switch (opt){
    case 1: 
            system("cls");
            printf("Please enter the name of the costumer: \t");
            scanf(" %s",&ord.customerName);
            // ord.customerName[strlen(ord.customerName-1)]=0;
            strcpy(ord.date,__DATE__);
            printf("Please enter the number of items:    \t");
            scanf(" %d",&n);
            ord.noOfItems=n;
            // fgetc(stdin);
            for (int i = 0; i < n; i++)
            {
                printf("\nEnter the item no %d: \t\t\t",i+1);
                scanf(" %s",&ord.itm[i].item);
                printf("Enter the quantity of item: \t\t");
                scanf("%d",&ord.itm[i].qty);
                printf("Enter the unit price: \t\t\t");
                scanf("%f",&ord.itm[i].price);
            }
            generateBillHeader(ord.customerName,ord.date);

            for(int i=0;i<ord.noOfItems;i++){
            total += ord.itm[i].qty*ord.itm[i].price;    
            generateBillBody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
            }

            generateBillFooter(total);

            printf("\n\nDo you want to save the invoice[y/n]:\t");
            scanf("%s",&saveBill);

            if(saveBill=='y'){
                fp=fopen("RestaurantBill.txt","a+");
                fwrite(&ord,sizeof(struct orders),1,fp);
                if(fwrite!=0){
                    printf("\nSuccessfully Saved");
                }else{
                    printf("\nError Saving");
                }
                fclose(fp);
            }

            break;
    case 2: 
            system("cls");
            fp=fopen("RestaurantBill.txt","r");

            printf("\n***Your Previous Invoices**\n");
        
            while (fread(&order,sizeof(struct orders),1,fp)){
                float total1=0;
                generateBillHeader(order.customerName,order.date);
                for(int i=0;i<order.noOfItems;i++){
                    total1 = total1 + order.itm[i].qty*order.itm[i].price;
                    generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                }
                generateBillFooter(total1);
            }
            fclose(fp);
            break;

    case 3: 
          system("cls");  
          printf("Enter the name of the customer: ");
          scanf("%s",&name); 
          system("cls");
          fp=fopen("RestaurantBill.txt","r");
          printf("\n ***Invoices for %s**\n",name);
            
          while (fread(&order,sizeof(struct orders),1,fp)){
                float total1=0;
                if(!strcmp(name,order.customerName)){
                generateBillHeader(order.customerName,order.date);
                for(int i=0;i<order.noOfItems;i++){
                    total1 += order.itm[i].qty*order.itm[i].price;
                    generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                }
                generateBillFooter(total1);
                invoiceFound=1;
                }
             }
            fclose(fp);

            if(!invoiceFound){
                printf("\nSorry No Invoice for %S does not exist \n",name);
                printf("\n\n");
            }
            break;         

    case 4: 
            system("cls");
            fp=fopen("RestaurantBill.txt","w");
            printf("All Invoices Cleared");
            fclose(fp);
            break;

    case 5:
           printf("\n\t\tBye Bye :-)\n\n");
           exit(0);
           break;                 
    
    default:
        printf("\nSorry Invalid Option\n");
        break;
    }
        printf("\n\nDo you want to perform another operation?[y/n]\t");
        scanf("%s",&flag);

    }


    printf("\n\n");
    return 0;
}