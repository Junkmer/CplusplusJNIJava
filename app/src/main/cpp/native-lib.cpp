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
/* ------------------------------------------------------------------------- */
/** 方式一：将传入的参数，原封不动的赋值给对应的对象 **/
//    //将传入的参数 num 赋值给 thiz 类中 fieldId 对应的变量
//    env->SetIntField(thiz, fid, num);
//    //通过 fieldId 获取对应的值
//    jint newNum = env->GetIntField(thiz, fid);
//    return newNum;
/** 方式二：对传入的参数做二次修改，再赋值给对应的对象 **/
    //将传入的参数 num 修改之后，再赋值给 thiz 对象实例中 field 对应的变量
    num = 10068;
    env->SetIntField(thiz, fid, num);
    //获取 thiz 实例对象中 fieldId 对应的变量
    jint newNum = env->GetIntField(thiz, fid);
    return newNum;
/** 方式三：不启用传入的参数，重新 new 一个新的对象，重新赋值 **/

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
/* ------------------------------------------------------------------------- */
/** 方式一：将传入的参数，原封不动的赋值给对应的对象 **/
    //将传入的参数 ch 赋值给 thiz 实例对象中 fieldId 对应的变量
    env->SetCharField(thiz, fid, ch);
    //通过 fieldId 获取对应的值
    jchar newCh = env->GetCharField(thiz, fid);
    return newCh;
/** 方式二：对传入的参数做二次修改，再赋值给对应的对象 **/
    //将传入的参数 ch 修改之后，再赋值给 thiz 对象实例中 field 对应的变量

    //获取 thiz 实例对象中 fieldId 对应的变量

/** 方式三：不启用传入的参数，重新 new 一个新的对象，重新赋值 **/

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
/* ------------------------------------------------------------------------- */
/** 方式一：将传入的参数，原封不动的赋值给对应的对象 **/
//    //将传入的参数 str 赋值给 thiz 实例对象中 fieldId 对应的变量
//    env->SetObjectField(thiz, fid, str);
//    //获取 thiz 对象中fieldId对应的对象
//    jstring jstr = static_cast<jstring>(env->GetObjectField(thiz, fid));
//    return jstr;
/** 方式二：对传入的参数做二次修改，再赋值给对应的对象 **/
    //将传入的参数 str 修改之后，再赋值给 thiz 对象实例中 field 对应的变量
/*          style 1          */
//    jboolean isCopy = JNI_FALSE; // 返回JNI_TRUE表示原字符串的拷贝，返回JNI_FALSE表示返回原字符串的指针
//    const char* chr = env->GetStringUTFChars(str,0);
//    char c[120] = "你好 2017";
//    strcat(c,chr);//把chr拼接到c
//    str = env->NewStringUTF(c);
//    env->ReleaseStringUTFChars(str,chr);
//    return str;
/*          style 2          */
//    char buff[128] = {0};
//    jboolean isCopy = JNI_FALSE; // 返回JNI_TRUE表示原字符串的拷贝，返回JNI_FALSE表示返回原字符串的指针
//    const char *c_str = env->GetStringUTFChars(str, &isCopy);
//    sprintf(buff, "Junker %s", c_str); //在 str 字符基础上拼接字符
//    str = env->NewStringUTF(buff);
//    env->SetObjectField(thiz, fid, str);
//    jstring jstr = static_cast<jstring>(env->GetObjectField(thiz,fid));
//
//    env->ReleaseStringUTFChars(str, c_str);
//    return jstr;
/** 方式三：不启用传入的参数，重新 new 一个新的对象，重新赋值 **/
    jstring newJstr = env->NewStringUTF("你好 小爱");
    //将新建的参数 jstr 赋值给 thiz 实例对象中 fieldId 对应的变量
    env->SetObjectField(thiz, fid, newJstr);
    //获取 thiz 对象中 fieldId 对应的对象
    jstring jstr = static_cast<jstring>(env->GetObjectField(thiz,fid));

    env->DeleteLocalRef(newJstr);
    return jstr;
}

/**
 * 传参类型：数组( int[]/ string[]/ ...)
 */
