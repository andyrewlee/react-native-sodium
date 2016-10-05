
#include <jni.h>
#include "sodium.h"


#ifdef __cplusplus
extern "C" {
#endif

/* *****************************************************************************
 * Sodium-specific functions
 * *****************************************************************************
 */
JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_sodium_1init(JNIEnv *jenv, jclass jcls) {
  int result;
  result = (int)sodium_init();
  return (jint)result;
}

JNIEXPORT jstring JNICALL Java_org_libsodium_jni_SodiumJNI_sodium_1version_1string(JNIEnv *jenv, jclass jcls) {
  char *result = (char *)sodium_version_string();
  return (*jenv)->NewStringUTF(jenv, (const char *)result);
}



/* *****************************************************************************
 * Random data generation
 * *****************************************************************************
 */

JNIEXPORT jlong JNICALL Java_org_libsodium_jni_SodiumJNI_randombytes_1random(JNIEnv *jenv, jclass jcls) {
  uint32_t result;
  result = (uint32_t)randombytes_random();
  return (jlong)result;
}

JNIEXPORT jlong JNICALL Java_org_libsodium_jni_SodiumJNI_randombytes_1uniform(JNIEnv *jenv, jclass jcls, jlong j_upper_bound) {
  uint32_t result;
  result = (uint32_t)randombytes_uniform((uint32_t)j_upper_bound);
  return (jlong)result;
}

JNIEXPORT void JNICALL Java_org_libsodium_jni_SodiumJNI_randombytes_1buf(JNIEnv *jenv, jclass jcls, jbyteArray j_buf, jint j_size) {
  unsigned char *buf = (unsigned char *) (*jenv)->GetByteArrayElements(jenv, j_buf, 0);
  randombytes_buf(buf,(unsigned long long)j_size);
  (*jenv)->ReleaseByteArrayElements(jenv, j_buf, (jbyte *) buf, 0);
}

JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_randombytes_1close(JNIEnv *jenv, jclass jcls) {
  int result = (int)randombytes_close();
  return (jint)result;
}

JNIEXPORT void JNICALL Java_org_libsodium_jni_SodiumJNI_randombytes_1stir(JNIEnv *jenv, jclass jcls) {
  randombytes_stir();
}



/* *****************************************************************************
 * Public-key cryptography - authenticated encryption
 * *****************************************************************************
 */
JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1box_1keypair(JNIEnv *jenv, jclass jcls, jbyteArray j_pk, jbyteArray j_sk) {
  unsigned char *pk = (unsigned char *) (*jenv)->GetByteArrayElements(jenv, j_pk, 0);
  unsigned char *sk = (unsigned char *) (*jenv)->GetByteArrayElements(jenv, j_sk, 0);
  int result = (int)crypto_box_keypair(pk, sk);
  (*jenv)->ReleaseByteArrayElements(jenv, j_pk, (jbyte *) pk, 0);
  (*jenv)->ReleaseByteArrayElements(jenv, j_sk, (jbyte *) sk, 0);
  return (jint)result;
}

#ifdef __cplusplus
}
#endif
