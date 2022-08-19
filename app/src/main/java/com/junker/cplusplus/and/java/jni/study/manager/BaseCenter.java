package com.junker.cplusplus.and.java.jni.study.manager;

public class BaseCenter {
    private final static String TAG = BaseCenter.class.getSimpleName();

    private static class BaseCenterHolder {
        private static final BaseCenter baseCenter = new BaseCenter();
    }

    public static BaseCenter getInstance(){
        if (!JNIBaseManager.getInstance().isInited()){
            JNIBaseManager.getInstance().initSDK();
        }
        return BaseCenter.BaseCenterHolder.baseCenter;
    }

    private int number;

    public int getNumber(){
        return number;
    }

    public native int nativeDynamicRegisterFirst(int number);

    public native void nativeDynamicRegisterSecond(int number);
}
