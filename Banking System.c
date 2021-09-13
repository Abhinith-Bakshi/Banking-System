#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
char name_arr[20][20];
char phone[20][20];
char userName_arr[20][20];
int UID[20];
int pass_shift_arr[20];
char password_arr[20][20];
int arr_cnt = 0;
double transaction_arr[20][100];
int transaction_arr_count[20];
char transaction_arr_Str[20][100][1000];
double curr_bal[20];
int Existing_user(int uid,char pass[])
{
	printf("\nuid : %d ; pass : %s",uid,pass);
	int ind = -1;
	for(int i=0;i<sizeof(UID);i++)
	{
		if(UID[i] == uid)
		{
			ind = i;
			break;
		}
	}
	if(ind >= 0)
	{
		//char* decrypt_pass = Decrypt(password_arr[ind],pass_shift_arr[ind]);
		//strcpy(decrypt_pass,Decrypt(password_arr[ind],pass_shift_arr[ind]));
		//strcpy(password_arr[ind],decrypt_pass);
		if(strcmp(password_arr[ind],pass) == 0)
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
	else
	{
		return 3;
	}
}

void Register_user()
{
	printf("PLEASE WAIT...");
	printf("ENTER YOUR DETAILS: \n");
	printf("ENTER YOUR NAME: ");
	scanf("%s",name_arr[arr_cnt]);
	
	printf("ENTER YOUR PHONE NUMBER: ");
	scanf("%s",phone[arr_cnt]);	
	printf("SELECT YOUR USERNAME: ");
	scanf("%s",userName_arr[arr_cnt]);
	srand(time(0));
	int uid_gen = (rand() % (100000 - 999999)) + 999999;
	printf("YOU USER ID IS: %d\n",uid_gen);
	UID[arr_cnt] = uid_gen;
	
	printf("\nENTER YOUR PASSWORD: ");
	char user_pass[20];
	scanf(" %s",user_pass);
	//gets(user_pass);
	int rand_shift = (rand() % (0 - 25)) + 25;
	//printf("hello");
	//int rand_shift = 25;
	//char* user_pass_encrypt = Encrypt(user_pass , rand_shift);
	//System.out.println("create user shift:"+rand_shift);
	pass_shift_arr[arr_cnt] = rand_shift;
	strcpy(password_arr[arr_cnt],user_pass);
	printf("PLEASE WAIT WHILE WE CREATE YOUR ACCOUNT...\n");
	printf("ACCOUNT CREATED SUCCESSFULLY!!\n");
	arr_cnt += 1;
}
void Deposit(int uid)
{
	int ind = -1;
	for(int i=0;i<sizeof(UID);i++)
	{
		if(UID[i] == uid)
		{
			ind = i;
			break;
		}
	}
	printf("ENTER THE AMOUNT YOU WANT TO DEPOSIT: \n");
	double add_bal;
	scanf("%lf",&add_bal);
	int existing_vars = transaction_arr_count[ind];
	//System.out.println("ex:"+existing_vars);
	transaction_arr[ind][existing_vars] = add_bal;
	strcpy(transaction_arr_Str[ind][existing_vars],"Deposit");
	printf("PREVIOUS BALANCE: Rs. %lf\n",curr_bal[ind]);
	curr_bal[ind] += add_bal;
	printf("\nPROCESSING");
	printf("DONE.\n");
	printf("TRANSACTION SUCCESSFUL.\n");
	printf("\n");
	printf("CURRENT BALANCE: Rs. %lf \n",curr_bal[ind]);
	
	transaction_arr_count[ind]++;
}
void WithDraw(int uid)
{
	int ind = -1;
	for(int i=0;i<sizeof(uid);i++)
	{
		if(UID[i] == uid)
		{
			ind = i;
			break;
		}
	}
	printf("CURRENT BALANCE: Rs. %lf\n",curr_bal[ind]);
	/*System.out.println("Enter the amount you want to Withdraw from your account:");*/
	double del_bal = 0.0;
	do
	{
	    printf("ENTER THE AMOUNT YOU WANT TO WITHDRAW: \n");
		scanf("%lf",&del_bal);
		if(del_bal <= curr_bal[ind])
		{
			break;
		}
		else
		{
			printf("INSUFFICIENT BALANCE :( \nTRY AGAIN\n");
			continue;
		}
	}while(1);
	del_bal *= -1;
	int existing_vars = transaction_arr_count[ind];
	transaction_arr[ind][existing_vars] = del_bal;
	strcpy(transaction_arr_Str[ind][existing_vars],"Withdraw");
	curr_bal[ind] += del_bal;
	printf("PROCESSING...\n");
	printf("TRANSACTION SUCCESSFUL :)\n");
	printf("NEW BALANCE: Rs. %lf\n",curr_bal[ind]);
	transaction_arr_count[ind]++;
}
void TransferAmount(int giver_id)
{
	int giver_ind = -1;
	for(int i=0;i<sizeof(UID);i++)
	{
		if(UID[i] == giver_id)
		{
			giver_ind = i;
			break;
		}
	}
	int rec_ind = -1;
	do
	{
		int rec_id;
		printf("ENTER THE USER ID TO WHICH YOU WANT TO TRANSFER TO: \n");
		scanf("%d",&rec_id);
		int ind1 = -1;
		for(int i=0;i<sizeof(UID);i++)
		{
			if(UID[i] == rec_id)
			{
				ind1 = i;
				break;
			}
		}
		if(ind1 >= 0)
		{
			rec_ind = ind1;
			break;
		}
		else
		{
			printf("\tUSER ID NOT FOUND :(\n\tDO YOU WANT TO TRY AGAIN?\n\t1.YES\t2.NO\n");
			int ch;
			scanf("%d",&ch);
			if(ch == 1)
			{
				continue;
			}
			else
				break;
		}
		
	}while(1);
	double tran_amt = 0;
	if(rec_ind >=0)
	{
		printf("CURRENT BALANCE: Rs. %lf\n",curr_bal[giver_ind]);
		//double tran_amt = 0;
		do
		{
			printf("ENTER THE AMOUNT YOU WANT TO TRANSFER: \n");
			//scanf("%lf",&tran_amt);
			scanf("%lf",&tran_amt);
			if(tran_amt <= curr_bal[giver_ind])
			{
				break;
			}
			else
			{
				printf("INSUFFICIENT BALANCE :(\nTRY AGAIN\n");
				continue;
			}
		}while(1);
		int existing_vars = transaction_arr_count[giver_ind];
		transaction_arr[giver_ind][existing_vars] = (-1)*tran_amt;
		//char buf[10];
	//	char buf1[10];
	//	itoa(tran_amt,buf,10);
	//	itoa(UID[rec_ind],buf1,10);
		strcpy(transaction_arr_Str[rec_ind][existing_vars],"TRANSFER");
		curr_bal[giver_ind] += (-1)*tran_amt;
		transaction_arr_count[giver_ind]++;
		
		int existing_vars1 = transaction_arr_count[rec_ind];
		transaction_arr[rec_ind][existing_vars1] = tran_amt;
		strcpy(transaction_arr_Str[rec_ind][existing_vars1],"TRANSFER");
		curr_bal[rec_ind] += tran_amt;
		transaction_arr_count[rec_ind]++;
		printf("\nPROCESSING");
		printf("TRANSACTION SUCCESSFUL :)\n");
	}
	
}
void main()
{
	int login_var;
	do
	{
		printf("\n\t*****YES BANK******\n\n");
		printf("\t1.LOGIN\n\t2.REGISTER\n\t3.EXIT\n");
		int login_var;
		scanf("%d",&login_var);
		if(login_var == 1) 
		{
			int login_conf;
			printf("ENTER YOUR DETAILS: \n");
			printf("USER ID: \n");
			int user_id;
			scanf("%d",&user_id);
			printf("PASSWORD: \n");
			char password[20];
			scanf("%s",password);
			login_conf = Existing_user(user_id,password);//day1
			printf("AUTHENTICATING..");
			if(login_conf == 1)
			{
				printf("\nLOGIN SUCCESSFUL!!\n");
				printf("GETTING STARTED");
				int check_ctr = 1;
				do
				{
					int switch_var;
					printf("\n\tAVAILABLE OPTIONS IN OUR BANKING SYSTEMS:\n");
					printf("\t1.DEPOSIT\n\t2.WITHDRAW\n\t3.TRANSFER TO ANOTHER USER\n\t4.DISPLAY USER DETAILS\n\t5.DISPLAY TRANSACTION DETAILS\n\t6.LOG OUT\n\n");
					scanf("%d",&switch_var);
					switch(switch_var)
					{
					case 1:
						//Implementing deposit Module;
						Deposit(user_id);
						break;
					case 2:
						//Implementing withdraw module;
						WithDraw(user_id);
						break;
					case 3:
						//Implementing transfer module;
						TransferAmount(user_id);
						break;
					/*case 4:
						//Implementing user details display module;
						User_Details(user_id);
						break;
					case 5:
						//Implementing transaction details display module;
						Transaction_Details(user_id);
						break;*/
					case 6:
						printf("LOGGING OUT..\n");
						printf("DONE!!\n");
						printf("THANK YOU FOR USING OUR SERVICES.\nLOOKING FORWARD TO HELP YOU :)\n");
						check_ctr = 0;
						break;
					}
				}while(check_ctr > 0);
			}
			else if(login_conf == 2)
			{
				printf("INCORRECT PASSWORD :( \nPLEASE TRY AGAIN \n");
				continue;
			}
			else if(login_conf == 3)
			{
				printf("USER ACCOUNT DOES NOT EXIST :(");
				int reg_conf;
				printf("DO YOU WANT TO CREATE A NEW ACCOUNT?\n1.YES\t2.NO");
				scanf("%d",&reg_conf);
				if(reg_conf == 1)
				{
					Register_user();
				}
				else
				{
					printf("THANK YOU FOR USING OUR SERVICES.\nLOOKING FORWARD TO HELP YOU :)\n");
					
				}
			}
		}
		else if(login_var == 2)
		{
			printf("HI , WELCOME TO YES BANK :)\n");
			Register_user();
			printf("\n");
		}
		else
		{

			printf("THANK YOU!!");
			exit(0);
		}
	}while(1);
}
