package lab3;

import javax.servlet.*;
import javax.servlet.http.*;
import java.io.IOException;
import java.io.PrintWriter;

public class Ggg extends HttpServlet implements Servlet {
    public Ggg() {
        super();
        System.out.println("Ggg: constructor");
    }

    public void init(ServletConfig sc) throws ServletException {
        super.init();
        System.out.println("Ggg:init");
    }

    public void destroy() {
        super.destroy();
        System.out.println("Ggg:destroy");
    }

    //forward
//    protected void doGet(HttpServletRequest rq, HttpServletResponse rs)
//            throws ServletException, IOException {
//
//        System.out.println("Ggg:doGet");
//
//        String param = rq.getParameter("param");
//        System.out.println("Ggg:param = " + param);
//
//        rs.setContentType("text/html");
//        PrintWriter printWriter = rs.getWriter();
//        printWriter.println("<html> " +
//                "<body style=\"font-size: 27px\">" +
//                "Ggg:doGet: param = " + param +
//                "</body>" + "</html>");
//
//        RequestDispatcher rd = rq.getRequestDispatcher("/servletForward.html");
//        rd.forward(rq, rs);
//    }

//    protected void doPost(HttpServletRequest rq, HttpServletResponse rs)
//        throws ServletException, IOException
//    {
//        System.out.println("Ggg:doPost");
//
//        rs.setContentType("text/html");
//        PrintWriter printWriter = rs.getWriter();
//        printWriter.println("<html> " +
//                "<body style=\"font-size: 27px\">" +
//                "Ggg:doPost" +
//                "</body>" + "</html>");
//    }

    // forming http response
    protected void doGet (HttpServletRequest rq, HttpServletResponse rs)
        throws  ServletException, IOException
    {
        System.out.println("Ggg:doGet");
        String firstname = rq.getParameter("firstname");
        String lastname = rq.getParameter("lastname");
        rs.setContentType("text/html");
        PrintWriter pw = rs.getWriter();
        pw.println("<html> <body> <br>GggLOCAL:doGet:firstname=" + firstname
                + "<br>GggLOCAL:doGet:lastname=" + lastname + "<body><html>");
        pw.flush();
    }

    protected void doPost(HttpServletRequest rq, HttpServletResponse rs)
            throws ServletException, IOException {

        System.out.println("Ggg:doPost");

        String firstname = rq.getParameter("firstname");
        String lastname = rq.getParameter("lastname");

        rs.setContentType("text/html");
        PrintWriter pw = rs.getWriter();
        pw.println("<html> <body> <br>GggLOCAL:doPost:firstname=" + firstname
                + "<br>GggLOCAL:doPost:lastname=" + lastname + "<body><html>");
        pw.flush();
    }
}
