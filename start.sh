git clone https://github.com/google/breakpad app/src/main/jni/breakpad
cd app/src/main/jni/breakpad/src/third_party
mkdir lss
cd ../../../../../../..
cp app/src/main/jni/breakwrapper/linux_syscall_support.h app/src/main/jni/breakpad/src/third_party/lss/
