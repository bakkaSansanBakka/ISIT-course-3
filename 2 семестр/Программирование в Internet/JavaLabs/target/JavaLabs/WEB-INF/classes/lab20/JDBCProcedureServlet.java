package lab20;

import com.microsoft.sqlserver.jdbc.SQLServerDataSource;

import javax.servlet.http.*;
import javax.servlet.*;
import java.io.*;
import java.sql.Connection;
import java.sql.*;

public class JDBCProcedureServlet extends HttpServlet {
    static String SqlBookPrice = "{call GetBookPrice(?, ?)}";

    protected void doGet (HttpServletRequest rq, HttpServletResponse rs)
            throws ServletException, IOException {
        rs.setCharacterEncoding("CP1251");

        PrintWriter pw = rs.getWriter();
        String bookName = rq.getParameter("bookName");
        try {
            SQLServerDataSource sqlDs = new SQLServerDataSource();

            sqlDs.setIntegratedSecurity(false);
            sqlDs.setTrustServerCertificate(true);
            sqlDs.setUser("sa");
            sqlDs.setPassword("polina12122001");
            sqlDs.setServerName("LAPTOP-JA53F0CF");
            sqlDs.setPortNumber(1433);
            sqlDs.setDatabaseName("P_UNIVER");

            Connection conn = sqlDs.getConnection();

            CallableStatement stm = conn.prepareCall(SqlBookPrice);
            stm.setString(1, bookName);
            stm.registerOutParameter(2, Types.INTEGER);
            stm.execute();
            String response = stm.getString(2);
            pw.println("book price = " + response);
            conn.close();
        } catch (SQLException e) {
            System.out.println("JDBCPocedureServlet:doGet:SQLException:" + e);
        }
    }
}
