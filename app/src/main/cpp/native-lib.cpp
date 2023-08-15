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
    LOGE("c_test_func: %s, Line: %d, Func: %s vaddr:0x%lx\n", __FILE__, __LINE__, __func__,
         &c_test_func);
    return i + 10;
}

static int (*orig_log_print)(int prio, const char *tag, const char *fmt, ...);

static int my_libtest_log_print(int prio, const char *tag, const char *fmt, ...) {
    va_list ap;
    char buf[1024];
    int r;

    snprintf(buf, sizeof(buf), "[%s] %s", (NULL == tag ? "" : tag), (NULL == fmt ? "" : fmt));

    va_start(ap, fmt);
    r = __android_log_vprint(prio, "Dobby_libtest", buf, ap);
    va_end(ap);
    return r;
}

__attribute__((constructor)) static void dylibInject() {
    void *target_addr = (void *) DobbySymbolResolver("base.apk", "_Z11c_test_funci");
    DobbyHook(target_addr, (void *) &new_c_test_func, (void **) &old_c_test_func);
//    DobbyHook((void *) &c_test_func, (void *) &new_c_test_func, (void **) &old_c_test_func);
    void *log_vaddr = (void *) DobbySymbolResolver(NULL, "__android_log_print");
    DobbyHook(log_vaddr, (void *) my_libtest_log_print, (void **) &orig_log_print);
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
