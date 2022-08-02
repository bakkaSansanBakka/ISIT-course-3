package pack1.pack2.pack3.pack4;

public class B4 {
    public int numField;

    public B4(int num) {
        numField = num;
    }

    public void printInfo() {
        System.out.println("Class name: " + this.getClass().getSimpleName() + ", " + numField);
    }
}
