//**************************** StudentData ************************************
//  Copyright (c) 2026 Trenser 
//  All Rights Reserved 
//***************************************************************************** 
// 
// File    : mainMenu.c 
// Summary : Contains main menu api.
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
static uint8 ucStudentsCount = 0;
static uint8 ucCapacity = 10;
_sStudentRecord *sStudentRecordList = NULL; 
//****************************** Local Functions ******************************

//******************************.FUNCTION_HEADER.****************************** 

bool menuMain(void)
{
    uint8 ucOption = 0;
    while (1)
    {
        printf("Select one of the options:\n \
            1: StudentOverview\n \
            2: AddStudent\n \
            3: ListStudent\n \
            4: DeleteStudent\n");
        scanf("%hhu", &ucOption);

        switch (ucOption)
        {
            case 1:
            {
                menuStudentOverview();
                break;
            }
            case 2:
            {
                menuAddStudent();
                break;
            }
            case 3:
            {
                menuListStudent();
                break;
            }
            case 4:
            {
                menuDeleteStudent();
                break;
            }
            default:
            {
                printf("Enter a valid option: \n");
            }
        }
    }

    return false;
}

bool menuStudentOverview(void)
{

    return false;
}

bool menuAddStudent(void)
{
    _sStudent sStudentData;
    bool bReturnValue = false;

    do
    { 
        // allocate or reallocate memrory
        if (NULL == sStudentRecordList)
        {
            sStudentRecordList = (_sStudentRecord *)malloc(ucCapacity * sizeof(_sStudentRecord));

        }
        // add Get student info
        if(true == studentAdd(&sStudentData))
        {
            printf("Error During Student addition!\n");
            bReturnValue = true;
            break;
        }
        // increase the student count
        ucStudentsCount ++;

    } 
    while (0);

    return bReturnValue;

}
bool menuListStudent(void)
{


    return false;
}
bool menuDeleteStudent(void)
{

    return false;
}
// EOF 