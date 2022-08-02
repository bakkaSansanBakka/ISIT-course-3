package lab9;

import javax.servlet.*;

public class L1 implements ServletContextListener {
    public void contextInitialized(ServletContextEvent servletContextEvent) {
        System.out.println("L1:context initialized");
    }

    public void contextDestroyed(ServletContextEvent servletContextEvent) {
        System.out.println("L1:context destroyed");
    }
}
