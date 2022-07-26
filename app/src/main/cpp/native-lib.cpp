#include <jni.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include "util/LogUtil.h"

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
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_nativeInteger(JNIEnv *env, jobject thiz, jint num) {
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
//    //将传入的参数 num 修改之后，再赋值给 thiz 对象实例中 field 对应的变量
//    num = 10068;
//    env->SetIntField(thiz, fid, num);
//    //获取 thiz 实例对象中 fieldId 对应的变量
//    jint newNum = env->GetIntField(thiz, fid);
//    return newNum;
/** 方式三：不启用传入的参数，重新 new 一个新的对象，重新赋值 **/
    jint newInt = 10068;
    //将新建的参数 newInt 赋值给 thiz 实例对象中 fieldId 对应的变量
    env->SetIntField(thiz, fid, newInt);
    //获取 thiz 对象中 fieldId 对应的对象
    jint newNum = env->GetIntField(thiz, fid);
    return newNum;
}

/**
 * 传参类型：char
 */
extern "C"
JNIEXPORT jchar JNICALL
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_nativeChar(JNIEnv *env, jobject thiz, jchar ch) {
    //获取实例对应的 class
    jclass jclazz = env->GetObjectClass(thiz);
    //通过 jcazz获取对应的变量 fieldId
    jfieldID fid = env->GetFieldID(jclazz, "ch", "C");
/* ------------------------------------------------------------------------- */
/** 方式一：将传入的参数，原封不动的赋值给对应的对象 **/
//    //将传入的参数 ch 赋值给 thiz 实例对象中 fieldId 对应的变量
//    env->SetCharField(thiz, fid, ch);
//    //通过 fieldId 获取对应的值
//    jchar newCh = env->GetCharField(thiz, fid);
//    return newCh;
/** 方式二：对传入的参数做二次修改，再赋值给对应的对象 **/
//    //将传入的参数 ch 修改之后，再赋值给 thiz 对象实例中 field 对应的变量
//    ch = 456;
//    env->SetCharField(thiz,fid,ch);
//    //获取 thiz 实例对象中 fieldId 对应的变量
//    jchar jch = env->GetCharField(thiz,fid);
//    return jch;
/** 方式三：不启用传入的参数，重新 new 一个新的对象，重新赋值 **/
    jchar newChar = 222;
    //将新建的参数 newChar 赋值给 thiz 实例对象中 fieldId 对应的变量
    env->SetCharField(thiz, fid, newChar);
    //获取 thiz 对象中 fieldId 对应的对象
    jchar jch = env->GetCharField(thiz, fid);
    return jch;
}

/**
 * 传参类型：string
 */
extern "C"
JNIEXPORT jstring JNICALL
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_nativeString(JNIEnv *env, jobject thiz, jstring str) {
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
//    //修改传入的参数
/*----------update style 1 start ----------*/
//    jboolean isCopy = JNI_FALSE; // 返回JNI_TRUE表示原字符串的拷贝，返回JNI_FALSE表示返回原字符串的指针
//    const char* chr = env->GetStringUTFChars(str,&isCopy);
//    char c[120] = "你好 2017";
//    strcat(c,chr);//把chr拼接到c
//    str = env->NewStringUTF(c);
/*----------update style 1 end ----------*/
/*----------update style 2 start ----------*/
//    char buff[128] = {0};
//    jboolean isCopy = JNI_FALSE; // 返回JNI_TRUE表示原字符串的拷贝，返回JNI_FALSE表示返回原字符串的指针
//    const char *chr = env->GetStringUTFChars(str, &isCopy);
//    sprintf(buff, "Junker %s", chr); //在 str 字符基础上拼接字符
//    str = env->NewStringUTF(buff);
/*----------update style 2 end ----------*/
//    //将传入的参数 str 修改之后，再赋值给 thiz 对象实例中 field 对应的变量
//    env->SetObjectField(thiz,fid,str);
//    //获取 thiz 对象中 fieldId 对应的对象
//    jstring jstr = static_cast<jstring>(env->GetObjectField(thiz, fid));
//
//    env->ReleaseStringUTFChars(str, chr);
//    return jstr;
/** 方式三：不启用传入的参数，重新 new 一个新的对象，重新赋值 **/
    jstring newJstr = env->NewStringUTF("你好 小爱");
    //将新建的参数 newJstr 赋值给 thiz 实例对象中 fieldId 对应的变量
    env->SetObjectField(thiz, fid, newJstr);
    //获取 thiz 对象中 fieldId 对应的对象
    jstring jstr = static_cast<jstring>(env->GetObjectField(thiz, fid));

    env->DeleteLocalRef(newJstr);
    return jstr;
}

/**
 * 传参类型：数组( int[]/ string[]/ ...)
 */
extern "C"
JNIEXPORT jintArray JNICALL
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_nativeIntArray(JNIEnv *env, jobject thiz, jintArray numS) {
    //获取实例对应的 class
    jclass jclazz = env->GetObjectClass(thiz);
    //通过 jclazz 获取对应的变量 fieldId
    jfieldID fid = env->GetFieldID(jclazz, "numS", "[I");
/* ------------------------------------------------------------------------- */
/** 方式一：将传入的参数，原封不动的赋值给对应的对象 **/
//    //将传入的参数 numS 赋值给 thiz 实例对象中 fieldId 对应的变量
//    env->SetObjectField(thiz, fid, numS);
//    //获取 thiz 对象中 fieldId 对应的对象
//    jobject jobj = env->GetObjectField(thiz, fid);//获取对象字段，返回JObject(因为Array是object的实例)
//    jintArray jarr = reinterpret_cast<jintArray>(jobj);
//    return jarr;
/** 方式二：对传入的参数做二次修改，再赋值给对应的对象 **/
//    //修改传入的参数 numS
//    jint *elems = env->GetIntArrayElements(numS, nullptr);//获取 numS 数组对应的第一个item指针
//    jsize length = env->GetArrayLength(numS);//获得 numS 数组的长度
//    for (int i = 0; i < length; ++i) {
//        LOGCATE("elems[i] = %d", elems[i]);//遍历数组起始元素的值
//    }
//    LOGCATE("---修改之后---");//补充：修改传进来的数据，相关链接：https://www.cnblogs.com/lenve/p/4889326.html
//    for (int i = 0; i < length; i++) {
//        elems[i] = elems[i] + 1;
//        LOGCATE("elems[i] = %d", elems[i]);//遍历数组修改之后的元素值
//    }
//    //将传入的参数 numS 修改之后，再赋值给 thiz 对象实例中 field 对应的变量
//    env->SetObjectField(thiz, fid, numS);
//    //获取 thiz 实例对象中 fieldId 对应的变量
//    jobject jobj = env->GetObjectField(thiz, fid);//获取对象字段，返回JObject(因为Array是object的实例)
//    jintArray jarr = reinterpret_cast<jintArray>(jobj);
//    env->ReleaseIntArrayElements(numS, elems, 0);
//    return jarr;
/** 方式三：不启用传入的参数，重新 new 一个新的对象，重新赋值 **/
    //新建变量
    const int length = 3;
    jintArray newJintArr = env->NewIntArray(length);
    jint nativeArr[length] = {21, 22, 23};
    env->SetIntArrayRegion(newJintArr, 0, length, nativeArr);
    //将新建的参数 newJintArr 赋值给 thiz 实例对象中 fieldId 对应的变量
    env->SetObjectField(thiz, fid, newJintArr);
    //获取 thiz 对象中 fieldId 对应的对象
    jobject jobj = env->GetObjectField(thiz, fid);
    jintArray jarr = reinterpret_cast<jintArray>(jobj);
    return jarr;
}

