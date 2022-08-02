package lab22;

import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;

public class JAASFormAuthServlet extends HttpServlet implements Servlet {
    public JAASFormAuthServlet() {
        super();
        System.out.println("JAASFormAuthServlet: constructor");
    }

    public void init(ServletConfig sc) throws ServletException {
        super.init();
        System.out.println("JAASFormAuthServlet:init");
    }

    public void destroy() {
        super.destroy();
        System.out.println("JAASFormAuthServlet:destroy");
    }

    protected void doGet(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException {
        var rw = resp.getWriter();
        rw.write("JAASFormAuthServlet");
    }
}
