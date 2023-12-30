#include <stdio.h>
#include <stdlib.h>
#include "status.h"
#include "bignum_filter.h"

struct bit_flags
{
	int size;
	int capacity;
	int* data; //a pointer to an array to store the bits
};
typedef struct bit_flags Bit_flags;

BIT_FLAGS bit_flags_init_number_of_bits(int number_of_bits)
{
	Bit_flags* pBit_flags = (Bit_flags*)malloc(sizeof(Bit_flags));
	if (pBit_flags == NULL)
	{
		printf("Malloc failed in pBit_flags\n");
		return NULL;
	}
	
	//calculate the number of integers needed
	int remainder = number_of_bits % 32;
	if (remainder != 0)
		remainder = 1;
	else
		remainder = 0;
	int number_of_intergers = number_of_bits / 32 + remainder;

	//create spaces for the bits
	pBit_flags->data = (int*)malloc(sizeof(int) * number_of_intergers);
	if (pBit_flags->data == NULL)
	{
		printf("Malloc failed in pBit_flags->data\n");
		free(pBit_flags);
		return NULL;
	}

	//set all flags at zero
	for (int i = 0; i < number_of_intergers; i++)
		pBit_flags->data[i] = 0;

	//assign values
	pBit_flags->size = number_of_bits;
	pBit_flags->capacity = number_of_intergers * 32;

	return pBit_flags;
}

int bit_flags_get_size(BIT_FLAGS hBit_flags)
{
	Bit_flags* pBit_flags = (Bit_flags*)hBit_flags;
	return pBit_flags->size;
}

int bit_flags_get_capacity(BIT_FLAGS hBit_flags)
{
	Bit_flags* pBit_flags = (Bit_flags*)hBit_flags;
	return pBit_flags->capacity;
}

void bit_flags_destroy(BIT_FLAGS* phBit_flags)
{
	Bit_flags* pBit_flags = (Bit_flags*)*phBit_flags;
	free(pBit_flags->data);
	free(pBit_flags);
	*phBit_flags = NULL;
}

int bit_flags_check_flag(BIT_FLAGS hBit_flags, int flag_position)
{
	Bit_flags* pBit_flags = (Bit_flags*)hBit_flags;
	
	while (flag_position >= pBit_flags->capacity)
	{
		int* temp = (int*)malloc(sizeof(int) * ((pBit_flags->capacity) / 32 + 1));
		if (temp == NULL)
		{
			printf("Malloc failed in temp\n");
			return -1;
		}

		//copy data
		for (int i = 0; i < pBit_flags->capacity/32; i++)
			temp[i] = pBit_flags->data[i];
		free(pBit_flags->data);
		pBit_flags->data = temp;

		//increase capacity and size
		pBit_flags->capacity += 32;
		pBit_flags->size = flag_position;

		//set the last element of the new array to 0
		pBit_flags->data[(pBit_flags->capacity/32)-1] = 0;
	}
	
	int index_of_array = flag_position / 32;
	int flag_value = 1 << flag_position;
	int res = pBit_flags->data[index_of_array] & flag_value;
	if (res != 0)
		return 1;
	else
		return 0;
}

Status bit_flags_set_flag(BIT_FLAGS hBit_flags, int flag_position)
{
	Bit_flags* pBit_flags = (Bit_flags*)hBit_flags;
	//resize when needed
	while (flag_position >= pBit_flags->capacity)
	{
		int* temp = (int*)malloc(sizeof(int) * ((pBit_flags->capacity/32) +1));
		if (temp == NULL)
		{
			printf("Malloc failed in temp\n");
			return -1;
		}

		//copy data
		for (int i = 0; i < pBit_flags->capacity/32; i++)
			temp[i] = pBit_flags->data[i];
		free(pBit_flags->data);
		pBit_flags->data = temp;

		//increase capacity
		pBit_flags->capacity += 32;

		//set the last element of the new array to 0
		pBit_flags->data[(pBit_flags->capacity/32)-1] = 0;
	}

	//resize or not, always modify the current size to the latest flag_position
	if(flag_position > pBit_flags->size)
		pBit_flags->size = flag_position; 
	
	int index_of_array = flag_position / 32;
	int flag_value = 1 << flag_position;
	pBit_flags->data[index_of_array] = pBit_flags->data[index_of_array] | flag_value;
	return SUCCESS;
}

Status bit_flags_unset_flag(BIT_FLAGS hBit_flags, int flag_position)
{
	Bit_flags* pBit_flags = (Bit_flags*)hBit_flags;
	while (flag_position >= pBit_flags->capacity)
	{
		int* temp = (int*)malloc(sizeof(int) * ((pBit_flags->capacity) / 32 + 1));
		if (temp == NULL)
		{
			printf("Malloc failed in temp\n");
			return -1;
		}

		//copy data
		for (int i = 0; i < pBit_flags->capacity/32; i++)
			temp[i] = pBit_flags->data[i];
		free(pBit_flags->data);
		pBit_flags->data = temp;

		//increase capacity
		pBit_flags->capacity += 32;

		//set the last element of the new array to 0
		pBit_flags->data[(pBit_flags->capacity/32)-1] = 0;
	}
	//resize or not, always modify the current size to the latest flag_position
	if (flag_position > pBit_flags->size)
		pBit_flags->size = flag_position;

	int index_of_array = flag_position / 32;
	int flag_value = 1 << flag_position;
	pBit_flags->data[index_of_array] = pBit_flags->data[index_of_array] ^ flag_value;
	return SUCCESS;
}