extern "C"
JNIEXPORT jintArray JNICALL
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_intArrayFromJNI(JNIEnv *env, jobject thiz, jintArray numS) {
    //获取实例对应的 class
    jclass jclazz = env->GetObjectClass(thiz);
    //通过 jclazz 获取对应的变量 fieldId
    jfieldID fid = env->GetFieldID(jclazz, "numS", "[I");
    //将传入的参数 numS 赋值给 thiz 实例对象中 fieldId 对应的变量
    env->SetObjectField(thiz, fid, numS);
    //获取 thiz 对象中 fieldId 对应的对象
    jobject jobj = env->GetObjectField(thiz, fid);//获取对象字段，返回JObject(因为Array是object的实例)
    jintArray jarr = reinterpret_cast<jintArray>(jobj);
//    if (jarr) {
//        //获取 jarr 对象的值，并传回给 java层
//        jint *elems = env->GetIntArrayElements(jarr, nullptr);
//        //获得jarr数组的长度
//        jsize length = env->GetArrayLength(jarr);
//        //遍历数组元素的值
//        for (int i = 0; i < length; ++i) {
//            std::cout << elems[i] << std::endl;
//        }
//
////        //补充：再次修改传进来的数据，相关链接：https://www.cnblogs.com/lenve/p/4889326.html
////        std::cout << "---修改之后---" << std::endl;
////        for (int i = 0; i < length; i++) {
////            elems[i] = elems[i] + 1;//修改元素的值
////            std::cout << elems[i] << std::endl;
////        }
//        env->ReleaseIntArrayElements(jarr, elems, 0);
//        return jarr;
//    }

    return jarr;
/* ------------------------------------------------------------------------- */
/** 方式一：将传入的参数，原封不动的赋值给对应的对象 **/

/** 方式二：对传入的参数做二次修改，再赋值给对应的对象 **/
    //将传入的参数 numS 修改之后，再赋值给 thiz 对象实例中 field 对应的变量

    //获取 thiz 实例对象中 fieldId 对应的变量

/** 方式三：不启用传入的参数，重新 new 一个新的对象，重新赋值 **/

}

/**
 * 传参类型：对象
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_objectFromJNI(JNIEnv *env, jobject thiz, jobject obj) {
    //获取实例对应的 class
    jclass jclazz = env->GetObjectClass(thiz);
    //通过 jclazz 获取对应变量的 fieldId
    jfieldID fid = env->GetFieldID(jclazz, "bean", "Lcom/junker/cplusplus/and/java/jni/study/bean/DataBean;");
    //将传入的参数 obj 赋值给 thiz 实例对象中 fieldId 对应的变量
    env->SetObjectField(thiz, fid, obj);
    //获取 thiz 对象中 fieldId 对应的对象
    jobject jobj = env->GetObjectField(thiz, fid);
    return jobj;
/* ------------------------------------------------------------------------- */
/** 方式一：将传入的参数，原封不动的赋值给对应的对象 **/

/** 方式二：对传入的参数做二次修改，再赋值给对应的对象 **/
    //将传入的参数 obj 修改之后，再赋值给 thiz 对象实例中 field 对应的变量

    //获取 thiz 实例对象中 fieldId 对应的变量

/** 方式三：不启用传入的参数，重新 new 一个新的对象，重新赋值 **/

}

/**
 * 传参类型：集合-List<整型>
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_listIntegerFromJNI(JNIEnv *env, jobject thiz, jobject list) {
    //获取实例对应的 class
    jclass jclazz = env->GetObjectClass(thiz);
    //通过 jclazz 获取对应变量的 fieldId
    jfieldID fid = env->GetFieldID(jclazz, "list", "Ljava/util/List;");
    //将传入的参数 list 赋值给 thiz 实例对象中 fieldId 对应的变量
    env->SetObjectField(thiz, fid, list);
    //获取 thiz 对象中 fieldId 对应的对象
    jobject jobj = env->GetObjectField(thiz, fid);
    return jobj;
/* ------------------------------------------------------------------------- */
/** 方式一：将传入的参数，原封不动的赋值给对应的对象 **/

/** 方式二：对传入的参数做二次修改，再赋值给对应的对象 **/
    //将传入的参数 list 修改之后，再赋值给 thiz 对象实例中 field 对应的变量

    //获取 thiz 实例对象中 fieldId 对应的变量

/** 方式三：不启用传入的参数，重新 new 一个新的对象，重新赋值 **/

}

/**
 * 传参类型：集合-List<String>
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_listStringFromJNI(JNIEnv *env, jobject thiz, jobject list_string) {
    //获取实例对应的 class
    jclass jclazz = env->GetObjectClass(thiz);
    //通过 jclazz 获取对应变量的 fieldId
    jfieldID fid = env->GetFieldID(jclazz, "listString", "Ljava/util/List;");
    //将传入的参数 list_string 赋值给 thiz 实例对象中 fieldId 对应的变量
    env->SetObjectField(thiz, fid, list_string);
    //获取 thiz 对象中 fieldId 对应的对象
    jobject jobj = env->GetObjectField(thiz, fid);
    return jobj;
/* ------------------------------------------------------------------------- */
/** 方式一：将传入的参数，原封不动的赋值给对应的对象 **/

/** 方式二：对传入的参数做二次修改，再赋值给对应的对象 **/
    //将传入的参数 list_string 修改之后，再赋值给 thiz 对象实例中 field 对应的变量

    //获取 thiz 实例对象中 fieldId 对应的变量

