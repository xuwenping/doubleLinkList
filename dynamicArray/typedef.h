/*************************************************************************
	> File Name: typedef.h
	> Author: 
	> Mail: 
	> Created Time: Tue Mar 24 02:06:08 2015
 ************************************************************************/

#ifndef _TYPEDEF_H
#define _TYPEDEF_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define ret_if_fail(p) if(!(p))               \
  {printf("%s:%d Warning: "#p" failed.\n",    \
__func__, __LINE__); return;}

#define ret_val_if_fail(p, ret) if(!(p))           \
  {printf("%s:%d Warning: "#p" failed.\n",    \
__func__, __LINE__); return ret;}

typedef enum _Ret {
  Ret_OK,
  Ret_OOM,
  Ret_Fail,
  Ret_InvalidParams,
  Ret_MallocFial
}Ret;

typedef Ret (*DArrayDataVisitFunc)(void *ctx, void *value);
typedef int (*DataCompareFunc)(void *ctx, void * value);
typedef Ret (*SortFunc)(void **array, size_t nr, DataCompareFunc cmp);
#endif
