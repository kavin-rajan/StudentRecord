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

//****************************** Local Functions ******************************
static bool menuDisplayStudents(const _sStudentRecord *psStudentlist, uint8 ucCount);
static bool menuStudentOverview(void);
static bool menuAddStudent(void);
static bool menuListStudent(void);
static bool menuDeleteStudent(void);

static bool menuListSearchByName(void);
static bool menuListSortByName(void);		
static bool menuListSortByRoll(void);		
static bool menuListSortByRank(void);

static bool menuDeleteByName(void);
static bool menuDeleteByRoll(void);
static bool menuDeleteAll(void);

//******************************.FUNCTION_HEADER.****************************** 
//Purpose : Display main menu and based on user option respective function is 
//          called.
//Inputs  : 
//Outputs : 
//Return  : false: on Successful execution
//Notes   :
//***************************************************************************** 
bool menuMain(void)
{
    uint8 ucOption = 0;
    bool bReturnValue = false;

    while (1)
    {
        (void)printf("Select one of the options:\n \
            1: StudentOverview\n \
            2: AddStudent\n \
            3: ListStudent\n \
            4: DeleteStudent\n");
        (void)scanf("%hhu", &ucOption);

        switch (ucOption)
        {
            case 1:
            {
                (void)menuStudentOverview();
                break;
            }
            case 2:
            {
                (void)menuAddStudent();
                break;
            }
            case 3:
            {
                (void)menuListStudent();
                break;
            }
            case 4:
            {
                (void)menuDeleteStudent();
                break;
            }
            default:
            {
                (void)printf("Enter a valid option: \n");
            }
        }
    }

    return bReturnValue;
}

//******************************.FUNCTION_HEADER.******************************
//Purpose : Displays Total Number of students and their Average Marks
//Inputs  : 
//Outputs : 
//Return  : false: on Successful execution
//          true : if an error occurs druing Average Mark Calculation
//Notes   :
//***************************************************************************** 
static bool menuStudentOverview(void)
{
    bool bReturnValue = false;
    uint8 ucLocAvgMarks = 0;   

    if(0U == ucStudentsCount)
    {
        (void)printf("No Data available to display\n");
    }
    else
    {
        if (true == studentGetAvgMarksOfSubjects(&ucLocAvgMarks))
        {
            (void)printf("Error while calculating Average Marks!\n");
            bReturnValue = true;
        }
        else
        {
            // Display student overview
            (void)printf("\n%-20s | %-12s\n", "TotalNoOfStudents",
                         "AverageMarks");
            (void)printf("-----------------------------------------------\n");

            (void)printf("%-20hhu | %hhu\n", ucStudentsCount, ucLocAvgMarks);
            (void)printf("-----------------------------------------------\n");
        }

    }
    return bReturnValue;
}

//******************************.FUNCTION_HEADER.****************************** 
//Purpose : Adds a Student's data to database
//Inputs  : 
//Outputs : 
//Return  : false: on Successful execution
//          true : if any error occurs druing student data addition
//Notes   :
//***************************************************************************** 
static bool menuAddStudent(void)
{
    bool bReturnValue = false;
    static uint8 ucCapacity = MAX_DATA_SIZE;

    do
    { 
        // allocate if no student data present
        if (NULL == psStudentRecordList)
        {
            psStudentRecordList = 
            (_sStudentRecord *)malloc(ucCapacity * sizeof(_sStudentRecord));

            // memory allocation check
            if(NULL == psStudentRecordList)
            {
                (void)printf("Memory allocation error!\n");
                bReturnValue = true;
                break;                
            }
        }

        // allocate memory
        psStudentRecordList[ucStudentsCount].pDetails = 
                                        (_sStudent *)malloc(sizeof(_sStudent));
        if (NULL == psStudentRecordList[ucStudentsCount].pDetails)
        {
            (void)printf("Memory allocation error!\n");
            bReturnValue = true;
            break;
        }

        // Get Student info and Add to list
        if(true == studentAdd(psStudentRecordList[ucStudentsCount].pDetails))
        {
            (void)printf("Error During Student addition!\n");
            bReturnValue = true;
            break;
        }

        // calculate sum of marks
        if(true == studentCalcSum(psStudentRecordList[ucStudentsCount].pDetails, 
                            &psStudentRecordList[ucStudentsCount].unSumOfMarks))
        {
            (void)printf("Error During sum calculation!\n");
            bReturnValue = true;
            break;
        }

        // calculate sum of marks
        if(true == 
            studentCalcAverage(psStudentRecordList[ucStudentsCount].pDetails, 
                                &psStudentRecordList[ucStudentsCount].fAverage))
        {
            (void)printf("Error During Average Calculation!\n");
            bReturnValue = true;
            break;
        }

        // Calculate Grade
        if(true == 
            studentCalcGrades(psStudentRecordList[ucStudentsCount].pDetails))
        {
            (void)printf("Error During Grade Calculation!\n");
            bReturnValue = true;
            break;
        }
        // increase the student count
        ucStudentsCount ++;  
        
        // update Rank
        if(true == studentUpdateRank())
        {
            (void)printf("Error During Rank update!\n");
            bReturnValue = true;
            break;
        }        

    } 
    while (0);

    return bReturnValue;

}

