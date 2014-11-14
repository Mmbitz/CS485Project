#include <linux/linkage.h>
#include <linux/kernel.h>
#include <asm/uaccess.h>
//#include "GlobalDef.h"

#define ROWS 20
#define MAX_BUF_SIZE 256

extern char Defs [ROWS][MAX_BUF_SIZE];
extern char Names [ROWS][MAX_BUF_SIZE];
extern int varNum;
extern int isSame;

asmlinkage int sys_GetVariable(char __user*varname, char __user*vardef, int deflen) {

	int f; //Initialize f for the loop
	int h; //Initialize h for the loop
	int o;

	char nameTmp2[MAX_BUF_SIZE]; //Temp Buffer for the name
        char defTmp2[MAX_BUF_SIZE]; //Temp Buffer for the definition

	if(copy_from_user(nameTmp2, varname, MAX_BUF_SIZE))
	{
		printk(KERN_EMERG "GetVariable failed: copy_from_user() error");
		return -1;
	}

	for(h = 0; h < ROWS; h++)
	{
		printk(KERN_EMERG "The current item being searched is %s\n", Names[h]);
		for(f = 0; f < MAX_BUF_SIZE; f++)
		{
			if(Names[h][f] == nameTmp2[f])
			{
				isSame = isSame + 1;
			}
			else if (Names[h][f] != nameTmp2[f])
			{
				isSame = 0;
			}
		}
		if(isSame == MAX_BUF_SIZE)
		{
			for(o = 0; o < MAX_BUF_SIZE; o++)
			{
				defTmp2[o] = Defs[h][o];
			}
			copy_to_user(vardef, defTmp2, deflen);
			printk(KERN_EMERG "Successfully retrieved the value of %s = %s!\n", nameTmp2, defTmp2);
			isSame = 0;
			return 0;
		}
		else if((isSame != MAX_BUF_SIZE) && (h == (ROWS-1)))
	        {
			printk(KERN_EMERG "Could not find the variable %s in the kernel!\n", nameTmp2);
        		isSame = 0;
        		return -1;
        	}
		else if(isSame != MAX_BUF_SIZE)
		{
			isSame = 0;
		}
	}
	printk(KERN_EMERG "Something went awry!");
        return -1;
}
