void adminheader(){
	printf("\n\n\n\n\n");
    printf("\t\t\t\t\t\t\t\t! [LMS : ADMIN'S MENU] !\t\t\t\t\t\t\n");
    printf("\t\t\t<---------------------------------------------------------------------------------------------------------->");
    printf("\n\n\n");
}

int adminmenu(){
	int n=0;
    do{
        adminheader();
        printf("\t\t\tPress '1' to view list of Books\n");
        printf("\t\t\tPress '2' to add a new Books in the list\n");
        printf("\t\t\tPress '3' to delete a Book from the list\n");
        printf("\t\t\tPress '4' to check Book status\n");
        printf("\t\t\tPress '0' to return to main menu\n");
        scanf("\t\t\t%d",&n);
        if(n==0){
        	return 0;
		}
        else if(n==1){
        	displayBooks();
		}
        else if(n==2){
            addBooks();
        }
        else if(n==3){
            deleteBook();
        }
        else if(n==4){
        	checkStatus();
		}
        else{
            printf("\t\t\tInvalid choice entered.");
        }
    }while(n<=4);
	return 0;
}

int addBooks(){
	return 0;
}

int displayBooks(){
	return 0;
}

int deleteBook(){
	return 0;
}

int checkStatus(){
	return 0;
}
