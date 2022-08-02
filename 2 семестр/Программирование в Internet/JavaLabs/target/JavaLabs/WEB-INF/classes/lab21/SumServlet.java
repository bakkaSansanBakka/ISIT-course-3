package lab21;

import javax.servlet.http.*;
import javax.servlet.*;
import java.io.IOException;

public class SumServlet extends HttpServlet implements Servlet {
    public SumServlet() {
        super();
        System.out.println("SumServlet: constructor");
    }

    public void init(ServletConfig sc) throws ServletException {
        super.init();
        System.out.println("SumServlet:init");
    }

    public void destroy() {
        super.destroy();
        System.out.println("SumServlet:destroy");
    }

    protected void doPost(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException {
        System.out.println("SumServlet:doPost");

        if(req.getParameter("timeout") != null) {
            try {
                Thread.sleep(10000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        Float x = Float.parseFloat(req.getHeader("Value-X"));
        Float y = Float.parseFloat(req.getHeader("Value-Y"));
        float z = x + y;
        resp.setHeader("Value-Z", Float.toString(z));
    }
}
