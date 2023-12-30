#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "bignum_filter.h"

int main()
{
    int i;
    int temp;
    BIT_FLAGS hBit_flags = bit_flags_init_number_of_bits(2000000000);
    if (hBit_flags == NULL)
    {
        printf("Failed to allocate the memory for the bit_flag object.\n");
        exit(1);
    }
    //printf("Enter a list of positive integers and enter -1 to stop: \n");

    scanf("%d", &temp);
    while (temp != -1)
    {
        bit_flags_set_flag(hBit_flags, temp);
        scanf("%d", &temp);
    }

    for (i = 0; i < bit_flags_get_size(hBit_flags); i++)
    {
        if (bit_flags_check_flag(hBit_flags, i) != 0)
            printf("%d\n", i);
    }

    /* //Printing to see the bitflags positions
    for (int i = 0; i < bit_flags_get_capacity(hBit_flags); i++)
    {
        if (i % 32 == 0)
            printf("\n");
        else if (i % 4 == 0)
            printf(" ");
        printf("%d", bit_flags_check_flag(hBit_flags, i));
    }
    */

    bit_flags_destroy(&hBit_flags);
	return 0;
}
