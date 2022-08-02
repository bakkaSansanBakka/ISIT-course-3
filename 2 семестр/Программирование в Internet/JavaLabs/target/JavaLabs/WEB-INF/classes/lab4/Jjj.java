package lab4;

import JSPClasses.Regimex;

import javax.servlet.Servlet;
import javax.servlet.ServletConfig;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class Jjj extends HttpServlet implements Servlet {
    public Jjj() {
        super();
        System.out.println("Jjj: constructor");
    }

    public void init(ServletConfig sc) throws ServletException {
        super.init();
        System.out.println("Jjj:init");
    }

    public void destroy() {
        super.destroy();
        System.out.println("Jjj:destroy");
    }

//    protected void service (HttpServletRequest rq, HttpServletResponse rs)
//        throws ServletException, IOException
//    {
//        Regimex regimex = new Regimex();
//        Integer n = regimex.GetHOUR();
//        if ((n > 0) && (n <= 5))
//            rs.sendRedirect("night.jsp");
//        else if ((n > 5) && (n <= 12))
//            rs.sendRedirect("morning.jsp");
//        else if ((n > 12) && (n <= 17))
//            rs.sendRedirect("afternoon.jsp");
//        else
//            rs.sendRedirect("evening.jsp");
//    }

    protected void doGet (HttpServletRequest rq, HttpServletResponse rs)
        throws ServletException, IOException
    {
        rs.sendRedirect("afternoon.jsp");
    }

    protected void doPost (HttpServletRequest rq, HttpServletResponse rs)
            throws ServletException, IOException
    {
        rs.sendRedirect("night.jsp");
    }
}
