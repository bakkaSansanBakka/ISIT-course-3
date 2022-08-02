public class Main {
    public enum Job {
        Programmer(1500, 4),
        Architect(1600, 4),
        Electrician(1300, 3),
        Bartender(1200, 1),
        Cashier(1100, 1),
        Baker(1200, 2),
        Plumber(1300, 3),
        Secretary(1200, 2);

        private final double salary;
        private final int years;

        Job (double salary, int years) {
            this.salary = salary;
            this.years = years;
        }
    }

    public static void main(String[] args) {
        //1 - String creation
        String s01 = new String();
        System.out.println("s01.length = " + s01.length());

        char[] cs = {'0', '1', '2', '3', '4', '5', '6', '7'};
        String s02 = new String(cs);
        System.out.println("s02.length = " + s02.length() + " s02 = " + s02);

        String s03 = new String(cs, 3, 5);
        System.out.println("s03.length = " + s03.length() + " s03 = " + s03);

        String s04 = "01234567";
        System.out.println("s04.length = " + s04.length() + " s04 = " + s04);

        String s05 = new String("01234567");
        System.out.println("s05.length = " + s05.length() + " s05 = " + s05);

        //2 - string literals
        System.out.println("\"01234567\".length = " + "01234567".length());

        //3 - chars extraction
        String s06 = new String("01234567");
        for (int i = 0; i < s06.length(); i++) {
            System.out.print(s06.charAt(i) + (i < s06.length() - 1 ? "-" :""));
        }

        System.out.println("");

        char[] cs1 = new char[6 - 2];
        s06.getChars(2, 6, cs1, 0);
        for (int i = 0; i < cs1.length; i++) {
            System.out.print(cs1[i] + ((i < cs1.length - 1) ? "-" : ""));
        }
        System.out.println("");

        //4 - string comparison
        String s07 = new String("01234567");
        String s08 = new String("01234567");

        System.out.println("(s07 == s08) = " + (s07 == s08));
        System.out.println("(s07 == \"01234567\") = " + (s07 == "01234567"));
        System.out.println("s07.equals(s08) = " + s07.equals(s08));
        String s09 = s08;
        System.out.println("(s08 == s09) = " + (s08 == s09));

        //5 - char search
        String s10 = new String("Поиск символов в строке");
        System.out.println(s10.indexOf('ь'));
        System.out.println(s10.indexOf('о'));
        System.out.println(s10.lastIndexOf('о'));
        System.out.println(s10.indexOf('о', 6));
        System.out.println(s10.lastIndexOf('о', 6));
        System.out.println(s10.lastIndexOf('о', 15));

        //6 - substring extraction
        String s11 = new String("Извлечение подстроки из строки");
        System.out.println(s11.substring(11));
        System.out.println(s11.substring(11, 20));

        //7 - char replace, toUpperCase, toLowerCase
        String s12 = new String("Методы замены символов");
        System.out.println(s12.replace('е', 'э'));
        System.out.println(s12.toUpperCase());
        System.out.println(s12.toLowerCase());

        //8 - StringBuffer
        StringBuffer s13 = new StringBuffer(100);
        s13.append("Обычная строка");
        System.out.println("s13.length() = " + s13.length());
        System.out.println("s13.capacity = " + s13.capacity());
        s13.insert(8, "и простая ");
        System.out.println(s13);
        System.out.println("s13.length() = " + s13.length());
        System.out.println("s13.capacity = " + s13.capacity());
        s13.delete(7, 17);
        System.out.println(s13);
        s13.ensureCapacity(200);
        System.out.println("s13.capacity = " + s13.capacity());
        String s14 = s13.toString();
        System.out.println(s14);

        //9 - shells of primitive types
        Byte x1 = 3;
        Short x2 = 256;
        Integer x3 = 100;
        Float x4 = 3.14f;
        Double x5 = 2.9e10;
        Long x6 = 200000L;
        Character x7 = 'a';
        Boolean x8 = false;
        Number x9 = 11;

        //10 - simple enum
        Job job = Job.Programmer;
        switch (job) {
            case Plumber: System.out.println("Plumber"); break;
            case Baker: System.out.println("Baker"); break;
            case Electrician: System.out.println("Electrician"); break;
            default: System.out.println("default");
        }

        //11 - extended enum
        System.out.println(job.salary);
        System.out.println(job.years);
    }
}
