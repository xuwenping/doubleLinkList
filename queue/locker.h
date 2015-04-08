/*************************************************************************
	> File Name: locker.h
	> Author: 
	> Mail: 
	> Created Time: Sun 29 Mar 2015 04:09:42 PM CST
 ************************************************************************/

#ifndef _LOCKER_H
#define _LOCKER_H

#include "typedef.h"

struct _Locker;
typedef struct _Locker Locker;

typedef DListRet (*LockerLockFunc)(Locker *thiz);
typedef DListRet (*LockerUnlockFunc)(Locker *thiz);
typedef void (*LockerDestroyFunc)(Locker *thiz);

struct _Locker
{
  LockerLockFunc lock;
  LockerUnlockFunc unlock;
  LockerDestroyFunc destroy;

  char priv[0];
};

static inline DListRet Locker_lock(Locker *thiz)
{
  ret_val_if_fail(NULL != thiz, DList_Ret_InvalidParams);  

  thiz->lock(thiz);

  return DList_Ret_OK;
}

static inline DListRet Locker_unlock(Locker *thiz)
{
  ret_val_if_fail(NULL != thiz, DList_Ret_InvalidParams);  

  thiz->unlock(thiz);

  return DList_Ret_OK;
}

static inline DListRet Locker_destroy(Locker *thiz)
{
  ret_val_if_fail(NULL != thiz, DList_Ret_InvalidParams);  

  thiz->destroy(thiz);

  return DList_Ret_OK;
}

#endif
