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
void _initStudent(); // 初始化链表
void _initScore();
void _analysisStudentStr(char *str, Student *index); // 解析文件中单行字符串，将其按格式存储到内存结构体变量中
void _analysisScoreStr(char *str, Score *index);
void _init();                         // 将文件中的数据按一定格式读取到内存中，用结构体链表存储
void _destroyStudent(Student *index); // 释放结构体链表所占内存空间
void _destroyScore(Score *index);
void _quit();                      // 释放内存，将结构体链表中的数据存储到文件中
void appendStudent(Student index); // 结构体链表尾插
void appendScore(Score index);
int convertNum(char *index);                    // 将数字字符串转换为数字
void countGeneraAndFinalScore(Score *index);    // 计算出综合分数和使得学分
void save();                                    // 将结构体链表中的数据存储到文件中
Student *studentSearchById(int id);             // 通过学号查找相对应学生的信息，返回链表中相对应结构体节点的地址
Student *studentSearchByRoomNum(char *roomNum); // 通过宿舍号码查找相对应学生的信息，返回一个存储相应学生信息的新链表
Score *scoreSearchById(int id);                 // 通过学号查找相对应学生的成绩信息，返回一个存储相应成绩信息的新链表
void deleteById(int id);
void sortByScore(int isReversed); // 将链表中的保存学生成绩的节点，按综合成绩排序
void show();                      // 显示命令行用户交互界面
void search();                    // 根据相应要求搜索学生信息和成绩信息
void showScore();                 // 显示所有学生成绩
void showScoreInfo();             // 显示单个学生成绩信息
void showStudentInfo();           // 显示单个学生信息
void type();                      // 命令行录入信息模块

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
    countGeneraAndFinalScore(index);
}

