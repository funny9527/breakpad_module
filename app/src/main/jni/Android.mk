LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

subdirs := $(LOCAL_PATH)/breakpad/android/google_breakpad/Android.mk \
        $(LOCAL_PATH)/breakwrapper/Android.mk
include $(subdirs)