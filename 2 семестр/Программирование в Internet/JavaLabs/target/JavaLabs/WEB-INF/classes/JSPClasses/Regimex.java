package JSPClasses;
import java.util.*;

public class Regimex {
    protected String R = null;
    Calendar calendar;
    protected Date d = new Date();
    public Regimex(Calendar c) {
        this.calendar = c;
    }
    public Regimex() {
        this.calendar = Calendar.getInstance();
    }
    public Integer GetHOUR() {
        return ((Integer)calendar.get(Calendar.HOUR_OF_DAY));
    }
    public Integer GetWeekDay() {
        return ((Integer)calendar.get(Calendar.DAY_OF_WEEK));
    }
}
