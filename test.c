#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>

#define __NR_GlobalDef 315
#define __NR_SaveVariable 316
#define __NR_GetVariable 317
#define __NR_NextVariable 318


main(){
	int retval;
	int retval2;
	int retval3;
	int retval4;
	char name[256] = "Matt";
	char def[256] = "Truck";
	char name2[256] = "Derek";
        char def2[256] = "Car";
	char name3[256] = "Bobert";
        char def3[256] = "Bus";
	char name4[256] = "Brad";
        char def4[256] = "Truck";
        char name5[256] = "Tyler";
        char def5[256] = "Car";
        char name6[256] = "Paul";
        char def6[256] = "Bus";
	char name7[256] = "Hampton";
        char def7[256] = "Truck";
        char name8[256] = "Kyle";
        char def8[256] = "Car";
        char name9[256] = "Sack";
        char def9[256] = "Bus";
        char name10[256] = "Yack";
        char def10[256] = "Truck";
        char name11[256] = "Sarah";
        char def11[256] = "Car";
        char name12[256] = "Pooter";
        char def12[256] = "Bus";
	char name13[256] = "Nuts";
        char def13[256] = "Truck";
        char name14[256] = "Racial";
        char def14[256] = "Car";
        char name15[256] = "Slur";
        char def15[256] = "Bus";
	char name16[256] = "Dicks";
        char def16[256] = "Truck";
        char name17[256] = "Loops";
        char def17[256] = "Car";
        char name18[256] = "Cereal";
        char def18[256] = "Bus";
        char name19[256] = "Hotdogs";
        char def19[256] = "Truck";




	int len = 256;
	char DefBuff[256];

	int len2 = 256;
	int len3 = 256;
	char Prev[256] = " ";
	char NameBuff[256];
	char DefBuff2[256];

	printf("Starting the call!");
	retval = syscall(__NR_GlobalDef, 1);
	printf("Finished, returned with value %d\n", retval);

	printf("Starting the call!");
        retval = syscall(__NR_SaveVariable, name, def);
        printf("Finished, returned with value %d\n", retval);

	printf("Starting the call!");
        retval2 = syscall(__NR_SaveVariable, name2, def2);
        printf("Finished, returned with value %d\n", retval2);

	printf("Starting the call!");
        retval3 = syscall(__NR_SaveVariable, name3, def3);
        printf("Finished, returned with value %d\n", retval3);

	printf("Starting the call!");
        retval = syscall(__NR_SaveVariable, name4, def4);
        printf("Finished, returned with value %d\n", retval);

        printf("Starting the call!");
        retval2 = syscall(__NR_SaveVariable, name5, def5);
        printf("Finished, returned with value %d\n", retval2);

        printf("Starting the call!");
        retval3 = syscall(__NR_SaveVariable, name6, def6);
        printf("Finished, returned with value %d\n", retval3);

	printf("Starting the call!");
        retval = syscall(__NR_SaveVariable, name7, def7);
        printf("Finished, returned with value %d\n", retval);

        printf("Starting the call!");
        retval2 = syscall(__NR_SaveVariable, name8, def8);
        printf("Finished, returned with value %d\n", retval2);

        printf("Starting the call!");
        retval3 = syscall(__NR_SaveVariable, name9, def9);
        printf("Finished, returned with value %d\n", retval3);

	printf("Starting the call!");
        retval = syscall(__NR_SaveVariable, name10, def10);
        printf("Finished, returned with value %d\n", retval);

        printf("Starting the call!");
        retval2 = syscall(__NR_SaveVariable, name11, def11);
        printf("Finished, returned with value %d\n", retval2);

        printf("Starting the call!");
        retval3 = syscall(__NR_SaveVariable, name12, def12);
        printf("Finished, returned with value %d\n", retval3);

	printf("Starting the call!");
        retval = syscall(__NR_SaveVariable, name13, def13);
        printf("Finished, returned with value %d\n", retval);

        printf("Starting the call!");
        retval2 = syscall(__NR_SaveVariable, name14, def14);
        printf("Finished, returned with value %d\n", retval2);

        printf("Starting the call!");
        retval3 = syscall(__NR_SaveVariable, name15, def15);
        printf("Finished, returned with value %d\n", retval3);

	printf("Starting the call!");
        retval = syscall(__NR_SaveVariable, name16, def16);
        printf("Finished, returned with value %d\n", retval);

        printf("Starting the call!");
        retval2 = syscall(__NR_SaveVariable, name17, def17);
        printf("Finished, returned with value %d\n", retval2);

        printf("Starting the call!");
        retval3 = syscall(__NR_SaveVariable, name18, def18);
        printf("Finished, returned with value %d\n", retval3);

	printf("Starting the call!");
        retval = syscall(__NR_SaveVariable, name19, def19);
        printf("Finished, returned with value %d\n", retval);

	printf("Starting the call!");
        retval4 = syscall(__NR_GetVariable, name, DefBuff, len);
        printf("Finished, returned with value %d\n", retval4);
	printf("This is what was rerturned %s\n", DefBuff);

	int j;
	int p;
	retval = 0;
	int count = 0;
	while (retval == 0)
	{
		printf("\n\nStarting the NextVariable call!\n");

		printf("This is Prev before %s\n", Prev);

		retval = syscall(__NR_NextVariable, Prev, NameBuff, len, DefBuff2, len);
       		printf("Finished, returned with value %d\n", retval);
       		printf("This is what was rerturned %s\n", NameBuff);
       		printf("This is what was rerturned %s\n", DefBuff2);

		for(j = 0; j<256; j++)
		{
			Prev[j] = NameBuff[j];
		}
	}
}
