

$(document).ready(function() {
    $('#submitOrder').click(function() {
        alert('Your order cannot be processed at this time.\nPlease try again in a few months time :)');
    })

})


/*
var quoteList = [];

var quote = {
    quoteText:'',
    quoteAuthor:'',
    quoteRef:''
};
*/


/* https://stackoverflow.com/a/7431565 */
/*
$(document).ready(function() {
    $.ajax({
        type: "GET",
        url: "data/quotes.csv",
        dataType: "text",
        success: function(data) {processData(data);}
     });
});

function processData(allText) {
    var allTextLines = allText.split(/\r\n|\n/);
    var headers = allTextLines[0].split(',');
    var lines = [];

    for (var i=1; i<allTextLines.length; i++) {
        var data = allTextLines[i].split(',');
        if (data.length == headers.length) {

            var tarr = [];
            for (var j=0; j<headers.length; j++) {
                tarr.push(headers[j]+":"+data[j]);
            }
            lines.push(tarr);
        }
    }
    // alert(lines);
}
*/


/* https://stackoverflow.com/a/28544299 */
/*
arr = bufferString.split('\n');

var headers = arr[0].split(',');

for(var i = 1; i < arr.length; i++) {
    var data = arr[i].split(',');
    var obj = {};
    for(var j = 0; j < data.length; j++) {
        obj[headers[j].trim()] = data[j].trim();
    }
}
*/