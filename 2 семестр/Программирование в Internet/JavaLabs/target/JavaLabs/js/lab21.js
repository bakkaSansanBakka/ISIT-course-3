const req = new XMLHttpRequest();

const simpleSumForm = document.querySelector("#simplesumform");
const simpleSumButton = simpleSumForm.querySelector('[name="add"]');

///1///

simpleSumButton.addEventListener('click', () => {

    const x = simpleSumForm.elements['x'];
    const y = simpleSumForm.elements['y'];
    const z = simpleSumForm.elements['z'];

    req.open("POST","SumServlet", true);
    req.onerror = (ev) => {
        console.log(ev);
    };
    req.onload = () => {
        console.log("response");
        if (req.readyState === 4) {
            if (req.status === 200) {
                z.value = req.getResponseHeader("Value-Z");
            } else {
                alert("status = " + req.status + "\n" + req.statusText);
            }
        }
    }
    req.setRequestHeader("Value-X",  x.value);
    req.setRequestHeader("Value-Y",  y.value);
    console.log("send");
    req.send();
});

///2///

const nformXML = document.querySelector("#nformxml");
const nformbuttonXML = nformXML.elements['get'];

nformbuttonXML.addEventListener('click', () => {
    const n = nformXML.elements['n'];
    const span = document.querySelector('#xml');

    req.open("POST","RandomArrayServletXML", true);
    req.onerror = (ev) => {
        console.log(ev);
    };
    req.onload = () => {
        console.log("response");
        if (req.readyState === 4) {
            if (req.status === 200) {
                var xmldoc = req.responseXML;
                console.log(xmldoc);
                var tsnum = xmldoc.getElementsByTagName("num");
                console.log(tsnum);
                var rc = "";
                for (var i = 0; i < tsnum.length; i++){
                    rc += tsnum[i].textContent+ " ";
                }
                span.innerHTML = rc;
            } else {
                alert("status = " + req.status + "\n" + req.statusText);
            }
        }
    }
    req.setRequestHeader("XRand-N",  n.value)
    req.send();
});


const nformJSON = document.querySelector("#nformjson");
const nformbuttonJSON = nformJSON.elements['get'];

///3///

nformbuttonJSON.addEventListener('click', () => {
    const n = nformJSON.elements['n'];
    const span = document.querySelector('#json');

    req.open("POST","RandomArrayServletJSON", true);
    req.onerror = (ev) => {
        console.log(ev);
    };
    req.onload = () => {
        console.log("response");
        if (req.readyState === 4) {
            if (req.status === 200) {
                console.log(req.responseText);6
                var array = JSON.parse(req.responseText).nums;
                let rc = "";
                for (var i = 0; i < array.length; i++) {
                    rc += array[i] + " ";
                }
                span.innerHTML = rc;
            } else {
                alert("status = " + req.status + "\n" + req.statusText);
            }
        }
    }
    req.setRequestHeader("XRand-N",  n.value)
    req.send();
});

///4///
const nformCombined = document.querySelector("#combined");
const nformbuttonCombined = nformCombined.elements['start'];

nformbuttonCombined.addEventListener('click', () => {
    const x = nformCombined.elements['x'];
    const y = nformCombined.elements['y'];
    const z = nformCombined.elements['z'];
    const nxml = nformCombined.elements['nxml'];
    const njson = nformCombined.elements['njson'];
    const spanxml = document.querySelector('#xml2');
    const spanjson = document.querySelector('#json2');

    req.open("POST","SumServlet?timeout=1", false);
    req.setRequestHeader("Value-X",  x.value);
    req.setRequestHeader("Value-Y",  y.value);
    req.send();
    z.value = req.getResponseHeader("Value-Z");
    console.log("SumServlet");

    req.open("POST","RandomArrayServletXML?timeout=1", false);
    req.setRequestHeader("XRand-N",  nxml.value)
    req.send();
    let xmldoc = req.responseXML;
    console.log(xmldoc);
    let tsnum = xmldoc.getElementsByTagName("num");
    console.log(tsnum);
    let rc = "";
    for (var i = 0; i < tsnum.length; i++){
        rc += tsnum[i].textContent+ " ";
    }
    spanxml.innerHTML = rc;
    console.log("XML");

    req.open("POST","RandomArrayServletJSON?timeout=1", false);
    req.setRequestHeader("XRand-N",  njson.value)
    req.send();
    var array = JSON.parse(req.responseText).nums;
    rc = "";
    for (var i = 0; i < array.length; i++) {
        rc += array[i] + " ";
    }
    spanjson.innerHTML = rc;
    console.log("JSON");
});

////5/////

// nformbuttonJSON.addEventListener('click', () => {
//     const n = nformJSON.elements['n'];
//     const span = document.querySelector('#json');
//
//     $.ajax('RandomArrayServletJSON', {
//         method: 'POST',
//         beforeSend: function(request) {
//             request.setRequestHeader("XRand-N", n.value);
//         },
//         success: function (data) {
//             console.log(data);
//             let rc = "";
//             for (var i = 0; i < data.nums.length; i++) {
//                 rc += data.nums[i] + " ";
//             }
//             span.innerHTML = rc;
//         }
//     })
// });