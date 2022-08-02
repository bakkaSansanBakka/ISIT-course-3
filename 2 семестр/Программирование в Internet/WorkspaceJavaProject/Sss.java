import javax.servlet.*;
import javax.servlet.http.*;
import java.io.IOException;
import java.io.PrintWriter;

public class Sss extends HttpServlet implements Servlet {
    public Sss() {
        super();
        System.out.println("Sss: constructor");
    }

    public void init(ServletConfig sc) throws ServletException {
        super.init();
        System.out.println("Sss:init");
    }

    public void destroy() {
        super.destroy();
        System.out.println("Sss:destroy");
    }

//    protected void service(HttpServletRequest rq, HttpServletResponse rs)
//        throws ServletException, IOException {
//        System.out.println("Sss:service: " + rq.getMethod());
//
//        rs.setContentType("text/html");
//        PrintWriter printWriter = rs.getWriter();
//        printWriter.println("<html> " + "<body style=\"font-size: 27px\">" +
//                "Sss:service: " + rq.getMethod() +
//                "<br>Sss:getRemoteHost: " + rq.getRemoteHost() +
//                "<br>Sss:getServerName: " + rq.getServerName() +
//                "</body>" + "</html>");
//    }

    protected void doGet(HttpServletRequest rq, HttpServletResponse rs)
        throws ServletException, IOException {
        String firstname = rq.getParameter("firstname");
        String lastname = rq.getParameter("lastname");
        System.out.println("Sss:doGet:firstname = " + firstname);
        System.out.println("Sss:doGet:lastname = " + lastname);

        rs.setContentType("text/html");
        PrintWriter printWriter = rs.getWriter();

        printWriter.println("<html> " +
                "<body style=\"font-size: 27px\">" +
                "Request string: " + rq.getMethod() + " " +
                rq.getRequestURI() + " " + rq.getProtocol() + " " +
                rq.getQueryString() +
                "<br>doGet method firstname = " + firstname +
                " lastname = " + lastname +
                "<br>Sss:service: " + rq.getMethod() +
                "<br>Sss:getRemoteHost: " + rq.getRemoteHost() +
                "<br>Sss:getServerName: " + rq.getServerName() +
                "</body>" + "</html>");
        printWriter.close();
    }

    protected void doPost(HttpServletRequest rq, HttpServletResponse rs)
            throws ServletException, IOException {
        String firstname = rq.getParameter("firstname");
        String lastname = rq.getParameter("lastname");
        System.out.println("Sss:doPost:firstname = " + firstname);
        System.out.println("Sss:doPost:lastname = " + lastname);

        rs.setContentType("text/html");
        PrintWriter printWriter = rs.getWriter();
        printWriter.println("<html> " +
                "<body style=\"font-size: 27px\">" +
                "Sss:doPost: firstname = " + firstname +
                "<br>Sss:doPost: lastname = " + lastname +
                "</body>" + "</html>");
        printWriter.close();
    }
}
