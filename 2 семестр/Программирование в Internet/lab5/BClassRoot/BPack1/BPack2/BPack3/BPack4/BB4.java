package BPack1.BPack2.BPack3.BPack4;

public class BB4 {
    public int numField;

    public BB4(int num) {
        numField = num;
    }

    public void printInfo() {
        System.out.println("Class name: " + this.getClass().getSimpleName() + ", " + numField);
    }
}