//******************************.FUNCTION_HEADER.****************************** 
//Purpose : Displays Student data from record
//Inputs  : psStudentlist: List that contains student data
//          ucCount      : Number of students to display
//Outputs : 
//Return  : false: on Successful execution
//          true : if input pointer is NULL
//Notes   :
//***************************************************************************** 
static bool menuDisplayStudents(const _sStudentRecord *psStudentlist, uint8 ucCount) 
{
    bool bReturnValue = false;

    if(NULL == psStudentlist)
    {
        (void)printf("pointer is NULL!\n");
        bReturnValue = true;
    }
    else if (0U == ucCount)
    {
        (void)printf("No data to display.\n");
    }
    else
    {
        (void)printf("\n%-15s | %-6s | %-10s | %-4s\n",
             "Name", "RollNo", "TotalMarks", "Rank");
        (void)printf("--------------------------------------------\n");

        for (uint8 i = 0; i < ucCount; i++) 
        {
            (void)printf("%-15s | %-6hu | %-10lu | %-4hhu\n", 
                    psStudentlist[i].pDetails->pcName, 
                    psStudentlist[i].pDetails->unRollNumber,
                    psStudentlist[i].unSumOfMarks, 
                    psStudentlist[i].ucRank);
        }
        (void)printf("--------------------------------------------\n");
    }

    return bReturnValue;
}

//******************************.FUNCTION_HEADER.****************************** 
//Purpose : Searches student data by name and displays it.
//Inputs  : 
//Outputs : 
//Return  : false: on Successful execution
//          true : if error occurs during Student data display 
//Notes   :
//***************************************************************************** 
static bool menuListSearchByName(void)
{
    uint8 ucFlag = 0;
    uint8 ucBuffer[BUFFER_SIZE];
    bool bReturnValue = false;

    // get the Student's name 
    (void)printf("Enter Student's name to get data: \n");
    (void)scanf(" %99[^\n]", ucBuffer);

    for(uint8 i = 0; i < ucStudentsCount; i++)
    {
        if(0 == strcmp((const char *)psStudentRecordList[i].pDetails->pcName,
                         (const char *)ucBuffer))
        {
            // Display the student data
            bReturnValue = menuDisplayStudents(&psStudentRecordList[i], 
                                                COUNT_ONE);
            ucFlag++;
            break;
        }
    }
    if(0U == ucFlag)
    {
        (void)printf("Name not found!\n");
    }
    return bReturnValue;
}

//******************************.FUNCTION_HEADER.****************************** 
//Purpose : Sorts student data by name and displays them.
//Inputs  : 
//Outputs : 
//Return  : false: on Successful execution
//          true : if error occurs during Student data display 
//Notes   :
//***************************************************************************** 
static bool menuListSortByName(void)
{
    bool bReturnValue = false;

    // Sort Student record list with sum of marks
    qsort(psStudentRecordList, 
        ucStudentsCount, 
        sizeof(_sStudentRecord), 
        (__compar_fn_t)studentCompareName);

    //Display the list of students
    bReturnValue = menuDisplayStudents(psStudentRecordList, ucStudentsCount);

    return bReturnValue;
}	

//******************************.FUNCTION_HEADER.****************************** 
//Purpose : Sorts student data by roll number and displays them.
//Inputs  : 
//Outputs : 
//Return  : false: on Successful execution
//          true : if error occurs during Student data display 
//Notes   :
//***************************************************************************** 
static bool menuListSortByRoll(void)
{
    bool bReturnValue = false;

    // Sort Student record list with sum of marks
    qsort(psStudentRecordList,
         ucStudentsCount,
         sizeof(_sStudentRecord),
         (__compar_fn_t)studentCompareRollNo);

    //Display the list of students
    bReturnValue = menuDisplayStudents(psStudentRecordList, ucStudentsCount);

    return bReturnValue;
}

