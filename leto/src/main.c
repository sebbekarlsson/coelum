#include <coelum/main.h>
#include <stdio.h>


int main(int argc, char* argv[])
{

    coelum_init();

    if (coelum_main(argc, argv))
    {
        printf("Coelum crashed.");
    }

    return 0;
}