/**
 * 传参类型：对象
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_nativeObject(JNIEnv *env, jobject thiz, jobject obj) {
    //获取实例对应的 class
    jclass jclazz = env->GetObjectClass(thiz);
    //通过 jclazz 获取对应变量的 fieldId
    jfieldID fid = env->GetFieldID(jclazz, "bean", "Lcom/junker/cplusplus/and/java/jni/study/bean/DataBean;");
/** 方式一：将传入的参数，原封不动的赋值给对应的对象 **/
//    //将传入的参数 obj 赋值给 thiz 实例对象中 fieldId 对应的变量
//    env->SetObjectField(thiz, fid, obj);
//    //获取 thiz 对象中 fieldId 对应的对象
//    jobject jobj = env->GetObjectField(thiz, fid);
//    return jobj;
/** 方式二：对传入的参数做二次修改，再赋值给对应的对象 **/
//    //修改传入的参数
//    jclass jclaChild = env->GetObjectClass(obj);
//    jfieldID nameFid = env->GetFieldID(jclaChild,"name", "Ljava/lang/String;");
//    jfieldID ageFid = env->GetFieldID(jclaChild,"age", "I");
//    //设置名字
//    jstring jstr = static_cast<jstring>(env->GetObjectField(obj, nameFid));
//    const char *chr = env->GetStringUTFChars(jstr,JNI_FALSE);
//    char buff[120] = "你好 张三 ";
//    strcat(buff,chr);//把chr拼接到c
//    jstr = env->NewStringUTF(buff);
//    env->SetObjectField(obj,nameFid,jstr);
//    //设置年龄
//    env->SetIntField(obj,ageFid,23);
//    //将传入的参数 obj 修改之后，再赋值给 thiz 对象实例中 field 对应的变量
//    env->SetObjectField(thiz,fid,obj);
//    //获取 thiz 实例对象中 fieldId 对应的变量
//    jobject jobj = env->GetObjectField(thiz,fid);
//
//    env->ReleaseStringUTFChars(jstr,chr);
//    env->DeleteLocalRef(jstr);
//    return jobj;
/** 方式三：不启用传入的参数，重新 new 一个新的对象，重新赋值 **/
    jclass newClazz = env->FindClass("com/junker/cplusplus/and/java/jni/study/bean/DataBean");
    char *method_name = "<init>";//获取构造函数名
    char *method_sign = "(Ljava/lang/String;I)V";//获取构造参数格式
    jmethodID constructor_method_id = env->GetMethodID(newClazz, method_name, method_sign);//构造函数
    //创建新对象
    char buff[120] = "你好 张三";
    jstring buffStr = env->NewStringUTF(buff);
    jobject newObj = env->NewObject(newClazz, constructor_method_id, buffStr, 11);
    //将新建的参数 newObj 赋值给 thiz 实例对象中 fieldId 对应的变量
    env->SetObjectField(thiz, fid, newObj);
    //获取 thiz 对象中 fieldId 对应的对象
    jobject jobj = env->GetObjectField(thiz, fid);
    return jobj;
}

/**
 * 传参类型：集合-List<整型>
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_nativeListInteger(JNIEnv *env, jobject thiz, jobject list_integer) {
    //获取实例对应的 class
    jclass jclazz = env->GetObjectClass(thiz);
    //通过 jclazz 获取对应变量的 fieldId
    jfieldID fid = env->GetFieldID(jclazz, "list", "Ljava/util/List;");
/* ------------------------------------------------------------------------- */
/** 方式一：将传入的参数，原封不动的赋值给对应的对象 **/
//    //将传入的参数 list 赋值给 thiz 实例对象中 fieldId 对应的变量
//    env->SetObjectField(thiz, fid, list);
//    //获取 thiz 对象中 fieldId 对应的对象
//    jobject jobj = env->GetObjectField(thiz, fid);
//    return jobj;
/** 方式二：对传入的参数做二次修改，再赋值给对应的对象 **/
//    //修改传入的参数
//    jclass array_class = env->GetObjectClass(list_integer);//获取 List 集合 class
//    jmethodID mod_set = env->GetMethodID(array_class,"set", "(ILjava/lang/Object;)Ljava/lang/Object;");//获取List类中set的方法ID
//    jclass integer_class = env->FindClass("java/lang/Integer");//获取 Integer 类
//    jmethodID mod_int_value = env->GetStaticMethodID(integer_class,"valueOf", "(I)Ljava/lang/Integer;");//获取 Integer类中 静态方法
//    jobject integer_obj = env->CallStaticObjectMethod(integer_class,mod_int_value,27);//通过静态方法创建 Integer对象实例
//    env->CallObjectMethod(list_integer,mod_set,0,integer_obj);//修改 list_integer 集合中第一个数据的value
//    //将传入的参数 list_integer 修改之后，再赋值给 thiz 对象实例中 field 对应的变量
//    env->SetObjectField(thiz, fid, list_integer);
//    //获取 thiz 实例对象中 fieldId 对应的变量
//    jobject jobj = env->GetObjectField(thiz, fid);
//
//    env->DeleteLocalRef(integer_obj);
//    return jobj;
/** 方式三：不启用传入的参数，重新 new 一个新的对象，重新赋值 **/
    //创建新对象
    jclass cls_array = env->FindClass("java/util/ArrayList"); //获取 ArrayList class
    jmethodID mod_init = env->GetMethodID(cls_array, "<init>", "()V");//获取 ArrayList 构造函数
    jmethodID mod_add = env->GetMethodID(cls_array, "add", "(Ljava/lang/Object;)Z");//获取 ArrayList add方法ID
    jobject obj_array = env->NewObject(cls_array, mod_init);//创建 ArrayList 实例对象
    jclass cls_integer = env->FindClass("java/lang/Integer");//获取 Integer class
    jmethodID mod_init_integer = env->GetStaticMethodID(cls_integer, "valueOf", "(I)Ljava/lang/Integer;");//获取用于创建 Integer 实例对象 valueOf 静态方法ID
    jobject obj_integer = env->CallStaticObjectMethod(cls_integer, mod_init_integer, 27);//通过 valueOf静态方法创建 Integer 对象实例
    env->CallBooleanMethod(obj_array, mod_add, obj_integer);//将 Integer 对象添加到 ArrayList 集合中
    //将新建的参数 cls_array 赋值给 thiz 实例对象中 fieldId 对应的变量
    env->SetObjectField(thiz, fid, obj_array);
    //获取 thiz 对象中 fieldId 对应的对象
    jobject j_obj = env->GetObjectField(thiz, fid);

    env->DeleteLocalRef(obj_array);
    env->DeleteLocalRef(cls_integer);
    return j_obj;
}

