include <linux/linkage.h>
#include <linux/kernel.h>
#include <asm/uaccess.h>
#include <string.h>

#define ROWS 20
#define COLUMNS 2
#define MAX_BUF_SIZE 128

extern char *Names [ROWS][COLUMNS];

asmlinkage int sys_SaveVariable(char __user*prevname, char __user*varname, int namelen, char __user*vardef, int deflen) {

        char prevTmp[MAX_BUF_SIZE]; //Temp Buffer for the name

        if(copy_from_user(prevTmp, prevname, MAX_BUF_SIZE)) //Copy the argument from the user
        {
                printk(KERN_EMERG "NextVariable failed : copy_from_user error!");
        }

        int g = 0;

        for(g = 0; g < ROWS; g++)
        {
                if(prevTmp == "")
                {
                        copy_to_user(varname, Names[0][0], namelen);
                        copy_to_user(vardef, Names[0][1], deflen);
                        printk(KERN_EMERG "%s = %s\n", Names[0][0], Names[0][1]);
                        return 0;
                }
                else if(prevTmp == Names[g][0]
                {
                        if(Names[g+1][0] != NULL)
                        {
                                copy_to_user(varname, Names[g+1][0], namelen);
                                copy_to_user(vardef, Names[g+1][1], deflen);
                                printk(KERN_EMERG "%s = %s\n", Names[g+1][0], Names[g+1][1]);
                                return 0;
                        }
                        else if (Names[g+1][0] == NULL)
                        {
                                printk(KERN_EMERG "End of variables!\n");
                                return -1;
                        }
                }
                else if(g = (ROWS-1))
                {
                        printk(KERN_EMERG "The previous variable given was not found!\n");
                        return -2;
                }
        }
}
