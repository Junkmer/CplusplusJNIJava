package com.junker.cplusplus.and.java.jni.study.bean;

public class DataBean {
    private String name;
    private int age;

    public DataBean(String name, int age) {
        this.name = name;
        this.age = age;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }

    @Override
    public String toString() {
        return "DataBean{" +
                "name='" + name + '\'' +
                ", age=" + age +
                '}';
    }
}
