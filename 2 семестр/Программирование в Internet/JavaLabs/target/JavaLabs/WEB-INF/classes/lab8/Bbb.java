package lab8;

import javax.servlet.*;
import javax.servlet.http.*;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Enumeration;

public class Bbb extends HttpServlet implements Servlet {
    public Bbb() {
        super();
        System.out.println("Bbb: constructor");
    }

    public void init(ServletConfig sc) throws ServletException {
        super.init();
        System.out.println("Bbb:init");
    }

    public void destroy() {
        super.destroy();
        System.out.println("Bbb:destroy");
    }

    protected void doPost(HttpServletRequest rq, HttpServletResponse rs)
            throws ServletException, IOException {

        System.out.println("Bbb:doPost");

        String param1 = rq.getParameter("Header1");
        String param2 = rq.getParameter("Header2");
        String param3 = rq.getParameter("Header3");

        String outString = "<html>" +
                "<body>" +
                "Bbb:doPost:parameters"
                + "<br>param1 = " + param1
                + "<br>param2 = " + param2
                + "<br>param3 = " + param3
                + "<br>Bbb:doPost:request headers:";

        String headerName;
        Enumeration enh = rq.getHeaderNames();

        rs.setContentType("text/html");

        rs.addHeader("BbbResponseHeader1", "BbbResponseHeader1Value");
        rs.addHeader("BbbResponseHeader2", "BbbResponseHeader2Value");

        PrintWriter pw = rs.getWriter();
        pw.println(outString);
        while (enh.hasMoreElements()) {
            headerName = (String) enh.nextElement();
            pw.println("<br>" + headerName + " = " + rq.getHeader(headerName));
        }
        pw.println("<body><html>");
        pw.flush();
    }
}