/** 方式三：不启用传入的参数，重新 new 一个新的对象，重新赋值 **/

}

/**
 * 传参类型：集合-List<int[]>
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_listIntArrayFromJNI(JNIEnv *env, jobject thiz, jobject list_int_array) {
    //获取实例对应的 class
    jclass jcazz = env->GetObjectClass(thiz);
    //通过 jclazz 获取对应变量的 fieldId
    jfieldID fid = env->GetFieldID(jcazz, "listIntArray", "Ljava/util/List;");
    //将传入的参数 list_int_array 赋值给 thiz 实例对象中 fieldId 对应的变量
    env->SetObjectField(thiz, fid, list_int_array);
    //获取 thiz 对象中 fieldId 对应的对象
    jobject jobj = env->GetObjectField(thiz, fid);
    return jobj;
/* ------------------------------------------------------------------------- */
/** 方式一：将传入的参数，原封不动的赋值给对应的对象 **/

/** 方式二：对传入的参数做二次修改，再赋值给对应的对象 **/
    //将传入的参数 list_int_array 修改之后，再赋值给 thiz 对象实例中 field 对应的变量

    //获取 thiz 实例对象中 fieldId 对应的变量

/** 方式三：不启用传入的参数，重新 new 一个新的对象，重新赋值 **/

}

/**
 * 传参类型：集合-List<Object>
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_listObjectFromJNI(JNIEnv *env, jobject thiz, jobject list_object) {
    //获取实例对应的 class
    jclass jclazz = env->GetObjectClass(thiz);
    //通过 jclazz 获取对应变量的 fieldId
    jfieldID fid = env->GetFieldID(jclazz, "listObject", "Ljava/util/List;");
    //将传入的参数 list_object 赋值给 thiz 实例对象中 fieldId 对应的变量
    env->SetObjectField(thiz, fid, list_object);
    //获取 thiz 对象中 fieldId 对应的对象
    jobject jobj = env->GetObjectField(thiz, fid);
    return jobj;
/* ------------------------------------------------------------------------- */
/** 方式一：将传入的参数，原封不动的赋值给对应的对象 **/

/** 方式二：对传入的参数做二次修改，再赋值给对应的对象 **/
    //将传入的参数 list_object 修改之后，再赋值给 thiz 对象实例中 field 对应的变量

    //获取 thiz 实例对象中 fieldId 对应的变量

/** 方式三：不启用传入的参数，重新 new 一个新的对象，重新赋值 **/

}

/**
 * 传参类型：Map数组-Map<整型>
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_mapIntegerFromJNI(JNIEnv *env, jobject thiz, jobject map_integer) {
    //获取实例对应的 class
    jclass jclazz = env->GetObjectClass(thiz);
    //通过 jclazz 获取对应变量的 fieldId
    jfieldID fid = env->GetFieldID(jclazz, "mapInteger", "Ljava/util/Map;");
    //将传入的参数 map_integer 赋值给 thiz 实例对象中 fieldId 对应的变量
    env->SetObjectField(thiz, fid, map_integer);
    //获取 thiz 对象中 fieldId 对应的对象
    jobject jobj = env->GetObjectField(thiz, fid);
    return jobj;
/* ------------------------------------------------------------------------- */
/** 方式一：将传入的参数，原封不动的赋值给对应的对象 **/

/** 方式二：对传入的参数做二次修改，再赋值给对应的对象 **/
    //将传入的参数 map_integer 修改之后，再赋值给 thiz 对象实例中 field 对应的变量

    //获取 thiz 实例对象中 fieldId 对应的变量

/** 方式三：不启用传入的参数，重新 new 一个新的对象，重新赋值 **/

}

/**
 * 传参类型：Map数组-Map<String>
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_mapStringFromJNI(JNIEnv *env, jobject thiz, jobject map_string) {
    //获取实例对应的 class
    jclass jclazz = env->GetObjectClass(thiz);
    //通过 jclazz 获取对应变量的 fieldId
    jfieldID fid = env->GetFieldID(jclazz, "mapString", "Ljava/util/Map;");
    //将传入的参数 map_string 赋值给 thiz 实例对象中 fieldId 对应的变量
    env->SetObjectField(thiz, fid, map_string);
    //获取 thiz 对象中 fieldId 对应的变量
    jobject jobj = env->GetObjectField(thiz, fid);
    return jobj;
/* ------------------------------------------------------------------------- */
/** 方式一：将传入的参数，原封不动的赋值给对应的对象 **/

/** 方式二：对传入的参数做二次修改，再赋值给对应的对象 **/
    //将传入的参数 map_string 修改之后，再赋值给 thiz 对象实例中 field 对应的变量

    //获取 thiz 实例对象中 fieldId 对应的变量

/** 方式三：不启用传入的参数，重新 new 一个新的对象，重新赋值 **/

}

