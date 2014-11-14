#include <linux/linkage.h>
#include <linux/kernel.h>
#include <asm/uaccess.h>

#define ROWS 20
#define MAX_BUF_SIZE 256

extern char Defs [ROWS][MAX_BUF_SIZE];
extern char Names [ROWS][MAX_BUF_SIZE];
extern int varNum;
extern int isSame;

asmlinkage int sys_SaveVariable(char __user*varname,  char __user*vardef) {

	char defTmp[MAX_BUF_SIZE]; //Temp Buffer for the definition
	char nameTmp[MAX_BUF_SIZE]; //Temp Buffer for the name
	int t; //Initialize t for the other loop
        int i; //Initialize i for the loop
	int j; //Initialize j for the other loop
	printk(KERN_EMERG "VarNum is %d", varNum);
	if(varNum == 0)
	{
		printk(KERN_EMERG "The first!\n");
		if(copy_from_user(nameTmp, varname, MAX_BUF_SIZE))
		{
			printk(KERN_EMERG "SaveVar failed: copy_from_user() error"); //Copy the argument from the user
			return -1;
		}
		if(copy_from_user(defTmp, vardef, MAX_BUF_SIZE))
		{
			printk(KERN_EMERG "SaveVar failed: copy_from_user() error"); //Copy the argument from the user
			return -1;
		}
		for(i = 0; i<MAX_BUF_SIZE; i++)
		{
			Names[varNum][i] = nameTmp[i];
		}
		for(i = 0; i<MAX_BUF_SIZE; i++)
		{
			Defs[varNum][i] = defTmp[i];
		}
		printk(KERN_EMERG "The first variable is %s = %s!\n", Names[0], Defs[0]);
		varNum++;
		return 0;
	}
	else if(varNum > 0)
	{
		if(copy_from_user(nameTmp, varname, MAX_BUF_SIZE))
		{
			printk(KERN_EMERG "SaveVar failed: copy_from_user() error"); //Copy the argument from the user
			return -1;
		}
		if(copy_from_user(defTmp, vardef, MAX_BUF_SIZE))
		{
			printk(KERN_EMERG "SaveVar failed: copy_from_user() error"); //Copy the argument from the user
			return -1;
		}
		printk(KERN_EMERG "The items have been copied");
		for(j = 0; j < ROWS; j++)
		{
			printk(KERN_EMERG "The item that it is being compared to is %s\n", Names[j]);

			for(i = 0; i < MAX_BUF_SIZE; i++)
			{
				if(Names[j][i] != nameTmp[i])
				{
					isSame = 0;
				}
				if(Names[j][i] == nameTmp[i])
				{
					isSame = isSame + 1;
				}
			}
			printk(KERN_EMERG "The isSame variable for the %d element is %d\n", j, isSame);

			if(isSame == MAX_BUF_SIZE)
			{
				printk(KERN_EMERG "The variable %s already exists, changing definition to %s", nameTmp, defTmp);
				for(t = 0; t<MAX_BUF_SIZE; t++)
				{
					Defs[j][t] = defTmp[t];
				}
				isSame = 0;
				return 0;
			}
			else if((isSame != MAX_BUF_SIZE) && (varNum >= (ROWS-1)))
                        {
                                printk(KERN_EMERG "There is not enough space!");
                                isSame = 0;
                                return -1;
                        }
			else if((isSame != MAX_BUF_SIZE) && (j == (ROWS-1)))
			{
				printk(KERN_EMERG "Inserting a new variable %s = %s at spot %d", nameTmp, defTmp, varNum);
				for(t = 0; t<MAX_BUF_SIZE; t++)
                                {
                                        Names[varNum][t] = nameTmp[t];
                                        Defs[varNum][t] = defTmp[t];
                                }
				varNum++;
                                isSame = 0;
                                return 0;
			}
			else if(isSame != MAX_BUF_SIZE)
                        {
                                isSame = 0;
                        }
		}
	}
	printk(KERN_EMERG "Something went awry!");
	return -1;
}
