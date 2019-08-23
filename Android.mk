# Copyright 2006-2014 The Android Open Source Project

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE_RELATIVE_PATH := hw
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE :=  android.hardware.simple@2.0-service
LOCAL_INIT_RC := android.hardware.simple@2.0-service.rc
LOCAL_SRC_FILES := service.cpp Simphw.cpp
LOCAL_SHARED_LIBRARIES := liblogcat liblog libbase libcutils libpcrecpp android.hardware.simple@2.0 libhidlbase libhidltransport libutils


LOCAL_CFLAGS := -Werror

include $(BUILD_EXECUTABLE)
