package lab9;

import javax.servlet.*;
import javax.servlet.http.*;

public class L2 implements HttpSessionAttributeListener {
    public void attributeAdded(HttpSessionBindingEvent httpSessionBindingEvent) {
        System.out.println("L2:session attribute added");
    }

    public void attributeRemoved(HttpSessionBindingEvent httpSessionBindingEvent) {
        System.out.println("L2:session attribute removed");
    }

    public void attributeReplaced(HttpSessionBindingEvent httpSessionBindingEvent) {
        System.out.println("L2:session attribute replaced");
    }
}
