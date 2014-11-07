#include <linux/linkage.h>
#include <linux/kernel.h>
#include <asm/uaccess.h>
#include <string.h>

#define ROWS 20
#define COLUMNS 2
#define MAX_BUF_SIZE 128

extern char *Names [ROWS][COLUMNS];

asmlinkage int sys_GetVariable(char __user*varname, char __user*vardef, int deflen) {

        char nameTmp2[MAX_BUF_SIZE]; //Temp Buffer for the name
        char defTmp2[MAX_BUF_SIZE]; //Temp Buffer for the definition


        if(copy_from_user(nameTmp2, varname, MAX_BUF_SIZE))
        {
                printk(KERN_EMERG "GetVariable failed: copy_from_user() error");
                return -1;
        }

        int f = 0; //Initialize f for the loop

        for(f = 0; f < ROWS; f++){
                if(Names[f][0] == nameTmp2)
                {
                        copy_to_user(vardef, Names[f][1], deflen);
                        printk(KERN_EMERG "Successfully retrieved the value of %s = %s!\n", Names[f][0], Names[f][1]);
                        return 0;
                }
                else if (f == (ROWS-1))
                {
                        printk(KERN_EMERG "Could not find the variable %s in the kernel!\n", nameTmp2);
                        return -1;
                }
        }
}
