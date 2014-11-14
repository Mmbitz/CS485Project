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

asmlinkage int sys_NextVariable(char __user*prevname, char __user*varname, int namelen, char __user*vardef, int deflen) {

	char nameTmp3[MAX_BUF_SIZE];
	char defTmp3[MAX_BUF_SIZE];
	char prevTmp[MAX_BUF_SIZE]; //Temp Buffer for the name
	int g;
	int t;
	int c;

	if(copy_from_user(prevTmp, prevname, MAX_BUF_SIZE)) //Copy the argument from the user
	{
		printk(KERN_EMERG "NextVariable failed : copy_from_user error!");
		return -2;
	}

	printk(KERN_EMERG "The current item being search for is %s\n", prevTmp);

	if(prevTmp[0] == ' ')
	{
		printk(KERN_EMERG "You gave a blank string to get the first item\n");
		for(c = 0; c < MAX_BUF_SIZE; c++)
                {
                         nameTmp3[c] = Names[0][c];
                         defTmp3[c] = Defs[0][c];
                }
		copy_to_user(vardef, defTmp3, deflen);
                copy_to_user(varname, nameTmp3, namelen);
		return 0;
	}

	for(g = 0; g < ROWS; g++)
	{
		for(t = 0; t < MAX_BUF_SIZE; t++)
		{
			if(Names[g][t] == prevTmp[t])
			{
				isSame = isSame + 1;
			}
			else if (Names[g][t] != prevTmp[t])
			{
				isSame = 0;
			}
		}

		printk(KERN_EMERG "The isSame variable for the %d element is %d\n", g, isSame);

		if ((isSame == MAX_BUF_SIZE) && (g == (ROWS-1)))
		{
			printk(KERN_EMERG "You have given the name of the last item on the list. Now exiting!\n");
			isSame = 0;
			return -1;
		}
		else if (isSame == MAX_BUF_SIZE)
		{
			for(c = 0; c < MAX_BUF_SIZE; c++)
			{
                                nameTmp3[c] = Names[g+1][c];
                                defTmp3[c] = Defs[g+1][c];
			}
			copy_to_user(vardef, defTmp3, deflen);
			copy_to_user(varname, nameTmp3, namelen);
			printk(KERN_EMERG "Successfully retrieved the next item, it is %s = %s!\n", nameTmp3, defTmp3);
			isSame = 0;
			return 0;
		}
		else if((isSame != MAX_BUF_SIZE) && (g == (ROWS-1)))
		{
			printk(KERN_EMERG "You have given the name of an item not on the list. Now exiting!\n");
			isSame = 0;
			return -2;
		}
		else if(isSame != MAX_BUF_SIZE)
		{
			isSame = 0;
		}
	}
	printk(KERN_EMERG "Something went awry!");
    return -2;
}
