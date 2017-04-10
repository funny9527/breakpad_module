LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

GOOGLE_BREAKPAD_PATH := $(LOCAL_PATH)/../breakpad

LOCAL_C_INCLUDES := $(JAVASCRIPTCORE_PATH)/src \
                $(JAVASCRIPTCORE_PATH)/src/common/android/include

LOCAL_MODULE    := libwrapper
LOCAL_SRC_FILES := onload.cpp

LOCAL_STATIC_LIBRARIES += breakpad_client

LOCAL_LDLIBS := -llog -lz -latomic

include $(BUILD_SHARED_LIBRARY)