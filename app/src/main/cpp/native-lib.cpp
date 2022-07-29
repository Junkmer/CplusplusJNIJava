#include <jni.h>
#include <string>
#include <iostream>

extern "C"
JNIEXPORT jstring JNICALL
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_stringFromJNI__(JNIEnv *env, jobject thiz) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

/////////////////////////////////////////////////////////////////////////////////
//############## 由浅入深-至上而下 ################
/////////////////////////////////////////////////////////////////////////////////

/**
 * 传参类型：整型(int/long/short/...)
 */
extern "C"
JNIEXPORT jint JNICALL
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_integerFromJNI(JNIEnv *env, jobject thiz, jint num) {
    //获取实例对应的 class
    jclass jclazz = env->GetObjectClass(thiz);
//    jclass jclazz = env->FindClass("com/junker/cplusplus/and/java/jni/study/manager/JNIBaseManager");  //也可以通过反射获取
    //通过jclass获取对应的变量的 fieldId
    jfieldID fid = env->GetFieldID(jclazz, "num", "I");
    //将传入的参数 num 赋值 给  thiz 类中 fieldId 对应的变量
    env->SetIntField(thiz, fid, num);
    //通过 fieldId 获取对应的值
    jint newNum = env->GetIntField(thiz, fid);
    return newNum;
}

/**
 * 传参类型：char
 */
extern "C"
JNIEXPORT jchar JNICALL
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_charFromJNI(JNIEnv *env, jobject thiz, jchar ch) {
    //获取实例对应的 class
    jclass jclazz = env->GetObjectClass(thiz);
    //通过 jcazz获取对应的变量 fieldId
    jfieldID fid = env->GetFieldID(jclazz, "ch", "C");
    //将传入的参数 ch 赋值给 thiz 实例对象中 fieldId 对应的变量
    env->SetCharField(thiz, fid, ch);
    //通过 fieldId 获取对应的值
    jchar newCh = env->GetCharField(thiz, fid);
    return newCh;
}

/**
 * 传参类型：string
 */
extern "C"
JNIEXPORT jstring JNICALL
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_stringFromJNI__Ljava_lang_String_2(JNIEnv *env, jobject thiz, jstring str) {
    //获取实例对应的 class
    jclass jclazz = env->GetObjectClass(thiz);
    //通过 jclazz 获取对应的变量 fieldId
    jfieldID fid = env->GetFieldID(jclazz, "str", "Ljava/lang/String;");
    //将传入的参数 str 赋值给 thiz 实例对象中 fieldId 对应的变量
    env->SetObjectField(thiz,fid,str);
    //获取 thiz 对象中fieldId对应的对象
    jstring jstr = static_cast<jstring>(env->GetObjectField(thiz,fid));
    if (jstr) {

        //获取 jstr对象的值，并传回给 java层
        int size = env->GetStringUTFLength(jstr);
        const char *value = env->GetStringUTFChars(str, nullptr);
        std::string result(value, size);
        std::cout<< "result[%s] = " << result.c_str() << std::endl;

        env->ReleaseStringChars(jstr, reinterpret_cast<const jchar *>(value));
        env->DeleteLocalRef(jstr);

        return env->NewStringUTF(result.c_str());
    }
    return env->NewStringUTF("");
}

/**
 * 传参类型：数组( int[]/ string[]/ ...)
 */
extern "C"
JNIEXPORT jintArray JNICALL
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_intArrayFromJNI(JNIEnv *env, jobject thiz, jintArray numS) {
    jclass jclazz = env->GetObjectClass(thiz);
    jfieldID fid = env->GetFieldID(jclazz, "numS", "[I");
    jintArray intArr = static_cast<jintArray>(env->GetObjectClass(thiz,fid));

    // 将传入的参数 numS 赋值给 thiz 实例对象中 fieldId 对应的变量
    jint len = 0, sum = 0;
    jint *arr = env->GetIntArrayElements(numS, 0);
    len = env->GetArrayLength(numS);
    //由于一些版本不兼容，i 不定义再for循环中
    jint i = 0;
    for (; i < len; ++i) {
        sum += arr[i];
    }

    env->NewIntArray(sum);

    env->ReleaseIntArrayElements(numS,arr,0);

}

/**
 * 传参类型：对象
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_objectFromJNI(JNIEnv *env, jobject thiz, jobject obj) {
    // TODO: implement objectFromJNI()
}

/**
 * 传参类型：集合-List<整型>
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_listIntegerFromJNI(JNIEnv *env, jobject thiz, jobject list) {
    // TODO: implement listIntegerFromJNI()
}

/**
 * 传参类型：集合-List<String>
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_listStringFromJNI(JNIEnv *env, jobject thiz, jobject map_int) {
    // TODO: implement listStringFromJNI()
}

/**
 * 传参类型：集合-List<int[]>
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_listIntArrayFromJNI(JNIEnv *env, jobject thiz, jobject list_int_array) {
    // TODO: implement listIntArrayFromJNI()
}

/**
 * 传参类型：集合-List<Object>
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_listObjectFromJNI(JNIEnv *env, jobject thiz, jobject list_object) {
    // TODO: implement listObjectFromJNI()
}

/**
 * 传参类型：Map数组-Map<整型>
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_mapIntegerFromJNI(JNIEnv *env, jobject thiz, jobject map_integer) {
    // TODO: implement mapIntegerFromJNI()
}

/**
 * 传参类型：Map数组-Map<String>
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_mapStringFromJNI(JNIEnv *env, jobject thiz, jobject map_string) {
    // TODO: implement mapStringFromJNI()
}

/**
 * 传参类型：Map数组-Map<int[]>
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_mapIntegerArrayFromJNI(JNIEnv *env, jobject thiz, jobject map_integer_array) {
    // TODO: implement mapIntegerArrayFromJNI()
}

/**
 * 传参类型：Map数组-Map<Object>
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_mapObjectFromJNI(JNIEnv *env, jobject thiz, jobject map_object) {
    // TODO: implement mapObjectFromJNI()
}

/**
 * 传参类型：集合嵌套集合-List<List>
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_listListFromJNI(JNIEnv *env, jobject thiz, jobject list_list) {
    // TODO: implement listListFromJNI()
}

/**
 * 传参类型：Map嵌套Map-Map<Map>
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_mapMapFromJNI(JNIEnv *env, jobject thiz, jobject map_map) {
    // TODO: implement mapMapFromJNI()
}