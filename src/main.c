//**************************** StudentData ************************************
//  Copyright (c) 2026 Trenser 
//  All Rights Reserved 
//***************************************************************************** 
// 
// File    : main.c 
// Summary : Contains main function of StudentData.
// Note    : 
// Author  : Kavin M
// Date    : 17.04.2026
// 
//***************************************************************************** 
 
//******************************* Include Files ******************************* 
#include "types.h"
#include "mainMenu.h"

//******************************* Local Types ********************************* 

//***************************** Local Constants ******************************* 

//***************************** Local Variables ******************************* 

//****************************** Local Functions ******************************

//******************************.FUNCTION_HEADER.****************************** 
//Purpose : Main function for StudentData
//Inputs  : 
//Outputs : 
//Return  : EXIT_SUCCESS: on Successful execution
//Notes   :
//***************************************************************************** 
int main(void)
{
    if(true == menuMain())
    {
        (void)printf("Error opening main menu\n");
    }
    else
    {
        // skip
    }
    return EXIT_SUCCESS;
}
// EOF 