//**************************** StudentData ************************************
//  Copyright (c) 2026 Trenser Technology Solutions (P) Ltd 
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
uint8 ucStudentsCount = 0;
_sStudentRecord *psStudentRecordList = NULL; 

//****************************** Local Functions ******************************
bool studentGetString(const uint8 *pDisplayText, uint8 **pcData);
static bool studentValidateMarks(const uint8 *pucMarks);
bool studentSwapData(uint8 ucIndex);
bool studentDeleteData(uint8 ucIndex);
static bool studentCheckRollNo(uint32 ulRoll);
static int32 studentCompareNames(const uint8 *pucNameA, const uint8 *pucNameB);

//******************************.FUNCTION_HEADER.****************************** 
//Purpose : Get's a string from user, dynamically allocates memory based on 
//          string
//Inputs  : pucDisplayText : Text to display to user
//          pucData        : Pointer to String
//Outputs : 
//Return  : true: on Successful execution
//          false : if any error occurs during memory allocation  
//Notes   :
//***************************************************************************** 
bool studentGetString(const uint8 *pucDisplayText, uint8 **pucData)
{
    bool bReturnValue = true;
    uint8 ucBuffer[BUFFER_SIZE] = {0};

    do
    {
        if ((NULL == pucDisplayText) || (NULL == pucData))
        {
            (void)printf("pointer is NULL!\n");
            bReturnValue = false;
            break;
        }

        (void)printf("%s\n", pucDisplayText);
        (void)scanf(" %99[^\n]", ucBuffer);

        *pucData = 
                (uint8 *)malloc((strlen((const char *)ucBuffer) + (size_t)1) * 
                sizeof(uint8));

        // Memory allocation check
        if(NULL == *pucData)
        {
            (void)printf("Error in allocating memory\n");
            bReturnValue = false;
            break;
        }
        else
        {
            // skip
        }

        (void)strcpy((char *)*pucData, (const char *)ucBuffer);
    }
    while (0);

    return bReturnValue;
}

//******************************.FUNCTION_HEADER.****************************** 
//Purpose : To validate the marks given by user
//Inputs  : pucMarks : Pointer to array that contains marks of a student
//Outputs : 
//Return  : true  : Marks are in valid range
//          false : Marks outside valid range 
//Notes   : valid marks : 0 to 100
//***************************************************************************** 
static bool studentValidateMarks(const uint8 *pucMarks)
{
    bool bReturnValue = true;

    do
    {
        if (NULL == pucMarks)
        {
            (void)printf("pointer is NULL!\n");
            bReturnValue = false;
            break;
        }
        else
        {
            // skip
        }

        for(uint8 i = 0; i < NUMBER_OF_SUBJECTS; i++)
        {
            if(pucMarks[i] > MAX_MARKS)
            {
                (void)printf("invalid mark entered!!\n");
                bReturnValue = false;
                break;
            }
        }

    } 
    while (0);

    return bReturnValue;
}

//******************************.FUNCTION_HEADER.****************************** 
//Purpose : To check availability of roll number
//Inputs  : ulRoll : Roll number to check
//Outputs : 
//Return  : true  : Roll number can be used
//          false : if Roll number is already available in StudentRecordList
//Notes   :
//*****************************************************************************
static bool studentCheckRollNo(uint32 ulRoll)
{
    bool bReturnValue = true;

    if(ucStudentsCount > 0U)
    {
        for(uint8 i = 0; i < ucStudentsCount; i++)
        {
            if(psStudentRecordList[i].pDetails->unRollNumber == ulRoll)
            {
                // Roll number already exist in StudentRecordList
                bReturnValue = false;
            }
        }
    }

    return bReturnValue;
}

