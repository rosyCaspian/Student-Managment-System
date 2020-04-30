#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Student
{
    int id;
    char *name;
    char *gender;
    char *roomNum;
    char *phoneNum;
    struct Student *next;
} Student;

typedef struct Score
{
    int id;
    char *courseNum;
    char *courseName;
    int credit;
    int usualScore;
    int experimentScore;
    int paperScore;
    float generalScore;
    float finalScore;
    struct Score *next;
} Score;

// 函数声明
void _initStudent();
void _initScore();
void _analysisStudentStr(char *str, Student *index);
void _analysisScoreStr(char *str, Score *index);
void _init();
void _destroyStudent(Student *index);
void _destroyScore(Score *index);
void _quit();
void appendStudent(Student index);
void appendScore(Score index);
int convertNum(char *index);
void counGeneraAndFinalScore(Score *index);
void save();
Student *studentSearchById(int id);
Student *studentSearchByRoomNum(char *roomNum);
Score *scoreSearchById(int id);
void deleteById(int id);
void sortByScore(int isReversed);

// 全局变量
Student *pStudent = NULL;
Score *pScore = NULL;

void _initStudent()
{
    pStudent = (Student *)malloc(sizeof(Student));
    pStudent->next = NULL;
}

void _initScore()
{
    pScore = (Score *)malloc(sizeof(Score));
    pScore->next = NULL;
}

void _init()
{
    FILE *fpStudent = NULL;
    FILE *fpScore = NULL;
    if (!((fpStudent = fopen("A.TXT", "r")) && (fpScore = fopen("B.TXT", "r"))))
    {
        printf("Fail to open file!\n");
        exit(0); //退出程序（结束程序）
    }
    _initScore();
    _initStudent();

    char studentLine[1024];
    char scoreLine[1024];
    Student tempStudent;
    Score tempScore;

    while (!feof(fpStudent))
    {
        fgets(studentLine, 1024, fpStudent);
        _analysisStudentStr(studentLine, &tempStudent);
        appendStudent(tempStudent);
    }

    while (!feof(fpScore))
    {
        fgets(scoreLine, 1024, fpScore);
        _analysisScoreStr(scoreLine, &tempScore);
        appendScore(tempScore);
    }

    fclose(fpStudent);
    fclose(fpScore);
}

void _analysisStudentStr(char *str, Student *index)
{
    int num, k, j, i = 0;
    char tempStr[20];

    // id
    if (str[i] == '0')
        i++;
    for (k = 0; str[i] != ' '; i++)
        tempStr[k++] = str[i];
    tempStr[k] = '\0';
    index->id = convertNum(tempStr);

    // name
    for (i++, k = 0; str[i] != ' '; i++)
        tempStr[k++] = str[i];
    tempStr[k] = '\0';
    index->name = (char *)malloc(sizeof(char) * k + 1);
    strcpy(index->name, tempStr);

    // gender
    for (i++, k = 0; str[i] != ' '; i++)
        tempStr[k++] = str[i];
    tempStr[k] = '\0';
    index->gender = (char *)malloc(sizeof(char) * k + 1);
    strcpy(index->gender, tempStr);

    // roomNum
    for (i++, k = 0; str[i] != ' '; i++)
        tempStr[k++] = str[i];
    tempStr[k] = '\0';
    index->roomNum = (char *)malloc(sizeof(char) * k + 1);
    strcpy(index->roomNum, tempStr);

    // phoneNum
    for (i++, k = 0; (str[i] != '\0') && (str[i] != '\n'); i++)
        tempStr[k++] = str[i];
    tempStr[k] = '\0';
    index->phoneNum = (char *)malloc(sizeof(char) * k + 1);
    strcpy(index->phoneNum, tempStr);
}

void _analysisScoreStr(char *str, Score *index)
{
    int num, k, j, i = 0;
    char tempStr[20];

    // id
    if (str[i] == '0')
        i++;
    for (k = 0; str[i] != ' '; i++)
        tempStr[k++] = str[i];
    tempStr[k] = '\0';
    index->id = convertNum(tempStr);

    // courseNum
    for (i++, k = 0; str[i] != ' '; i++)
        tempStr[k++] = str[i];
    tempStr[k] = '\0';
    index->courseNum = (char *)malloc(sizeof(char) * k + 1);
    strcpy(index->courseNum, tempStr);

    // courseName
    for (i++, k = 0; str[i] != ' '; i++)
        tempStr[k++] = str[i];
    tempStr[k] = '\0';
    index->courseName = (char *)malloc(sizeof(char) * k + 1);
    strcpy(index->courseName, tempStr);

    // credit
    for (i++, k = 0; str[i] != ' '; i++)
        tempStr[k++] = str[i];
    tempStr[k] = '\0';
    index->credit = convertNum(tempStr);

    // usualScore
    for (i++, k = 0; str[i] != ' '; i++)
        tempStr[k++] = str[i];
    tempStr[k] = '\0';
    index->usualScore = convertNum(tempStr);

    // experimentScore
    for (i++, k = 0; str[i] != ' '; i++)
        tempStr[k++] = str[i];
    tempStr[k] = '\0';
    if (strcmp(tempStr, "-1") == 0)
        index->experimentScore = -1;
    else
        index->experimentScore = convertNum(tempStr);

    // paperScore
    for (i++, k = 0; (str[i] != '\0') && (str[i] != '\n'); i++)
        tempStr[k++] = str[i];
    tempStr[k] = '\0';
    index->paperScore = convertNum(tempStr);

    // genera and finalScore
    counGeneraAndFinalScore(index);
}