/**
 * 传参类型：集合-List<String>
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_nativeListString(JNIEnv *env, jobject thiz, jobject list_string) {
    //获取实例对应的 class
    jclass jclazz = env->GetObjectClass(thiz);
    //通过 jclazz 获取对应变量的 fieldId
    jfieldID fid = env->GetFieldID(jclazz, "listString", "Ljava/util/List;");
/* ------------------------------------------------------------------------- */
/** 方式一：将传入的参数，原封不动的赋值给对应的对象 **/
//    //将传入的参数 list_string 赋值给 thiz 实例对象中 fieldId 对应的变量
//    env->SetObjectField(thiz, fid, list_string);
//    //获取 thiz 对象中 fieldId 对应的对象
//    jobject jobj = env->GetObjectField(thiz, fid);
//    return jobj;
/** 方式二：对传入的参数做二次修改，再赋值给对应的对象 **/
//    //修改传入的 list_string 参数
//    jclass cls_list = env->GetObjectClass(list_string);
//    jmethodID mod_set = env->GetMethodID(cls_list,"set", "(ILjava/lang/Object;)Ljava/lang/Object;");
//    jstring item_str = env->NewStringUTF("Junker");
//    env->CallObjectMethod(list_string,mod_set,0,item_str);
//    //将传入的参数 list_string 修改之后，再赋值给 thiz 对象实例中 field 对应的变量
//    env->SetObjectField(thiz,fid,list_string);
//    //获取 thiz 实例对象中 fieldId 对应的变量
//    jobject j_obj = env->GetObjectField(thiz,fid);
//    return j_obj;
/** 方式三：不启用传入的参数，重新 new 一个新的对象，重新赋值 **/
    //创建新对象
    jclass array_class = env->FindClass("java/util/ArrayList");//获取 ArrayList class
    jmethodID mod_init = env->GetMethodID(array_class, "<init>", "()V");//获取 ArrayList 构造方法ID
    jmethodID mod_add = env->GetMethodID(array_class, "add", "(Ljava/lang/Object;)Z");//获取 ArrayList add方法ID
    jstring item_str = env->NewStringUTF("Junker");//创建一个 string 对象
    jobject obj_array = env->NewObject(array_class, mod_init);//创建一个 ArrayList 对象
    env->CallBooleanMethod(obj_array, mod_add, item_str);//给 ArrayList 对象添加 数据
    //将新建的参数 array_class 赋值给 thiz 实例对象中 fieldId 对应的变量
    env->SetObjectField(thiz, fid, obj_array);
    //获取 thiz 对象中 fieldId 对应的对象
    jobject j_obj = env->GetObjectField(thiz, fid);

    env->DeleteLocalRef(obj_array);
    return j_obj;
}

/**
 * 传参类型：集合-List<int[]>
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_nativeListIntArray(JNIEnv *env, jobject thiz, jobject list_int_array) {
    //获取实例对应的 class
    jclass jcazz = env->GetObjectClass(thiz);
    //通过 jclazz 获取对应变量的 fieldId
    jfieldID fid = env->GetFieldID(jcazz, "listIntArray", "Ljava/util/List;");
/* ------------------------------------------------------------------------- */
/** 方式一：将传入的参数，原封不动的赋值给对应的对象 **/
//    //将传入的参数 list_int_array 赋值给 thiz 实例对象中 fieldId 对应的变量
//    env->SetObjectField(thiz, fid, list_int_array);
//    //获取 thiz 对象中 fieldId 对应的对象
//    jobject jobj = env->GetObjectField(thiz, fid);
//    return jobj;
/** 方式二：对传入的参数做二次修改，再赋值给对应的对象 **/
//    //修改传入的参数
//    jclass cls_list = env->GetObjectClass(list_int_array);
//    jmethodID mod_set = env->GetMethodID(cls_list,"set", "(ILjava/lang/Object;)Ljava/lang/Object;");
//    jmethodID mod_get = env->GetMethodID(cls_list,"get", "(I)Ljava/lang/Object;");
//    jintArray item_arr = reinterpret_cast<jintArray>(env->CallObjectMethod(list_int_array,mod_get,0));
//    jint* elem = env->GetIntArrayElements(item_arr, nullptr);
//    jint length = env->GetArrayLength(item_arr);
//    for (int i = 0; i < length; ++i) {
//        elem[i] = elem[i]+25;
//    }
//    //将传入的参数 list_int_array 修改之后，再赋值给 thiz 对象实例中 field 对应的变量
//    env->SetObjectField(thiz,fid,list_int_array);
//
//    //获取 thiz 实例对象中 fieldId 对应的变量
//    jobject j_obj = env->GetObjectField(thiz,fid);
//    return j_obj;
/** 方式三：不启用传入的参数，重新 new 一个新的对象，重新赋值 **/
    //创建新对象
    jclass cls_array = env->FindClass("java/util/ArrayList");//获取 ArrayList class
    jmethodID cls_init = env->GetMethodID(cls_array, "<init>", "()V");//获取 ArrayList 构造函数
    jmethodID cls_add = env->GetMethodID(cls_array, "add", "(Ljava/lang/Object;)Z");//获取 ArrayList add方法ID
    jobject obj_list = env->NewObject(cls_array, cls_init);//创建 ArrayList 实例对象
    jintArray array = env->NewIntArray(3);//创建 jintArray 对象
    jsize length = env->GetArrayLength(array);
    jint item[] = {2, 3, 4};
    env->SetIntArrayRegion(array, 0, length, item);//给 jintArray 对象赋值
    env->CallBooleanMethod(obj_list, cls_add, array);//给 ArrayList 添加数据
    //将新建的参数 obj_list 赋值给 thiz 实例对象中 fieldId 对应的变量
    env->SetObjectField(thiz, fid, obj_list);
    //获取 thiz 对象中 fieldId 对应的对象
    jobject j_obj = env->GetObjectField(thiz, fid);
    return j_obj;
}

