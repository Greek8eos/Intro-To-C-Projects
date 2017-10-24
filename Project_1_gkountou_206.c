/* The Game of Sarlagiin Evriig
 *
 * George Kountouris
 *
 * G00928016
 *
 * Project 1 Lab Section 206
 *
 * Date Last Modified: 10/09/2016
 *
*/

#include<stdio.h>
#include<stdlib.h>

void EnterRandomSeed();
int  playerThrow(int *p, int *c, int *rp, int *rc);
int  computerThrow(int *p, int *c, int *rp, int *rc);

int main()
{
	char ch,ch2;
	int playerPoints,computerPoints,playerKopeks,computerKopeks,roundPlayerPoints,roundComputerPoints;
	
	EnterRandomSeed();
		
	playerKopeks=10;	
	computerKopeks=10;

	while(playerKopeks!=0&&computerKopeks!=0) /*while computer or player has kopeks (money)*/
	{
		playerPoints=0;
	        computerPoints=0;
	        roundPlayerPoints=0;
	        roundComputerPoints=0;

		printf("Would you like to play? Please enter Y for Yes and N for No.\n");	
		scanf(" %c",&ch);
		switch(ch)		
		{	
			case 'N':
			case 'n':exit(0);
			case 'Y':ch='y';
			case 'y':printf("Welcome to the game!You start off with %d kopeks, and the computer starts off with %d kopeks.\nYou both now bet 1 kopek to start the game\nWould you like to throw first?\n",playerKopeks,computerKopeks);
				 scanf(" %c",&ch2);
					 
				 if(ch2=='Y'||ch2=='y')
				 {
					playerThrow(&playerPoints,&computerPoints,&roundPlayerPoints,&roundComputerPoints);/*if player says yes, goes to playerThrow method,passes by refernce*/
					
					if(playerPoints>computerPoints) /*checks to see if player wins*/
					{
						playerKopeks= playerKopeks+1;
						computerKopeks= computerKopeks-1;
						printf("Congratulations! You win this game and won the bet!\nYour points were: %d, the computer's points were: %d.\nYour remaining Kopeks are: %d, and the computer's Kopeks: %d\n",playerPoints,computerPoints,playerKopeks,computerKopeks);
					}
					else
					{
						computerKopeks= computerKopeks+1;
						playerKopeks= playerKopeks-1;
						printf("\nYou lost the game and the bet.\nYour points were: %d and the computer's points were: %d.\nYour remaining Kopeks are: %d, and the computer's Kopeks: %d\n",playerPoints,computerPoints,playerKopeks,computerKopeks);
					}
				 }
				 else
				 {
					computerThrow(&playerPoints,&computerPoints,&roundPlayerPoints,&roundComputerPoints); /*player said no, so computer goes first; passes by reference*/
					
					if(computerPoints>playerPoints) /*checks to see if computer won*/
					{
						computerKopeks= computerKopeks+1;
						playerKopeks= playerKopeks-1;
						printf("You lost the game and the bet.\nYour points were: %d and the computer's points were: %d.\nYour remaining Kopeks are: %d, and the computer's remaining Kopeks are: %d\n",playerPoints,computerPoints,playerKopeks,computerKopeks);
					}
					else if(playerPoints>computerPoints) 
					{
						playerKopeks= playerKopeks+1;
						computerKopeks= computerKopeks-1;
						printf("Congratulations! You win this game and won the bet!\nYour points were: %d, the computer's points were: %d.\nYour remaining Kopeks are: %d, and the computer's Kopeks: %d.\n",playerPoints,computerPoints,playerKopeks,computerKopeks);
					}	
				 }					 
				 break;
	 		default: printf("Please enter a valid choice\n"); /*check for invalid input*/
				 break;
		}
		
		
		if(playerKopeks==0)
		{
			printf("I am sorry, you have no more kopeks to bet. Better luck next time.\n");
			exit(0);
		}
		else
		{
			if(computerKopeks==0)
			{
			printf("Congratulations! You took all of the computer's kopeks! The computer has none left!\n");
			exit(0);
			}
		}
	}
}


void EnterRandomSeed()
{
	unsigned int myRandomSeed;
	printf("Hello, please enter a random number seed: ");
	scanf("%d", &myRandomSeed);
	srandom(myRandomSeed);
	
}

