<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib uri = "TagLibrary.tld" prefix ="taglibrary" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html>
<head>
    <title>Tags Page</title>
</head>
<body>
    <taglibrary:dossier action="post">
        <taglibrary:surname/><br>
        <taglibrary:lastname/><br>
        <taglibrary:sex/><br>
        <taglibrary:submit/><br>
    </taglibrary:dossier>
</body>
</html>
