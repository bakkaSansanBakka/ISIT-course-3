public class Main {
    public static void Task1() {
        System.out.println("Task 1");

        int[] xx = new int[10];

        for (int i = 0; i < xx.length; i++){
            xx[i] = i;
        }


        for (int i = 0; i < xx.length; i++) {
            System.out.println(xx[i]);
        }
    }

    public static void Task2() {
        System.out.println("Task 2");

        int [][] xx = new int[5][5];

        for (int i = 0; i < xx.length; i++) {
            for (int j = 0; j < xx.length; j++) {
                xx[i][j] = i + j;
            }
        }


        for (int i = 0; i < xx.length; i++) {
            System.out.println(" ");
            for (int j = 0; j < xx[i].length; j++) {
                System.out.print(xx[i][j]);
            }
        }
    }

    public static void Task3() {
        System.out.println("Task 3");

        int shift = 2;
        int num1 = -9;
        int num2 = 2;

        System.out.printf("%s >>> %s = %s%n", num1, shift, num1 >>> shift);
        System.out.printf("%s <<= %s = %s%n", num2, shift, num2 <<= shift);
        System.out.printf("%s ^= %s = %s%n", num1, num2, num2 ^= num1);
        System.out.printf("%s & %s = %s%n", num1, num2, num1 & num2);
        System.out.printf("NOT %s = %s%n", num2, ~num2);
    }

    public static void Task4() {
        System.out.println("Task 4\n");

        boolean or_result = true || false;
        boolean and_result = true && false;

        System.out.print("true || false = ");
        System.out.print(or_result);
        System.out.print("\ntrue && false = ");
        System.out.print(and_result);
        System.out.print("\nTernary operator: ");
        System.out.print(false ? "true\n" : "false\n");
    }

    public static void Task5() {
        System.out.println("Task5");

        System.out.println("If operator:");
        if (2 > 1) System.out.println("2 > 1");

        System.out.println("For operator:");
        for (int i = 0; i < 2; i++) {
            System.out.println(i);
        }

        System.out.println("While operator:");
        int num = 1;
        while (num < 5) {
            System.out.println(num);
            num++;
        }

        System.out.println("Do while operator:");
        int num_int = 0;
        do {
            System.out.println(num_int);
            num_int++;
        } while (num_int < 0);

        System.out.println("Switch operator:");
        switch (num_int) {
            case 1: System.out.println("num_int is 1");
                break;
            case 2: System.out.println("num_int is 2");
                break;
            default: System.out.println("default");
        }
    }

    public static void Task6() {
        System.out.println("Task 6");
        System.out.println(DummyClass.staticVariable);
        DummyClass.Method();
    }

    public static void main(String[] args) {
	    Task1();
        System.out.println("\n");
        Task2();
        System.out.println("\n");
        Task3();
        System.out.println("\n");
        Task4();
        System.out.println("\n");
        Task5();
        System.out.println("\n");
        Task6();
    }
}

class DummyClass{
    public static String staticVariable = "Static string variable";

    public static void Method() {
        System.out.println("Static Method");
    }
}
