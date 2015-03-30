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

#endif
