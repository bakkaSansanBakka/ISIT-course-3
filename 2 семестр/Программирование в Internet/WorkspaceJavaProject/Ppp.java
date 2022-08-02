import org.apache.commons.httpclient.*;
import org.apache.commons.httpclient.HttpClient;
import org.apache.commons.httpclient.methods.GetMethod;

import javax.servlet.*;
import javax.servlet.http.*;
import java.io.IOException;
import java.io.PrintWriter;

public class Ppp extends HttpServlet implements Servlet {
    public Ppp() {
        super();
        System.out.println("Ppp: constructor");
    }

    public void init(ServletConfig sc) throws ServletException {
        super.init();
        System.out.println("Ppp:init");
    }


    public void destroy() {
        super.destroy();
        System.out.println("Ppp:destroy");
    }

    // forward
//    protected void service(HttpServletRequest rq, HttpServletResponse rs)
//        throws ServletException, IOException {
//
//        String phoneNumber = rq.getParameter("phone");
//        String email = rq.getParameter("email");
//        System.out.println("Ppp:service:phone number = " + phoneNumber);
//        System.out.println("Ppp:service:email = " + email);
//
//        rs.setContentType("text/html");
//        PrintWriter printWriter = rs.getWriter();
//        printWriter.println("<html> " +
//                "<body style=\"font-size: 27px\">" +
//                "Ppp:service: phone number = " + phoneNumber +
//                "<br>Ppp:service: email = " + email +
//                "</body>" + "</html>");
//
//        RequestDispatcher rd = rq.getRequestDispatcher("/Ggg");
//        rd.forward(rq, rs);
//    }
//
//    protected void doGet(HttpServletRequest rq, HttpServletResponse rs)
//            throws ServletException, IOException {
//
//        System.out.println("Ppp:doGet");
//
//        String param = rq.getParameter("param");
//        System.out.println("Ppp:param = " + param);
//
//        rs.setContentType("text/html");
//        PrintWriter printWriter = rs.getWriter();
//        printWriter.println("<html> " +
//                "<body style=\"font-size: 27px\">" +
//                "Ppp:doGet: param = " + param +
//                "</body>" + "</html>");
//
//        String paramStr = "param=" + param;
//
//        RequestDispatcher rd = rq.getRequestDispatcher("/Ggg?" + paramStr);
//        rd.forward(rq, rs);
//    }

    // forming GET request
    protected void doGet(HttpServletRequest rq, HttpServletResponse rs)
        throws ServletException, IOException {
        System.out.println("Ppp:service");

        String firstname = rq.getParameter("firstname");
        String lastname = rq.getParameter("lastname");
        String parmstr = "firstname=" + firstname + "&" + "lastname=" + lastname;

        HttpClient hc = new HttpClient();
        System.out.println("Ppp:create httpclient");

        String uri = "http://localhost:8080/Ggg?" + parmstr;
        GetMethod gm = new GetMethod(uri);
        System.out.println("Ppp:create getmethod");
        hc.executeMethod(gm);
        System.out.println("Ppp:execute get method");
        rs.setContentType("text/html");
        PrintWriter pw = rs.getWriter();
        pw.println(gm.getResponseBodyAsString());
        System.out.println("Ppp:printwriter");
        pw.flush();
    }
}