int playerThrow(int *p, int *c, int *rp, int *rc) /*method for when player throws*/
{
	int myRandomNum;
	char input;

	if(((*c)<132&&(*rc)<132)&&((*p)<132&&(*rp)<132)) /*checks to see if someone has reached or passed 132 points*/
	{
		myRandomNum=random()%100;
		printf("Generated Number: %d.\n",myRandomNum);
		
		if(myRandomNum>=0&&myRandomNum<=16) /*checks for Dooshni Everi*/
		{
			printf("You rolled Dooshni Ever! You lost: %d points for this round. It is now the computer's turn.\n",(*rp));
			(*rp)=0;
	
			computerThrow(p,c,rp,rc); /* goes to computerThrow, since its computer's turn*/
			return 0;			
		}
		else
		{
		
			if(myRandomNum>=17&&myRandomNum<=32) /*checks for Khurtel Ever*/
			{
				(*p)+=(*rp);
				printf("You rolled Khartel Ever! Your points for this round have been added to your banked points!\nYour total points are: %d and your points this round were: %d\nIt is now the computers turn.\n",*p,*rp);
				if((*p)>=132||(*rp)>=132) /*checks to see if score has been reached by playr or passed*/
				{
					return 0;
				}
				(*rp)=0; /* resets roundPoints pointer to 0 for next round*/
				computerThrow(p,c,rp,rc);	
				return 0;
			}
		
			else
			{

				if(myRandomNum>=33&&myRandomNum<=55)
				{
					(*rp)+=2;  /* adds two points to roundPoints*/
					(*p)+=(*rp); /*adds round points to banked points*/
				       if((*p)>=132||(*rp)>=132)
                                        {
						printf("+2 points\n");
						return 0;
                                        }
					else
					{
		                	        printf("+2 points!, would you like to throw again?\n");
                                	        scanf(" %c", &input);
						if(input=='y'||input=='Y')
						{	
							(*p)-=(*rp); /*since player wants to throw again,subtracts roundPoints from total points, and continues with player throwing*/
							playerThrow(p,c,rp,rc);
							return 0;
						}
						
						printf("Total round points:%d, total banked points:%d\n",*rp,*p);
						(*rp)=0;	/*since player doesnt want to throw, resets roundpoints to zero.*/
						printf("Computer's turn.\n");
						computerThrow(p,c,rp,rc);
						return 0;
					}
				}
		
				else
				{

					if(myRandomNum>=56&&myRandomNum<=68)
					{
						(*rp)+=3;
						(*p)+=(*rp);
						if((*p)>=132||(*rp)>=132)
						{
							printf("+3 points\n");	
							return 0;
						}
						else
						{
		                       			 printf("+3 points!, would you like to throw again?\n");
                                      			  scanf(" %c", &input);	
							if(input=='y'||input=='Y')
							{
								(*p)-=(*rp);
								playerThrow(p,c,rp,rc);
								return 0;
							}
							printf("Total round points:%d, total banked points:%d\n",*rp,*p);
							(*rp)=0;
							printf("Computer's turn.\n");
							computerThrow(p,c,rp,rc);
							return 0;
						}
					}
		
					else
					{

						if(myRandomNum>=69&&myRandomNum<=83)
						{
							(*rp)+=5;
		                        		(*p)+=(*rp);
							if((*p)>=132||(*rp)>=132)
							{
								printf("+5 points\n");
								return 0;
							}
							else
							{

							        printf("+5 points!, would you like to throw again?\n");
	                     	                	        scanf(" %c", &input);
								if(input=='y'||input=='Y')
								{
									(*p)-=(*rp);
									playerThrow(p,c,rp,rc);
									return 0;
								}
								printf("Total round points:%d, total banked points:%d\n",*rp,*p);
								(*rp)=0;
								printf("Computer's turn.\n");
								computerThrow(p,c,rp,rc);
								return 0;
							}

						}
						else
						{
		
							if(myRandomNum>=84&&myRandomNum<=92)
							{
								
								(*rp)+=10;
								(*p)+=(*rp);
								if((*p)>=132||(*rp)>=132) 
								{    
									 printf("+10 points\n");
			                                                 return 0;                     
                                                                } 
								else 
								{
									 printf("+10 points!\nWould you like to throw again?\n");
                                                               		 scanf(" %c",&input);
									if(input=='y'||input=='Y')
							       		  {	
										(*p)-=(*rp);
										playerThrow(p,c,rp,rc);
										return 0;
									  }
									printf("Total round points:%d, total banked points:%d\n",*rp,*p);
									(*rp)=0;
									printf("Computer's turn.\n");
									computerThrow(p,c,rp,rc);
							           	return 0;
								}	
							}
		
	
							else	
							{
								if(myRandomNum>=93&&myRandomNum<=99)
								{
									(*rp)+=15;
									(*p)+=(*rp);
									if((*p)>=132||(*rp)>=132)
									{
										printf("+15 points\n");
										return 0;
									}
									else		
									{
				                                	        printf("+15 points!, would you like to throw again?\n");
                				                	        scanf(" %c", &input);
										if(input=='y'||input=='Y')
										{		
											(*p)-=(*rp);
											playerThrow(p,c,rp,rc);
											return 0;
										}
										printf("Total round points:%d, total banked points:%d\n",*rp,*p);
										(*rp)=0;
										printf("Computer's turn.\n");
										computerThrow(p,c,rp,rc);
										return 0;
									}
								}
							}
						}	
					}
				}
			}		
		}		
	}
	else
	{
		return 0;
	}
}

