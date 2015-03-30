/*************************************************************************
	> File Name: locker_pthread.c
	> Author: 
	> Mail: 
	> Created Time: Sun 29 Mar 2015 04:09:05 PM CST
 ************************************************************************/

#include "locker_pthread.h"

typedef struct _PrivInfo
{
  pthread_mutex_t mutex;
}PrivInfo;

static DListRet locker_pthread_lock(Locker *thiz)
{
  PrivInfo *priv = (PrivInfo *)thiz->priv;
  int ret = pthread_mutex_lock(&priv->mutex);
  return ret == 0 ? DList_Ret_OK : DList_Ret_Fail;
}

static DListRet locker_pthread_unlock(Locker *thiz)
{
  PrivInfo *priv = (PrivInfo *)thiz->priv;
  int ret = pthread_mutex_unlock(&priv->mutex);
  return ret == 0 ? DList_Ret_OK : DList_Ret_Fail; 
}

static void locker_pthread_destroy(Locker *thiz)
{
  PrivInfo *priv = (PrivInfo *)thiz->priv;
  int ret = pthread_mutex_destroy(&priv->mutex);
  free(thiz);
  thiz = NULL;
}

Locker *locker_pthread_create()
{
  Locker *thiz = (Locker *)malloc(sizeof(Locker) + sizeof(PrivInfo)); 

  if(NULL != thiz)
  {
    PrivInfo *priv = (PrivInfo *)thiz->priv;
    thiz->lock = locker_pthread_lock;
    thiz->unlock = locker_pthread_unlock;
    thiz->destroy = locker_pthread_destroy;

    pthread_mutex_init(&(priv->mutex), NULL);
  }
}


