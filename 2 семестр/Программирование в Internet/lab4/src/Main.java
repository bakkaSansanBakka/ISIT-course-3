public class Main {

    public static void main(String[] args) {
	    CCC cccDefaultVariable = new CCC();
        CCC cccCustomVariable = new CCC(60, 50);

        System.out.println(String.format("cccDefaultVariable.x = %s, cccCustomVariable.x = %s",
                cccDefaultVariable.x, cccCustomVariable.x));

        System.out.println(String.format("sum of cccCustomVariable fields = %s", cccCustomVariable.sum()));

        int x = 20, y = 10;
        System.out.println(String.format("%s - %s = %s", x, y, CCC.ssub(x, y)));

        DDD dddDefaultVariable = new DDD();
        DDD dddCustomVariable = new DDD(40, 30);

        System.out.println(String.format("dddDefaultVariable.x = %s, dddCustomVariable.x = %s",
                dddDefaultVariable.x, dddCustomVariable.x));

        System.out.println(String.format("dddCustomVariable superclass' y variable = %s", dddCustomVariable.GetY()));
        System.out.println(String.format("sum of dddCustomVariable fields = %s", dddCustomVariable.sum()));
        System.out.println(String.format("x * y + super.x * super.y = %s", dddCustomVariable.calc()));
    }
}
