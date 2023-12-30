void adminheader(){
	printf("\n\n\n\n\n");
    printf("\t\t\t\t\t\t\t\t! [LMS : ADMIN'S MENU] !\t\t\t\t\t\t\n");
    printf("\t\t\t<---------------------------------------------------------------------------------------------------------->");
    printf("\n\n\n");
}

struct usernode{
	char username[50];
    char book1[100];
    char book2[100];
    int userIssued;
    struct usernode*loc;
};
struct usernode*userstart=NULL;

adduserData(char username[], char book1[],char book2[], int userIssued){
    struct usernode*t1=(struct usernode*)malloc(sizeof(struct usernode));
    struct usernode*t=NULL;
    userstart=t1;
    strcpy(t1->username,username);
    strcpy(t1->book1,book1);
    strcpy(t1->book2,book2);   
	t1->userIssued=userIssued;
	FILE*p=fopen("usersdata.txt","a");
	fprintf(p,"%s %s %s %d\n",username,book1,book2,userIssued);
	fclose(p);
    t1->loc=(struct usernode*)malloc(sizeof(struct usernode));
    t=t1;
    t1=t1->loc;
    free(t1);
    t->loc=NULL;
	return 0;
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
		else if(n==6){
        	returnBook();
		}
        else{
            printf("\t\t\tInvalid choice entered.");
        }
    }while(n<=6);
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
	printf("\n\t\t\tBOOK NAME\t\t\tNET QUANTITY\t\t\tISSUED\n\n",name,qty);
    while(fgets(booknqty,sizeof(booknqty),p)!=NULL){
        if(sscanf(booknqty,"%s %d %d",name,&qty,&issued)==3) {
            printf("\t\t\t%s\t\t\t\t%d\t\t\t%d\n",name,qty,issued);
        }
    }
    fclose(p);
    return 0;
}

int deleteBook(){
	char name[100];
    printf("\t\t\tEnter name of Book to be removed/deleted: ");
    scanf("%s",name);
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
    	printf("\n\t\t\tNo such book was present.\n\n");
    	return 0;
	}
	else{
		//update the file by overwriting
		p=fopen("books.txt","w");
		current=bookStart;
    	while(current!=NULL){
	    	if(strcmp(current->bookname,name)!=0){
	    		fprintf(p,"%s %d %d\n",current->bookname,current->qty,current->issued);
	        	struct node*temp=current;
	        }
	        current=current->loc;
    	}
		fclose(p);
		printf("\t\t\tDeleted successfully\n\n");
		return 0;
	}
}

int checkStatus(){
	char name[100];
    printf("\t\t\tEnter name of Book: ");
    scanf("%s",name);
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
	struct node*current=bookStart;
    while(current!=NULL) {
        if(strcmp(current->bookname,name)==0) {
            if(current->issued<current->qty){
            	printf("\n\t\t\tBook is available for issue.\n\n");
			}
			else{
				printf("\n\t\t\tBook is currently not available for issue.\n\n");
			}
            return 0;
        }
        current=current->loc;
    }
	printf("\n\t\t\tNo such book is available.\n\n");
	return 0;
}

int updateuserData(char username[],char bookname[]){
	//reading data from "usersdata.txt" into linked list
	struct usernode*userStart=NULL;
    struct usernode*userEnd=NULL;
    FILE*p=fopen("usersdata.txt","r");
    if(p==NULL){
    	printf("\n\t\t\tError occured...\n\n");
    	return 0;
	}
	char userData[300];
    while(fgets(userData,sizeof(userData),p)!=NULL){
    	char exusername[50],exbook1[100],exbook2[100];
    	int exuserIssued;
        if(sscanf(userData,"%s %s %s %d",exusername,exbook1,exbook2,&exuserIssued)==4){
        	struct usernode*temp=(struct usernode*)malloc(sizeof(struct usernode));
        	strcpy(temp->username,exusername);
        	strcpy(temp->book1,exbook1);
        	strcpy(temp->book2,exbook2);
        	temp->userIssued=exuserIssued;
        	temp->loc=NULL;
        	
        	if(userEnd==NULL){
        		userStart=temp;
			}
			else{
				userEnd->loc=temp;
			}
			userEnd=temp;
		}
	}
	fclose(p);
	struct usernode*current=userStart;
	//update the file by overwriting
	p=fopen("usersdata.txt","w");
	while(current!=NULL){
    	if(strcmp(current->username,username)==0) {
            current->userIssued+=1;
            if(strcmp(current->book1,"Null")==0){
            	strcpy(current->book1,bookname);
            	strcpy(current->book2,"Null");
			}
			else{
				strcpy(current->book2,bookname);
			}
        }
        fprintf(p,"%s %s %s %d\n",current->username,current->book1,current->book2,current->userIssued);
        struct node*temp=current;
        current=current->loc;
	}
	fclose(p);
	printf("\n\t\tUser data updated successfully.\n");
	return 0;
}

