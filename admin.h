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
        printf("\t\t\tPress '1' to view list of Books in the Library\n");
        printf("\t\t\tPress '2' to add new Books in the Library\n");
        printf("\t\t\tPress '3' to delete a Book from the Library\n");
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

struct node{
	char bookname[150];
    int qty;
    struct node*loc;
};
struct node*start=NULL;

int addBooks(){
    int num,i,qty;
    char name[100],ch[100],fname;
    struct node*temp=(struct node*)malloc(sizeof(struct node));
    struct node*t=NULL;
    start=temp;
    printf("\t\t\tHow many Books do you wish to add? ");
    scanf("%d",&num);
    for(i=0;i<num;i++){
        printf("\t\t\tEnter name of Book: ");
        scanf("%s",name);
        printf("\t\t\tEnter quantity: ");
        scanf("%d",&qty);
        strcpy(temp->bookname,name);
    	temp->qty=qty;
    	FILE*p=fopen("books.txt","a");
    	fprintf(p,"%s %d\n",name,qty);
    	fclose(p);
        temp->loc=(struct node*)malloc(sizeof(struct node));
        t=temp;
        temp=temp->loc;
    }
    free(temp);
    t->loc=NULL;
    printf("\t\t\tAdded successfully\n\n");
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
