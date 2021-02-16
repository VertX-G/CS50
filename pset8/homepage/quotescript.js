// load scripts when the document is ready
$(document).ready(function() {
    // populate the array of quotes
    var quotes = [
        {
        	"text": "“My hour for tea is half-past five, and my buttered toast waits for nobody.”",
        	"author": "Wilkie Collins, The Woman in White",
        	"ref": "https://www.goodreads.com/quotes/tag/toast"
        },
        {
        	"text": "“Toast was a pointless invention from the Dark Ages. Toast was an implement of torture that caused all those subjected to it to regurgitate in verbal form the sins and crimes of their past lives.<br>Toast was a ritual item devoured by fetishists in the belief that it would enhance their kinetic and sexual powers. Toast cannot be explained by any rational means.<br><br>Toast is me.<br><br>I am toast.”",
        	"author": "Margaret Atwood, Oryx and Crake",
        	"ref": "https://www.goodreads.com/quotes/tag/toast"
        },
        {
        	"text": "“I don't drink coffee I take tea my dear<br>I like my toast done on one side ...”",
        	"author": "Sting, Nothing Like the Sun",
        	"ref": "https://www.goodreads.com/quotes/tag/toast"
        },
        {
        	"text": "“Though we eat little flesh and drink no wine,<br>Yet let's be merry; we'll have tea and toast;<br>Custards for supper, and an endless host<br>Of syllabubs and jellies and mincepies,<br>And other such ladylike luxuries.”",
        	"author": "Percy Bysshe Shelley, The Complete Poems",
        	"ref": "https://www.goodreads.com/quotes/tag/toast"
        },
        {
        	"text": "“If you're going to be in a traffic jam, at least enjoy the flavor. Make some toast.”",
        	"author": "Bashar",
        	"ref": "https://www.goodreads.com/quotes/tag/toast"
        },
        {
        	"text": "“I always like toast in a crisis.”",
        	"author": "James Goss, Doctor Who: Dead Air",
        	"ref": "https://www.goodreads.com/quotes/tag/toast"
        },
        {
        	"text": "“There is nothing more depressing than toast that no one eats.”",
        	"author": "Peter Hedges, What's Eating Gilbert Grape",
        	"ref": "https://www.goodreads.com/quotes/tag/toast"
        },
        {
        	"text": "“Figs are delicious with soft cheese and ham,<br>Toast is quite scrumptious with butter and jam,<br>Eggs are improved by parsley and salt,<br>But milkshakes are best with strawberries and malt.”",
        	"author": "Angelica Banks, Finding Serendipity",
        	"ref": "https://www.goodreads.com/quotes/tag/toast"
        },
        {
        	"text": '“If toast always lands butter-side down, and cats always land on their feet, what happens if you strap toast on the back of a cat and drop it?”',
        	"author": "Steven Wright",
        	"ref": "http://www.foodreference.com/html/qtoast.html"
        },
        {
        	"text": '“I never had a piece of toast<br>Particulary long and wide,<br>But fell upon the sanded floor,<br>And always on the buttered side.”',
        	"author": "James Payn, English novelist (1830-1898)",
        	"ref": "http://www.foodreference.com/html/qtoast.html"
        },
        {
        	"text": "“I never strove to rule the roast,<br>She ne'er refus'd to pledge my toast.”",
        	"author": "Matthew Prior, 'Turtle and Sparrow'",
        	"ref": "http://www.foodreference.com/html/qtoast.html"
        },
        {
        	"text": "“I went to a restaurant that serves 'breakfast at any time'. So I ordered French Toast during the Renaissance.”",
        	"author": "Steven Wright",
        	"ref": "https://www.brainyquote.com/topics/toast-quotes"
        },
        {
        	"text": "“I like to use 'I Can't Believe it's Not Butter' on my toast in the morning, because sometimes when I eat breakfast, I like to be incredulous. How was breakfast? Unbelievable.”",
        	"author": "Demetri Martin",
        	"ref": "https://www.brainyquote.com/topics/toast-quotes"
        },
        {
        	"text": "“That I survived the Holocaust and went on to love beautiful girls, to talk, to write, to have toast and tea and live my life - that is what is abnormal.”",
        	"author": "Elie Wiesel",
        	"ref": "https://www.brainyquote.com/topics/toast-quotes"
        },
        {
        	"text": "“A slice of hot, buttered toast is the perfect meal. It's not too much and not too little, and it gives you just the right buzz.”",
        	"author": "Naveen Andrews",
        	"ref": "https://www.brainyquote.com/topics/toast-quotes"
        }
    ];

    shuffle(quotes);

    qindex = 0;

    setQuote(qindex, quotes);

    // change the quote when the user clicks anywhere in the window
    $(document).click(function(evt){

        //debugger;

        //if($(evt.target).closest('navbar')){      // all clicks are navbar
        //->if($(evt.target).hasClass('navbar')){     // only works with navbar, not children
        //if($(evt.target).children('navbar')){     // all clicks are navbar
        //if($(evt.target) == 'navbar'){            // no clicks are navbar
        //if($(evt.target).hasClass('navbar').children){ // no clicks are navbar
        //->if($(evt.target).attr('href') != undefined){ // hasAttribute is not a function
        //if($(evt.target).hasClass('nav[\w\d-]+')){ // no clicks are navbar

        // do not change when the user clicks anywhere in the navbar, or on an href
        if($(evt.target).hasClass('navbar') || $(evt.target).parents('nav').length > 0 || $(evt.target).attr('href') != undefined){
            return;
        }

        qindex++;

        if(qindex >= quotes.length){
            shuffle(quotes);
            qindex = 0
        }

        setQuote(qindex, quotes);
    })
})

// inject the next quote in the array into the html code
function setQuote(i, quotes) {
    $('#quoteText').html(quotes[i].text);
    $('#quoteAuthor').html(quotes[i].author);
    $('#quoteAuthor').prop('href', quotes[i].ref);
}

/* https://bost.ocks.org/mike/shuffle/ */
// shuffle the quotes array
function shuffle(array) {
  var m = array.length, t, i;

  // While there remain elements to shuffle…
  while (m) {

    // Pick a remaining element…
    i = Math.floor(Math.random() * m--);

    // And swap it with the current element.
    t = array[m];
    array[m] = array[i];
    array[i] = t;
  }

  return array;
};

/*
var list = []

for (var i = 0; i < 15; i++)
{
    list.push(i);
}
console.log(list);

shuffle(list);
console.log(list);
*/
