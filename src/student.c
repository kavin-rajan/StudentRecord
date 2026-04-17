//**************************** StudentData ************************************
//  Copyright (c) 2026 Trenser 
//  All Rights Reserved 
//***************************************************************************** 
// 
// File    : student.c 
// Summary : Contains supporting function to calculate sutdent data.
// Note    : 
// Author  : Kavin M
// Date    : 17.04.2026
// 
//***************************************************************************** 
 
//******************************* Include Files ******************************* 
#include "student.h"

//******************************* Local Types ********************************* 
 
//***************************** Local Constants ******************************* 

//***************************** Local Variables ******************************* 
 
//****************************** Local Functions ******************************

//******************************.FUNCTION_HEADER.****************************** 

bool studentGetString(char *pDisplayText, char **pcData)
{
    bool bReturnValue = false;
    char cBuffer[BUFFER_SIZE];

    do
    {
        if ((NULL == pDisplayText) || (NULL == pcData))
        {
            bReturnValue = true;
            break;
        }

        (void)printf("%s\n", pDisplayText);
        scanf(" %[^\n]", cBuffer);
        
        // printf("%d\n", strlen(cBuffer));

        *pcData = (char *)malloc(strlen(cBuffer) * sizeof(char));

        // Memory allocation check
        if(NULL == *pcData)
        {
            (void)printf("Error in allocating memory\n");
            bReturnValue = true;
            break;
        }
        else
        {
            // skip
        }

        strcpy(*pcData, cBuffer);
    }
    while (0);

    return bReturnValue;
}

bool studentValidateMarks(uint8 *pucMarks)
{
    bool bReturnValue = false;

    do
    {
        if (NULL == pucMarks)
        {
            (void)printf("pointer is NULL!\n");
            bReturnValue = true;
            break;
        }
        else
        {
            // skip
        }

        for(int i = 0; i < NUMBER_OF_SUBJECTS; i++)
        {
            if(pucMarks[i] > 100)
            {
                (void)printf("invalid mark entered!!\n");
                bReturnValue = true;
                break;
            }
        }

    } 
    while (0);

    return bReturnValue;
}


bool studentAdd(_sStudent *pstInfo)
{
    bool bReturnValue = false;

    do
    {
        // input NULL Check
        if (NULL == pstInfo)
        {
            (void)printf("pointer is NULL!\n");
            bReturnValue = true;
            break;
        }

        // Get Student Name
        if (true == studentGetString("Enter Student's Name: ", &pstInfo->pcName))
        {
            printf("error in getting student name\n");
            bReturnValue = true;
            break;
        }
        else
        {
            //skip
        }

        // Get roll number
        (void)printf("Enter Student's roll number: ");
        scanf("%hd", &pstInfo->unRollNumber);

        // Get Marks
        (void)printf("Enter Marks of 10 subjects: ");
        for(int i = 0; i < NUMBER_OF_SUBJECTS; i++)
        {
            scanf("%hhd", &pstInfo->ucMarks[i]);
        }

        //validate input marks
        if (true == studentValidateMarks(&pstInfo->ucMarks[0]))
        {
            (void)printf("Mark validation failed!\n");
            bReturnValue = true;
            break;
        }
        else
        {
            // skip
        }

        // Get Address
        if (true == studentGetString("Enter Student's Address: ", &pstInfo->pcAddress))
        {
            (void)printf("error in getting student Address\n");
            bReturnValue = true;
            break;
        }
        else
        {
            //skip
        }
    } 
    while (0);
    
    return bReturnValue;
}
// EOF 