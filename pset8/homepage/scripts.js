// LOAD SCRIPTS WHEN DOCUMENT IS READY
$(document).ready(function() {
    
    // FADE IN H1 TITLE
    $('#heroH1').fadeIn();

    // ORDERS PAGE - SUBMIT CLICK
    // Building the alert message
    $('#submitOrder').click(function() {
        var message = 'Your order of ';

        var bread=$('#breads option:selected').text();
        if (bread != 'Choose...') {
            message += bread + ' ';
        }

        message += 'toast ';
        
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

    // ORDERS PAGE - IMAGE VISIBILITY
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