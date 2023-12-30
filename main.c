// LIBRARY MANAGEMENT SYSTEM USING DATA STRUCTURES (Linked List) IN "C"

#include<stdio.h>
#include<string.h>
#include "admin.h"
#include "user.h"

void header(){
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t\t\t\t\t\tLIBRARY MANAGEMENT SYSTEM\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t<---------------------------------------------------------------------------------------------------------->");
    printf("\n\n\n\n\n\n");
}

int reg(){
    header();
    char username[50], name[50], ch[50], fname;
    FILE*p=fopen("users.txt","r");
    printf("\t\t\tEnter desired username (Remember, it will be your passkey in future!): ");
    scanf("\t\t\t%s",username);
    while(fgets(ch,sizeof(ch),p)!=NULL){
        ch[strcspn(ch,"\n")]='\0';	//Removing the newline character
        if(strcmp(ch,username)==0){
            fclose(p);
            printf("\t\t\tUsername already exists. Please choose another username!\n");
            reg();
        }
    }
    fclose(p);
    p=fopen("users.txt", "a");
    fprintf(p,"%s\n", username);
    fclose(p);
    adduserData(username,"Null","Null",0);
    printf("\t\t\tRegistration successful! Login with your username to proceed further!\n");
    login();
    return 0;
}
     
int login(){
    header();
    char username[50], ch[50];
    int found=0;
    FILE*p=fopen("users.txt","r");
    printf("\t\t\tEnter username: ");
    scanf("\t\t\t%s",username);
    while (fgets(ch,sizeof(ch),p)!=NULL){
		ch[strcspn(ch,"\n")]='\0';	//Removing the newline character
        if (strcmp(ch,username)==0){
        	found=1;
            break;
        }
    }
    fclose(p);
    if(found==1){
    	printf("\n\t\t\tWelcome! Login details have been verified successfully...\n");
    	if(strcmp(username,"AdminX")==0){
    		printf("\n\n\n\t\t\tGood to see you, Admin!! Here's your admin-menu...");
    		adminmenu();
    		main();
		}
		else{
			printf("\n\n\n\t\t\tHelllo there, %s!! Here's your user-menu...",username);
    		usermenu();
    		main();
		}
    }
    else{
        printf("\n\t\t\tInvalid username entered. Try again...\n");
        login();
    }
}


void project_details(){
    printf("\t\t\tThis is a console-based menu-driven program intended to be a Library Management System with various functionalities.\n\t\t\tDesigned & owned by Anshika Chhabra.\n");
}

int main(){
    int n=0;
    do{
        header();
        printf("\t\t\tPress '1' to Register\n");
        printf("\t\t\tPress '2' to Login\n");
        printf("\t\t\tPress '3' to view 'Project Details'\n");
        scanf("\t\t\t%d",&n);
        if(n==1){
        	reg();
		}
        else if(n==2){
            login();
            return 0;
        }
        else if(n==3){
            project_details();
            main();
        }
        else{
            printf("\t\t\tInvalid choice entered.");
        }
    }while(n<=3);
    return 0;
}
