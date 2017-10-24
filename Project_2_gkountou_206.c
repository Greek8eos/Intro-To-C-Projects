/*
 * Project 2
 * George Kountouris	G00928016
 * Lab Section: 206
 */
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define X_SEMIRANGE 3
#define Y_SEMIRANGE 2

int  correctRound(double num);
int f(double num);
void print();
void draw();
void initialize();

char graph[Y_SEMIRANGE*20+1][X_SEMIRANGE*20+1];

int main()
{	
	int i;
	double j;
	initialize();//initializes the graph array to empty characters.	
	draw(); //draws an empty array to form the graph shape
	
	for(j=0; j<X_SEMIRANGE*20+1;j++)	//for loop used to create the array for a specific funcitons. f() function is called and used
	{	
		i=correctRound(j);	
		graph[f(j)][i]='o';
		
	}
	print();	//prints the array (graph)
}

int  f(double num)
{
	int j;
	int x= X_SEMIRANGE*20+1;
	int y=Y_SEMIRANGE*20+1;
	double f;
	
	double denominator= pow(-X_SEMIRANGE+(num*0.1),2);	//computes the denominator of the form x squared, number is muliplied by .1 for increment 
	if(denominator !=0)					//checks for denominator being zero
	{
		f=exp(-1/denominator);				//finds a y value for f=e to the -1/(x^2)
		//f=cos(pow((-X_SEMIRANGE+(num*0.1)),2));
		f*=10;						//multiplies the y value by 10 to scale it
		j=correctRound(f);
		j=(Y_SEMIRANGE*10)-j;				// subtracts y from the x axis 
	}
	else							// if the denominator is zero
		j=Y_SEMIRANGE*10;				// skips undefined region
	return j;	
}

int  correctRound(double num)
{
	int i=0;
	if(num>=0)
		i=(int)(num+0.5);
	else
		i=(int)(num-0.5);
	return i;
}

void initialize()
{
	int i,j;
	int x= X_SEMIRANGE*20+1;
	int y=Y_SEMIRANGE*20+1;
	
	for(i=0; i<y;i++)	// puts empty spaces in the array
	{
		for(j=0; j<x;j++)
		{
			graph[i][j]=' ';
		}
	}
}

void print()
{
	int x=X_SEMIRANGE*20+1;
	int y=Y_SEMIRANGE*20+1;
	int i,j;
	
	for(i=0;i<y;i++)	//prints the array
	{
		for(j=0;j<x;j++)
		{
			printf("%c",graph[i][j]);
		}
		printf("\n");
	}
}

void draw()		//draws the array into a graph
{
	int i,j;
	int x=X_SEMIRANGE*20+1;
	int y=Y_SEMIRANGE*20+1;
		
	for(i=0; i<x; i++)
	{
		graph[y/2][i]='-';
	}
	for(j=0; j<y; j++)
	{
		graph[j][x/2]='|';
	}
}

