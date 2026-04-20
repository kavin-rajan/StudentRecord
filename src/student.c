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
uint8 ucStudentsCount = 0;
_sStudentRecord *psStudentRecordList = NULL; 

//****************************** Local Functions ******************************
bool studentGetString(const uint8 *pDisplayText, uint8 **pcData);
static bool studentValidateMarks(const uint8 *pucMarks);
int32 studentCompareSum(const void *psRecordA, const void *psRecordB);
bool studentSwapData(uint8 ucIndex);
bool studentDeleteData(uint8 ucIndex);
static bool studentCheckRollNo(uint32 ulRoll);

//******************************.FUNCTION_HEADER.****************************** 
//Purpose : Get's a string from user, dynamically allocates memory based on 
//          string
//Inputs  : pucDisplayText : Text to display to user
//          pucData        : Pointer to String
//Outputs : 
//Return  : false: on Successful execution
//          true : if any error occurs during memory allocation  
//Notes   :
//***************************************************************************** 
bool studentGetString(const uint8 *pucDisplayText, uint8 **pucData)
{
    bool bReturnValue = false;
    uint8 ucBuffer[BUFFER_SIZE];

    do
    {
        if ((NULL == pucDisplayText) || (NULL == pucData))
        {
            (void)printf("pointer is NULL!\n");
            bReturnValue = true;
            break;
        }

        (void)printf("%s\n", pucDisplayText);
        (void)scanf(" %99[^\n]", ucBuffer);

        *pucData = 
        (uint8 *)malloc(strlen((const char *)ucBuffer) * sizeof(uint8));

        // Memory allocation check
        if(NULL == *pucData)
        {
            (void)printf("Error in allocating memory\n");
            bReturnValue = true;
            break;
        }
        else
        {
            // skip
        }

        strcpy((char *)*pucData, (const char *)ucBuffer);
    }
    while (0);

    return bReturnValue;
}

