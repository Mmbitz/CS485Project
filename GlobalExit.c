#include <linux/linkage.h>
#include <linux/kernel.h>
#include <asm/uaccess.h>
#include <string.h>

#define ROWS 20
#define COLUMNS 2
#define MAX_BUF_SIZE 128

extern char *Names [ROWS][COLUMNS];

asmlinkage void sys_GlobalExit() {

        int y = 0;

        for(y = 0; y < ROWS; y++)
        {
                Names[y][0] = "";
                Names[y][1] = "";
        }
}
