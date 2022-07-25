package com.junker.cplusplus.and.java.jni.study.manager;

import android.content.Context;
import android.util.Log;

import java.util.List;
import java.util.Map;

public class JavaNativeMethod {
    private static final String TAG = JavaNativeMethod.class.getSimpleName();

    private static boolean sIsLoadLibrarySuccess = false;

    static {
        try {
            sIsLoadLibrarySuccess = loadIMLibrary();
        } catch (Exception e) {
            Log.e(TAG, e.toString());
        }
    }

    private static boolean loadIMLibrary() {
        if (sIsLoadLibrarySuccess) {
            return true;
        }
        try {
            System.loadLibrary("study");
            sIsLoadLibrarySuccess = true;
            Log.i(TAG, "system load so library success, libStudy.so");
        } catch (UnsatisfiedLinkError e) {
            sIsLoadLibrarySuccess = false;
            Log.e(TAG, "system load so library failed, " + e.getMessage());
        } catch (Exception e) {
            sIsLoadLibrarySuccess = false;
            Log.e(TAG, "system load so library failed, " + e.getMessage());
        }
        return sIsLoadLibrarySuccess;
    }

    private static class JavaNativeMethodHolder {
        private static final JavaNativeMethod nativeMethod = new JavaNativeMethod();
    }

    public static JavaNativeMethod getInstance() {
        return JavaNativeMethod.JavaNativeMethodHolder.nativeMethod;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /**
     * 默认生成的native方法
     */
    public native String stringFromJNI();

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //############## 由浅入深-至上而下 ################

    /**
     * 传参类型：整型(int/long/short/...)
     */
    public native int integerFromJNI(int num);

    /**
     * 传参类型：char
     */
    public native char charFromJNI(char ch);

    /**
     * 传参类型：string
     */
    public native String stringFromJNI(String str);

    /**
     * 传参类型：数组( int[]/ string[]/ ...)
     */
    public native int[] intArrayFromJNI(int[] num);

    /**
     * 传参类型：对象
     */
    public native Object objectFromJNI(Object obj);

    /**
     * 传参类型：集合-List<整型>
     */
    public native List<Integer> listIntegerFromJNI(List<Integer> list);

    /**
     * 传参类型：集合-List<String>
     */
    public native List<String> listStringFromJNI(List<String> mapInt);

    /**
     * 传参类型：集合-List<int[]>
     */
    public native List<int[]> listIntArrayFromJNI(List<int[]>);

    /**
     * 传参类型：集合-List<Object>
     */
    public native List<Object> listObjectFromJNI(List<Object>);

    /**
     * 传参类型：Map数组-Map<整型>
     */
    public native Map<Integer,Integer> mapIntegerFromJNI(Map<Integer,Integer>);

    /**
     * 传参类型：Map数组-Map<String>
     */
    public native Map<String,String> mapStringFromJNI(Map<String,String>);

    /**
     * 传参类型：Map数组-Map<int[]>
     */
    public native Map<Integer,int[]> mapIntgerFromJNI(Map<Integer,int[]>);

    /**
     * 传参类型：Map数组-Map<Object>
     */
    public native Map<Integer,Object> mapObjectFromJNI(Map<Integer,Object>);

    /**
     * 传参类型：集合嵌套集合-List<List>
     */
    public native List<List<Object>> listListFromJNI(List<List<Object>>);

    /**
     * 传参类型：Map嵌套Map-Map<Map>
     */
    public native Map<Integer,Map<Integer,Object>> mapMapFromJNI(Map<Integer,Map<Integer,Object>>);

}