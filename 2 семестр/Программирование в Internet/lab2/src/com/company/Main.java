package com.company;

public class Main {
    public static int differenceOf2Power (int a1, int a2) {
        return (int)Math.pow(a1, 2) - (int)Math.pow(a2, 2);
    }

    public static float differenceOf3Power (float a1, float a2) {
        return (float)Math.pow(a1, 3) - (float)Math.pow(a2, 3);
    }

    public static double differenceOf4Power (double a1, double a2) {
        return Math.pow(a1, 4) - Math.pow(a2, 4);
    }

    public static int charSum (char a, char b) {
        return a + b;
    }

    public static int charDifference (char a, char b) {
        return a - b;
    }

    public static void main(String[] args) {
        //1.1
        int a_int = 3, b_int = 3;
        System.out.println(String.format("%s ^ 2 - %s ^ 2 is %s", a_int, b_int, differenceOf2Power(a_int, b_int)));

        //1.2
        float a_float = 3.3f, b_float = 2.2f;
        System.out.println(String.format("%s ^ 3 - %s ^ 3 is %s", a_float, b_float, differenceOf3Power(a_float, b_float)));

        //1.3
        double a_double, b_double;
        a_double = 3.3;
        b_double = 2.2;
        System.out.println(String.format("%s ^ 4 - %s ^ 4 is %s", a_double, b_double, differenceOf4Power(a_double, b_double)));

        //2.1
        char a_char = 'M', b_char = 'A';
        System.out.println(String.format("%s + %s = %s", a_char, b_char, charSum(a_char, b_char)));
        System.out.println(String.format("%s - %s = %s", a_char, b_char, charDifference(a_char, b_char)));
    }
}