void _destroyStudent(Student *index)
{
    Student *pTemp = NULL;
    while (index)
    {
        pTemp = index->next;
        if (index->name)
            free(index->name);
        if (index->gender)
            free(index->gender);
        if (index->roomNum)
            free(index->roomNum);
        if (index->phoneNum)
            free(index->phoneNum);
        free(index);
        index = pTemp;
    }
}

void _destroyScore(Score *index)
{
    Score *pTemp = NULL;
    while (index)
    {
        pTemp = index->next;
        if (index->courseNum)
            free(index->courseNum);
        if (index->courseName)
            free(index->courseName);
        free(index);
        index = pTemp;
    }
}

void _quit()
{
    save();
    _destroyStudent(pStudent);
    _destroyScore(pScore);
}

int convertNum(char *index)
{
    int i, num;
    for (i = num = 0; index[i] != '\0'; i++)
    {
        num *= 10;
        num += (index[i] - 48);
    }
    return num;
}

void counGeneraAndFinalScore(Score *index)
{

    if (index->experimentScore == -1)
        index->generalScore = index->usualScore * 0.3 + index->paperScore * 0.7;
    else
        index->generalScore = index->usualScore * 0.15 + index->experimentScore * 0.15 + index->paperScore * 0.7;

    if (index->generalScore > 60)
    {
        if (index->generalScore > 70)
        {
            if (index->generalScore > 80)
            {
                if (index->generalScore > 90)
                    index->finalScore = index->credit;
                else
                    index->finalScore = index->credit * 0.8;
            }
            else
                index->finalScore = index->credit * 0.75;
        }
        else
            index->finalScore = index->credit * 0.6;
    }
    else
        index->finalScore = 0;
}

void appendStudent(Student index)
{
    Student *pTemp = pStudent;

    while (pTemp->next)
        pTemp = pTemp->next;

    pTemp->next = (Student *)malloc(sizeof(Student));
    pTemp->next->id = index.id;
    pTemp->next->name = index.name;
    pTemp->next->gender = index.gender;
    pTemp->next->roomNum = index.roomNum;
    pTemp->next->phoneNum = index.phoneNum;
    pTemp->next->next = NULL;
}

void appendScore(Score index)
{
    Score *pTemp = pScore;

    while (pTemp->next)
        pTemp = pTemp->next;

    pTemp->next = (Score *)malloc(sizeof(Score));
    pTemp->next->id = index.id;
    pTemp->next->courseName = index.courseName;
    pTemp->next->courseNum = index.courseNum;
    pTemp->next->credit = index.credit;
    pTemp->next->usualScore = index.usualScore;
    pTemp->next->experimentScore = index.experimentScore;
    pTemp->next->paperScore = index.paperScore;
    pTemp->next->generalScore = index.generalScore;
    pTemp->next->finalScore = index.finalScore;
    pTemp->next->next = NULL;
}

void save()
{
    FILE *fpStudent = NULL;
    FILE *fpScore = NULL;
    if (!((fpStudent = fopen("A.TXT", "w")) && (fpScore = fopen("B.TXT", "w"))))
    {
        printf("Fail to open file!\n");
        exit(0); //退出程序（结束程序）
    }

    Student *pTempStudent = pStudent->next;
    Score *pTempScore = pScore->next;

    while (pTempStudent)
    {
        char *formatStr = (pTempStudent->id <= 9 ? "0%d %s %s %s %s" : "%d %s %s %s %s");
        fprintf(fpStudent, formatStr, pTempStudent->id, pTempStudent->name, pTempStudent->gender, pTempStudent->roomNum, pTempStudent->phoneNum);
        if (pTempStudent->next != NULL)
            fputc('\n', fpStudent);
        pTempStudent = pTempStudent->next;
    }

    while (pTempScore)
    {
        char *formatStr = (pTempScore->id <= 9 ? "0%d %s %s %d %d %d %d" : "%d %s %s %d %d %d %d");
        fprintf(fpScore, formatStr, pTempScore->id, pTempScore->courseNum, pTempScore->courseName, pTempScore->credit, pTempScore->usualScore, pTempScore->experimentScore, pTempScore->paperScore);
        if (pTempScore->next != NULL)
            fputc('\n', fpScore);
        pTempScore = pTempScore->next;
    }

    fclose(fpStudent);
    fclose(fpScore);
}