/**
 * 传参类型：集合-List<Object>
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_nativeListObject(JNIEnv *env, jobject thiz, jobject list_object) {
    //获取实例对应的 class
    jclass jclazz = env->GetObjectClass(thiz);
    //通过 jclazz 获取对应变量的 fieldId
    jfieldID fid = env->GetFieldID(jclazz, "listObject", "Ljava/util/List;");
/* ------------------------------------------------------------------------- */
/** 方式一：将传入的参数，原封不动的赋值给对应的对象 **/
//    //将传入的参数 list_object 赋值给 thiz 实例对象中 fieldId 对应的变量
//    env->SetObjectField(thiz, fid, list_object);
//    //获取 thiz 对象中 fieldId 对应的对象
//    jobject j_obj = env->GetObjectField(thiz, fid);
//    return j_obj;
/** 方式二：对传入的参数做二次修改，再赋值给对应的对象 **/
//    //修改传入的参数
//    jclass valueClass = env->GetObjectClass(list_object);
//    jclass bean_cls = env->FindClass("com/junker/cplusplus/and/java/jni/study/bean/DataBean");
//    jmethodID bean_init = env->GetMethodID(bean_cls, "<init>", "(Ljava/lang/String;I)V");
//    jstring new_name = env->NewStringUTF("Junker");
//    jobject new_bean = env->NewObject(bean_cls, bean_init, new_name, 27);
//    jmethodID list_set = env->GetMethodID(valueClass, "set", "(ILjava/lang/Object;)Ljava/lang/Object;");//获取List对象的 set() 的 methodID
//    env->CallObjectMethod(list_object, list_set, 0, new_bean);
//    //将传入的参数 list_object 修改之后，再赋值给 thiz 对象实例中 field 对应的变量
//    env->SetObjectField(thiz, fid, list_object);
//    //获取 thiz 实例对象中 fieldId 对应的变量
//    jobject j_obj = env->GetObjectField(thiz, fid);
//    return j_obj;
/** 方式三：不启用传入的参数，重新 new 一个新的对象，重新赋值 **/
    //创建新对象
    jclass list_jcs = env->FindClass("java/util/ArrayList");//获取 ArrayList class
    jmethodID list_init = env->GetMethodID(list_jcs, "<init>", "()V");//获取 ArrayList 构造函数
    jobject array_list = env->NewObject(list_jcs, list_init);//创建 ArrayList 对象
    jmethodID add_mid = env->GetMethodID(list_jcs, "add", "(Ljava/lang/Object;)Z");//获取 ArrayList add方法ID
    jclass bean_class = env->FindClass("com/junker/cplusplus/and/java/jni/study/bean/DataBean");//获取 DataBean class
    jmethodID bean_init = env->GetMethodID(bean_class, "<init>", "(Ljava/lang/String;I)V");//获取 DataBean 构造函数
    //将新建的参数 array_list 赋值给 thiz 实例对象中 fieldId 对应的变量
    jstring name = env->NewStringUTF("Junker");
    jobject bean_obj = env->NewObject(bean_class, bean_init, name, 27);
    env->CallBooleanMethod(array_list, add_mid, bean_obj);
    env->SetObjectField(thiz, fid, array_list);
    //获取 thiz 对象中 fieldId 对应的对象
    jobject j_obj = env->GetObjectField(thiz, fid);
    return j_obj;
}

/**
 * 传参类型：Map数组-Map<整型>
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_nativeMapInteger(JNIEnv *env, jobject thiz, jobject map_integer) {
    //获取实例对应的 class
    jclass jclazz = env->GetObjectClass(thiz);
    //通过 jclazz 获取对应变量的 fieldId
    jfieldID fid = env->GetFieldID(jclazz, "mapInteger", "Ljava/util/Map;");
/* ------------------------------------------------------------------------- */
/** 方式一：将传入的参数，原封不动的赋值给对应的对象 **/
//    //将传入的参数 map_integer 赋值给 thiz 实例对象中 fieldId 对应的变量
//    env->SetObjectField(thiz, fid, map_integer);
//    //获取 thiz 对象中 fieldId 对应的对象
//    jobject jobj = env->GetObjectField(thiz, fid);
//    return jobj;
/** 方式二：对传入的参数做二次修改，再赋值给对应的对象 **/
//    //修改传入的参数
//    jclass cls_map = env->GetObjectClass(map_integer);//获取传入的对象参数 class
//    jmethodID mod_get = env->GetMethodID(cls_map,"get", "(Ljava/lang/Object;)Ljava/lang/Object;");//获取 map get方法ID
//    jmethodID mod_replace = env->GetMethodID(cls_map,"replace", "(Ljava/lang/Object;Ljava/lang/Object;Ljava/lang/Object;)Z");//获取 map replace方法ID
//    jclass cls_integer = env->FindClass("java/lang/Integer");//获取 Integer class
//    jmethodID mod_static_init = env->GetStaticMethodID(cls_integer,"valueOf", "(I)Ljava/lang/Integer;");//获取 Integer  valueOf静态函数ID
////    jmethodID mod_intValue = env->GetMethodID(cls_integer,"intValue", "()I");//获取 Integer intValue函数ID
//    jobject map_key = env->CallStaticObjectMethod(cls_integer,mod_static_init,1);//实例化 Integer 对象并赋初始值
//    jobject map_value = env->CallObjectMethod(map_integer,mod_get,map_key);//获取传入的 map_integer 对象中 map_key 对应 value 值
//    jobject map_new_value = env->CallStaticObjectMethod(cls_integer,mod_static_init,10086);
//    env->CallBooleanMethod(map_integer,mod_replace,map_key,map_value,map_new_value);
//    //将传入的参数 map_integer 修改之后，再赋值给 thiz 对象实例中 field 对应的变量
//    env->SetObjectField(thiz,fid,map_integer);
//    //获取 thiz 实例对象中 fieldId 对应的变量
//    jobject j_obj = env->GetObjectField(thiz,fid);
//    return j_obj;
/** 方式三：不启用传入的参数，重新 new 一个新的对象，重新赋值 **/
    //创建新对象
    jclass cls_hashmap = env->FindClass("java/util/HashMap");
    jmethodID mod_init = env->GetMethodID(cls_hashmap, "<init>", "()V");
    jmethodID mod_put = env->GetMethodID(cls_hashmap, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");
    jobject obj_hashmap = env->NewObject(cls_hashmap, mod_init);
    jclass cls_integer = env->FindClass("java/lang/Integer");
    jmethodID mod_valueOf = env->GetStaticMethodID(cls_integer, "valueOf", "(I)Ljava/lang/Integer;");
    for (int i = 0; i < 3; ++i) {
        jobject obj_integer_key = env->CallStaticObjectMethod(cls_integer, mod_valueOf, i);
        jobject obj_integer_value = env->CallStaticObjectMethod(cls_integer, mod_valueOf, 10081 + i);
        env->CallObjectMethod(obj_hashmap, mod_put, obj_integer_key, obj_integer_value);

        env->DeleteLocalRef(obj_integer_key);
        env->DeleteLocalRef(obj_integer_value);
    }
    //将新建的参数 obj_hashmap 赋值给 thiz 实例对象中 fieldId 对应的变量
    env->SetObjectField(thiz, fid, obj_hashmap);
    //获取 thiz 对象中 fieldId 对应的对象
    jobject j_obj = env->GetObjectField(thiz, fid);
    return j_obj;
}

