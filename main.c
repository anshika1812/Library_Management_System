// LIBRARY MANAGEMENT SYSTEM USING DATA STRUCTURES (Linked List) IN "C"

#include<stdio.h>

void header(){
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t\t\t\t\t\t\tLIBRARY MANAGEMENT SYSTEM\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t<----------------------------------------------------------------------------------------------------------------------->");
    printf("\n\n\n\n\n\n");
}
        
int login(){
    header();
    int username;
    printf("\t\t\tEnter username: ");
    scanf("\t\t\t%d",&username);
    if(username==1812){
        printf("\n\t\t\tWelcome! Login details have been verified successfully...\n");
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
        printf("\t\t\tPress '1' to Login\n");
        printf("\t\t\tPress '2' to view 'Project Details'\n");
        scanf("\t\t\t%d",&n);
        if(n==1){
            login();
        }
        else if(n==2){
            project_details();
            main();
        }
        else{
            printf("\t\t\tInvalid choice entered.");
        }
    }while(n<3);
    return 0;
}
