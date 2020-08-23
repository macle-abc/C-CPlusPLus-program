#include "control.h"

/// <summary>
/// 判断name是否在array中唯一
/// </summary>
/// <param name="array">候选人数组</param>
/// <param name="name">需要判断唯一性的name</param>
/// <param name="count">候选人总数</param>
/// <returns>如果name唯一则返回true，否则返回false</returns>
static bool IsUnique(CandidateKey* array, const char* name, int count)
{
    int isFirst = 0;
    for (int i = 0; i != count; ++i)
    {
        if (strncmp(array[i].name, name, 80) == 0)
        {
            isFirst++;
        }
        if (isFirst > 1)
        {
            return false;
        }
    }
    return true;
}

void PrintError(const char* error, bool isExit)
{
    if (isExit)
    {
        fprintf(stderr, error);
        exit(-1);
    }
    fprintf(stderr, error);
    fprintf(stderr, "\n");
}

CandidateKey* CheckValidityCandidates(int argc, const char* argv[])
{
    if (argc < 4 || argc > 10)
    {
        PrintError("Please ensure that the number of candidates is between 3 and 9!", true);
        return NULL;
    }
    CandidateKey* array = (CandidateKey*)malloc(sizeof(CandidateKey) * (argc - 1));
    if (!array)
    {
        PrintError("Malloc Error!", true);
        return NULL;
    }
    memset(array, 0, sizeof(CandidateKey) * (argc - 1));
    for (int i = 1; i != argc; ++i)
    {
        strncpy(array[i - 1].name, strlwr((char*)argv[i]), 80);
    }
    for (int i = 0; i != argc - 1; ++i)
    {
        if (!IsUnique(array, array[i].name, argc - 1))
        {
            free(array);
            array = NULL;
            PrintError("Make sure that the names of the candidates will not be repeated!", true);
            return NULL;
        }
    }
    return array;
}

bool CheckValidityVoters(int number)
{
    if (number < 10 || number > 30)
    {
        return false;
    }
    return true;
}

int GetVotersCount()
{
    int voters = 0;
    while (true)
    {

        printf("Number of voters:");
        scanf("%d", &voters);
        while (getchar() != '\n')
        {
            ;
        }
        if (CheckValidityVoters(voters))
        {
            break;
        }
        else
        {
            PrintError("Number of voters must be between 10 and 30!", false);
        }
    }
    return voters;
}

void Vote(CandidateKey* array, size_t* candidateVotes, const char* name, size_t count)
{
    int index = GetKeyIndex(array, strlwr((char*)name), count);
    if (index == -1)
    {
        return;
    }
    candidateVotes[index]++;
}

WinnerInfo GetWinnerInfo(CandidateKey* array, size_t* candidateVotes, size_t count)
{
    WinnerInfo winnerInfo = { 0 };
    size_t max = 0;
    for (int i = 0; i != count; ++i)
    {
        if (max < candidateVotes[i])
        {
            max = candidateVotes[i];
        }
    }
    for (int i = 0; i != count; ++i)
    {
        if (max == candidateVotes[i])
        {
            winnerInfo.index[winnerInfo.count] = i;
            winnerInfo.count++;
            winnerInfo.name[i] = array[i].name;
        }
    }
    return winnerInfo;
}