/**
 * 传参类型：Map数组-Map<String>
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_nativeMapString(JNIEnv *env, jobject thiz, jobject map_string) {
    //获取实例对应的 class
    jclass jclazz = env->GetObjectClass(thiz);
    //通过 jclazz 获取对应变量的 fieldId
    jfieldID fid = env->GetFieldID(jclazz, "mapString", "Ljava/util/Map;");
/* ------------------------------------------------------------------------- */
/** 方式一：将传入的参数，原封不动的赋值给对应的对象 **/
//    //将传入的参数 map_string 赋值给 thiz 实例对象中 fieldId 对应的变量
//    env->SetObjectField(thiz, fid, map_string);
//    //获取 thiz 对象中 fieldId 对应的变量
//    jobject j_obj = env->GetObjectField(thiz, fid);
//    return jobj;
/** 方式二：对传入的参数做二次修改，再赋值给对应的对象 **/
//    //修改传入的参数
//    jclass cls_map = env->GetObjectClass(map_string);//获取 map class
//    jmethodID mod_replace = env->GetMethodID(cls_map,"replace", "(Ljava/lang/Object;Ljava/lang/Object;Ljava/lang/Object;)Z");//获取 map replace方法ID
//    jmethodID mod_get = env->GetMethodID(cls_map,"get", "(Ljava/lang/Object;)Ljava/lang/Object;");//获取 map get方法ID
//    jstring str_key = env->NewStringUTF("two");//two 需要和java层传入的key值对应
//    jobject obj_value = env->CallObjectMethod(map_string,mod_get,str_key);//获取 map_string 中 str_key 对应的 str_value 值
//    auto str_value = reinterpret_cast<jstring>(obj_value);//将 jobject 对象转化成 jstring 对象
//    if (str_value){
//        const char* ch = env->GetStringUTFChars(str_value, JNI_FALSE);//获取 jstring 对象内容的指针
//        char item[120] = "and custom";//新建一个 char 数组
//        strcat(item,ch);//将 jstring 内容 附加到 item 后面
//        jstring str_new_value = env->NewStringUTF(item);//新建一个 jstring 实例
//        env->CallBooleanMethod(map_string,mod_replace,str_key,obj_value,str_new_value);//修改 map_string 对象中 str_key 对应的 value 值
//
//        env->ReleaseStringUTFChars(str_value,ch);//释放内存
//    }
//    //将传入的参数 map_string 修改之后，再赋值给 thiz 对象实例中 field 对应的变量
//    env->SetObjectField(thiz,fid,map_string);
//    //获取 thiz 实例对象中 fieldId 对应的变量
//    jobject j_obj = env->GetObjectField(thiz,fid);
//    return j_obj;
/** 方式三：不启用传入的参数，重新 new 一个新的对象，重新赋值 **/
    //创建新对象
    jclass cls_hashmap = env->FindClass("java/util/HashMap");
    jmethodID mod_init = env->GetMethodID(cls_hashmap, "<init>", "()V");
    jmethodID mod_put = env->GetMethodID(cls_hashmap, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");
    jobject obj_hashmap = env->NewObject(cls_hashmap, mod_init);
    env->CallObjectMethod(obj_hashmap, mod_put, env->NewStringUTF("1"), env->NewStringUTF("Junker"));
    env->CallObjectMethod(obj_hashmap, mod_put, env->NewStringUTF("2"), env->NewStringUTF("Jerry"));
    env->CallObjectMethod(obj_hashmap, mod_put, env->NewStringUTF("3"), env->NewStringUTF("Bob"));
    //将新建的参数 obj_hashmap 赋值给 thiz 实例对象中 fieldId 对应的变量
    env->SetObjectField(thiz, fid, obj_hashmap);
    //获取 thiz 对象中 fieldId 对应的对象
    jobject j_obj = env->GetObjectField(thiz, fid);
    return j_obj;
}

/**
 * 传参类型：Map数组-Map<int[]>
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_nativeMapIntegerArray(JNIEnv *env, jobject thiz, jobject map_integer_array) {
    //获取实例对象对应的 class
    jclass jclazz = env->GetObjectClass(thiz);
    //通过 jclazz 获取对应变量的 fieldId
    jfieldID fid = env->GetFieldID(jclazz, "mapIntegerArray", "Ljava/util/Map;");
/* ------------------------------------------------------------------------- */
/** 方式一：将传入的参数，原封不动的赋值给对应的对象 **/
//    //将传入的参数 map_integer_array 赋值给 thiz 实例对象中 fieldId 对应的变量
//    env->SetObjectField(thiz, fid, map_integer_array);
//    //获取 thiz 实例对象中 fieldId 对应的变量
//    jobject jobj = env->GetObjectField(thiz, fid);
//    return jobj;
/** 方式二：对传入的参数做二次修改，再赋值给对应的对象 **/
//    //修改传入的参数
//    jclass cls_map = env->FindClass("java/util/Map");
//    jmethodID mod_replace = env->GetMethodID(cls_map,"replace", "(Ljava/lang/Object;Ljava/lang/Object;Ljava/lang/Object;)Z");
//    jmethodID mod_get = env->GetMethodID(cls_map,"get", "(Ljava/lang/Object;)Ljava/lang/Object;");
//    jclass cls_integer = env->FindClass("java/lang/Integer");
//    jmethodID mod_valueOf = env->GetStaticMethodID(cls_integer,"valueOf", "(I)Ljava/lang/Integer;");
//    jobject obj_integer_key = env->CallStaticObjectMethod(cls_integer,mod_valueOf,1);//创建 Integer 对象用作 map 对象的 key 值
//    jobject obj_value = env->CallObjectMethod(map_integer_array,mod_get,obj_integer_key);//获取 map 中 obj_integer_key key 对应的 原始 value 值
//    if (obj_value){
//        auto array_value = reinterpret_cast<jintArray>(obj_value);
//        jint* elem = env->GetIntArrayElements(array_value, nullptr);
//        jsize length = env->GetArrayLength(array_value);
//        for (int i = 0; i < length; ++i) {
//            elem[i] = elem[i]+1000;
//        }
//        env->CallBooleanMethod(map_integer_array,mod_replace,obj_integer_key,obj_value,array_value);//更新 map 中 obj_integer_key key 对应的 value 值
//
//        env->ReleaseIntArrayElements(array_value,elem,0);//释放内存
//    }
//    //将传入的参数 map_integer_array 修改之后，再赋值给 thiz 对象实例中 field 对应的变量
//    env->SetObjectField(thiz,fid,map_integer_array);
//    //获取 thiz 实例对象中 fieldId 对应的变量
//    jobject j_obj = env->GetObjectField(thiz,fid);
//    return j_obj;
/** 方式三：不启用传入的参数，重新 new 一个新的对象，重新赋值 **/
    //创建新对象
    jclass cls_hashmap = env->FindClass("java/util/HashMap");//获取 HashMap class
    jmethodID mod_init = env->GetMethodID(cls_hashmap, "<init>", "()V");//获取 HashMap 构造函数ID
    jmethodID mod_put = env->GetMethodID(cls_hashmap, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");//获取 HashMap get方法ID
    jobject obj_hashmap = env->NewObject(cls_hashmap, mod_init);//创建 HashMap 对象实例
    jclass cls_integer = env->FindClass("java/lang/Integer");//获取 Integer class
    jmethodID mod_valueOf = env->GetStaticMethodID(cls_integer, "valueOf", "(I)Ljava/lang/Integer;");//获取 Integer valueOf静态成员函数ID
    for (int i = 0; i < 3; ++i) {
        jobject obj_key = env->CallStaticObjectMethod(cls_integer, mod_valueOf, 001 + i);//通过 Integer valueOf静态成员函数创建 Integer 对象并赋初始值
        jintArray array_value = env->NewIntArray(3);//创建 jintArray 对象并设置长度
        jsize length = env->GetArrayLength(array_value);//获取 jintArray 长度
        jint elem[] = {111 + i, 222 + i, 333 + i};//创建 jint 数组
        env->SetIntArrayRegion(array_value, 0, length, elem);//给 array_value 数组赋值
        env->CallObjectMethod(obj_hashmap, mod_put, obj_key, array_value);//给新建的 obj_hashmap 对象添加数据
    }
    //将新建的参数 obj_hashmap 赋值给 thiz 实例对象中 fieldId 对应的变量
    env->SetObjectField(thiz, fid, obj_hashmap);
    //获取 thiz 对象中 fieldId 对应的对象
    jobject j_obj = env->GetObjectField(thiz, fid);
    return j_obj;
}

