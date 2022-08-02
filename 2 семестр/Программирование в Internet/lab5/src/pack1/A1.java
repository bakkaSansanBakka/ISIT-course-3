package pack1;

import BPack1.AA1;

public class A1 extends AA1 {
    public int numField;

    public A1(int num) {
        super(num);
        numField = num;
    }

    public void printInfo() {
        System.out.println("Class name: " + this.getClass().getSimpleName() + ", " + numField);
    }
}
