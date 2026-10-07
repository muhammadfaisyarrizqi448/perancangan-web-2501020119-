#include <stdio.h>
// main function - 
// where the execution of program begins
int i, j;
float k;

int main(int argc, char** argv)
{
    // prints hello world
    printf("Hello World\n");
    printf("argc = %d\n", argc);
    for (int ndx = 0; ndx != argc; ++ndx)
        printf("argv[%d] --> %s\n", ndx, argv[ndx]);
    printf("argv[argc] = %p\n", (void*)argv[argc]);
    return 0;
}