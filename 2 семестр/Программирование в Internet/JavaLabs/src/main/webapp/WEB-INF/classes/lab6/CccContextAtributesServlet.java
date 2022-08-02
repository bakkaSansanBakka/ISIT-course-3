package lab6;

import lab6.JavaBeans.CBean;

import javax.servlet.*;
import javax.servlet.http.*;
import java.io.IOException;

public class CccContextAtributesServlet extends HttpServlet implements Servlet {

    CBean cBean;

    public CccContextAtributesServlet() {
        super();
        System.out.println("CccContextAtributesServlet: constructor");
    }

    public void init(ServletConfig sc) throws ServletException {
        super.init();
        System.out.println("CccContextAtributesServlet:init");

        cBean = new CBean();
        ServletContext servletContext = sc.getServletContext();
        servletContext.setAttribute("atrCBean", cBean);
    }

    public void destroy() {
        super.destroy();
        System.out.println("CccContextAtributesServlet:destroy");
    }

    protected void service (HttpServletRequest rq, HttpServletResponse rs)
        throws ServletException, IOException
    {
        String CBeanParam = rq.getParameter("CBean");
        String Value1 = rq.getParameter("Value1");
        String Value2 = rq.getParameter("Value2");
        String Value3 = rq.getParameter("Value3");

        ServletContext servletContext = rq.getServletContext();

        if (CBeanParam.equals("new"))
        {
            //cBean = new CBean();
            servletContext.setAttribute("atrCBean", cBean);
            if (!(Value1 == null))
            {
                cBean.SetValue1(Value1);
            }

            if (!(Value2 == null))
            {
                cBean.SetValue2(Value2);
            }

            if (!(Value3 == null))
            {
                cBean.SetValue3(Value3);
            }
        }

        servletContext.setAttribute("atrCBean", cBean);

        rq.getRequestDispatcher("/pages/lab6/CccContextAtributes.jsp").forward(rq, rs);
    }
}