Student *studentSearchById(int id)
{
    Student *pTemp = pStudent->next;
    while (pTemp)
    {
        if (pTemp->id == id)
            return pTemp;
        pTemp = pTemp->next;
    }
    return NULL;
}

Student *studentSearchByRoomNum(char *roomNum)
{
    Student *pTemp = pStudent->next;
    Student *pResult = (Student *)malloc(sizeof(Student));
    Student *pResultTemp = pResult;
    pResult->next = NULL;

    while (pTemp)
    {
        if (strcmp(pTemp->roomNum, roomNum) == 0)
        {
            pResultTemp->next = (Student *)malloc(sizeof(Student));
            pResultTemp->next->id = pTemp->id;
            pResultTemp->next->name = pTemp->name;
            pResultTemp->next->gender = pTemp->gender;
            pResultTemp->next->roomNum = pTemp->roomNum;
            pResultTemp->next->phoneNum = pTemp->phoneNum;
            pResultTemp->next->next = NULL;
            pResultTemp = pResultTemp->next;
        }
        pTemp = pTemp->next;
    }
    return pResult;
}

Score *scoreSearchById(int id)
{
    Score *pTemp = pScore->next;
    Score *pResult = (Score *)malloc(sizeof(Score));
    Score *pResultTemp = pResult;

    while (pTemp)
    {
        if (pTemp->id == id)
        {
            pResultTemp->next = (Score *)malloc(sizeof(Score));
            pResultTemp->next->id = pTemp->id;
            pResultTemp->next->courseNum = pTemp->courseNum;
            pResultTemp->next->courseName = pTemp->courseName;
            pResultTemp->next->credit = pTemp->credit;
            pResultTemp->next->usualScore = pTemp->usualScore;
            pResultTemp->next->experimentScore = pTemp->experimentScore;
            pResultTemp->next->paperScore = pTemp->paperScore;
            pResultTemp->next->generalScore = pTemp->generalScore;
            pResultTemp->next->generalScore = pTemp->generalScore;
            pResultTemp = pResultTemp->next;
        }
        pTemp = pTemp->next;
    }

    return pResult;
}

void deleteById(int id)
{
    Student *pTempStudent = pStudent;
    Score *pTempScore = pScore;

    while (pTempStudent->next)
    {
        if (pTempStudent->next->id == id)
        {
            Student *freeTemp = pTempStudent->next;
            pTempStudent->next = pTempStudent->next->next;
            free(freeTemp->name);
            free(freeTemp->gender);
            free(freeTemp->roomNum);
            free(freeTemp->phoneNum);
            free(freeTemp);
            break;
        }
        pTempStudent = pTempStudent->next;
    }

    while (pTempScore->next)
    {
        if (pTempScore->next->id == id)
        {
            Score *freeTemp = pTempScore->next;
            pTempScore->next = pTempScore->next->next;
            free(freeTemp->courseNum);
            free(freeTemp->courseName);
            free(freeTemp);
            continue;
        }
        pTempScore = pTempScore->next;
    }
}

void sortByScore(int isReversed)
{
    Score *pTemp, *pTempLast, *pNow, *pLast;
    Score *pUse = pScore;
    int n = 0;
    while (pUse->next)
    {
        pUse = pUse->next;
        n++;
    }

    for (int i = 0; i < n; i++)
    {
        pLast = pScore;
        pNow = pScore->next;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (isReversed == 0)
            {
                if (pNow->generalScore > pNow->next->generalScore)
                {
                    Score *pT = pNow;
                    pLast->next = pNow->next;
                    pT->next = pLast->next->next;
                    pLast->next->next = pT;
                }
                else
                    pNow = pNow->next;
            }
            else if (isReversed == 1)
            {
                if (pNow->generalScore < pNow->next->generalScore)
                {
                    Score *pT = pNow;
                    pLast->next = pNow->next;
                    pT->next = pLast->next->next;
                    pLast->next->next = pT;
                }
                else
                    pNow = pNow->next;
            }
            pLast = pLast->next;
        }
    }
}

int main()
{
    _init();
    sortByScore(0);
    //deleteById(1);
    /*Student *p1 = studentSearchById(2);
    printf("id: %d\n", p1->id);
    Student *p2 = studentSearchByRoomNum("101")->next;
    while (p2)
    {
        printf("%s\n", p2->roomNum);
        p2 = p2->next;
    }*/
    Score *p = scoreSearchById(1)->next;
    while (p)
    {
        printf("id: %d\n", p->id);
        p = p->next;
    }

    _quit();
    return 0;
}