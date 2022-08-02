<%@ page import="lab6.JavaBeans.CBean" %>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>CccSessionAttributes page</title>
</head>
<body>
<%
    HttpSession sessionI = request.getSession();
    String sessionId = sessionI.getId();
    CBean cBean = (CBean) sessionI.getAttribute(sessionId);
%>
<%=request.getParameter("CBean")%>
<p>Value1 = <%=cBean.GetValue1()%></p>
<p>Value2 = <%=cBean.GetValue2()%></p>
<p>Value3 = <%=cBean.GetValue3()%></p>
</body>
</html>
