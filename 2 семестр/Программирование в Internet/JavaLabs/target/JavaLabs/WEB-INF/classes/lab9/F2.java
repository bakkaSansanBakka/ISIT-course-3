package lab9;

import javax.servlet.*;
import java.io.*;

public class F2  implements Filter {
    public void init(FilterConfig cfg) throws ServletException {
        System.out.println("F2:init");
    }

    public void destroy() {
        System.out.println("F2:destroy");
    }

    public void doFilter(ServletRequest rq, ServletResponse rs, FilterChain ch)
            throws IOException, ServletException {
        var filter = rq.getParameter("block2");
        if(filter == null) {
            System.out.println("F2:pass");
            ch.doFilter(rq, rs);
            return;
        } else {
            var writer = rs.getWriter();
            writer.write("F2 blocks request to this resource");
            System.out.println("F2:block");
        }
    }
}