int  computerThrow(int *p, int *c, int *rp,int *rc) /*method for when the computer throws*/
{
	int myRandomNum;
        char input;
	
	if(((*p)<132&&(*rp)<132)&&((*c)<132&&(*rc)<132))
	{
		if((*rc)>25) /* checks to see if computer has exceeded 25pts*/
                {
                        (*c)+=(*rc); /*adds the roundpoints to total points*/
                         printf("The computer has gotten over 25 points.It got: %d, and its total points are:%d It is now your turn\n",*rc,*c);
                        (*rc)=0;	/*resets round points to zero for next round*/
                        playerThrow(p,c,rp,rc);	/*moves to player throw since its players turn now*/
			return 0;
                }


		myRandomNum=random()%100;
        	printf("Generated Number: %d.\n",myRandomNum);

        	        if(myRandomNum>=0&&myRandomNum<=16)
               		 {
                	        printf("Computer rolled Dooshni Ever! It lost %d  points for this round.Its total points are: %d. It is now the player's turn.\n",*rc,*c);
                	        (*rc)=0;	
				playerThrow(p,c,rp,rc);
				return 0;
			}
			else
		
				if(myRandomNum>=17&&myRandomNum<=32)
				{
					(*c)+=(*rc);
					printf("Computer rolled Khartel Ever! Its  points for this round have been added to its  banked points!\nTotal round points: %d and Total banked points: %d\nIt is now your turn.\n",*rc,*c);
                		        (*rc)=0;
                		        playerThrow(p,c,rp,rc);	
					return 0;
				}
				else
					if(myRandomNum>=33&&myRandomNum<=55)
					{
					printf("+2 points for the Computer\nIt throws again!\n");
					(*rc)+=2;
					computerThrow(p,c,rp,rc);
					return 0;
					}
					else
						if(myRandomNum>=56&&myRandomNum<=68)
						{
						printf("+3 points for the Computer\nIt throws again!");
                			        (*rc)+=3;
                			        computerThrow(p,c,rp,rc);
						}
						else
		
							if(myRandomNum>=69&&myRandomNum<=83)
							{
								printf("+5 points for the Computer\nIt throws again!");
                					        (*rc)+=5;
                					        computerThrow(p,c,rp,rc);
								return 0;
							}
							else
								if(myRandomNum>=84&&myRandomNum<92)
								{
									printf("+10 points for the Computer\nIt throws again!");
                						        (*rc)+=10;
                       							 computerThrow(p,c,rp,rc);
									 return 0;
								}
								else
									if(myRandomNum>=93&&myRandomNum<=99)
									{
										printf("+15 points for the Computer\nIt throws again!");
                       								 (*rc)+=15;
									
							                        computerThrow(p,c,rp,rc);
										return 0;
									}
	}
	else
	{
		return 0;
	}
	
}
