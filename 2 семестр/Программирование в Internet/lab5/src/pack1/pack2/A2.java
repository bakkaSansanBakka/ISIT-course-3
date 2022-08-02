package pack1.pack2;

public class A2 {
    public int numField;

    public A2(int num) {
        numField = num;
    }

    public void printInfo() {
        System.out.println("Class name: " + this.getClass().getSimpleName() + ", " + numField);
    }
}
