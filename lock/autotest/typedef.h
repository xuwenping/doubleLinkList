/*************************************************************************
	> File Name: typedef.h
	> Author: 
	> Mail: 
	> Created Time: Fri 27 Mar 2015 09:53:12 PM CST
 ************************************************************************/

#ifndef _TYPEDEF_H
#define _TYPEDEF_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define ret_if_fail(p) if(!(p))            \
  {printf("%s:%d Warning: "#p" failed.\n", \
__func__, __LINE__); return;}

#define ret_val_if_fail(p, ret) if(!(p))   \
  {printf("%s:%d Warning: "#p" failed.\n", \
__func__, __LINE__); return (ret);}

typedef enum _DListRet {
  DList_Ret_OK,
  DList_Ret_Fail,
  DList_Ret_MallocFail,
  DList_Ret_ListIsEmpty,
  DList_Ret_InvalidParams,
  DList_Ret_Index_Overstep
}DListRet;

struct _List;
typedef struct _List List;

typedef DListRet (*ListDataVisitFunc)(void *ctx, void *value);

DListRet List_foreach(List *thiz, ListDataVisitFunc visit, void *ctx);

#endif
