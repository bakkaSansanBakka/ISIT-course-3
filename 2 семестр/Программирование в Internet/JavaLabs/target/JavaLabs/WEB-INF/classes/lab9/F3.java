package lab9;

import javax.servlet.*;
import java.io.*;

public class F3  implements Filter {
    public void init(FilterConfig cfg) throws ServletException {
        System.out.println("F3:init");
    }

    public void destroy() {
        System.out.println("F3:destroy");
    }

    public void doFilter(ServletRequest rq, ServletResponse rs, FilterChain ch)
            throws IOException, ServletException {
        var filter = rq.getParameter("block3");
        if(filter == null) {
            System.out.println("F3:pass");
            ch.doFilter(rq, rs);
            return;
        } else {
            var writer = rs.getWriter();
            writer.write("F3 blocks request to this resource");
            System.out.println("F3:block");
        }
    }
}
