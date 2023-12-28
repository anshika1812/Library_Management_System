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
        printf("\t\t\tPress '5' to issue a Book to a user\n");
        printf("\t\t\tPress '6' to process return from a user\n");
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
		else if(n==5){
        	issueBook();
		}
		else if(n==4){
        	returnBook();
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
    int issued;
    struct node*loc;
};
struct node*start=NULL;

int updateQty(char name[],int newqty){
	//reading data from file into linked list so as to make updation of quantity possible
    struct node*bookStart=NULL;
    struct node*bookEnd=NULL;
    FILE*p=fopen("books.txt","r");
    if(p==NULL){
    	addBooks();
    	return 0;
	}
	char bookData[200];
    while(fgets(bookData,sizeof(bookData),p)!=NULL){
    	char exname[100];
    	int exqty,exissued;
        if(sscanf(bookData,"%s %d %d",exname,&exqty,&exissued)==3){
        	struct node*temp=(struct node*)malloc(sizeof(struct node));
        	strcpy(temp->bookname,exname);
        	temp->qty=exqty;
        	temp->issued=exissued;
        	temp->loc=NULL;
        	
        	if(bookEnd==NULL){
        		bookStart=temp;
			}
			else{
				bookEnd->loc=temp;
			}
			bookEnd=temp;
		}
	}
	fclose(p);
	int bookPresent=0;
	struct node*current=bookStart;
    while(current!=NULL) {
        if(strcmp(current->bookname,name)==0) {
            //book found, update the quantity
            bookPresent=1;
            break;
        }
        current=current->loc;
    }
    if(bookPresent==0){
    	return -1;
	}
	else{
		//update the file by overwriting
		p=fopen("books.txt","w");
		current=bookStart;
    	while(current!=NULL){
	    	if(strcmp(current->bookname,name)==0) {
	            current->qty+=newqty;
	        }
	        fprintf(p,"%s %d %d\n",current->bookname,current->qty,current->issued);
	        struct node*temp=current;
	        current=current->loc;
    	}
		fclose(p);
		return 0;
	}
}

int addBooks(){
    int num,i,qty,issued,cont;
    char name[100],ch[100],fname;
    struct node*t1=(struct node*)malloc(sizeof(struct node));
    struct node*t=NULL;
    start=t1;
    printf("\t\t\tHow many Books do you wish to add? ");
    scanf("%d",&num);
    for(i=0;i<num;i++){
        printf("\t\t\tEnter name of Book: ");
        scanf("%s",name);
        printf("\t\t\tEnter quantity: ");
        scanf("%d",&qty);
        cont=updateQty(name,qty);
        if(cont==-1){
	        strcpy(t1->bookname,name);
	    	t1->qty=qty;
	    	issued=0;
	    	t1->issued=issued;
	    	FILE*p=fopen("books.txt","a");
	    	fprintf(p,"%s %d %d\n",name,qty,issued);
	    	fclose(p);
	        t1->loc=(struct node*)malloc(sizeof(struct node));
	        t=t1;
	        t1=t1->loc;
		}
    }
    free(t1);
    if(t!=NULL){
    	t->loc=NULL;
	}
    printf("\t\t\tAdded successfully\n\n");
	return 0;
}

int displayBooks(){
	char booknqty[200];
	char name[100];
    int qty,issued;
	FILE*p=fopen("books.txt","r");
	if(p==NULL){
		printf("Error displaying...");
		return 0;
	}
	printf("\n\t\t\tBOOK NAME\t\t\t\tQUANTITY\n\n",name,qty);
    while(fgets(booknqty,sizeof(booknqty),p)!=NULL){
        if(sscanf(booknqty,"%s %d %d",name,&qty,&issued)==3) {
            printf("\t\t\t%s\t\t\t\t%d\n",name,qty,issued);
        }
    }
    fclose(p);
    return 0;
}

int deleteBook(){
	return 0;
}

int checkStatus(){
	return 0;
}

int issueBook(){
	return 0;
}

int returnBook(){
	return 0;
}
