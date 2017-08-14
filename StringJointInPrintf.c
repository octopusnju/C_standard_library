#include <stdio.h>

#define Macro_A "[Macro_A]"
#define Macro_B "[Macro_B]"

char *Str_A = "Str_A";
char Str_B[10] = "Str_B";

int main()
{
    printf(Macro_A"\n");
    printf(Macro_B"\n");
    printf(Macro_A Macro_B"\n");
    //printf(Str_A"\n");
    printf(Str_A);
    printf("\n");
    //printf(Str_B"\n");
    printf(Str_B);
    printf("\n");
    //printf(Str_A Str_B);
    printf(Str_A, Str_B);
    printf("\n");
    printf("%s %d\n", "NNN", 111, 222);

    return 0;
}
