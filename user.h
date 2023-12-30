void userheader(){
	printf("\n\n\n\n\n");
    printf("\t\t\t\t\t\t\t\t! [LMS : USERS' MENU] !\t\t\t\t\t\t\n");
    printf("\t\t\t<---------------------------------------------------------------------------------------------------------->");
    printf("\n\n\n");
}

struct node2{
	char bookname[150];
    int qty;
    int issued;
    struct node2*loc;
};
struct node2*Start=NULL;

struct usernode2{
	char username[50];
    char book1[100];
    char book2[100];
    int userIssued;
    struct usernode2*loc;
};
struct usernode2*Userstart=NULL;

int usermenu(){
	int n=0;
    do{
        userheader();
        printf("\t\t\tPress '1' to view list of Books in the Library\n");
        printf("\t\t\tPress '2' to view list of Books currently issued by you\n");
        printf("\t\t\tPress '3' to check availability of a Book currently\n");
        printf("\t\t\tPress '4' to drop a message to the admin or to raise a query :)\n");
        printf("\t\t\tPress '0' to return to main menu\n");
        printf("\n\t\t\tNOTE:\n\t\t\tTo issue/return a book, kindly ask the admin to process your request.\n");
        printf("\t\t\tNot more than 2 books can be issued by a user at a time.\n");
        scanf("\t\t\t%d",&n);
        if(n==0){
        	return 0;
		}
        else if(n==1){
        	showBooks();
		}
        else if(n==2){
            viewIssued();
        }
        else if(n==3){
            viewStatus();
        }
        else if(n==4){
        	dropMessage();
		}
        else{
            printf("\t\t\tInvalid choice entered.");
        }
    }while(n<=4);
	return 0;
}

int showBooks(){
	char booknqty[200];
	char name[100];
	char status[100];
    int qty,issued;
	FILE*p=fopen("books.txt","r");
	if(p==NULL){
		printf("Error displaying...");
		return 0;
	}
	printf("\n\t\t\tBOOK NAME\t\t\tSTATUS\n\n");
    while(fgets(booknqty,sizeof(booknqty),p)!=NULL){
        if(sscanf(booknqty,"%s %d %d",name,&qty,&issued)==3) {
        	if(qty>issued){
        		strcpy(status,"Can be issued currently");
        		printf("\t\t\t%s\t\t\t%s\n",name,status);
			}
			else{
				strcpy(status,"Cannot be issued currently");
        		printf("\t\t\t%s\t\t\t%s\n",name,status);
			}
        }
    }
    fclose(p);
	return 0;
}

int viewIssued(){
	//reading data from "usersdata.txt" into linked list
	char username[50];
	struct usernode2*userStart=NULL;
    struct usernode2*userEnd=NULL;
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
        	struct usernode2*temp=(struct usernode2*)malloc(sizeof(struct usernode2));
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
	printf("\t\t\tEnter your username: ");
	scanf("%s",username);
	struct usernode2*ucurrent=userStart;
    while(ucurrent!=NULL) {
        if(strcmp(ucurrent->username,username)==0) {
            if(ucurrent->userIssued==0){
            	printf("\n\t\t\tNo books have been issued by you currently.\n");
				return 0;
			}
			else if(ucurrent->userIssued==1){
				printf("\n\t\t\tCurrently,1 book has been issued by you.\n");
				printf("\t\t\tName of the book: %s\n",ucurrent->book1);
				return 0;
			}
			else{
				printf("\n\t\t\tCurrently,2 books have been issued by you.\n");
				printf("\t\t\tName of 1st book: %s\n",ucurrent->book1);
				printf("\t\t\tName of 2nd book: %s\n",ucurrent->book2);
				printf("\n\t\t\tPlease return at least one book to be able to issue another.\n");
				return 0;
			}
            break;
        }
        ucurrent=ucurrent->loc;
    }
}

int viewStatus(){
	char name[100];
    printf("\t\t\tEnter name of Book: ");
    scanf("%s",name);
    struct node2*bookStart=NULL;
    struct node2*bookEnd=NULL;
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
        	struct node2*temp=(struct node2*)malloc(sizeof(struct node2));
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
	struct node2*current=bookStart;
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

int dropMessage(){
	return 0;
}
