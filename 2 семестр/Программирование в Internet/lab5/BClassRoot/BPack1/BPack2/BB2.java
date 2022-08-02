package BPack1.BPack2;

public class BB2 {
    public int numField;

    public BB2(int num) {
        numField = num;
    }

    public void printInfo() {
        System.out.println("Class name: " + this.getClass().getSimpleName() + ", " + numField);
    }
}
