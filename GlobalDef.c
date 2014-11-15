#include <linux/linkage.h>
#include <linux/kernel.h>
#include <asm/uaccess.h>
//#include "GlobalDef.h"

//Define the max variables and the max length
#define ROWS 20
#define MAX_BUF_SIZE 256

//Declare the global variables
//The array for holding the names
char Names [ROWS][MAX_BUF_SIZE];
//The array for holding the definitions
char Defs [ROWS][MAX_BUF_SIZE];
//The variable for the variable number
int varNum;
//The variable for comparing the variables
int isSame;
//The variable for first print
int notFirst;
//This function defines the basic initialization
asmlinkage int sys_GlobalDef(int Do){
	int j;
	int i;
	printk(KERN_EMERG "GlobalDef is starting\n");
	//Resetting the values for the variable number and comparison number
	varNum = 0;
	isSame = 0;
	notFirst = 0;

	//Resetting the arrays to hold new items
	for(j = 0; j<ROWS; j++)
	{
		for(i = 0; i<MAX_BUF_SIZE; i++)
		{
			Names[j][i] = ' ';
		}
	}

	for(j = 0; j<ROWS; j++)
        {
                for(i = 0; i<MAX_BUF_SIZE; i++)
                {
			Defs[j][i] = ' ';
                }
        }

	printk(KERN_EMERG "GlobalDef is done\n");
	return 0;
}