/**
 * 传参类型：Map数组-Map<Object>
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_nativeMapObject(JNIEnv *env, jobject thiz, jobject map_object) {
    //获取 thiz 实例对象对应的 class
    jclass jclazz = env->GetObjectClass(thiz);
    //通过 jclazz 获取对应变量的 fieldId
    jfieldID fid = env->GetFieldID(jclazz, "mapObject", "Ljava/util/Map;");
/* ------------------------------------------------------------------------- */
/** 方式一：将传入的参数，原封不动的赋值给对应的对象 **/
//    //将传入的参数 mapObject 赋值给 thiz 实例对象中 fieldId 对应的变量
//    env->SetObjectField(thiz, fid, map_object);
//    //获取 thiz 实例对象中 fieldId 对应的变量
//    jobject jobj = env->GetObjectField(thiz, fid);
//    return jobj;
/** 方式二：对传入的参数做二次修改，再赋值给对应的对象 **/
//    //修改传入的参数
//    jclass cls_map = env->GetObjectClass(map_object);//获取 map_object 对应的 class
//    jmethodID mod_get = env->GetMethodID(cls_map,"get", "(Ljava/lang/Object;)Ljava/lang/Object;");//获取 Map get函数ID
////    jmethodID mod_replace = env->GetMethodID(cls_map,"replace", "(Ljava/lang/Object;Ljava/lang/Object;Ljava/lang/Object;)Z");
//    jclass cls_integer = env->FindClass("java/lang/Integer");//获取 Integer class
//    jmethodID mod_valueOf = env->GetStaticMethodID(cls_integer,"valueOf", "(I)Ljava/lang/Integer;");//获取 Integer valueOf静态成员函数ID
//    jclass cls_bean = env->FindClass("com/junker/cplusplus/and/java/jni/study/bean/DataBean");//获取 DataBean class
//    jmethodID mod_setName = env->GetMethodID(cls_bean,"setName", "(Ljava/lang/String;)V");//获取 DataBean setName函数ID
//    jmethodID mod_setAge = env->GetMethodID(cls_bean,"setAge", "(I)V");//获取 DataBean setAge函数ID
//    jobject obj_integer_key = env->CallStaticObjectMethod(cls_integer,mod_valueOf,1);//通过 valueOf 静态成员函数创建 Integer 对象并赋值
//    jobject obj_bean_value = env->CallObjectMethod(map_object,mod_get,obj_integer_key);//获取 map_object 中 key=1 对应的 value 对象
//    env->CallVoidMethod(obj_bean_value,mod_setName,env->NewStringUTF("新名字"));//通过 setName 函数更新 name 值
//    env->CallVoidMethod(obj_bean_value,mod_setAge,31);//通过 setAge 函数更新 age 值
//    //将传入的参数 map_object 修改之后，再赋值给 thiz 对象实例中 field 对应的变量
//    env->SetObjectField(thiz,fid,map_object);
//    //获取 thiz 实例对象中 fieldId 对应的变量
//    jobject j_obj = env->GetObjectField(thiz,fid);
//    return j_obj;
/** 方式三：不启用传入的参数，重新 new 一个新的对象，重新赋值 **/
    //创建新对象
    jclass cls_hashmap = env->FindClass("java/util/HashMap");//获取HashMap class
    jmethodID mod_hashmap_init = env->GetMethodID(cls_hashmap, "<init>", "()V");//获取 HashMap 构造函数
    jmethodID mod_put = env->GetMethodID(cls_hashmap, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");//获取 HashMap put方法ID
    jclass cls_integer = env->FindClass("java/lang/Integer");//获取 Integer class
    jmethodID mod_valueOf = env->GetStaticMethodID(cls_integer, "valueOf", "(I)Ljava/lang/Integer;");//获取 Integer valueOf静态函数ID
    jclass cls_bean = env->FindClass("com/junker/cplusplus/and/java/jni/study/bean/DataBean");//获取 DataBean class
    jmethodID mod_bean_init = env->GetMethodID(cls_bean, "<init>", "(Ljava/lang/String;I)V");//获取 DataBean 构造函数
    jobject obj_hashmap = env->NewObject(cls_hashmap, mod_hashmap_init);//创建 HashMap 对象
    for (int i = 0; i < 3; ++i) {
        jobject key_integer = env->CallStaticObjectMethod(cls_integer, mod_valueOf, 1000 + i);//创建 Integer 对象
        jobject value_bean = env->NewObject(cls_bean, mod_bean_init, env->NewStringUTF("我是超人"), 100 + i);//创建 DataBean 对象
        env->CallObjectMethod(obj_hashmap, mod_put, key_integer, value_bean);//给 HashMap 对象添加数据
    }
    //将新建的参数 obj_hashmap 赋值给 thiz 实例对象中 fieldId 对应的变量
    env->SetObjectField(thiz, fid, obj_hashmap);
    //获取 thiz 对象中 fieldId 对应的对象
    jobject j_obj = env->GetObjectField(thiz, fid);
    return j_obj;
}

