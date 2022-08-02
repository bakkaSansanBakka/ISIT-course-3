package lab22;

import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;

public class JAASBasicAuthServlet extends HttpServlet implements Servlet {
    public JAASBasicAuthServlet() {
        super();
        System.out.println("JAASBasicAuthServlet: constructor");
    }

    public void init(ServletConfig sc) throws ServletException {
        super.init();
        System.out.println("JAASBasicAuthServlet:init");
    }

    public void destroy() {
        super.destroy();
        System.out.println("JAASBasicAuthServlet:destroy");
    }

    protected void doGet(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException {
        var rw = resp.getWriter();
        rw.write("JAASBasicAuthServlet");
    }
}
