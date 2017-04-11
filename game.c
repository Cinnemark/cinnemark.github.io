//		//		//		//		//		//		//		//		//		//

//  GAME SCREEN

//		//		//		//		//		//		//		//		//		//

/*var quest = [
  question:"Vilken av följande öar ingår inte i Öckerö kommun?",
  wrong: ["Knippla","Hyppeln","Grötö"],
  correct: "Vinga"
];*/
function make_question(q,a,w0,w1,w2)
{
  return {
    question: q,
    answer: a,
    wrong: [ w0,w1,w2]
  };
}

var questions =[

    make_question(
      "Vilken av följande öar ingår inte i Öckerö kommun?",
      "Vinga",
      "Knippla","Hyppeln","Grötö"
    ),

    make_question(
      "Ernst Bremer kom från Öckerö. Vad var han mest känd för?",
      "Spritsmuggling",
      "Sjöräddningssällskapet","Skärgårdsdeckare","Marinbiologisk forskning"
    ),

    make_question(
      "Öckerö är en av två svenska kommuner som saknar fast landförbindelse. " +
      "Vad heter den andra?",
      "Gotland",
      "Visby kommun","Borgholms kommun","Orust"
    ),
    make_question(
      "Vilken av Öckerö kommuns öar är störst?",
      "Björkö",
      "Hönö","Öckerö","Rörö"
    ),

    make_question(
      "Vilken av Öckerö kommuns öar har flest invånare?",
      "Hönö",
      "Björkö","Öckerö","Rörö"
    ),
];



var currentQ ;

function choose( id ){ //
    var obj = document.getElementById(id)
    //console.log( obj.innerHTML ) ;

    if ( obj.innerHTML === currentQ.answer )
    {
      console.log("pim pom");
      obj.style.backgroundColor = '#4d4';
      set_question( questions[tick%5]);
    }
    else
    {
      console.log("buh buu");
      obj.style.backgroundColor = 'red';
    }
}

var qstory = [] ;
var options = [] ;
function set_question( Q )
{
  currentQ = Q ;
  //lez zee if noticable
//  var order = [ Q.wrong[0],Q.wrong[1],Q.wrong[2],Q.answer ];
  var q = document.getElementById("question") ;
  q.innerHTML = "<h2>" + Q.question + "</h2>";

  //  terrible randomness

  var abcd = [
    document.getElementById("option_a") ,
    document.getElementById("option_b") ,
    document.getElementById("option_c") ,
    document.getElementById("option_d")
  ];
  var ri = (now()|0) + tick & 3 ;

  abcd[ ri ].innerHTML = Q.answer;
  abcd[ (ri+1)&3 ].innerHTML = Q.wrong[2];
  abcd[ (ri+2)&3 ].innerHTML = Q.wrong[0];
  abcd[ (ri+3)&3 ].innerHTML = Q.wrong[1];

  for( var i = 0 ; i < 4 ; ++i )
    abcd[i].style.backgroundColor = 'grey' ;
}

function game_init()
{
  qstory.length = 0 ;
  tick = 0 ;
  update = menu_update ;
  document.getElementById("zone").style.visibility = "visible" ;


  set_question( questions[0]);
  //show game layout
}



function game_update()
{

  console.log("tehe");

}
