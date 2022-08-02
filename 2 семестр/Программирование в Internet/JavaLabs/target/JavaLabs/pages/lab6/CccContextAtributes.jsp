<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ page import="lab6.JavaBeans.CBean" %>
<html>
<head>
    <title>CccContextAttributes page</title>
</head>
<body>
<%
    ServletContext sc = getServletConfig().getServletContext();
    CBean cBean = (CBean)sc.getAttribute("atrCBean");
%>
<%=request.getParameter("CBean")%>
<p>Value1 = <%=cBean.GetValue1()%></p>
<p>Value2 = <%=cBean.GetValue2()%></p>
<p>Value3 = <%=cBean.GetValue3()%></p>

</body>
</html>
