#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#define BUFFER_SIZE 1024

extern uint32_t MyChkSum(const char *buff, size_t len, uint32_t prevchk);

bool Compare(const char *p_A_filename, const char *p_B_filename)
{
    char buffer[BUFFER_SIZE] = {0};
    size_t currByteNumber = 0;
    uint64_t sumByteNumber = 0; // uint32_t would work if file size is <= 4GB
    uint32_t checksumA = 0;
    uint32_t checksumB = 0;

    FILE *A_file = fopen(p_A_filename, "rb");
    if (!A_file)
    {
        return 0;
    }

    FILE *B_file = fopen(p_B_filename, "rb");
    if (!B_file)
    {
        fclose(A_file);
        return 0;
    }

    while ((currByteNumber = fread(buffer, sizeof(char), BUFFER_SIZE, A_file)) > 0)
    {
        checksumA = MyChkSum(buffer, currByteNumber, checksumA);
        sumByteNumber += currByteNumber;
    }

    if (ferror(A_file))
    {
        fclose(A_file);
        fclose(B_file);
        // Other Error handling must be implemented
        return 0;
    }

    while (sumByteNumber > 0)
    {
        currByteNumber = fread(buffer, sizeof(char), BUFFER_SIZE, B_file);
        if (currByteNumber == 0)
        {
            fclose(A_file);
            fclose(B_file);
            return 0;
        }
        checksumB = MyChkSum(buffer, currByteNumber, checksumB);
        sumByteNumber -= currByteNumber;
    }

    if (ferror(B_file))
    {
        fclose(A_file);
        fclose(B_file);
        // Other Error handling must be implemented
        return 0;
    }

    fclose(A_file);
    fclose(B_file);

    return (checksumB == checksumA);
}