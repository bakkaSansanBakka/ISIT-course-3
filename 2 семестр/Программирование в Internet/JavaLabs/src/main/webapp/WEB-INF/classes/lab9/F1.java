package lab9;

import javax.servlet.*;
import java.io.*;

public class F1  implements Filter {
    public void init(FilterConfig cfg) throws ServletException {
        System.out.println("F1:init");
    }

    public void destroy() {
        System.out.println("F1:destroy");
    }

    public void doFilter(ServletRequest rq, ServletResponse rs, FilterChain ch)
            throws IOException, ServletException {
        var filter = rq.getParameter("block1");
        if(filter == null) {
            System.out.println("F1:pass");
            ch.doFilter(rq, rs);
            return;
        } else {
            var writer = rs.getWriter();
            writer.write("F1 blocks request to this resource");
            System.out.println("F1:block");
        }
    }
}