//******************************.FUNCTION_HEADER.****************************** 
//Purpose : Get Student data from user and and check its validity
//Inputs  : 
//Outputs : pstInfo : struct that contains student data
//Return  : true  : if data received from user is valid
//          false : if any received data from user is invald
//Notes   :
//*****************************************************************************
bool studentAdd(_sStudent *pstInfo)
{
    bool bReturnValue = true;
    const uint8 *ucNameText = (const uint8 *)"Enter Student's Name: ";
    const uint8 *ucAddressText = (const uint8 *)"Enter Student's Address: ";
    do
    {
        // input NULL Check
        if (NULL == pstInfo)
        {
            (void)printf("pointer is NULL!\n");
            bReturnValue = false;
            break;
        }

        // Get Student Name
        if (false == studentGetString(ucNameText,
                                     &pstInfo->pcName))
        {
            (void)printf("error in getting student name\n");
            bReturnValue = false;
            break;
        }
        else
        {
            //skip
        }

        // Get roll number
        (void)printf("Enter Student's roll number: ");
        (void)scanf("%hu", &pstInfo->unRollNumber);
        if (false == studentCheckRollNo(pstInfo->unRollNumber))
        {
            (void)printf("Roll No Already Exist!\n");
            bReturnValue = false;
            break;
        }
        else
        {
            //skip
        }        

        // Get Marks
        (void)printf("Enter Marks of 10 subjects: ");
        for(uint8 i = 0; i < NUMBER_OF_SUBJECTS; i++)
        {
            (void)scanf("%hhu", &pstInfo->ucMarks[i]);
        }

        //validate input marks
        if (false == studentValidateMarks(&pstInfo->ucMarks[0]))
        {
            (void)printf("Mark validation failed!\n");
            bReturnValue = false;
            break;
        }
        else
        {
            // skip
        }

        // Get Address
        if (false == studentGetString(ucAddressText,
                                     &pstInfo->pcAddress))
        {
            (void)printf("error in getting student Address\n");
            bReturnValue = false;
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

//******************************.FUNCTION_HEADER.****************************** 
//Purpose : Calculate total marks for a student
//Inputs  : pstInfo : struct that contains student data
//Outputs : pulSum  : Total marks
//Return  : true  : on Successful Total Marks calculation
//          false : if any passed argument is NULL
//Notes   :
//*****************************************************************************
bool studentCalcSum(_sStudent *pstInfo, uint32 *pulSum)
{
    bool bReturnValue = true;
    uint32 ulLocSum = 0;

    do
    {
        // input pointer check;
        if ((NULL == pstInfo) || (NULL == pulSum))
        {
            (void)printf("pointer is NULL!\n");
            bReturnValue = false;
            break;
        }
   
        for(uint8 i = 0; i < NUMBER_OF_SUBJECTS; i++)
        {
            ulLocSum += pstInfo->ucMarks[i];
        }

        *pulSum = ulLocSum;
    }
    while (0);
    
    return bReturnValue;
}

//******************************.FUNCTION_HEADER.****************************** 
//Purpose : Calculate average marks for a student
//Inputs  : pstInfo : struct that contains student data
//Outputs : pfAvg   : Average marks
//Return  : true  : on Successful Average Marks calculation
//          false : if any passed argument is NULL
//Notes   :
//*****************************************************************************
bool studentCalcAverage(_sStudent *pstInfo, float *pfAvg){
    bool bReturnValue = true;
    uint32 ulLocSum = 0;
    
    do
    {
        // input pointer check;
        if ((NULL == pstInfo) || (NULL == pfAvg))
        {
            (void)printf("pointer is NULL!\n");
            bReturnValue = false;
            break;
        }

        // Calculate sum
        for(uint8 i = 0; i < NUMBER_OF_SUBJECTS; i++)
        {
            ulLocSum += pstInfo->ucMarks[i];
        }

        //caluclate average
        *pfAvg = (float)ulLocSum/NUMBER_OF_SUBJECTS;
    }
    while (0);

    return bReturnValue;    
}

//******************************.FUNCTION_HEADER.****************************** 
//Purpose : Calculate grades for each subject for a student
//Inputs  : pstInfo : struct that contains student data
//Outputs : 
//Return  : true  : on Successful Grades calculation
//          false : if any passed argument is NULL
//Notes   :
//*****************************************************************************
bool studentCalcGrades(const _sStudent* pstInfo)
{
    bool bReturnValue = true;
    do
    {
        // input pointer check;
        if ((NULL == pstInfo))
        {
            (void)printf("pointer is NULL!\n");
            bReturnValue = false;
            break;
        }

        // calculate grades
        /*
        A -> 90–100
        B -> 80–89
        C -> 70-79
        D -> 60-69
        E -> 50-59
        F -> 0-49
        */
        for(uint8 i = 0; i < NUMBER_OF_SUBJECTS; i++)
        {
            if ((pstInfo->ucMarks[i] >= 90U) && (pstInfo->ucMarks[i] <= 100U))
            {
                psStudentRecordList[ucStudentsCount].cGrade[i] = 'A';
            }
            else if ((pstInfo->ucMarks[i] >= 80U) && (pstInfo->ucMarks[i] < 90U))
            {
                psStudentRecordList[ucStudentsCount].cGrade[i] = 'B';
            } 
            else if ((pstInfo->ucMarks[i] >= 70U) && (pstInfo->ucMarks[i] < 80U))
            {
                psStudentRecordList[ucStudentsCount].cGrade[i] = 'C';
            }
            else if ((pstInfo->ucMarks[i] >= 60U) && (pstInfo->ucMarks[i] < 70U))
            {
                psStudentRecordList[ucStudentsCount].cGrade[i] = 'D';
            }
            else if ((pstInfo->ucMarks[i] >= 50U) && (pstInfo->ucMarks[i] < 60U))
            {
                psStudentRecordList[ucStudentsCount].cGrade[i] = 'E';
            }
            else
            {
                psStudentRecordList[ucStudentsCount].cGrade[i] = 'F';
            }                                      
        }
    }
    while (0);

    return bReturnValue; 
}

//******************************.FUNCTION_HEADER.****************************** 
//Purpose : Compare function to sort stuent data by Name
//Inputs  : pucNameA : name of student A
//          pucNameB : name of student B
//Outputs : 
//Return  : 0 : if both names are in lexographical ascending order
//          1 : if student A name lexographically lower than student B
//Notes   :
//*****************************************************************************
static int32 studentCompareNames(const uint8 *pucNameA, const uint8 *pucNameB) 
{  
    int32 lReturnValue = 0;
    uint32 i = 0U;

    while ((pucNameA[i] != 0U) && (pucNameB[i] != 0U) && 
            (pucNameA[i] == pucNameB[i]))
    {
        i++;
    }

    if ((pucNameA[i] != pucNameB[i]))
    {
        if ((pucNameA[i] != 0U) && (0U == pucNameB[i]))
        {
            lReturnValue = 1;
        }
        else if (pucNameA[i] > pucNameB[i])
        {
            lReturnValue = 1;
        }
        else
        {
            // skip
        }
        
    }
    return lReturnValue;
}

//******************************.FUNCTION_HEADER.****************************** 
//Purpose : to sort psStudentRecordList based on eType
//Inputs  : eType : key value that to find what need to be sorted
//Outputs : 
//Return  : 
//Notes   :
//*****************************************************************************
void studentSort(_eSortType eType)
{
    _sStudentRecord sTemp;
    uint8 ucFlag;

    for (uint8 i = 0U; i < ucStudentsCount; i++)
    {
        for (uint8 j = 0U; j < (ucStudentsCount - 1U); j++)
        {
            ucFlag = 0U;
            switch (eType)
            {
                case SORT_BY_NAME:
                {
                    if(1 == studentCompareNames(
                        psStudentRecordList[j].pDetails->pcName, 
                        psStudentRecordList[j + 1U].pDetails->pcName))
                    {
                        ucFlag = 1U;
                    }                   
                    break;
                }
                case SORT_BY_SUM:
                {
                    if (psStudentRecordList[j].unSumOfMarks > 
                        psStudentRecordList[j + 1U].unSumOfMarks)
                    {
                        ucFlag = 1U;
                    }
                    break;
                }
                case SORT_BY_ROLL_NO:
                {
                    if (psStudentRecordList[j].pDetails->unRollNumber > 
                        psStudentRecordList[j + 1U].pDetails->unRollNumber)
                    {
                        ucFlag = 1U;
                    }
                    break;
                }  
                case SORT_BY_RANK:
                {
                    if (psStudentRecordList[j].ucRank > 
                        psStudentRecordList[j + 1U].ucRank)
                    {
                        ucFlag = 1U;
                    }
                    break;
                } 
                default:
                {
                    (void)printf("Invalid Sort Option!\n");
                    break;
                }                             
            }

            if (1U == ucFlag)
            {
                sTemp = psStudentRecordList[j];
                psStudentRecordList[j] = psStudentRecordList[j + 1U];
                psStudentRecordList[j + 1U] = sTemp;
            }
        }
    }
}

//******************************.FUNCTION_HEADER.****************************** 
//Purpose : Calculate Rank for the student data in the list
//Inputs  : 
//Outputs : 
//Return  : 
//Notes   :
//*****************************************************************************
bool studentUpdateRank(void)
{
    if(ucStudentsCount == COUNT_ONE)
    {
        psStudentRecordList->ucRank = 1;
    }
    else
    {
        // Sort Student record list with sum of marks
        studentSort(SORT_BY_SUM);

        // update rank
        for (uint8 i = 0; i < ucStudentsCount; i++) 
        {
            // rank = index + 1
            if ((i > 0U) && 
                (psStudentRecordList[i].unSumOfMarks == 
                psStudentRecordList[i - 1U].unSumOfMarks)) 
            {
                // Give same rank for same marks
               psStudentRecordList[i].ucRank = 
                                            psStudentRecordList[i - 1U].ucRank;
            } 
            else 
            {
                psStudentRecordList[i].ucRank = i + 1U;
            }
        }
    }

    return true;
}

//******************************.FUNCTION_HEADER.****************************** 
//Purpose : To get number of student's data available in the list
//Inputs  : 
//Outputs : pulCount : Number of student's data available in list
//Return  : true   : on successful execution
//          false  : if input pointer is NULL
//Notes   :
//*****************************************************************************
bool studentGetCount(uint32 *pulCount)
{
    bool bReturnValue = true;   
    
    if(NULL == pulCount)
    {
        (void)printf("pointer is NULL!\n");
        bReturnValue = false;
    }
    else
    {
        *pulCount = ucStudentsCount;
    }

    return bReturnValue; 
}

//******************************.FUNCTION_HEADER.****************************** 
//Purpose : To get average mark of all student's data available in the list
//Inputs  : 
//Outputs : pucAvgMarks : Average marks of all student's
//Return  : true : on successful execution
//          false  : if input pointer is NULL
//Notes   :
//*****************************************************************************
bool studentGetAvgMarksOfSubjects(uint8 *pucAvgMarks)
{
    bool bReturnValue = true;  
    float fLocAverage = 0.0;
    
    if(NULL == pucAvgMarks)
    {
        (void)printf("pointer is NULL!\n");
        bReturnValue = false;
    }
    else if(0U == ucStudentsCount)
    {
        (void)printf("No Student data available to calculate average\n");
    }
    else
    {   
        for (uint8 i = 0; i < ucStudentsCount; i++)
        {
            fLocAverage += psStudentRecordList[i].fAverage;
        }

        // divide by the number of students
        fLocAverage = fLocAverage/(float)ucStudentsCount;

        *pucAvgMarks = (uint8)fLocAverage;
    }

    return bReturnValue; 
}

//******************************.FUNCTION_HEADER.****************************** 
//Purpose : Free dynamically allocated memory
//Inputs  : ucIndex: Index at which the allocated memroy should be freed
//Outputs : 
//Return  : true   : on successful execution
//          false  : if ucIndex is invalid
//Notes   :
//*****************************************************************************
bool studentDeleteData(uint8 ucIndex)
{
    bool bReturnValue = true;

    if(ucIndex > ucStudentsCount)
    {
        (void)printf("Invalid index!\n");
        bReturnValue = false;
    }
    else
    {
        // Free Adress
        free(psStudentRecordList[ucIndex].pDetails->pcAddress);

        // Free Name
        free(psStudentRecordList[ucIndex].pDetails->pcName);

        // Free Student Data
        free(psStudentRecordList[ucIndex].pDetails);
    }

    return bReturnValue;
}

//******************************.FUNCTION_HEADER.****************************** 
//Purpose : Delete data at an index in a array by replacing it with next data
//Inputs  : ucIndex: Index at which the data should be deleted
//Outputs : 
//Return  : true   : on successful execution
//          false  : if ucIndex is invalid
//Notes   :
//*****************************************************************************
bool studentSwapData(uint8 ucIndex)
{
    bool bReturnValue = true;

    if(ucIndex > ucStudentsCount)
    {
        (void)printf("Invalid index!\n");
        bReturnValue = false;
    }
    else
    {
        for(uint8 i = ucIndex; i < (ucStudentsCount - 1U); i++)
        {
            // swap the data
            psStudentRecordList[i] = psStudentRecordList[i + 1U];
        }
        // Decrease Student count by one
        (void)printf("Deleted Successfully\n");
        ucStudentsCount--;
    }

    return bReturnValue;
}

//******************************.FUNCTION_HEADER.****************************** 
//Purpose : Delete a student data in the list by name
//Inputs  : pucName: Name of the student data to delete
//Outputs : 
//Return  : true   : on successful execution
//          false  : if error occurs during data deletion
//Notes   :
//*****************************************************************************
bool studentDeleteByName(const uint8 *pucName)
{
    uint8 ucFlag = 0;
    bool bReturnValue = true;

    for(uint8 i = 0; i < ucStudentsCount; i++)
    {
        if(0U == ucFlag)
        {
            if(0 == 
                strcmp((const char *)psStudentRecordList[i].pDetails->pcName,
                            (const char *)pucName))
            {
                // delete the data at that index and free memory
                if(false == studentDeleteData(i))
                {
                    bReturnValue = false;
                }
                if(false == studentSwapData(i))
                {
                    bReturnValue = false;
                }
                ucFlag++;
                break;
            }
            else
            {
                // skip
            }
        }
        else
        {
            // skip
        }
    }
    if(0U == ucFlag)
    {
        (void)printf("Name not found!\n");
    }

    return bReturnValue;
}

//******************************.FUNCTION_HEADER.****************************** 
//Purpose : Delete a student data in the list by roll number
//Inputs  : ulRoll: roll number of the student data to delete
//Outputs : 
//Return  : true : on successful execution
//          false: if error occurs during data deletion
//Notes   :
//*****************************************************************************
bool studentDeleteByRoll(uint32 ulRoll)
{
    uint8 ucFlag = 0;
    bool bReturnValue = true;

    for(uint8 i = 0; i < ucStudentsCount; i++)
    {
        if(0U == ucFlag)
        {
            if(ulRoll == psStudentRecordList[i].pDetails->unRollNumber)
            {
                // delete the data at that index and free memory
                if(false == studentDeleteData(i))
                {
                    bReturnValue = false;
                }
                if(false == studentSwapData(i))
                {
                    bReturnValue = false;
                }
                ucFlag++;
                break;
            }
            else
            {
                // skip
            }
        }
        else
        {
            // skip
        }
    }

    if(0U == ucFlag)
    {
        (void)printf("Roll No not found!\n");
    }

    return bReturnValue;
}

//******************************.FUNCTION_HEADER.****************************** 
//Purpose : Delete all students data in the list
//Inputs  : 
//Outputs : 
//Return  : true   : on successful execution
//          false  : if error occurs during data deletion
//Notes   :
//*****************************************************************************
bool studentDeleteAll(void)
{
    bool bReturnValue = true;
    uint8 ucCount = ucStudentsCount;

    for(uint8 i = 0; i < ucCount; i++)
    {
        // delete the data at that index and free memory
        if (false == studentDeleteData(i))
        {
            (void)printf("Error while Deleting data\n");
        }
    }
    // Reset Student count and free Student list
    ucStudentsCount = 0;
    free(psStudentRecordList);
    psStudentRecordList = NULL;

    return bReturnValue;
}
// EOF 