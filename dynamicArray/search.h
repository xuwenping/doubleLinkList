/*************************************************************************
	> File Name: search.h
	> Author: 
	> Mail: 
	> Created Time: Thu Mar 26 23:48:33 2015
 ************************************************************************/

#ifndef _SEARCH_H
#define _SEARCH_H

#include <stdio.h>
#include "typedef.h"

int qsearch(void **array, size_t nr, void *data, DataCompareFunc cmp);

#endif
