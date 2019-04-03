#include <jni.h>
#include <string>
#include "signature.cpp"

extern "C" JNIEXPORT jstring JNICALL
Java_keithwang_jnisignature_Jni_stringFromJNI(
        JNIEnv *env,
        jobject) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}


extern "C" JNIEXPORT jstring JNICALL
Java_keithwang_jnisignature_Jni_getSignatureKey(
        JNIEnv *env,
        jclass,
        jobject contextObject) {

    char *sha1 = getKeySha1(env, contextObject);

    LOGD("%s",sha1);

    return env->NewStringUTF(sha1);
}

extern "C" JNIEXPORT jboolean JNICALL
Java_keithwang_jnisignature_Jni_isSameKey(
        JNIEnv *env,
        jclass,
        jobject contextObject) {

    char *sha1 = getKeySha1(env, contextObject);

    return checkValidity(sha1);
}


