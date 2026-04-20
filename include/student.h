//**************************** student.h ************************************
//  Copyright (c) 2026 Trenser 
//  All Rights Reserved 
//***************************************************************************** 
// 
// Summary    : header file for Student.c
// Note       : 
// Author     : Kavin M
// Date       : 17.04.2026
// 
//***************************************************************************** 

#ifndef STUDENT_H_ 
#define STUDENT_H_ 
 
//******************************* Include Files ******************************* 
#include "types.h"

//******************************* Global Types ******************************** 
#define NUMBER_OF_SUBJECTS 10U
#define MAX_DATA_SIZE 50 // Buffer size to store student data
#define BUFFER_SIZE 100
#define MAX_MARKS 100U
#define COUNT_ONE 1U


// structure that holds student info
typedef struct __sStudent
{
    uint8 *pcName;
    uint16 unRollNumber;
    uint8 ucMarks[NUMBER_OF_SUBJECTS];
    uint8 *pcAddress;
}_sStudent;

// Struct for Student record
typedef struct __sStudentRecord
{
    _sStudent *pDetails;
    uint32 unSumOfMarks;
    float fAverage;
    char cGrade[NUMBER_OF_SUBJECTS];
    uint8 ucRank;
}_sStudentRecord;

//***************************** Global Constants ****************************** 
 
//***************************** Global Variables ****************************** 
extern _sStudentRecord *psStudentRecordList; 
extern uint8 ucStudentsCount;
//**************************** Forward Declarations *************************** 
bool studentAdd(_sStudent *pstInfo);
bool studentCalcSum(_sStudent *pstInfo, uint32 *pulSum);
bool studentCalcAverage(_sStudent *pstInfo, float *pfAvg);
bool studentCalcGrades(const _sStudent* pstInfo);
bool studentUpdateRank(void);
bool studentGetCount(uint32* pulCount);
bool studentGetAvgMarksOfSubjects(uint8* pucAvgMarks);
bool studentDeleteByName(const uint8* pucName);
bool studentDeleteByRoll(uint32 ulRoll);
bool studentDeleteAll(void);
int32 studentCompareRank(const void *psRecordA, const void *psRecordB);
int32 studentCompareRollNo(const void *psRecordA, const void *psRecordB);
int32 studentCompareName(const void *psRecordA, const void *psRecordB); 
#endif // STUDENT_H_ 
// EOF 