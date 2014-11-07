#include <linux/linkage.h>
#include <linux/kernel.h>
#include <asm/uaccess.h>
#include <string.h>

#define ROWS 20
#define COLUMNS 2
#define MAX_BUF_SIZE 128

extern char *Names [ROWS][COLUMNS];

asmlinkage int sys_SaveVariable(char __user*varname, char __user*vardef) {

        char nameTmp[MAX_BUF_SIZE]; //Temp Buffer for the name
        char defTmp[MAX_BUF_SIZE]; //Temp Buffer for the definition

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

        int i = 0; //Initialize i for the loop

        for(i = 0; i < ROWS; i++){
                if(Names[i][0] == NULL)
                {
                        printk(KERN_EMERG "Space Found, variable %s = %s added!\n", nameTmp, defTmp);
                        Names[i][0] = nameTmp;
                        Names[i][1] = defTmp;
                        return 0;
                }
                else if (Names[i][0] == nameTmp)
                {
                        printk(KERN_EMERG "Variable %s exists, changing definition %s =  %s!\n", nameTmp, nameTmp, defTmp);
                        Names[i][1] = defTmp;
                        return 0;
                }
                else
                {
                        if (i == (ROWS-1))
                        {
                                printk(KERN_EMERG "Not enough space for entries, the variable was not added!\n");
                                return -1;
                        }
                }
        }
}
