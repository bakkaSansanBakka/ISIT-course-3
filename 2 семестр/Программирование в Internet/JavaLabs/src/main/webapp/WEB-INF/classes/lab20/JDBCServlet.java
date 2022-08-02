package lab20;

import com.microsoft.sqlserver.jdbc.SQLServerDataSource;

import javax.servlet.http.*;
import javax.servlet.*;
import java.io.*;
import java.sql.*;

public class JDBCServlet extends HttpServlet {
    protected static String SqlBook = "select * from book";
    protected static String SqlBookWhere = "select * from book where book_name = ?";

    protected void doGet(HttpServletRequest rq, HttpServletResponse rs)
            throws ServletException, IOException {
        rs.setCharacterEncoding("CP1251");
        PrintWriter pw = rs.getWriter();
        var bookName = rq.getParameter("bookName");
        try{
            SQLServerDataSource sqlDs = new SQLServerDataSource();

            sqlDs.setIntegratedSecurity(false);
            sqlDs.setTrustServerCertificate(true);
            sqlDs.setUser("sa");
            sqlDs.setPassword("polina12122001");
            sqlDs.setServerName("LAPTOP-JA53F0CF");
            sqlDs.setPortNumber(1433);
            sqlDs.setDatabaseName("P_UNIVER");

            Connection conn = sqlDs.getConnection();
            pw.println("<table>");

            if(bookName == null) {

                PreparedStatement stm = conn.prepareStatement(SqlBook);
                ResultSet rss = stm.executeQuery();
                while (rss.next()) {
                    pw.println("<tr><td>"+rss.getString(1)+"</td>" +
                            "<td>"+rss.getString(2)+"</td>" +
                            "<td>"+rss.getString(3)+"</td></tr>");
                }
            }
            else {
                CallableStatement stm = conn.prepareCall(SqlBookWhere);
                stm.setString(1, bookName);
                ResultSet rss = stm.executeQuery();
                pw.println("<table>");
                while (rss.next()) {
                    pw.println("<tr><td>"+rss.getString(1)+"</td>" +
                            "<td>"+rss.getString(2)+"</td>" +
                            "<td>"+rss.getString(3)+"</td></tr>");
                }
            }
            pw.println("</table>");
            conn.close();
        }
        catch (SQLException e) {
            System.out.println("JDBCServlet:doGet:SQLException:" + e);
        }
    }
}
