package BPack1;
import pack1.A1;

public class AA1 {
    public int numField;

    public AA1(int num) {
        numField = num;
    }

    public void printInfo() {
        System.out.println("Class name: " + this.getClass().getSimpleName() + ", " + numField);
    }

    public void useAClass() {
        A1 a1 = new A1(627);
        a1.printInfo();
    }
}
