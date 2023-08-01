#include <jni.h>
#include <string>
#include "Util.h"
#include "Dobby/include/dobby.h"


//函数指针用于保留原来的执行流程
static int (*old_c_test_func)(int i);

//新函数
static int new_c_test_func(int i) {
    int origin_ret = old_c_test_func(i);
    printf("原来的参数:%d,返回值:%d\n", i, origin_ret);
    return 10 * 10;
}

// 待 hook 函数
int c_test_func(int i) {
    LOGE("c_test_func: %s, Line: %d, Func: %s \n", __FILE__, __LINE__, __func__);
    return i + 10;
}

__attribute__((constructor)) static void dylibInject() {
//    void *target_addr = (void *) DobbySymbolResolver("libtest_for_hook.so", "c_test_func");
    DobbyHook((void *) &c_test_func, (void *) &new_c_test_func, (void **) &old_c_test_func);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_cn_my_dobby_1study_MainActivity_call_1test_1function(JNIEnv *env, jobject thiz) {
    // TODO: implement call_test_function()
    char text[0x100];
    int ret = c_test_func(10);
    sprintf(text, "(10 + 10) = %d", ret);
    return env->NewStringUTF(text);
}
