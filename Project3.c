/*George Kountouris	G00928016
 * Project 3
 * LabSection 207
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct node
{
	char str[20];
	struct node * next;
}node;

void menu(); //method for the menu interface
void addString(node **nodeArray, int setAdd); //method to insert a string to the list, user input is asked for
void removeString(node **nodeArray, int setRemove);//method to remove a string from the list, user input is asked for
void deleteSet(node **nodeArray, int setClear);//method to clear a set
int strcmpa(char *s1, char *s2);// compares two strings
void printList(node **nodeArray, int set);//prints the specified set
void copySet(node **nodeArray, int set, int destSet);//copies one set to another
void insertStringToSet(node **nodeArray, char *s,int destSet);//inserts a strin to  set, only used in union, no user input is asked
void unionSets(node **nodeArray, int setOne, int setTwo, int destinedSet);// creates a union set
void intersectionSets(node **nodeArray,int setOne,int setTwo, int destinedSet);// creates an intersection set
void symmetricDifference(node **nodeArray,int setOne,int setTwo,int destinedSet);// creates a symmetric difference set
void removeStringSet(node **nodeArray, int setRemove,char *s);//removes a string from a set, only used in symmetric difference, no user input is asked

int main()
{
	char ch;
	int i,set,destSet,setOne,setTwo,destinedSet;
	node *nodeArray[10];
	for(i=0;i<=9;i++) //initialized dummy pointers for lists
	{
		nodeArray[i]=malloc(sizeof(node));
		if(!nodeArray[i])
		{
			printf("memory allocation failed!\n");
			exit(1);
		}
		nodeArray[i]->next=NULL;		
	}

	do
	{
		menu();
		scanf(" %c",&ch);
		
		switch(ch)
		{
			case 'a': printf("Which set:\n");
				  int setAdd;
				  scanf("%d",&setAdd);
				  if(setAdd>9||setAdd<0)// checks for invalid set input, same for all if statement in switch choices
				  {
					printf("Enter valid set number: 0-9\n");
					break;
				  }
				  addString(nodeArray,setAdd);
				  break;
			case 'r': printf("Which set:\n");
				  int setRemove;
				  scanf("%d",&setRemove);
				  removeString(nodeArray,setRemove);
				  break;
			case 'u': printf("Choose destination set:\n");
				  scanf("%d",&destinedSet);
				  printf("Choose first set:\n");
				  scanf("%d",&setOne);
				  printf("Choose second set:\n");
				  scanf("%d",&setTwo);
				  if((destinedSet<0||destinedSet>9)||(setOne<0||setOne>9)||(setTwo<0||setTwo>9))
				  {
					printf("Please make sure your set numbers are between 0 and 9\n");
					break;
				  }
				  unionSets(nodeArray, setOne, setTwo, destinedSet);
				  break;
			case 'i': printf("Choose destination set:\n");
                                  scanf("%d",&destinedSet);
                                  printf("Choose first set:\n");
                                  scanf("%d",&setOne);
                                  printf("Choose second set:\n");
                                  scanf("%d",&setTwo);
				  if((destinedSet<0||destinedSet>9)||(setOne<0||setOne>9)||(setTwo<0||setTwo>9))
                                  {
                                        printf("Please make sure your set numbers are between 0 and 9\n");
                                        break;
                                  }
				  intersectionSets(nodeArray,setOne,setTwo, destinedSet);
				  break;
			case 's': printf("Choose destination  set:\n");
                                  scanf("%d",&destinedSet);
                                  printf("Choose first set:\n");
                                  scanf("%d",&setOne);
                                  printf("Choose second set:\n");
                                  scanf("%d",&setTwo);
				  if((destinedSet<0||destinedSet>9)||(setOne<0||setOne>9)||(setTwo<0||setTwo>9))
                                  {
                                        printf("Please make sure your set numbers are between 0 and 9\n");
                                        break;
                                  } 
				  symmetricDifference(nodeArray,setOne,setTwo,destinedSet);
				  break;
			case 'c': printf("Choose a destination set to copy to:\n");
				  scanf("%d",&destSet);
				  printf("Choose a set to copy:\n");
				  scanf("%d",&set);
				  if((destSet<0||destSet>9)||(set<0||set>9))
                                  {
                                        printf("Please make sure your set numbers are between 0 and 9\n");
                                        break;
                                  }
				  copySet(nodeArray,set,destSet);
				  break;
			case 'z': printf("Which set would you like to clear:\n");
				  int setClear;
				  scanf("%d",&setClear);
				  if(setClear>9||setClear<0)
                                  {
                                        printf("Enter valid set number: 0-9\n");
                                        break;
          			  }
				  deleteSet(nodeArray, setClear);
				  break;
			case 'p': printf("Choose a set:\n");
				  int set;
				  scanf("%d",&set);
				  if(set>9||set<0)
                                  {
                                        printf("Enter valid set number: 0-9\n");
                                        break;
                                  }

				  printList(nodeArray,set); 
				  break;
			case 'q': ch=='q';
				  break;
			default: printf("Please enter a valid choice.\n");
		}
	}while(ch!='q');
	
	for(i=0;i<=9;i++) //free for memory leaks
	{
		free(nodeArray[i]);
	}
	
}

void menu()
{
	printf(" add string (a)     remove string (r)\n");
	printf(" union (u)          intersection (i)\n");
	printf(" symmetric difference (s)     copy (c)\n");
	printf(" clear (z)          print set (p)\n");
	printf(" quit (q)\n");
}

void addString(node **nodeArray,int setAdd)
{
	node* head=nodeArray[setAdd]->next;
	node* prev=nodeArray[setAdd];
	node* newNode;
	char input[20];
	int compare=0;

	printf("Please enter a String:\n");
	scanf("%s",input);
	
	newNode=malloc(sizeof(node));

	while(head!=NULL)
	{
		compare=strcmpa(head->str,input);
		if(compare==0)//if strings are the same
		{
			printf("String already exists in list, add not successful.\n");
			break;
		}
		else if(compare<0) //if input is greater than string at node
		{
			prev=head;
			head=head->next;		
		}
		else if(compare>0) //if input is less than string at node
		{
			newNode=malloc(sizeof(node));
			strcpy(newNode->str,input);
			prev->next=newNode;
			newNode->next=head;
			break;
		}
	}

        if(head==NULL)//empt list
        {
                newNode=malloc(sizeof(node));
                strcpy(newNode->str,input);
                prev->next=newNode;
                newNode->next=NULL;
        }

}

void removeString(node **nodeArray, int setRemove)
{
	node *head=nodeArray[setRemove]->next;
	node *prev=nodeArray[setRemove];
	char input[20];
	int compare=0;
	
	printf("Input string to remove:\n");
	scanf("%s",input);

	while(head!=NULL)
	{
		compare=strcmpa(head->str,input);
		if(compare==0)//if strings are the same
		{
			prev->next=head->next;
			free(head);
			break;
		}
		prev=head;//if not, traverse through list
		head=head->next;
	}
}

void unionSets(node **nodeArray, int setOne, int setTwo, int destinedSet)
{
	node *headOne= nodeArray[setOne]->next;
	node *headTwo=nodeArray[setTwo]->next;
	
	while(headOne)
	{
		insertStringToSet(nodeArray,headOne->str,destinedSet);
		headOne=headOne->next;//travers through the set	
	}
	while(headTwo)
	{
		insertStringToSet(nodeArray,headTwo->str,destinedSet);
		headTwo=headTwo->next;//traverse through the set
	}
}

void deleteSet(node **nodeArray, int setClear)
{
	node *head=nodeArray[setClear];
	node *kill=nodeArray[setClear]->next;
	while(kill)//while kill doesnt point to null, it will delete nodes
	{              
		head->next=kill->next;
		free(kill);
		kill=head->next;
        }

}

void symmetricDifference(node **nodeArray,int setOne,int setTwo,int destinedSet)
{
	copySet(nodeArray,setOne,destinedSet);//copies first set into destination set
	copySet(nodeArray,setTwo,destinedSet);//copies second set into destination set
	int compare=0;
	node *headOne=nodeArray[setOne]->next;
	node *headTwo=nodeArray[setTwo]->next;
	
	while(headOne)
	{
		while(headTwo)
		{
			compare=strcmpa(headOne->str,headTwo->str);
			if(compare==0) //if strings in set are equal, removes the string from the destination set
			{
				removeStringSet(nodeArray,destinedSet,headOne->str);
				break;
			}
			headTwo=headTwo->next;	//else transverse through second set	
		}
		headTwo=nodeArray[setTwo]->next;//starts pointer to beginning of second set
		headOne=headOne->next;//moves pointer one next in first set
	}
}

void copySet(node **nodeArray, int set, int destSet)
{
	node *head=nodeArray[set]->next;

	while(head)
	{
		insertStringToSet(nodeArray,head->str,destSet);
		head=head->next;
	}	
}

void intersectionSets(node **nodeArray,int setOne,int setTwo, int destinedSet)//while loops have same explaination as symmetric difference funciton
{	
	node *headOne= nodeArray[setOne]->next;
	node *headTwo= nodeArray[setTwo]->next;
	int compare=0;

	while(headOne) 
	{	
		while(headTwo)
		{	
			compare=strcmpa(headOne->str,headTwo->str);
			if(compare==0)
			{
				insertStringToSet(nodeArray,headOne->str,destinedSet);//inserts the string to desination set if they are the same
				break;
			}
			headTwo=headTwo->next;	
		}
		headTwo=nodeArray[setTwo]->next;
		headOne=headOne->next;
	}
}

void printList(node **nodeArray, int set)
{
	node *head=nodeArray[set]->next;
	printf("set: {");
	while(head!=NULL)
	{
		printf("%s",head->str);
		if(head->next!=NULL)
			printf(",");
		head=head->next;
		
	}
	printf("}\n");
}

void insertStringToSet(node **nodeArray, char *s,int destSet)//same as addString, but no user input
{
	node* head=nodeArray[destSet]->next;
        node* prev=nodeArray[destSet];
        node* newNode;
        int compare=0;
                
        newNode=malloc(sizeof(node));
        
        while(head!=NULL)
        {       
                compare=strcmpa(head->str,s);
		if(compare==0)
		{
			break;
		}
                else if(compare<0)
                {       
                        prev=head;
                        head=head->next;
                }
                else if(compare>0)
                {       
                        newNode=malloc(sizeof(node));
                        strcpy(newNode->str,s);
                        prev->next=newNode;
                        newNode->next=head;
                        break;
                }
        }
        
        if(head==NULL)
        {       
                newNode=malloc(sizeof(node));
                strcpy(newNode->str,s);
                prev->next=newNode;
                newNode->next=NULL;
        }

}

void removeStringSet(node **nodeArray, int setRemove,char *s)//same as removeString, but no user input
{
        node *head=nodeArray[setRemove]->next;
        node *prev=nodeArray[setRemove];
        int compare=0;

        while(head!=NULL)
        {
                compare=strcmpa(head->str,s);
                if(compare==0)
                {
                        prev->next=head->next;
                        free(head);
                        break;
                }
                prev=head;
                head=head->next;
        }
}


int strcmpa(char *s1, char *s2)
{
   while (*s1 && tolower(*s1) == tolower(*s2))
   {
      s1++;
      s2++;
   }
   return tolower(*s1) - tolower(*s2);
}
