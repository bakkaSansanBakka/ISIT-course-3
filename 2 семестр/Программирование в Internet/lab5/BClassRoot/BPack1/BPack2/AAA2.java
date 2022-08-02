package BPack1.BPack2;

public class AAA2 {
    public int numField;

    public AAA2(int num) {
        numField = num;
    }

    public void useObjectA() {

    }

    public void printInfo() {
        System.out.println("Class name: " + this.getClass().getSimpleName() + ", " + numField);
    }
}
