
var loaded=false,wavetime = 10.,imgscale=1.,alpha=1.,//lerp to 1.5
	mx=0,my=0,cur_img = 0;

img=new Image();
var img_src=[
'img/DSC_0803.jpeg',
'img/DSC_0001.jpeg',
'img/DSC_0152_low.jpg',
'img/DSC_0019.jpeg',
'img/DSC_0126.jpeg',
'img/DSC_1377.jpeg',
'img/DSC_0371.jpeg',
'img/DSC_0433.jpeg',
'img/orange.jpg',
];
	
function change_bg()
{

	alhpa=1.;
	++cur_img; cur_img%=img_src.length;
	load_data(img_src[cur_img]);
	imgscale=1.25
}
function load_data(str){
	//image
	//img = null;
	//img=new Image();
	img.src = str;//'orange.jpg'; //bg image
	//img.src = 'img/orange_hsc.jpg'; //bg image

	//img.onload = 'img.png';
	img.onload = function(){
		loaded=true;
	};
}


function scale_to_fit( cw, ch, iw, ih )
{
	var x= iw/cw;
	var y= ih/ch;
	return min(x,y);
}


function draw_stuff() {
	//clear
	c.setTransform(1,0,0,1,0,0);

	c.fillStyle = 'rgb(0,0,0,.1)';
	c.fillRect(0,0,cw,ch);

	var wbeg=ch*.1,wend=ch*.9,wh=wend-wbeg;
	
	//image 
	imgscale += ( 1. - imgscale )*.00135;
	if(loaded){
		var s= scale_to_fit(cw, ch, img.width,img.height);
		c.setTransform(imgscale,0,0,imgscale,cw/2,ch/2);
		c.drawImage(img,
					(img.width-s*cw)/2,
					(img.height-s*ch)/2,
					s*cw,
					s*ch,
					-cw/2,-ch/2,
					cw,ch);
		alpha-=alpha*.05;
	}else{}

	c.setTransform(1,0,0,1,0,0);
	if(alpha > .01)	{
		c.fillStyle= 'rgba(204,170,15,'+ alpha.toString() + ')';
		c.fillRect(0,0,cw,ch);
	}
	
	//waves
	c.fillStyle='#111133';
	function wavepoly(start,end,freq,amp,div,t){
		c.beginPath();
		c.moveTo(0,0);
		for(var i=0;i<div+1;++i)
			c.lineTo(i*cw/div,
					 start+amp+amp*sin((t*freq)-(i/div)*6.28)*ratio);
		c.lineTo(cw,0);
		c.lineTo(0,0);
		c.fill();
		
		c.beginPath();
		c.fillStyle='#fff';		
		c.moveTo(0,ch);
		for(var i=0;i<div+1;++i)
			c.lineTo(i*cw/div,
					 end-amp+amp*sin((t*freq)-(i/div)*6.28)*ratio);
		c.lineTo(cw,ch);
		c.lineTo(0,ch);
		c.fill();
	}
	wavetime*=.985;
	wavepoly(wbeg,wend,.5, ch/50, 24,wavetime +
			 fract(now())*.01);

}

function scroll_to(x){
	window.scrollTo(0,document.getElementById(x).offsetTop);
}


//Entry
var sw,sh,cw,ch;
var cm,oss,tja,soc;
/*
  Entry
*/ 

(function() {
	//global canvas, context2d
	cv = document.getElementById("canvas");
	if(!cv)
		return document.write("Can't find canvas id! HTML5 support bork?");
    c = cv.getContext('2d');

//	change_bg();
 	imgscale=1.25
 load_data('img/orange.jpg');

	//obtain elements
	cin=document.getElementById("cinnemark");
	oss=document.getElementById("om_oss");
	tja=document.getElementById("tjanster");
	soc=document.getElementById("socialt");


    // resize event
    window.addEventListener('resize', resize_canvas, false);

	//mouse move
	canvas.addEventListener('mousemove',function (e){
		var rect=cv.getBoundingClientRect();
		mx = e.clientX - rect.left;
		my = e.clientY - rect.top;
	},false);
        
    function resize_canvas() {
		cw=sw=canvas.width=window.innerWidth;
		ch=sh=canvas.height= 0|(window.innerHeight *.75);
		ratio = sw/sh;

		if( cv.width / cv.height < 1. ){
			//load default / widescreen css
		}else{
			//load highscreen css
		}
//			mobile_layout();
//		else
		
		draw_stuff();
		//assign to div
    }

	resize_canvas();
	

	//
	window.setInterval(change_bg,  10000);
	window.setInterval(draw_stuff,100/24);
	
})();
