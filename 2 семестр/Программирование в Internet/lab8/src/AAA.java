public class AAA {

    public AAA(Integer number) {
        try {
            if (number == null) {
                throw new ExceptionAAA1();
            }
        }
        catch (ExceptionAAA1 exception) {
            System.out.println(exception.getMessage());
        }
    }

    public void methode(int number) {
        try{
            if (number == 0) {
                throw new ExceptionAAA2();
            }
            if (number < 0) {
                throw new ExceptionAAA3();
            }
            System.out.println(number);
        }
        catch (ExceptionAAA2 exception) {
            System.out.println(exception.getMessage());
        }
        catch (ExceptionAAA3 exception) {
            System.out.println(exception.getMessage());
        }
    }
}
