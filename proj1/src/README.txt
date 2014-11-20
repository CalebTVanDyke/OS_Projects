UTHREAD USER LIBRARY
====================
To integrate your library code simply include uthread.h in your main application code file.
Then update the Makefile to point to your application program.  If your main application code is in the file main.c there is nothing to update otherwise you will need to update the following lines:

Line 3: replace main.o with your_file_name.o

Line 4: replace main with your_file_name
		replace main.o with your_file_name.o

Line 6: replace main.o with your_file_name.o
		replace main.c with your_file_name.c

Line 7: replace main.c with your_file_name.c

Where your_file_name is the name of your main program for your application code.
Then to compile you can simply type make.  Then run your applicaiton using ./your_file_name