/**
 * 传参类型：集合嵌套集合-List<List>
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_nativeListList(JNIEnv *env, jobject thiz, jobject list_list) {
    //获取 thiz 实例对象对应的 class
    jclass jclazz = env->GetObjectClass(thiz);
    //通过 jclazz 获取对应变量的 fieldId
    jfieldID fid = env->GetFieldID(jclazz, "listList", "Ljava/util/List;");
/* ------------------------------------------------------------------------- */
/** 方式一：将传入的参数，原封不动的赋值给对应的对象 **/
//    //将传入的参数 list_list 赋值给 thiz 对象实例中 fieldId 对应的变量
//    env->SetObjectField(thiz, fid, list_list);
//    //获取 thiz 对象实例中 fieldId 对应的 变量
//    jobject jobj = env->GetObjectField(thiz, fid);
//    return jobj;
/** 方式二：对传入的参数做二次修改，再赋值给对应的对象 **/
//    //修改传入的参数
//    jclass cls_list = env->GetObjectClass(list_list);//获取参数 list_list 对应的 class
//    jmethodID mod_get = env->GetMethodID(cls_list,"get", "(I)Ljava/lang/Object;");//获取 List get函数ID
//    jmethodID mod_set = env->GetMethodID(cls_list,"set", "(ILjava/lang/Object;)Ljava/lang/Object;");//获取 List set函数ID
//    jclass cls_bean = env->FindClass("com/junker/cplusplus/and/java/jni/study/bean/DataBean");//获取 DataBean class
//    jmethodID setName = env->GetMethodID(cls_bean,"setName", "(Ljava/lang/String;)V");//获取 DataBean setName函数ID
//    jmethodID setAge = env->GetMethodID(cls_bean,"setAge", "(I)V");//获取 DataBean setAge函数ID
//    jobject obj_list = env->CallObjectMethod(list_list,mod_get,0);//获取 list_list 对应索引的对象
//    jobject obj_list_bean = env->CallObjectMethod(obj_list,mod_get,0);//获取 list_list_item 对应的 DataBean 对象
//    env->CallVoidMethod(obj_list_bean,setName,env->NewStringUTF("Junker"));//重新给 obj_list_bean 对象DataBean name参数 赋值
//    env->CallVoidMethod(obj_list_bean,setAge,27);////重新给 obj_list_bean 对象DataBean age参数 赋值
//    //将传入的参数 list_list 修改之后，再赋值给 thiz 对象实例中 field 对应的变量
//    env->SetObjectField(thiz,fid,list_list);
//    //获取 thiz 实例对象中 fieldId 对应的变量
//    jobject j_obj = env->GetObjectField(thiz,fid);
//    return j_obj;
/** 方式三：不启用传入的参数，重新 new 一个新的对象，重新赋值 **/
    //创建新对象
    jclass cls_arraylist = env->FindClass("java/util/ArrayList");//获取 ArrayList class
    jmethodID mod_list_init = env->GetMethodID(cls_arraylist, "<init>", "()V");//获取 ArrayList 构造函数ID
    jmethodID mod_list_add = env->GetMethodID(cls_arraylist, "add", "(Ljava/lang/Object;)Z");//获取 ArrayList add函数ID
    jclass cls_bean = env->FindClass("com/junker/cplusplus/and/java/jni/study/bean/DataBean");//获取 DataBean class
    jmethodID mod_bean_init = env->GetMethodID(cls_bean, "<init>", "(Ljava/lang/String;I)V");//获取 DataBean 构造函数ID
    jobject obj_list_list = env->NewObject(cls_arraylist, mod_list_init);//创建父类 List 对象
    for (int i = 0; i < 3; ++i) {
        jobject obj_list = env->NewObject(cls_arraylist, mod_list_init);//创建子类 List 对象
        for (int j = 0; j < 3; ++j) {
            jobject obj_bean = env->NewObject(cls_bean, mod_bean_init, env->NewStringUTF("超人大侠"), 100 + i);//创建 DataBean 对象
            env->CallBooleanMethod(obj_list, mod_list_add, obj_bean);//给子类 List 对象添加数据
        }
        env->CallBooleanMethod(obj_list_list, mod_list_add, obj_list);//给父类 List 对象添加数据
    }
    //将新建的参数 obj_list_list 赋值给 thiz 实例对象中 fieldId 对应的变量
    env->SetObjectField(thiz, fid, obj_list_list);
    //获取 thiz 对象中 fieldId 对应的对象
    jobject j_obj = env->GetObjectField(thiz, fid);
    return j_obj;
}

/**
 * 传参类型：Map嵌套Map-Map<Map>
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_nativeMapMap(JNIEnv *env, jobject thiz, jobject map_map) {
    //获取 thiz 实例对象对应的 class
    jclass jclazz = env->GetObjectClass(thiz);
    //通过 jclazz 获取对应变量的 fieldId
    jfieldID fid = env->GetFieldID(jclazz, "mapMap", "Ljava/util/Map;");
/* ------------------------------------------------------------------------- */
/** 方式一：将传入的参数，原封不动的赋值给对应的对象 **/
//    //将传入的参数 map_map 赋值给 thiz 对象实例中 fieldId 对应的变量
//    env->SetObjectField(thiz, fid, map_map);
//    //获取 thiz 对象实例中 fieldId 对应的变量
//    jobject jobj = env->GetObjectField(thiz, fid);
//    return jobj;
/** 方式二：对传入的参数做二次修改，再赋值给对应的对象 **/
//    //修改传入的参数
//    jclass cls_map = env->GetObjectClass(map_map);//获取 map_map 对象对应的 Map class
//    jmethodID mod_get = env->GetMethodID(cls_map,"get", "(Ljava/lang/Object;)Ljava/lang/Object;");//获取 Map get函数ID
////    jmethodID mod_replace = env->GetMethodID(cls_map,"replace", "(Ljava/lang/Object;Ljava/lang/Object;Ljava/lang/Object;)Z");//获取 Map replace函数ID
//    jclass cls_bean = env->FindClass("com/junker/cplusplus/and/java/jni/study/bean/DataBean");//获取 DataBean class
//    jmethodID setName = env->GetMethodID(cls_bean,"setName", "(Ljava/lang/String;)V");//获取 DataBean setName函数ID
//    jmethodID setAge = env->GetMethodID(cls_bean,"setAge", "(I)V");//获取 DataBean setAge函数ID
//    jclass cls_integer = env->FindClass("java/lang/Integer");//获取 Integer class
//    jmethodID mod_valueOf = env->GetStaticMethodID(cls_integer,"valueOf", "(I)Ljava/lang/Integer;");//获取 Integer valueOf静态函数ID
//    jobject obj_key = env->CallStaticObjectMethod(cls_integer,mod_valueOf,11);//创建 Integer 对象作为父类 map key
//    jobject obj_key_key = env->CallStaticObjectMethod(cls_integer,mod_valueOf,1);//创建 Integer 对象作为子类 map key
//    jobject obj_map = env->CallObjectMethod(map_map,mod_get,obj_key);//获取父类 map 对应的子类 map 对象
//    jobject obj_map_bean = env->CallObjectMethod(obj_map,mod_get,obj_key_key);//获取子类 map 对应的item DataBean 对象
//    env->CallVoidMethod(obj_map_bean,setName,env->NewStringUTF("Junker"));//给子类 map 对应的item DataBean 对象重新赋值
//    env->CallVoidMethod(obj_map_bean,setAge,27);////给子类 map 对应的item DataBean 对象重新赋值
//    //将传入的参数 map_map 修改之后，再赋值给 thiz 对象实例中 field 对应的变量
//    env->SetObjectField(thiz,fid,map_map);
//    //获取 thiz 实例对象中 fieldId 对应的变量
//    jobject j_obj = env->GetObjectField(thiz,fid);
//    return j_obj;
/** 方式三：不启用传入的参数，重新 new 一个新的对象，重新赋值 **/
    //创建新对象
    jclass cls_hashmap = env->FindClass("java/util/HashMap");//获取 HashMap class
    jmethodID mod_hashmap_init = env->GetMethodID(cls_hashmap, "<init>", "()V");//获取 HashMap 构造函数ID
    jmethodID mod_hashmap_put = env->GetMethodID(cls_hashmap, "put",
                                                 "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");//获取 HashMap put构造函数ID
    jclass cls_bean = env->FindClass("com/junker/cplusplus/and/java/jni/study/bean/DataBean");//获取 DataBean class
    jmethodID mod_bean_init = env->GetMethodID(cls_bean, "<init>", "(Ljava/lang/String;I)V");//获取 DataBean 构造函数
    jclass cls_integer = env->FindClass("java/lang/Integer");//获取 Integer class
    jmethodID mod_valueOf = env->GetStaticMethodID(cls_integer, "valueOf", "(I)Ljava/lang/Integer;");//获取 Integer valueOf静态函数ID
    jobject obj_map_map = env->NewObject(cls_hashmap, mod_hashmap_init);//创建父类 HashMap 对象
    for (int i = 0; i < 3; ++i) {
        jobject obj_key = env->CallStaticObjectMethod(cls_integer, mod_valueOf, i);//创建 Integer 作为父类 HashMap key
        jobject obj_value = env->NewObject(cls_hashmap, mod_hashmap_init);//创建 HashMap 作为父类 HashMap value
        for (int j = 0; j < 3; ++j) {
            jobject obj_key_key = env->CallStaticObjectMethod(cls_integer, mod_valueOf, j);//创建 Integer 作为子类 HashMap key
            jobject obj_key_value = env->NewObject(cls_bean, mod_bean_init, env->NewStringUTF("Junker"), 1000 + i);//创建 DataBean 作为子类 value
            env->CallObjectMethod(obj_value, mod_hashmap_put, obj_key_key, obj_key_value);//给子类 HashMap 对象添加数据
        }
        env->CallObjectMethod(obj_map_map, mod_hashmap_put, obj_key, obj_value);//给父类 HashMap 对象添加数据
    }
    //将新建的参数 obj_map_map 赋值给 thiz 实例对象中 fieldId 对应的变量
    env->SetObjectField(thiz, fid, map_map);
    //获取 thiz 对象中 fieldId 对应的对象
    jobject j_obj = env->GetObjectField(thiz, fid);
    return j_obj;
}

