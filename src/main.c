#include "types.h"
#include "mainMenu.h"

#define MENU_ERROR 1

int main(void)
{
    if(true == menuMain())
    {
        printf("Error opening main menu\n");
    }
    else
    {
        // skip
    }
    return 0;
}