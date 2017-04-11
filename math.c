/*
	Author: Kristoffer Gustavsson
	AKA: Nopykon, nopy, qristofer, Kreaver,
	twitter: @qristofer
	e-mail: cykloffer  at gmail com
*/

//time, random

'use strict';//rm from release


function now(){return Date.now()/1e3;}

var seed = 9;
function srnd(){
	seed=(seed*1103515245+12345)& 0x7fffffff;
	return seed;
}


//timing
var last=now(),rest=0;
function num_frames(Hz)
{
    var cur=now(),
		pas=(cur-last)+rest,
		n
		;

	n= 0 | pas / (1/Hz) ;

	if( n > 0 )
	{
		last=cur;//<< mv to �f n > 0
		if( n > 3 )
		{
			rest=0;//.5/Hz;
			n = 3;
		}
		else
		{
			rest=pas-n*1/Hz;
		}
		return n;
	}
	return 0;
}

// just get's annoying typing Math. all the time
// rm this to save bytes
var sqrt=Math.sqrt,
	abs=Math.abs,
	min=Math.min,
	max=Math.max,
	sin=Math.sin,
	cos=Math.cos,
	ran=Math.random,
	floor=Math.floor,
	round=Math.round ,
	PI = Math.PI
	;


function clamp(v,b,e){return v<b?b:v>e?e:v;}
function rnd(){	return ran()*0xffffff;}
function ranf(){ return 1-2*ran(); }



function VALID( x )
{
	//COMMENT WITH RELEASE

	if ( x == 0.)
		console.log( 'Zero!', x);
	if ( isNaN(x) )
		console.log( 'Nan!', x);
	if ( x == -'Infinity' || x == 'Infinity' )
		console.log( 'Inf!', x);

}

////DOUBLE ARRAY EXPERIMENTATION NOOBQUEST
//for js13k 2017, I'll be using integers only. >:(

//NOOBQUEST 2000
//attempt to help the compiler create double arrays with the double's allocated
//aligned in memory, then again, I may just be obscuring things for a compiler
//that would figure out the right thing otherwise
//I HAVE NO IDEA IF IT WORKS,
//( but it's also shorter syntax than [0., 0., .... ] ( js13k )
//I've tried Float32Array, but for some reason that slowed things down in FF

function darr ( n )
{
	var v = new Array(n);
	for( var i=0; i<n; ++i)
		v[i]=0.0;
	return v;
}
//NOOBQUEST 2001
//attempt to un-fragment an array and rid the allocation memory past length,
//like so: var nv = copya(v); v=null; v=nv;
//I HAVE NO IDEA IF IT WORKS
function copya( v )
{
	var nv = new Array( v.length );
	for( var i = 0, e = v.length; i<e; ++i )
		nv[i] = v[i];
	return nv;
}

//compare n elements in arrays a & b, return true if all are equal
function same(a,b,n){
	for( var i = 0; i < n; ++i)
		if(a[i]!=b[i])
			return 0;
	return 1;

	//var i=0;for(; i < n && a[i]==b[i] ; ++i);return (i==n);

}

//find [] in [] with n identical values, ret index (length of vv if non found)
function findo(vv,v,ne)
{
	var i=0,e=vv.length;
	for(;i<e && !same(vv[i],v,ne);++i);
	return i;
}

//copy sub array values from b to subarray a
function cpyr( a,b, ai, bi, n){for( ;n--; ++ai,++bi )a[ai]=b[bi]; return a;}
//copy n elements a->b form 0 to n
function cpy(d,s,n){for(var i=0; i<n;++i)d[i]=s[i]; return d;}

//DON'T USE //DON'T USE //DON'T USE //DON'T USE //DON'T USE //DON'T USE
function set(){//DON'T USE //DON'T USE //DON'T USE in real time
	for(var i=1; i<arguments.length; ++i)
	    arguments[0][i-1]=arguments[i];
	return arguments[0];
}
//DON'T USE //DON'T USE //DON'T USE //DON'T USE




//interp n elements t amount, store in d
function interp(d,a,b,t,n)
{
	for(var i=0; i<n; ++i)
		d[i] = a[i] + (b[i]-a[i])*t;
	return d;
}

//vector 3d stuff
function dot(a,b){	return a[0]*b[0]+a[1]*b[1]+a[2]*b[2];	}

function cross2(xp,a,b)
{
	//cross
	xp[0]=a[1]*b[2] - a[2]*b[1];
	xp[1]=a[2]*b[0] - a[0]*b[2];
	xp[2]=a[0]*b[1] - a[1]*b[0];
	return xp;
}

function cross(xp,c,va,vb)
{
	var ax = va[0]-c[0],
		ay = va[1]-c[1],
		az = va[2]-c[2],
		bx = vb[0]-c[0],
		by = vb[1]-c[1],
		bz = vb[2]-c[2]
		;
	//cross
	xp[0]=ay*bz - az*by;
	xp[1]=az*bx - ax*bz;
	xp[2]=ax*by - ay*bx;
	return xp;
}

function normalize(n)
{
	var len = sqrt( n[0]*n[0] + n[1]*n[1] + n[2]*n[2] );
	n[0] /= len;
	n[1] /= len;
	n[2] /= len;
	return n;
}

//matrix stuf
function set4(v,x,y,z,w){v[0]=x,v[1]=y,v[2]=z,v[3]=w;}

function vset(v,x,y,z)
{
	v[0]=x,v[1]=y,v[2]=z;
}

function vsub( d, a, b)
{
	d[0] = a[0]-b[0];
	d[1] = a[1]-b[1];
	d[2] = a[2]-b[2];
	return d;
}

