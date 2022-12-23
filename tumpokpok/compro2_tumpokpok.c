#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
void menu(){
	FILE *menu;
	char pg;
	if((menu = fopen("menu.txt","r")) == NULL){
		printf("ERROR in open file");
		exit(1);
	}
	while((pg = fgetc(menu)) != EOF){
		printf("%c", pg);
	};
}

typedef struct{
	int pt;
	char o[2];     //order
	float q[99];   //quantity
	float subtotal, total, discount;
	float tprice[99];
}ORDER;


void orders(int p, int aa, int num[], char date[10], int n){
	ORDER ods;				  
	char *code[25] = {"S1", "S2", "S3", "S4", "S5", "L1", "L2", "L3", "L4", "C1", "C2", "C3", "C4", "G1", "G2", "G3",
					"O1", "O2", "O3", "O4", "D1", "D2", "D3", "D4", "D5"};
	char *namemn[25] = {"Tum Poo-Plara", "Tum Thai", "Tum Thai Kai Kem", "Tum Khawphod", "Tum Sua","Larb Moo", 
					  "Larb Ped", "Larb Kap Moo", "Nam Tok Moo", "Soup Nor Mai", "Gaeng Om", "Super Peek Gai",
					  "Tom Saap Kra Dook Aon", "Kor Moo Yang", "Grilled Chicken", "Grilled Catfish", "Kanom Jeen",
					  "Sticky Rice ", "Steamed Rice", "Kap Moo     ", "Ice", "Water", "Coke ", "Pepsi", "Est  "};
	float price[25] = {40, 40, 50, 50, 50, 50, 55, 60, 60, 40, 50, 60, 60, 60, 35, 40, 10, 10, 10, 10, 9, 15, 20, 20, 20};
	int i = 0, j = 0, a = 0, b = 0, k, z = 0, choose, d = 0, newpoint = 0;
	char finorder[99][999];
	float finqt[99], total;
	/**************get orders*************/
	do{
		printf("\nCode Menu: ");
		scanf("%s", &ods.o);
		if(*ods.o == '0'){
			break;
		}
		for(j=0;j<2;j++){
			finorder[i][j] = ods.o[j];
		}
		printf("Quantity: ");
		scanf("%f", &ods.q[i]);
		finqt[i] = ods.q[i];
		i++;	
	}while(*ods.o != '0');
	printf("--------------------------------------------------------------------\n");
	
	/**************change orders*************/
	do{
		printf("Do you want to change orders?\n");
		printf("Enter 1 for add menu and quantity\nEnter 2 for delete menu and quantity\nEnter 3 for finish orders: ");
		scanf("%d", &choose);
		printf("--------------------------------------------------------------------\n");
		/***add orders***/
		if(choose == 1){
			int choice;
			printf("Add quantity in menu that already ordered ENTER 1\n");
			printf("Add new orders ENTER 2: ");
			scanf("%d", &choice);
			printf("-------------------------------------------------------------\n");
			if(choice == 1){
				do{
					printf("Add code menu: ");
					scanf("%s", &ods.o);
					if(*ods.o == '0'){
						break;
					}	
					for(a=0;a<i;a++){
						if(strcmp(ods.o, finorder[a]) == 0){
							printf("Quantity: ");
							scanf("%f", &ods.q[i]);
							finqt[a] += ods.q[i];
							break;
						}	
					}
				}while(*ods.o != '0');
			}	
			if(choice == 2){
				do{
					printf("Add code menu: ");
					scanf("%s", &ods.o);
					if(*ods.o == '0'){
						break;
					}	
					for(j=0;j<2;j++){
						finorder[i][j] = ods.o[j];
					}
					printf("Quantity: ");
					scanf("%f", &ods.q[i]);
					finqt[i] = ods.q[i];
					i++;
				}while(*ods.o != '0');
			}
			printf("-------------------------------------------------------------\n");
		}
		/***delete orders***/
		else if(choose == 2){
			do{
				printf("Code order to delete: ");
				scanf("%s", &ods.o);
				if(*ods.o == '0'){
					break;
				}
				
				for(a=0;a<i;a++){
					if(strcmp(ods.o, finorder[a]) == 0){
						printf("Quantity to delete: ");
						scanf("%f", &ods.q[i]);
						finqt[a] -= ods.q[i];
					}	
				}	
			}while(*ods.o != '0');
			printf("-------------------------------------------------------------\n");
		}	
	}while(choose != 3);
	
	/*************print orders, receipt and points*************/
	a = 0;
	ods.subtotal = 0;
	printf("           Menu                         Quantity             Price\n\n");
	do{
		if(strcmp(finorder[a], code[d]) == 0){
			ods.tprice[a] = finqt[a]*price[d];
			printf("%s %-22s%19.0f%20.2f THB\n", finorder[a], namemn[d], finqt[a], ods.tprice[a]);
			ods.subtotal += ods.tprice[a];
			a++;
			d = 0;
		}	
		else{
			d++;
		}
	}while(strcmp(finorder[a], "\0") != 0);
	printf("--------------------------------------------------------------------\n");
	printf("SUBTOTAL%56.2f THB\n", ods.subtotal);
	if(p > ods.subtotal){
		printf("This time you can't use points, \nnext time please buy with minimum price.\n");
		p = 0;
	}
	printf("DISCOUNT%53d.00 THB\n", p);
	ods.total = ods.subtotal - p;
	if(ods.subtotal < 200){
		newpoint = 0;
	}
	else if(ods.subtotal == 200){
		newpoint = 15;
	}
	else if(ods.subtotal > 200 && ods.subtotal < 500){
		newpoint = 20;
	}
	else if(ods.subtotal == 500){
		newpoint = 50;
	}
	else if(ods.subtotal > 500){
		newpoint = 100;
	}
	printf("TOTAL%59.2f THB\n", ods.total);
	printf("--------------------------------------------------------------------\n");
	printf("You have received %d points.\n", newpoint);
	
	/*add point in file*/
	int temp = -1, point[999], ppoint[999];
	char buffer[999];
	char path[] = "points.txt";
	FILE *fptr, *ftemp, *fpp, *cp, *readpoint;
	fpp = fopen("phonepoints.csv", "w");
	fptr = fopen(path, "r");
	ftemp = fopen("point.txt", "w");
	if (fptr == NULL || ftemp == NULL){
    	printf("ERROR in open file2");
    	exit(1);
    }
    while((fgets(buffer, 999, fptr)) != NULL){
    	temp++;
    	if(aa == 0){
    		if(temp == n){
    		point[n] = newpoint;
    		fprintf(ftemp, "%d\n", point[n]);
		}
			else{
				fprintf(ftemp, "%s", buffer);
			}
		}
		else if(aa != 0){
			if(temp == aa){
    		point[aa] = newpoint;
    		fprintf(ftemp, "%d\n", point[aa]);
			}
			else{
				fprintf(ftemp, "%s", buffer);
			}
		}
	} 
	/*read file point and keep in array*/
	readpoint = fopen("points.txt", "r");
	for(i=0;i<999;i++){
		fscanf(readpoint, "%d\n", &ppoint[i]);
		if(num[i] == 0){
			break;
		}
	}
	if(aa == 0){
		ppoint[n] = newpoint;
	}
	else{
		ppoint[aa] = newpoint;
	}
	for(i=0;i<temp+1;i++){
		fprintf(fpp, "%d, %d\n", num[i], ppoint[i]);
	}
	fclose(readpoint);
	fclose(fptr);
    fclose(ftemp);
    fclose(fpp);
    remove(path);	
    rename("point.txt", path);
    
    /*income*/
    FILE *inc, *di;
	if((inc = fopen("income.csv", "a")) == NULL){
		printf("ERROR in open file");
		exit(1);
	}
	if((di = fopen("date-income.txt", "a")) == NULL){
		printf("ERROR in open file");
		exit(1);
	}
	fprintf(di, "%s %.2f\n", date, ods.total);
    fprintf(inc, "%s, %.2f\n", date, ods.total);
    fclose(inc);
    fclose(di);
}