/***************************************** Thread start *********************************************/
/**
* 线程处理
*/

JavaVM *gJavaVM = NULL;//全局 JavaVM 变量
jobject gJavaObj = NULL;//全局 jobject 变量

jmethodID nativeCallback = NULL;//全局的方法ID

static void *native_thread_exec(void *arg) {
    //从全局的JavaVM中获取到环境变量
    JNIEnv *env;
    gJavaVM->AttachCurrentThread(&env, NULL);

    //线程循环
    for (int i = 0; i < 1; ++i) {
        LOGCATE("start thread time");
        double startTime, stopTime, durationTimeTime;
        startTime = time(NULL);

        sleep(5);//单位：秒

        stopTime = time(NULL);
        durationTimeTime = (double) difftime(stopTime, startTime);
        LOGCATE("耗时(time): : %f", durationTimeTime);

        //跨线程回调Java层函数
        const char *desc = "我是错误提示desc_001";
        jstring descStr = env->NewStringUTF(desc);
        LOGCATE("native_thread_exec - 2 - the pThread id : %ld", pthread_self());
        env->CallVoidMethod(gJavaObj, nativeCallback, 100 + i, descStr);
    }

    gJavaVM->DetachCurrentThread();
    LOGCATE("----------------------------");
    return ((void *) nullptr);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_nativeThreadInteraction(JNIEnv *env, jobject thiz, jobject call_back) {
    gJavaObj = env->NewGlobalRef(call_back);
    jclass clazz = env->GetObjectClass(call_back);
    nativeCallback = env->GetMethodID(clazz, "onError", "(ILjava/lang/String;)V");

    //操作方式二，调用JNI函数保存JavaVM
    env->GetJavaVM(&gJavaVM);

    pthread_t id;
    //通过 pthread 库创建线程
    LOGCATE("create native thread");
    if (pthread_create(&id, NULL, native_thread_exec, NULL) != 0) {
        LOGCATE("native thread create fail");
        return;
    }
    LOGCATE("native thread create success");
}

//JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
////    //操作方式一，调用JNI函数保存JavaVM. 记录 Java 虚拟机指针
////    gJavaVM = vm;
//
//    //获取 JNIEnv 指针
//    JNIEnv *env = NULL;
//    //获取JNI_VERSION版本
//    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
//        LOGCATE("check version error");
//        return -1;
//    }
//
//    //返回JNI 的版本
//    return JNI_VERSION_1_6;
//}

/**-------------------------------------- Thread end --------------------------------------**/

/**************************************** 动态注册 start ****************************************/

jstring dynamicRegister(JNIEnv *env) {
    std::string hello = "Hello from C++ by 动态注册";
    return env->NewStringUTF(hello.c_str());
}

/**
 * 所谓的动态注册 是指，动态注册JAVA的Native方法，使得c/c++里面方法名 可以和 java 的Native方法名可以不同，
 * 动态注册是将将二者方法名关联起来，以后在修改Native方法名时，只需修改动态注册关联的方法名称即可
 *  System.loadLibrary("xxx"); 这个方法还是必须要调用的，不管动态还是静态
 */
#define JNIREG_CLASS "com/junker/cplusplus/and/java/jni/study/manager/JNIBaseManager"  //Java类的路径：包名+类名
#define NUM_METHOES(x) ((int) (sizeof(x) / sizeof((x)[0]))) //获取方法的数量

static JNINativeMethod method_table[] = {
        // 第一个参数a 是java native方法名，
        // 第二个参数 是native方法参数,括号里面是传入参的类型，外边的是返回值类型，
        // 第三个参数 是c/c++方法参数,括号里面是返回值类型，
        {"nativeDynamicRegisterMethod", "()Ljava/lang/String;", (jstring *) dynamicRegister},
};

static int registerMethods(JNIEnv *env, const char *className, JNINativeMethod *gMethods, int numMethods) {
    jclass clazz = env->FindClass(className);
    if (clazz == NULL) {
        return JNI_FALSE;
    }
    //注册native方法
    if (env->RegisterNatives(clazz, gMethods, numMethods) < 0) {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

extern "C"
JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = NULL;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }
    assert(env != NULL);

// 注册native方法
    if (!registerMethods(env, JNIREG_CLASS, method_table, NUM_METHOES(method_table))) {
        return JNI_ERR;
    }

    return JNI_VERSION_1_6;
}

/**------------------------------------- 动态注册 end -------------------------------------**/

