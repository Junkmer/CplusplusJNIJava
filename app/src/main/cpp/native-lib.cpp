#include <jni.h>
#include <string>
#include <iostream>
#include <LogUtil.h>

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
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_charFromJNI(JNIEnv *env, jobject thiz, jchar ch) {
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
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_intArrayFromJNI(JNIEnv *env, jobject thiz, jintArray numS) {
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
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_objectFromJNI(JNIEnv *env, jobject thiz, jobject obj) {
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
    //将新建的参数 xxx 赋值给 thiz 实例对象中 fieldId 对应的变量
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
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_listIntegerFromJNI(JNIEnv *env, jobject thiz, jobject list_integer) {
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
    jmethodID mod_init = env->GetMethodID(cls_array,"<init>", "()V");//获取 ArrayList 构造函数
    jmethodID mod_add = env->GetMethodID(cls_array,"add", "(Ljava/lang/Object;)Z");//获取 ArrayList add方法ID
    jobject obj_array = env->NewObject(cls_array,mod_init);//创建 ArrayList 实例对象
    jclass cls_integer = env->FindClass("java/lang/Integer");//获取 Integer class
    jmethodID mod_init_integer = env->GetStaticMethodID(cls_integer,"valueOf", "(I)Ljava/lang/Integer;");//获取用于创建 Integer 实例对象 valueOf 静态方法ID
    jobject obj_integer = env->CallStaticObjectMethod(cls_integer,mod_init_integer,27);//通过 valueOf静态方法创建 Integer 对象实例
    env->CallBooleanMethod(obj_array,mod_add,obj_integer);//将 Integer 对象添加到 ArrayList 集合中
    //将新建的参数 cls_array 赋值给 thiz 实例对象中 fieldId 对应的变量
    env->SetObjectField(thiz,fid,obj_array);
    //获取 thiz 对象中 fieldId 对应的对象
    jobject j_obj = env->GetObjectField(thiz,fid);

    env->DeleteLocalRef(obj_array);
    env->DeleteLocalRef(cls_integer);
    return j_obj;
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
    jmethodID mod_init = env->GetMethodID(array_class,"<init>", "()V");//获取 ArrayList 构造方法ID
    jmethodID mod_add = env->GetMethodID(array_class,"add", "(Ljava/lang/Object;)Z");//获取 ArrayList add方法ID
    jstring item_str = env->NewStringUTF("Junker");//创建一个 string 对象
    jobject obj_array = env->NewObject(array_class,mod_init);//创建一个 ArrayList 对象
    env->CallBooleanMethod(obj_array,mod_add,item_str);//给 ArrayList 对象添加 数据
    //将新建的参数 array_class 赋值给 thiz 实例对象中 fieldId 对应的变量
    env->SetObjectField(thiz,fid,obj_array);
    //获取 thiz 对象中 fieldId 对应的对象
    jobject j_obj = env->GetObjectField(thiz,fid);

    env->DeleteLocalRef(obj_array);
    return j_obj;
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
    jclass cls_array = env->FindClass("java/util/ArrayList");
    jmethodID cls_init = env->GetMethodID(cls_array,"<init>", "()V");
    jmethodID cls_add = env->GetMethodID(cls_array,"add", "(Ljava/lang/Object;)Z");
    jobject obj_list = env->NewObject(cls_array,cls_init);
    jintArray array = env->NewIntArray(3);
    jsize length = env->GetArrayLength(array);
    jint item[] = {2,3,4};
    env->SetIntArrayRegion(array,0,length,item);
    env->CallBooleanMethod(obj_list,cls_add,array);
    //将新建的参数 obj_list 赋值给 thiz 实例对象中 fieldId 对应的变量
    env->SetObjectField(thiz,fid,obj_list);
    //获取 thiz 对象中 fieldId 对应的对象
    jobject j_obj = env->GetObjectField(thiz,fid);
    return j_obj;
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
    //将新建的参数 xxx 赋值给 thiz 实例对象中 fieldId 对应的变量
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
Java_com_junker_cplusplus_and_java_jni_study_manager_JNIBaseManager_mapIntegerFromJNI(JNIEnv *env, jobject thiz, jobject map_integer) {
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
    //修改传入的参数
    jclass cls_map = env->GetObjectClass(map_integer);
    jmethodID mod_get = env->GetMethodID(cls_map,"get", "(Ljava/lang/Object;)Ljava/lang/Object;");
    jmethodID mod_replace = env->GetMethodID(cls_map,"replace", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");
    jclass cls_integer = env->FindClass("java/lang/Integer");
    jmethodID mod_static_init = env->GetStaticMethodID(cls_integer,"valueOf", "(I)Ljava/lang/Integer;");
    jmethodID mod_intValue = env->GetMethodID(cls_integer,"intValue", "()I");
    jobject map_key = env->CallStaticObjectMethod(cls_integer,mod_static_init,1);
    jobject map_value = env->CallObjectMethod(map_integer,mod_get,map_key);
    env->CallStaticObjectMethod(cls_integer,mod_static_init,10086);

    //将传入的参数 map_integer 修改之后，再赋值给 thiz 对象实例中 field 对应的变量

    //获取 thiz 实例对象中 fieldId 对应的变量

/** 方式三：不启用传入的参数，重新 new 一个新的对象，重新赋值 **/
    //创建新对象

    //将新建的参数 xxx 赋值给 thiz 实例对象中 fieldId 对应的变量

    //获取 thiz 对象中 fieldId 对应的对象

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
/* ------------------------------------------------------------------------- */
/** 方式一：将传入的参数，原封不动的赋值给对应的对象 **/
    //将传入的参数 map_string 赋值给 thiz 实例对象中 fieldId 对应的变量
    env->SetObjectField(thiz, fid, map_string);
    //获取 thiz 对象中 fieldId 对应的变量
    jobject jobj = env->GetObjectField(thiz, fid);
    return jobj;
/** 方式二：对传入的参数做二次修改，再赋值给对应的对象 **/
    //修改传入的参数

    //将传入的参数 map_string 修改之后，再赋值给 thiz 对象实例中 field 对应的变量

    //获取 thiz 实例对象中 fieldId 对应的变量

/** 方式三：不启用传入的参数，重新 new 一个新的对象，重新赋值 **/
    //创建新对象

    //将新建的参数 xxx 赋值给 thiz 实例对象中 fieldId 对应的变量

    //获取 thiz 对象中 fieldId 对应的对象

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
    //修改传入的参数

    //将传入的参数 map_integer_array 修改之后，再赋值给 thiz 对象实例中 field 对应的变量

    //获取 thiz 实例对象中 fieldId 对应的变量

/** 方式三：不启用传入的参数，重新 new 一个新的对象，重新赋值 **/
    //创建新对象

    //将新建的参数 xxx 赋值给 thiz 实例对象中 fieldId 对应的变量

    //获取 thiz 对象中 fieldId 对应的对象

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
    //修改传入的参数

    //将传入的参数 map_object 修改之后，再赋值给 thiz 对象实例中 field 对应的变量

    //获取 thiz 实例对象中 fieldId 对应的变量

/** 方式三：不启用传入的参数，重新 new 一个新的对象，重新赋值 **/
    //创建新对象

    //将新建的参数 xxx 赋值给 thiz 实例对象中 fieldId 对应的变量

    //获取 thiz 对象中 fieldId 对应的对象

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
    //修改传入的参数

    //将传入的参数 list_list 修改之后，再赋值给 thiz 对象实例中 field 对应的变量

    //获取 thiz 实例对象中 fieldId 对应的变量

/** 方式三：不启用传入的参数，重新 new 一个新的对象，重新赋值 **/
    //创建新对象

    //将新建的参数 xxx 赋值给 thiz 实例对象中 fieldId 对应的变量

    //获取 thiz 对象中 fieldId 对应的对象

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
    //修改传入的参数

    //将传入的参数 map_map 修改之后，再赋值给 thiz 对象实例中 field 对应的变量

    //获取 thiz 实例对象中 fieldId 对应的变量

/** 方式三：不启用传入的参数，重新 new 一个新的对象，重新赋值 **/
    //创建新对象

    //将新建的参数 xxx 赋值给 thiz 实例对象中 fieldId 对应的变量

    //获取 thiz 对象中 fieldId 对应的对象

}