typedef struct{
	int ber;
	int pt;
	char date[10];
	float income;
}ss;

int main(){
	char tel[10], date[10];
	int choice, temp1 = 0;
	char np;
	FILE *ic;
	ss readpp;
	printf("====================================================================\n");
	printf("                             TUM POK POK\n");
	printf("====================================================================\n");
	printf("                        Welcome To TUM POK POK\n");   
	printf("ADMIN enter 1 STAFF enter 2: ");
	scanf("%d", &choice);
	printf("====================================================================\n");
	if(choice == 1){
		int ch;
		printf("                              For ADMIN\n");
		do{
			printf("What do you want to see?\n");
			printf("(1) For change menu\n");
			printf("(2) For see phone number and points of customer\n");
			printf("(3) For see income\n");
			printf("(4) End: ");
			scanf("%d", &ch);
			printf("--------------------------------------------------------------------\n");
			if(ch == 1){
				printf("- If you want to change menu, you can edit in file menu.txt and\n");
				printf("  you must add code in line 28, 30 and 34 for add or delete or change\n");
				printf("  code menu, menu and price.\n");
			}
			if(ch == 2){
				printf("This is all phone number and points of customer in this moment.\n");
				FILE *rpp;
				if((rpp = fopen("phonepoints.csv","r")) == NULL){
					printf("ERROR in open file");
					exit(1);
				}
				char str[100] = "";
				ss readpp;
				char *token;
				char *delim = ",";
				printf("\n          Phone Number            Points\n");
				while(fgets(str, sizeof(str), rpp) != NULL){
					token = strtok(str, delim);
					int col = 0;
					while(token != NULL){
						switch(col){
							case 0:
								readpp.ber = atoi(token);
								break;
							case 1:
								readpp.pt = atoi(token);
								break;
						}
						col++;
						token = strtok(NULL, delim);
					}
					printf("%20d        %10d\n", readpp.ber, readpp.pt);
				}
				fclose(rpp);	
			}
			if(ch == 3){
				int select;
				printf("What do you want to see?\n(1) All income\n(2) Income per week\n");
				scanf("%d", &select);
				if(select == 1){
					printf("This is your all income.\n");

					if((ic = fopen("income.csv", "r")) == NULL){
						printf("ERROR in open file");
						exit(1);
					}
					char st[100] = "";
				
					char *tk;
					char *del = ",";
					printf("\n              Date             Income\n");
					while(fgets(st, sizeof(st), ic) != NULL){
						tk = strtok(st, del);
						int co = 0;
						while(tk != NULL){
							switch(co){
								case 0:
									strcpy(readpp.date, tk);
									break;
								case 1:
									readpp.income = atof(tk);
									break;
							}	
							co++;
							tk = strtok(NULL, del);
						}
						temp1++;
						printf("%20s        %7.2f THB\n", readpp.date, readpp.income);
					}
					fclose(ic);	
				}
				if(select == 2){
					int countt = 0;
					float money = 0;
					printf("This is your income per week.\n");
					FILE *im;
					if((im = fopen("date-income.txt", "r")) == NULL){
						printf("ERROR in open file");
						exit(1);
					}
					printf("\n              Date              Income\n");
					while(fscanf(im, "%s %f", &readpp.date, &readpp.income) != EOF){
						printf("%21s%15.2f THB\n", readpp.date, readpp.income);
						money += readpp.income;
						countt++;
						if(countt == 7){
							break;
						}
					}
					printf("\n       Total income per week %.2f THB\n", money);
					fclose(im);
				}
			}	
			printf("--------------------------------------------------------------------\n");
		}while(ch != 4);
		
		
		
	}
	if(choice == 2){
		printf("                        How To Use For STAFF\n");
		printf("- Enter Date-Month-Year (dd-mm-yyyy).\n");
		printf("- Keep phone numbers from customers to earn points for discount.\n");
		printf("- Taking orders, Enter the menu code that customer ordered.\n");
		printf("- If all orders have been received, Enter 0 in Menu and Quantity.\n");
		printf("- After finish orders, If customer want to change orders or\n");
		printf("  calcel order, Enter 1 for add orders, Enter 2 for delete orders,\n  Enter 3 for finish\n");
		printf("- You can see the receipt tell customer for subtotal discount total\n  and points that customer earn.");
		printf("\n====================================================================\n");
		printf("Enter date/month/year : ");
		scanf("%s", date);

		printf("\nPlease enter phone number of customer to collect membership points.\n");
		printf("Phone Number : ");
		scanf("%s", tel);
		FILE *cp, *pp, *fptr, *ftemp;
		int phone = 0, m = 0, f = 0, count = 0, a = 0;
		int num[999] = {0}, status = 0, numphone[999] = {0}, count1 = 0;
		int point[999], p = 0, dup = 0;

    	phone = atoi(tel);    //change string to int
    
		/*******read file phone number & keep in array*******/
		if((cp = fopen("checkphone.txt", "r+")) == NULL){
			printf("ERROR in open file1");
			exit(1);
		}
		for(m=0;m<999;m++){
			fscanf(cp, "%d\n", &num[m]);
			if(num[m] == 0){
				break;
			}
			count++;
		}
	
		if((pp = fopen("points.txt", "a+")) == NULL){
			printf("ERROR in open file3");
			exit(1);
		}
		for(m=0;m<999;m++){
			fscanf(pp, "%d\n", &point[m]);
			if(num[m] == 0){
				break;
			}
			count1++;
		}
		for(m=0;m<count1;m++){
			if(phone == num[m]){
				a = m;
				status = 1;
				p = point[m];
			}
		}
		if(status == 0){
			point[m] = 0;
			num[count1] = phone;
		
			fprintf(pp, "%d\n", point[m]);    	//add phone number and point to excel
			fprintf(cp, "%d\n", phone);						//add phone number to file checkphone	
		}
		int n;
		n = m;
		fclose(pp);
		fclose(cp);
	
		printf("Your Points: %d\n", p);
		printf("\nPLEASE ENTER TO CONTINUE...\n");
		getch();
		printf("====================================================================\n");
		printf("                                 MENU\n");
		menu();
		orders(p, a, num, date, n);
		printf("====================================================================\n");
		printf("               THANK YOU FOR COMING TO OUR RESTAURANT \n            ** THINK OF SOMTUM, THINK OF TUM POK POK **");
	}
	return 0;
}