//******************************.FUNCTION_HEADER.****************************** 
//Purpose : Sorts student data by rank and displays them.
//Inputs  : 
//Outputs : 
//Return  : false: on Successful execution
//          true : if error occurs during Student data display 
//Notes   :
//***************************************************************************** 			
static bool menuListSortByRank(void)
{
    bool bReturnValue = false;

    // Sort Student record list with sum of marks
    qsort(psStudentRecordList, 
        ucStudentsCount, 
        sizeof(_sStudentRecord), 
        (__compar_fn_t)studentCompareRank);

    //Display the list of students
    bReturnValue = menuDisplayStudents(psStudentRecordList, ucStudentsCount);

    return bReturnValue;
}	

//******************************.FUNCTION_HEADER.****************************** 
//Purpose : Displays a menu that allows user to select an option to Search
//Inputs  : 
//Outputs : 
//Return  : false: on Successful execution
//          true : if error occurs in the selected option
//Notes   :
//***************************************************************************** 
static bool menuListStudent(void)
{
    bool bReturnValue = false;

    uint8 ucOption = 0;
    if(0U == ucStudentsCount)
    {
        (void)printf("---No Data available to display---\n");
    }
    else
    {
        (void)printf("Select one option to search:\n \
            1: Search by name\n \
            2: List all by name\n \
            3: List all by roll number\n \
            4: list all by rank\n");
        (void)scanf("%hhu", &ucOption);

        switch (ucOption)
        {
            case 1:
            {
                bReturnValue = menuListSearchByName();
                break;
            }
            case 2:
            {
                bReturnValue = menuListSortByName();
                break;
            }
            case 3:
            {
                bReturnValue = menuListSortByRoll();
                break;
            }
            case 4:
            {
                bReturnValue = menuListSortByRank();
                break;
            }
            default:
            {
                (void)printf("Enter a valid option: \n");
            }
        }
    }

    return bReturnValue;
}

//******************************.FUNCTION_HEADER.****************************** 
//Purpose : Displays a menu that allows user to select an option to Delete
//Inputs  : 
//Outputs : 
//Return  : false: on Successful execution
//          true : if error occurs in the selected option 
//Notes   :
//***************************************************************************** 
static bool menuDeleteStudent(void)
{
    bool bReturnValue = false;

    uint8 ucOption = 0;

    if(0U == ucStudentsCount)
    {
        (void)printf("---No Data available to delete!---\n");
    }
    else
    {
        (void)printf("Select one option to delete:\n \
        1: Delete by name\n \
        2: Delete by roll number\n \
        3: Delete all Student data\n");
        (void)scanf("%hhu", &ucOption);

        switch (ucOption)
        {
            case 1:
            {
                bReturnValue = menuDeleteByName();
                break;
            }
            case 2:
            {
                bReturnValue = menuDeleteByRoll();
                break;
            }
            case 3:
            {
                bReturnValue = menuDeleteAll();
                break;
            }
            default:
            {
                (void)printf("Enter a valid option: \n");
            }
        }
    }

    return bReturnValue;
}

//******************************.FUNCTION_HEADER.****************************** 
//Purpose : Get's Student name from user and delete the data from list
//Inputs  : 
//Outputs : 
//Return  : false: on Successful execution
//          true : if error occurs during Student data deletion 
//Notes   :
//***************************************************************************** 
static bool menuDeleteByName(void)
{

    uint8 ucBuffer[BUFFER_SIZE];
    bool bReturnValue = false;

    // get the Student's name 
    (void)printf("Enter Student's name to delete: \n");
    (void)scanf(" %99[^\n]", ucBuffer);

    bReturnValue = studentDeleteByName(ucBuffer);
    return bReturnValue;
}

//******************************.FUNCTION_HEADER.****************************** 
//Purpose : Get's roll number from user and delete the data from list
//Inputs  : 
//Outputs : 
//Return  : false: on Successful execution
//          true : if error occurs during Student data deletion 
//Notes   :
//***************************************************************************** 
static bool menuDeleteByRoll(void)
{
    uint32 ulLocRollNo = 0;
    bool bReturnValue = false;

    // get the Student's roll No 
    (void)printf("Enter Student's Roll No. to delete: \n");
    (void)scanf("%lu", &ulLocRollNo);

    if (true == studentDeleteByRoll(ulLocRollNo))
    {
        bReturnValue = true;
    }

    return bReturnValue;
}

//******************************.FUNCTION_HEADER.****************************** 
//Purpose : Delete all data stored 
//Inputs  : 
//Outputs : 
//Return  : false: on Successful execution
//          true : if error occurs during Student data deletion 
//Notes   :
//***************************************************************************** 
static bool menuDeleteAll(void)
{
    bool bReturnValue = false;
    
    bReturnValue = studentDeleteAll();

    return bReturnValue;
}	
// EOF 