#ifndef _STUDENT_H_ 
#define _STUDENT_H_ 
 
//******************************* Include Files ******************************* 
#include "types.h"

//******************************* Global Types ******************************** 
#define NUMBER_OF_SUBJECTS 10
#define BUFFER_SIZE 200

// structure that holds student info
typedef struct __sStudent
{
    char *pcName;
    uint16 unRollNumber;
    uint8 ucMarks[NUMBER_OF_SUBJECTS];
    char *pcAddress;
}_sStudent;

// Struct for Student record
typedef struct __sStudentRecord
{
    _sStudent *pDetails;
    uint16 unSumOfMarks;
    float average;
    char cGrade[10];
    uint8 ucRank;
}_sStudentRecord;

//***************************** Global Constants ****************************** 
 
//***************************** Global Variables ****************************** 
 
//**************************** Forward Declarations *************************** 
bool studentAdd(_sStudent* pstInfo);

//support functions
bool studentGetString(char *pDisplayText, char **pcData);
bool studentValidateMarks(uint8 *pucMarks);
#endif // _STUDENT_H_ 
// EOF 