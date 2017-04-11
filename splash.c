//		//		//		//		//		//		//		//		//		//

//  MENU SCREEN

//		//		//		//		//		//		//		//		//		//

var start_box ;
function menu_init()
{
  //document.body.style.textAlign = "center";
  tick = 0 ;
  update = menu_update ;

  var start_box = document.getElementById("start_button") ;
  //start_box.style.left = ((window.innerWidth>>1) - 154 ).toString() + "px"  ;

  start_box.innerHTML = "TRYCK HÄR FÖR ATT BÖRJA" ;
  start_box.style.visibility = "visible" ;
  start_box.addEventListener("click", function(){console.log("ALLAHU AKBAR")});
  //var xpos = window.innerWidth ;
  console.log(start_box.innerWidth);

  //console.log( xpos );
  //start_box.style.left = .toString() + "px" ;
}

function menu_update()
{



}

//		//		//		//		//		//		//		//		//		//

//  SPLASH SCREEN

//		//		//		//		//		//		//		//		//		//
var splash_box ;
function splash_init()
{

	//document.body.style.backgroundColor = "#000" ;
	clear_body();

	splash_box = make_box();

	splash_box.style.backgroundImage = "url(header_logo.svg)";
	splash_box.style.backgroundRepeat = "no-repeat";
	splash_box.style.backgroundSize = "50% auto";
	splash_box.style.backgroundPosition = "center center";
	splash_box.style.width = "100%";
	splash_box.style.height = "100%";
	splash_box.style.opacity = "0.0";

  tick = 0 ;
	update = splash_update ;
}

function splash_update()
{

	//splash_box.style.backgroundSize =  (50 + (tick/8)).toString() +"% auto";
	if( tick < 60  )
	{
		splash_box.style.opacity = (tick/60.).toString();
	}
	else if( tick > 120+60)//CHANGE STATE
	{
		clear_body();
		menu_init();
	}
	else if( tick > 120 )
	{
		splash_box.style.opacity = ((120+60-tick)/60.).toString();
	}
}