function tset(t,rx,ry,rz,ux,uy,uz,bx,by,bz,x,y,z)
{
	t[0]=rx;	t[1]=ry;	t[2]=rz;
	t[3]=ux;	t[4]=uy;	t[5]=uz;
	t[6]=bx;	t[7]=by;	t[8]=bz;
	t[9]=x;		t[10]=y;	t[11]=z;
}

function mset(t,rx,ry,rz,ux,uy,uz,bx,by,bz)
{
	t[0]=rx;	t[1]=ry;	t[2]=rz;
	t[3]=ux;	t[4]=uy;	t[5]=uz;
	t[6]=bx;	t[7]=by;	t[8]=bz;
}

function mmul3f(m,d,x,y,z )
{
	d[0] = m[0]*x + m[3]*y + m[6]*z;
	d[1] = m[1]*x + m[4]*y + m[7]*z;
	d[2] = m[2]*x + m[5]*y + m[8]*z;
}

function mmulv(m,d,v )
{
	d[0] = m[0]*v[0] + m[3]*v[1] + m[6]*v[2];
	d[1] = m[1]*v[0] + m[4]*v[1] + m[7]*v[2];
	d[2] = m[2]*v[0] + m[5]*v[1] + m[8]*v[2];
}

//transform * vec3, store in d
function tmulv(m,d,v )
{
	d[0] = m[0]*v[0] + m[3]*v[1] + m[6]*v[2] + m[9];
	d[1] = m[1]*v[0] + m[4]*v[1] + m[7]*v[2] + m[10];
	d[2] = m[2]*v[0] + m[5]*v[1] + m[8]*v[2] + m[11];
	return d;
}

//transform * vec3, store in d
function tmul3f(m,d,x,y,z )
{
	d[0] = m[0]*x + m[3]*y + m[6]*z + m[9];
	d[1] = m[1]*x + m[4]*y + m[7]*z + m[10];
	d[2] = m[2]*x + m[5]*y + m[8]*z + m[11];
	return d;
}



//multiply two tranforms
function tmul(d,a,b)
{
	//rotate
	d[0] = a[0]*b[0] + a[3]*b[1] + a[6]*b[2];
	d[1] = a[1]*b[0] + a[4]*b[1] + a[7]*b[2];
	d[2] = a[2]*b[0] + a[5]*b[1] + a[8]*b[2];

	d[3] = a[0]*b[3] + a[3]*b[4] + a[6]*b[5];
	d[4] = a[1]*b[3] + a[4]*b[4] + a[7]*b[5];
	d[5] = a[2]*b[3] + a[5]*b[4] + a[8]*b[5];

	d[6] = a[0]*b[6] + a[3]*b[7] + a[6]*b[8];
	d[7] = a[1]*b[6] + a[4]*b[7] + a[7]*b[8];
	d[8] = a[2]*b[6] + a[5]*b[7] + a[8]*b[8];

	//translate
	d[9] = a[0]*b[9] + a[3]*b[10] + a[6]*b[11] + a[9];
	d[10] = a[1]*b[9] + a[4]*b[10] + a[7]*b[11] + a[10];
	d[11] = a[2]*b[9] + a[5]*b[10] + a[8]*b[11] + a[11];
}

//multiply two 3x3 matrices (or transform), rotation only
function mmul(d,a,b)
{
	//rotate
	d[0] = a[0]*b[0] + a[3]*b[1] + a[6]*b[2];
	d[1] = a[1]*b[0] + a[4]*b[1] + a[7]*b[2];
	d[2] = a[2]*b[0] + a[5]*b[1] + a[8]*b[2];

	d[3] = a[0]*b[3] + a[3]*b[4] + a[6]*b[5];
	d[4] = a[1]*b[3] + a[4]*b[4] + a[7]*b[5];
	d[5] = a[2]*b[3] + a[5]*b[4] + a[8]*b[5];

	d[6] = a[0]*b[6] + a[3]*b[7] + a[6]*b[8];
	d[7] = a[1]*b[6] + a[4]*b[7] + a[7]*b[8];
	d[8] = a[2]*b[6] + a[5]*b[7] + a[8]*b[8];

}
/* ==


function tmulv(m,d,v)
{
	d.fill(0);
	for (var k = 0; k < 3; k++)
		for (var j = 0; j < 3; j++)
			d[j] += v[k] * m[k*3+j];
	d[0] += m[9];
	d[1] += m[10];
	d[2] += m[11];
	return d;
}

function tmul(d,a,b)
{
	var i,j,k;
	d.fill(0);
    for (i = 0; i < 4; i++)
		for (k = 0; k < 3; k++)
			for (j = 0; j < 3; j++)
                d[i*3+j] += b[i*3+k] * a[k*3+j];
	//add a's unscaled, unrotated translation
	 d[9] += a[9];
	 d[10] += a[10];
	 d[11] +=  a[11];
}


//transform * vec3, store in d
function tmulv(m,d,v )
{
	d[0] = m[0]*v[0] + m[3]*v[1] + m[6]*v[2] + m[9];
	d[1] = m[1]*v[0] + m[4]*v[1] + m[7]*v[2] + m[10];
	d[2] = m[2]*v[0] + m[5]*v[1] + m[8]*v[2] + m[11];
	return d;
}


function xtmul(d,a,b){

	for(var y=0,x; y<12; y += 3)
		for(x=0;x<3;++x)
			d[y+x]=a[x]*b[y] + a[x+3]*b[y+1] + a[x+6]*b[y+2];
	d[9] += a[9];//*1 ...
	d[10] += a[10];
	d[11] +=  a[11];
	return d;
}



*/
