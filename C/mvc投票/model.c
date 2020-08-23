#include "model.h"

int GetKeyIndex(CandidateKey* array, const char* name, int count)
{
    for (int i = 0; i != count; ++i)
    {
        if (strncmp(array[i].name, name, 80) == 0)
        {
            return i;
        }
    }
    return -1;
}
