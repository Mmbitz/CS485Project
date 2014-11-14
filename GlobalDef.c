#include <linux/linkage.h>
#include <linux/kernel.h>
#include <asm/uaccess.h>
//#include "GlobalDef.h"

#define ROWS 20
#define MAX_BUF_SIZE 256

char Names [ROWS][MAX_BUF_SIZE];
char Defs [ROWS][MAX_BUF_SIZE];
int varNum;
int isSame;

asmlinkage int sys_GlobalDef(int Do){
	int j;
	int i;
	printk(KERN_EMERG "GlobalDef is starting\n");
	varNum = 0;
	isSame = 0;

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
