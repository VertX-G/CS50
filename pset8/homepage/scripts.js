$(document).ready(function() {
    $('#heroH1').fadeIn();

    $('#submitOrder').click(function() {
        var message = 'Your order of ';

        var bread=$('#breads option:selected').text();
        if (bread != 'Choose...') {
            message += bread + ' ';
        }

        message += 'toast ';

        //var topping=$('input[type=radio][name=topping]').text();
        var topping=$('input[type=radio][name=topping]:checked')[0].value;
        if (topping != 'None') {
            message += 'with ' + topping + ' ';
        }
        console.log('Topping = '+topping);

        try {
            var honey=$('#honey:checked')[0].value;
            if (honey == 'honey') {
                message += 'and ' + honey + ' ';
            }
        }
        catch(err) {

        }

        message += 'cannot be processed at this time.\nPlease try again in a few months time :)';

        alert(message);
    });

    $('#breads').change(function() {
        var selected=$('#breads option:selected').val();
        if (selected == 1){
            $('#imgWhiteToast').removeClass('invisible');
            $('#imgCiabattaToast').addClass('invisible');
            $('#imgFrenchToast').addClass('invisible');
        }
        else if (selected == 2){
            $('#imgWhiteToast').addClass('invisible');
            $('#imgCiabattaToast').removeClass('invisible');
            $('#imgFrenchToast').addClass('invisible');
        }
        else if (selected == 3) {
            $('#imgWhiteToast').addClass('invisible');
            $('#imgCiabattaToast').addClass('invisible');
            $('#imgFrenchToast').removeClass('invisible');
        }
        else {
            $('#imgWhiteToast').addClass('invisible');
            $('#imgCiabattaToast').addClass('invisible');
            $('#imgFrenchToast').addClass('invisible');
        }
    });

    $('input[type=radio][name=topping]').change(function() {
        var topping = this.id;
        if (topping == 't1') {
            $('#imgCheese').removeClass('invisible');
            $('#imgBerries').addClass('invisible');
        }
        else if (topping == 't2') {
            $('#imgCheese').addClass('invisible');
            $('#imgBerries').removeClass('invisible');
        }
        else {
            $('#imgCheese').addClass('invisible');
            $('#imgBerries').addClass('invisible');
        }
    });

    $('#honey').change(function() {
        if (this.checked) {
            $('#imgHoney').removeClass('invisible');
        }
        else {
            $('#imgHoney').addClass('invisible');
        }

    });

    setTimeout(function(){$('.fadeIn').animate({'opacity': '100%'}, 3000);}, 1000);





});


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