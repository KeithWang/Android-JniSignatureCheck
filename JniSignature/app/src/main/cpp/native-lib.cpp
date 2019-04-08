#include <jni.h>
#include <string>
#include "signature.cpp"
#include "aes/aes.h"

jstring charToJstring(JNIEnv *env, char *src) {

    jsize len = strlen(src);
    jclass clsstring = env->FindClass("java/lang/String");
    jstring strencode = env->NewStringUTF("UTF-8");
    jmethodID mid = env->GetMethodID(clsstring, "<init>",
                                     "([BLjava/lang/String;)V");
    jbyteArray barr = env->NewByteArray(len);
    env->SetByteArrayRegion(barr, 0, len, (jbyte *) src);

    return (jstring) env->NewObject(clsstring, mid, barr, strencode);
}

char *getKey() {
    int n = 0;
    char s[23];//"NMTIzNDU2Nzg5MGFiY2RlZg";

    s[n++] = 'N';
    s[n++] = 'M';
    s[n++] = 'T';
    s[n++] = 'I';
    s[n++] = 'z';
    s[n++] = 'N';
    s[n++] = 'D';
    s[n++] = 'U';
    s[n++] = '2';
    s[n++] = 'N';
    s[n++] = 'z';
    s[n++] = 'g';
    s[n++] = '5';
    s[n++] = 'M';
    s[n++] = 'G';
    s[n++] = 'F';
    s[n++] = 'i';
    s[n++] = 'Y';
    s[n++] = '2';
    s[n++] = 'R';
    s[n++] = 'l';
    s[n++] = 'Z';
    s[n++] = 'g';
    char *encode_str = s + 1;
    return (char *) b64_decode(encode_str, strlen(encode_str));

}

extern "C" JNIEXPORT jstring JNICALL
Java_keithwang_jnisignature_Jni_stringFromJNI(
        JNIEnv *env,
        jclass) {
    return env->NewStringUTF(getKey());
}


extern "C" JNIEXPORT jstring JNICALL
Java_keithwang_jnisignature_Jni_getSignatureKey(
        JNIEnv *env,
        jclass,
        jobject contextObject) {

    char *sha1 = getKeySha1(env, contextObject);

    LOGD("%s", sha1);

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

extern "C" JNIEXPORT jstring JNICALL
Java_keithwang_jnisignature_Jni_encode(
        JNIEnv *env,
        jclass,
        jobject contextObject,
        jstring str_) {

    uint8_t *AES_KEY = (uint8_t *) (getKey());
    const char *in = env->GetStringUTFChars(str_, JNI_FALSE);
    char *baseResult = AES_128_ECB_PKCS5Padding_Encrypt(in, AES_KEY);
    env->ReleaseStringUTFChars(str_, in);
    return env->NewStringUTF(baseResult);
}


extern "C" JNIEXPORT jstring JNICALL
Java_keithwang_jnisignature_Jni_decode(
        JNIEnv *env,
        jclass,
        jobject contextObject,
        jstring str_) {


    uint8_t *AES_KEY = (uint8_t *) getKey();
    const char *str = env->GetStringUTFChars(str_, JNI_FALSE);
    char *desResult = AES_128_ECB_PKCS5Padding_Decrypt(str, AES_KEY);
    env->ReleaseStringUTFChars(str_, str);
//    return (*env)->NewStringUTF(env, desResult);
    //不用系统自带的方法NewStringUTF是因为如果desResult是乱码,会抛出异常
    return charToJstring(env, desResult);
}
