/*

  main.js
  entry

*/

'use strict';

//counters
var tick=0,	frame=0, PAUSE = 0;

//state
var update = null ;

function tick_check()
{
	if( PAUSE )
		return;
	var n=num_frames(60);
	if(n && update != null )
		for(; n--;++tick)
			update();
	else
		tick+=n;
}


function clear_body()
{
		var con = document.getElementById("content") ;
		for(;con.hasChildNodes();)
			con.removeChild(con.firstChild);
}

function make_box(id)
{

	var x = document.createElement( "div");
	x.id = id;
	x.className = "box" ;
	//x.style.visibility = "visible" ;
	var con = document.getElementById("content") ;
	con.appendChild(x);
	return x ;
}

//ENTRY - minimajs
void function main()
{
//	AC = new AudioContext();

	function resize()
	{
		 //set resolution
		 //cv.height = window.innerHeight;
     //cv.width = window.innerWidth ;
  }
	resize() ;

	window.addEventListener('resize', resize, false);

	splash_init();
	//menu_init();
	//game_init();

//	window.addEventListener('keydown',kbd);
//	window.addEventListener('keyup', kbu);

	//set redraw inteval function
	var anim= window.requestAnimationFrame ||
		window.webkitRequestAnimationFrame ||
		window.mozRequestAnimationFrame    ||
		window.oRequestAnimationFrame      ||
		window.msRequestAnimationFrame     ||
		null ;

	if(anim===null)
	{
		window.setInterval(tick_check,1000/60);
	}
	else
	{
		var r_anim = function()
			{

				tick_check();
				anim( r_anim );
			};
		anim( r_anim );
	}
}();
