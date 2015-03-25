/*************************************************************************
	> File Name: sort.h
	> Author: 
	> Mail: 
	> Created Time: Tue Mar 24 02:25:00 2015
 ************************************************************************/

#ifndef _SORT_H
#define _SORT_H

#include "typedef.h"

Ret bubble_sort(void **array, size_t nr, DataCompareFunc cmp, DataSwapFunc swap);

Ret change_sort(void **array, size_t nr, DataCompareFunc cmp);

Ret insert_sort(void **array, size_t nr, DataCompareFunc cmp);

Ret quick_sort(void **array, size_t nr, DataCompareFunc cmp);

#endif