//******************************.FUNCTION_HEADER.****************************** 
//Purpose : To validate the marks given by user
//Inputs  : pucMarks : Pointer to array that contains marks of a student
//Outputs : 
//Return  : false: Marks are in valid range
//          true : Marks outside valid range 
//Notes   : valid marks : 0 to 100
//***************************************************************************** 
static bool studentValidateMarks(const uint8 *pucMarks)
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

        for(uint8 i = 0; i < NUMBER_OF_SUBJECTS; i++)
        {
            if(pucMarks[i] > MAX_MARKS)
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

//******************************.FUNCTION_HEADER.****************************** 
//Purpose : To check availability of roll number
//Inputs  : ulRoll : Roll number to check
//Outputs : 
//Return  : false: Roll number can be used
//          true : if Roll number is already available in StudentRecordList
//Notes   :
//*****************************************************************************
static bool studentCheckRollNo(uint32 ulRoll)
{
    bool bReturnValue = false;

    if(ucStudentsCount > 0U)
    {
        for(uint8 i = 0; i < ucStudentsCount; i++)
        {
            if(psStudentRecordList[i].pDetails->unRollNumber == ulRoll)
            {
                // Roll number already exist in StudentRecordList
                bReturnValue = true;
            }
        }
    }

    return bReturnValue;
}

//******************************.FUNCTION_HEADER.****************************** 
//Purpose : Get Student data from user and and check its validity
//Inputs  : 
//Outputs : pstInfo : struct that contains student data
//Return  : false: if data received from user is valid
//          true : if any received data from user is invald
//Notes   :
//*****************************************************************************
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
        if (true == studentGetString((uint8 *)"Enter Student's Name: ",
                                     &pstInfo->pcName))
        {
            (void)printf("error in getting student name\n");
            bReturnValue = true;
            break;
        }
        else
        {
            //skip
        }

        // Get roll number
        (void)printf("Enter Student's roll number: ");
        (void)scanf("%hu", &pstInfo->unRollNumber);
        if (true == studentCheckRollNo(pstInfo->unRollNumber))
        {
            (void)printf("Roll No Already Exist!\n");
            bReturnValue = true;
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
        if (true == studentGetString((uint8 *)"Enter Student's Address: ",
                                     &pstInfo->pcAddress))
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

//******************************.FUNCTION_HEADER.****************************** 
//Purpose : Calculate total marks for a student
//Inputs  : pstInfo : struct that contains student data
//Outputs : pulSum  : Total marks
//Return  : false: on Successful Total Marks calculation
//          true : if any passed argument is NULL
//Notes   :
//*****************************************************************************
bool studentCalcSum(_sStudent *pstInfo, uint32 *pulSum)
{
    bool bReturnValue = false;
    uint32 ulLocSum = 0;

    do
    {
        // input pointer check;
        if ((NULL == pstInfo) || (NULL == pulSum))
        {
            (void)printf("pointer is NULL!\n");
            bReturnValue = true;
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
//Return  : false: on Successful Average Marks calculation
//          true : if any passed argument is NULL
//Notes   :
//*****************************************************************************
bool studentCalcAverage(_sStudent *pstInfo, float *pfAvg){
    bool bReturnValue = false;
    uint32 ulLocSum = 0;
    
    do
    {
        // input pointer check;
        if ((NULL == pstInfo) || (NULL == pfAvg))
        {
            (void)printf("pointer is NULL!\n");
            bReturnValue = true;
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
//Return  : false: on Successful Grades calculation
//          true : if any passed argument is NULL
//Notes   :
//*****************************************************************************
bool studentCalcGrades(const _sStudent* pstInfo)
{
    bool bReturnValue = false;
    do
    {
        // input pointer check;
        if ((NULL == pstInfo))
        {
            (void)printf("pointer is NULL!\n");
            bReturnValue = true;
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
//Purpose : Compare function to sort stuent data by Total Marks
//Inputs  : psRecordA : struct that contains data of student A
//          psRecordB : struct that contains data of student B
//Outputs : 
//Return  : 0 : if both students total marks are equal
//          1 : if student A has lower mark than student B
//          -1: if student A has higher mark than student B
//Notes   :
//*****************************************************************************
int32 studentCompareSum(const void *psRecordA, const void *psRecordB) 
{ 
    int32 lReturnValue = 0;
    const _sStudentRecord *pslocRecordA = (_sStudentRecord *)psRecordA;
    const _sStudentRecord *pslocRecordB = (_sStudentRecord *)psRecordB;


    if (pslocRecordB->unSumOfMarks > pslocRecordA->unSumOfMarks)
    {
        lReturnValue = 1;
    } 
    else if (pslocRecordB->unSumOfMarks < pslocRecordA->unSumOfMarks)
    {
        lReturnValue = -1;
    } 
    else
    {
        //skip
    }

    return lReturnValue;
}

//******************************.FUNCTION_HEADER.****************************** 
//Purpose : Compare function to sort stuent data by Name
//Inputs  : psRecordA : struct that contains data of student A
//          psRecordB : struct that contains data of student B
//Outputs : 
//Return  : 0 : if both students Name are equal
//          1 : if student A name lexographically lower than student B
//          -1: if student A name lexographically higher than student B
//Notes   :
//*****************************************************************************
int32 studentCompareName(const void *psRecordA, const void *psRecordB) 
{  
    int32 lReturnValue = 0;
    const _sStudentRecord *pslocRecordA = (_sStudentRecord *)psRecordA;
    const _sStudentRecord *pslocRecordB = (_sStudentRecord *)psRecordB;


    lReturnValue = strcmp((const char *)pslocRecordA->pDetails->pcName, 
                          (const char *)pslocRecordB->pDetails->pcName);

    return lReturnValue;
}

//******************************.FUNCTION_HEADER.****************************** 
//Purpose : Compare function to sort stuent data by Rank
//Inputs  : psRecordA : struct that contains data of student A
//          psRecordB : struct that contains data of student B
//Outputs : 
//Return  : 0 : if both students rank are equal
//          1 : if student A has lower rank than student B
//          -1: if student A has higher rank than student B
//Notes   :
//*****************************************************************************
int32 studentCompareRank(const void *psRecordA, const void *psRecordB) 
{
    
    int32 lReturnValue = 0;
    const _sStudentRecord *pslocRecordA = (_sStudentRecord *)psRecordA;
    const _sStudentRecord *pslocRecordB = (_sStudentRecord *)psRecordB;


    if (pslocRecordB->ucRank > pslocRecordA->ucRank)
    {
        lReturnValue = -1;
    } 
    else if (pslocRecordB->ucRank < pslocRecordA->ucRank)
    {
        lReturnValue = 1;
    } 
    else
    {
        //skip
    }

    return lReturnValue;
}

//******************************.FUNCTION_HEADER.****************************** 
//Purpose : Compare function to sort stuent data by Roll number
//Inputs  : psRecordA : struct that contains data of student A
//          psRecordB : struct that contains data of student B
//Outputs : 
//Return  : 0 : if both students Roll number are equal
//          1 : if student A has lower roll number than student B
//          -1: if student A has higher roll number than student B
//Notes   :
//*****************************************************************************
int32 studentCompareRollNo(const void *psRecordA, const void *psRecordB) 
{
    
    int32 lReturnValue = 0;
    const _sStudentRecord *pslocRecordA = (_sStudentRecord *)psRecordA;
    const _sStudentRecord *pslocRecordB = (_sStudentRecord *)psRecordB;


    if (pslocRecordB->pDetails->unRollNumber > 
        pslocRecordA->pDetails->unRollNumber)
    {
        lReturnValue = -1;
    } 
    else if (pslocRecordB->pDetails->unRollNumber < 
             pslocRecordA->pDetails->unRollNumber)
    {
        lReturnValue = 1;
    } 
    else
    {
        //skip
    }

    return lReturnValue;
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
        qsort(psStudentRecordList, 
            ucStudentsCount, 
            sizeof(_sStudentRecord), 
            (__compar_fn_t)studentCompareSum);

        // update rank
        for (uint8 i = 0; i < ucStudentsCount; i++) 
        {
            // rank = index + 1
            if ((i > 0U) && 
                (psStudentRecordList[i].unSumOfMarks == 
                psStudentRecordList[i - 1U].unSumOfMarks)) 
            {
                // Give same rank for same marks
               psStudentRecordList[i].ucRank = psStudentRecordList[i - 1U].ucRank;
            } 
            else 
            {
                psStudentRecordList[i].ucRank = i + 1U;
            }
        }
    }

    return false;
}

//******************************.FUNCTION_HEADER.****************************** 
//Purpose : To get number of student's data available in the list
//Inputs  : 
//Outputs : pulCount : Number of student's data available in list
//Return  : false : on successful execution
//          true  : if input pointer is NULL
//Notes   :
//*****************************************************************************
bool studentGetCount(uint32 *pulCount)
{
    bool bReturnValue = false;   
    
    // pointer NULL Check
    if(NULL == pulCount)
    {
        (void)printf("pointer is NULL!\n");
        bReturnValue = true;
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
//Return  : false : on successful execution
//          true  : if input pointer is NULL
//Notes   :
//*****************************************************************************
bool studentGetAvgMarksOfSubjects(uint8 *pucAvgMarks)
{
    bool bReturnValue = false;  
    float fLocAverage = 0.0;
    
    // pointer NULL Check
    if(NULL == pucAvgMarks)
    {
        (void)printf("pointer is NULL!\n");
        bReturnValue = true;
    }
    else if(0U == ucStudentsCount)
    {
        (void)printf("No Student data available to calculate average\n");
    }
    else
    {
        // find total sum of average marks
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
//Return  : false : on successful execution
//          true  : if ucIndex is invalid
//Notes   :
//*****************************************************************************
bool studentDeleteData(uint8 ucIndex)
{
    bool bReturnValue = false;

    if(ucIndex > ucStudentsCount)
    {
        (void)printf("Invalid index!\n");
        bReturnValue = true;
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
//Return  : false : on successful execution
//          true  : if ucIndex is invalid
//Notes   :
//*****************************************************************************
bool studentSwapData(uint8 ucIndex)
{
    bool bReturnValue = false;

    if(ucIndex > ucStudentsCount)
    {
        (void)printf("Invalid index!\n");
        bReturnValue = true;
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
//Return  : false : on successful execution
//          true  : if error occurs during data deletion
//Notes   :
//*****************************************************************************
bool studentDeleteByName(const uint8 *pucName)
{
    uint8 ucFlag = 0;
    bool bReturnValue = false;

    for(uint8 i = 0; i < ucStudentsCount; i++)
    {
        if(0U == ucFlag)
        {
            if(0 == 
                strcmp((const char *)psStudentRecordList[i].pDetails->pcName,
                            (const char *)pucName))
            {
                // delete the data at that index and free memory
                if(true == studentDeleteData(i))
                {
                    bReturnValue = true;
                }
                if(true == studentSwapData(i))
                {
                    bReturnValue = true;
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
//Return  : false : on successful execution
//          true  : if error occurs during data deletion
//Notes   :
//*****************************************************************************
bool studentDeleteByRoll(uint32 ulRoll)
{
    uint8 ucFlag = 0;
    bool bReturnValue = false;

    for(uint8 i = 0; i < ucStudentsCount; i++)
    {
        if(0U == ucFlag)
        {
            if(ulRoll == psStudentRecordList[i].pDetails->unRollNumber)
            {
                // delete the data at that index and free memory
                if(true == studentDeleteData(i))
                {
                    bReturnValue = true;
                }
                if(true == studentSwapData(i))
                {
                    bReturnValue = true;
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
//Return  : false : on successful execution
//          true  : if error occurs during data deletion
//Notes   :
//*****************************************************************************
bool studentDeleteAll(void)
{
    bool bReturnValue = false;
    uint8 ucCount = ucStudentsCount;

    for(uint8 i = 0; i < ucCount; i++)
    {
        // delete the data at that index and free memory
        if (true == studentDeleteData(i))
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