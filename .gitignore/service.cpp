#define LOG_TAG "android.hardware.simple@2.0-service"
#include <android/hardware/simple/2.0/ISimphw.h>
#include <hidl/LegacySupport.h>
#include "Simphw.h"
#include <signal.h>
#include <stdlib.h>
#include <pthread.h>
#include <log/logcat.h>
using android::hardware::simple::V2_0::ISimphw;
using android::hardware::simple::V2_0::implementation::Simphw;
using android::hardware::configureRpcThreadpool;
using android::hardware::joinRpcThreadpool;
using android::sp;

void *ringbuffer_read_thread(void *arg);
void * binderserver_datapush_thread(void *arg);

int main() {

  int ret = 0;
  pthread_t thread_id[2]; 
  pthread_create(&thread_id[0], NULL, ringbuffer_read_thread, NULL);
  pthread_create(&thread_id[1], NULL, binderserver_datapush_thread, NULL);
  pthread_join(thread_id[0], NULL); 
  pthread_join(thread_id[1], NULL); 
  
  return ret;
}


  //read device logcat & copy on shared buffer
void *ringbuffer_read_thread(void *arg)
{
  int ret = 0;
  arg = NULL;
  printf("Thread start......%s \n", __func__);
  android_logcat_context ctx = create_android_logcat();
  if (!ctx){
      printf("logcat context fail to creat func = %s\n", __func__);
      ret = 0;
    }
    ret = android_logcat_run_command(ctx, -1, -1, 0, NULL, NULL);
    if (ret < 0){
    printf("Fail to run/read data from ring buffer\n");
      ret = 0;
    }
    android_logcat_destroy(&ctx);
  return NULL;
}

  //send data to framework-client
void *binderserver_datapush_thread(void *arg)
{
  int res = 0;
  arg = NULL;
  printf("Thread start......%s \n", __func__);
  android::sp<ISimphw> ser = Simphw::getInstance();
  ALOGE("simp main");
  configureRpcThreadpool(1, true /*callerWillJoin*/);
  if (ser != nullptr) {
    res = ser->registerAsService();
      if(res != 0)
        ALOGE("Can't register instance of SimpleHardware, nullptr");
  } else {
        ALOGE("Can't create instance of SimpleHardware, nullptr");
  }
  joinRpcThreadpool();

  return NULL;
}