/**
 * 传参类型：Map数组-Map<int[]>
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_mapIntegerArrayFromJNI(JNIEnv *env, jobject thiz, jobject map_integer_array) {
    //获取实例对象对应的 class
    jclass jclazz = env->GetObjectClass(thiz);
    //通过 jclazz 获取对应变量的 fieldId
    jfieldID fid = env->GetFieldID(jclazz, "mapIntegerArray", "Ljava/util/Map;");
    //将传入的参数 map_integer_array 赋值给 thiz 实例对象中 fieldId 对应的变量
    env->SetObjectField(thiz, fid, map_integer_array);
    //获取 thiz 实例对象中 fieldId 对应的变量
    jobject jobj = env->GetObjectField(thiz, fid);
    return jobj;
/* ------------------------------------------------------------------------- */
/** 方式一：将传入的参数，原封不动的赋值给对应的对象 **/

/** 方式二：对传入的参数做二次修改，再赋值给对应的对象 **/
    //将传入的参数 map_integer_array 修改之后，再赋值给 thiz 对象实例中 field 对应的变量

    //获取 thiz 实例对象中 fieldId 对应的变量

/** 方式三：不启用传入的参数，重新 new 一个新的对象，重新赋值 **/

}

/**
 * 传参类型：Map数组-Map<Object>
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_mapObjectFromJNI(JNIEnv *env, jobject thiz, jobject map_object) {
    //获取 thiz 实例对象对应的 class
    jclass jclazz = env->GetObjectClass(thiz);
    //通过 jclazz 获取对应变量的 fieldId
    jfieldID fid = env->GetFieldID(jclazz, "mapObject", "Ljava/util/Map;");
    //将传入的参数 mapObject 赋值给 thiz 实例对象中 fieldId 对应的变量
    env->SetObjectField(thiz, fid, map_object);
    //获取 thiz 实例对象中 fieldId 对应的变量
    jobject jobj = env->GetObjectField(thiz, fid);
    return jobj;
/* ------------------------------------------------------------------------- */
/** 方式一：将传入的参数，原封不动的赋值给对应的对象 **/

/** 方式二：对传入的参数做二次修改，再赋值给对应的对象 **/
    //将传入的参数 map_object 修改之后，再赋值给 thiz 对象实例中 field 对应的变量

    //获取 thiz 实例对象中 fieldId 对应的变量

/** 方式三：不启用传入的参数，重新 new 一个新的对象，重新赋值 **/

}

/**
 * 传参类型：集合嵌套集合-List<List>
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_listListFromJNI(JNIEnv *env, jobject thiz, jobject list_list) {
    //获取 thiz 实例对象对应的 class
    jclass jclazz = env->GetObjectClass(thiz);
    //通过 jclazz 获取对应变量的 fieldId
    jfieldID fid = env->GetFieldID(jclazz, "listList", "Ljava/util/List;");
    //将传入的参数 list_list 赋值给 thiz 对象实例中 fieldId 对应的变量
    env->SetObjectField(thiz, fid, list_list);
    //获取 thiz 对象实例中 fieldId 对应的 变量
    jobject jobj = env->GetObjectField(thiz, fid);
    return jobj;
/* ------------------------------------------------------------------------- */
/** 方式一：将传入的参数，原封不动的赋值给对应的对象 **/

/** 方式二：对传入的参数做二次修改，再赋值给对应的对象 **/
    //将传入的参数 list_list 修改之后，再赋值给 thiz 对象实例中 field 对应的变量

    //获取 thiz 实例对象中 fieldId 对应的变量

/** 方式三：不启用传入的参数，重新 new 一个新的对象，重新赋值 **/

}

/**
 * 传参类型：Map嵌套Map-Map<Map>
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_mapMapFromJNI(JNIEnv *env, jobject thiz, jobject map_map) {
    //获取 thiz 实例对象对应的 class
    jclass jclazz = env->GetObjectClass(thiz);
    //通过 jclazz 获取对应变量的 fieldId
    jfieldID fid = env->GetFieldID(jclazz, "mapMap", "Ljava/util/Map;");
    //将传入的参数 map_map 赋值给 thiz 对象实例中 fieldId 对应的变量
    env->SetObjectField(thiz, fid, map_map);
    //获取 thiz 对象实例中 fieldId 对应的变量
    jobject jobj = env->GetObjectField(thiz, fid);
    return jobj;
/* ------------------------------------------------------------------------- */
/** 方式一：将传入的参数，原封不动的赋值给对应的对象 **/

/** 方式二：对传入的参数做二次修改，再赋值给对应的对象 **/
    //将传入的参数 map_map 修改之后，再赋值给 thiz 对象实例中 field 对应的变量

    //获取 thiz 实例对象中 fieldId 对应的变量

/** 方式三：不启用传入的参数，重新 new 一个新的对象，重新赋值 **/

}