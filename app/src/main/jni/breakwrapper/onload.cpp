#include <string.h>
#include <jni.h>
#include "log.h"
#include "client/linux/handler/exception_handler.h"

#ifdef __cplusplus
extern "C" {
#endif

const char* className = "com/crash/wrapper/BreakpadWrapper";


google_breakpad::ExceptionHandler* exceptionHandler;
JavaVM *jvm = NULL;

void onNativeCrash(const char* info) {
    LOGD("onNativeCrash end %s", info);
}

// 崩溃回调
bool DumpCallback(const google_breakpad::MinidumpDescriptor& descriptor,
                  void* context, bool succeeded) {
    LOGE("Dump path: %s\n", descriptor.path());
    onNativeCrash("test");
    return succeeded;
}


int native_wrapper(JNIEnv *env, jobject self, jstring code) {
    LOGE("crash begin");
    volatile int* a = (int*)(NULL);
    *a = 1;
    return 0;
}


static JNINativeMethod mMethods[] =
        {
                {"wrapper", "()V", (void *) native_wrapper},
        };


int register_methods(JNIEnv *env)
{
    jclass clazz;

    clazz = env->FindClass(className );

    if (clazz == NULL)
    {
        LOGE("Can't find class %s\n", className);
        return -1;
    }

    LOGD("register native methods");

    if (env->RegisterNatives(clazz, mMethods, sizeof(mMethods) / sizeof(mMethods[0])) != JNI_OK)
    {
        LOGE("Failed registering methods for %s\n", className);
        return -1;
    }


    google_breakpad::MinidumpDescriptor descriptor("/sdcard");
    exceptionHandler = new google_breakpad::ExceptionHandler(descriptor, NULL, DumpCallback, NULL,
                                                             true, -1);

    return 0;
}

jint JNI_OnLoad(JavaVM* vm, void *reserved)
{
    jvm = vm;

    JNIEnv* env = NULL;
    jint result = -1;

    LOGD("%s: +", __FUNCTION__);

    if (vm->GetEnv((void**) &env, JNI_VERSION_1_6) != JNI_OK)
    {
        LOGE("ERROR: GetEnv failed.\n");
        return result;
    }

    if (register_methods(env) < 0)
    {
        LOGE("ERROR: register methods failed.\n");
        return result;
    }

    return JNI_VERSION_1_6;
}



void JNI_OnUnload(JavaVM* vm, void *reserved)
{
    return;
}

#ifdef __cplusplus
}
#endif