int updateIssued(char bookname[]){
	struct node*bookStart=NULL;
    struct node*bookEnd=NULL;
    FILE*p=fopen("books.txt","r");
    if(p==NULL){
    	printf("\n\t\t\tError occured...\n\n");
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
	struct node*current=bookStart;
	//update the file by overwriting
	p=fopen("books.txt","w");
	while(current!=NULL){
    	if(strcmp(current->bookname,bookname)==0) {
            current->issued+=1;
        }
        fprintf(p,"%s %d %d\n",current->bookname,current->qty,current->issued);
        struct node*temp=current;
        current=current->loc;
	}
	fclose(p);
	printf("\n\t\tBook data updated successfully.\n");
	return 0;
}

int issueBook(){
	//reading data from "usersdata.txt" into linked list
	char username[50],bookname[100];
	int userPresent=0;
	int bookPresent=0;
	struct usernode*userStart=NULL;
    struct usernode*userEnd=NULL;
    FILE*p=fopen("usersdata.txt","r");
    if(p==NULL){
    	printf("\n\t\t\tError occured...\n\n");
    	return 0;
	}
	char userData[300];
    while(fgets(userData,sizeof(userData),p)!=NULL){
    	char exusername[50],exbook1[100],exbook2[100];
    	int exuserIssued;
        if(sscanf(userData,"%s %s %s %d",exusername,exbook1,exbook2,&exuserIssued)==4){
        	struct usernode*temp=(struct usernode*)malloc(sizeof(struct usernode));
        	strcpy(temp->username,exusername);
        	strcpy(temp->book1,exbook1);
        	strcpy(temp->book2,exbook2);
        	temp->userIssued=exuserIssued;
        	temp->loc=NULL;
        	
        	if(userEnd==NULL){
        		userStart=temp;
			}
			else{
				userEnd->loc=temp;
			}
			userEnd=temp;
		}
	}
	fclose(p);	
	//reading data from "books.txt"
	struct node*bookStart=NULL;
    struct node*bookEnd=NULL;
    FILE*f=fopen("books.txt","r");
    if(f==NULL){
    	printf("\n\t\t\tError occured...\n\n");
    	return 0;
	}
	char bookData[200];
    while(fgets(bookData,sizeof(bookData),f)!=NULL){
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
	fclose(f);
	
	printf("\t\t\tEnter name of user: ");
    scanf("%s",username);
    struct usernode*ucurrent=userStart;
    while(ucurrent!=NULL) {
        if(strcmp(ucurrent->username,username)==0) {
            userPresent=1;
            if(ucurrent->userIssued==2){
            	printf("\n\t\tThis user has 2 books issued currently. No more books can be issued, unless at least 1 book is returned.\n");
				return 0;
			}
            break;
        }
        ucurrent=ucurrent->loc;
    }
    if (userPresent==0){
        	printf("\n\t\tUser not found. Consider getting them registered first.\n");
        	return 0;
	}
	else{
		printf("\t\t\tEnter name of Book to be issued: ");
    	scanf("%s",bookname);
		struct node*bcurrent=bookStart;
	    while(bcurrent!=NULL) {
	        if(strcmp(bcurrent->bookname,bookname)==0) {
	            bookPresent=1;
				if(bcurrent->issued==bcurrent->qty)	{
					printf("\n\t\tBook is currently unavailable. Consider issuing another book meanwhile.\n");
					return 0;
				}
				break;
			}
			bcurrent=bcurrent->loc;
	}
	if (bookPresent==0){
		printf("\n\t\tThe required book couldn't be found. Consider issuing another book.\n");
        return 0;
	}
	else{
		updateuserData(username,bookname);
		updateIssued(bookname);
		printf("\n\t\tBook has been issued successfully");
	}
	return 0;
}

int returnBook(){
	return 0;
}