void _destroyStudent(Student *index)
{
    Student *pTemp = NULL;
    while (index)
    {
        pTemp = index->next;
        if (index->name)
        {
            free(index->name);
            index->name = NULL;
        }
        if (index->gender)
        {
            free(index->gender);
            index->gender = NULL;
        }
        if (index->roomNum)
        {
            free(index->roomNum);
            index->roomNum = NULL;
        }
        if (index->phoneNum)
        {
            free(index->phoneNum);
            index->phoneNum = NULL;
        }
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

void countGeneraAndFinalScore(Score *index)
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
            pResultTemp->next->name = (char *)malloc(sizeof(char) * strlen(pTemp->name) + 1);
            strcpy(pResultTemp->next->name, pTemp->name);
            pResultTemp->next->gender = (char *)malloc(sizeof(char) * strlen(pTemp->gender) + 1);
            strcpy(pResultTemp->next->name, pTemp->name);
            pResultTemp->next->gender = (char *)malloc(sizeof(char) * strlen(pTemp->gender) + 1);
            strcpy(pResultTemp->next->name, pTemp->name);
            pResultTemp->next->roomNum = (char *)malloc(sizeof(char) * strlen(pTemp->roomNum) + 1);
            strcpy(pResultTemp->next->roomNum, pTemp->roomNum);
            pResultTemp->next->phoneNum = (char *)malloc(sizeof(char) * strlen(pTemp->phoneNum) + 1);
            strcpy(pResultTemp->next->phoneNum, pTemp->phoneNum);
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
            pResultTemp->next->courseNum = (char *)malloc(sizeof(char) * strlen(pTemp->courseNum) + 1);
            strcpy(pResultTemp->next->courseNum, pTemp->courseNum);
            pResultTemp->next->courseName = (char *)malloc(sizeof(char) * strlen(pTemp->courseName) + 1);
            strcpy(pResultTemp->next->courseName, pTemp->courseName);
            pResultTemp->next->credit = pTemp->credit;
            pResultTemp->next->usualScore = pTemp->usualScore;
            pResultTemp->next->experimentScore = pTemp->experimentScore;
            pResultTemp->next->paperScore = pTemp->paperScore;
            pResultTemp->next->generalScore = pTemp->generalScore;
            pResultTemp->next->finalScore = pTemp->finalScore;
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

void type()
{
    Score temp;
    char tempStr1[10];
    char tempStr2[20];

    printf("学号: ");
    scanf("%d", &temp.id);

    printf("课程编号: ");
    scanf("%s", tempStr1);
    temp.courseNum = (char *)malloc(sizeof(strlen(tempStr1)) + 1);
    strcpy(temp.courseNum, tempStr1);
    temp.courseNum[sizeof(strlen(tempStr1))] = '\0';

    printf("课程名称: ");
    scanf("%s", tempStr2);
    temp.courseName = (char *)malloc(sizeof(strlen(tempStr2)) + 1);
    strcpy(temp.courseName, tempStr2);
    temp.courseName[sizeof(strlen(tempStr2))] = '\0';

    printf("学分: ");
    scanf("%d", &temp.credit);

    printf("平时成绩: ");
    scanf("%d", &temp.usualScore);

    printf("实验成绩: ");
    scanf("%d", &temp.experimentScore);

    printf("卷面成绩: ");
    scanf("%d", &temp.paperScore);

    countGeneraAndFinalScore(&temp);

    appendScore(temp);
}

void showStudentInfo(Student *index)
{
    printf("\n学号: %d\n", index->id);
    printf("姓名: %s\n", index->name);
    printf("性别: %s\n", index->gender);
    printf("宿舍号码: %s\n", index->roomNum);
    printf("电话号码: %s\n", index->phoneNum);
}

void showScoreInfo(Score *index)
{
    printf("\n课程编号: %s\n", index->courseNum);
    printf("课程名称: %s\n", index->courseName);
    printf("学分 : %d\n", index->credit);
    printf("平时成绩 : %d\n", index->usualScore);
    printf("实验成绩 : %d\n", index->experimentScore);
    printf("卷面成绩  : %d\n", index->paperScore);
    printf("综合成绩  : %.2f\n", index->generalScore);
    printf("实得学分 : %.2f\n", index->finalScore);
}

void showScore()
{
    Score *pTemp = pScore->next;
    while (pTemp)
    {
        printf("\n学号: %d", pTemp->id);
        showScoreInfo(pTemp);
        pTemp = pTemp->next;
    }
}

void search()
{
    int choice = -1;
    int num;
    char tempStr[30];
    printf("\n-------------查询------------\n");
    printf("  1. 学号查询学生信息\n");
    printf("  2. 宿舍号查询学生信息\n");
    printf("  3. 学号查询成绩信息\n");
    printf("----------------------------\n");
    printf("您的选择: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        printf("学号: ");
        scanf("%d", &num);
        Student *pResult = studentSearchById(num);
        if (pResult)
            showStudentInfo(pResult);
        break;
    case 2:
        printf("宿舍号: ");
        scanf("%s", tempStr);
        Student *pResult1 = studentSearchByRoomNum(tempStr);
        Student *pTemp1 = pResult1;
        if (pResult1)
        {
            while (pResult1->next)
            {
                showStudentInfo(pResult1->next);
                pResult1 = pResult1->next;
            }
            _destroyStudent(pTemp1);
        }
        break;
    case 3:
        printf("学号: ");
        scanf("%d", &num);

        Student *pResult3 = studentSearchById(num);
        if (pResult3)
            printf("姓名: %s\n", pResult3->name);

        Score *pResult2 = scoreSearchById(num);
        Score *pTemp2 = pResult2;
        if (pResult2)
        {
            while (pResult2->next)
            {
                showScoreInfo(pResult2->next);
                pResult2 = pResult2->next;
            }
            _destroyScore(pTemp2);
        }
        break;
    default:
        printf("错误的选择!\n");
        break;
    }
}

void show()
{
    int choice = -1;
    int num;
    printf("      欢迎来到学生管理系统!     \n\n");
    while (choice != 5)
    {
        printf("\n-----------功能菜单----------\n");
        printf("  1. 录入学生成绩数据\n");
        printf("  2. 查询\n");
        printf("  3. 删除\n");
        printf("  4. 排序并显示\n");
        printf("  5. 保存并退出\n");
        printf("---------------------------\n");
        printf("请输入您的选择: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            type();
            break;
        case 2:
            search();
            break;
        case 3:
            printf("学号: ");
            scanf("%d", &num);
            deleteById(num);
            break;
        case 4:
            sortByScore(1);
            showScore();
            break;
        case 5:
            break;
        default:
            printf("错误的选择!\n\n");
            break;
        }
    }
}

int main()
{
    _init();
    show();
    _quit();
    return 0;
}