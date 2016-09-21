/*
	Author: Kristoffer Gustavsson 
	AKA: Nopykon, nopy, qristofer, Kreaver, 
	twitter: @qristofer
	e-mail: cykloffer  at gmail com 
*/

//time, random	

function now(){return Date.now()/1e3;}
function rndi(){return (Math.random()*0xffffffff)|0;}
function ranf(){return Math.random()*2-1;}//-1 to 1

//timing
var tick=1,last=now(),rest=0;
function num_frames(Hz){
    var cur=now(),
		pas=(cur-last)+rest,
		n;

	n=0|(pas/(1.0/Hz));

	if( n > 0 ){
		last=cur;//<< mv to íf n > 0
		if( n > 10 ){
			rest=0;
			n=10;
		}else{
			rest=pas-1.0/Hz*n;
		}
	}
	return n;
}

// common math funcs 
function clamp(X,L,R){return X>R?R:X<L?L:X;} 

var sqrt=Math.sqrt,
	abs=Math.abs,
	min=Math.min,
	max=Math.max,
	sin=Math.sin,
	cos=Math.cos
	;
function fract(x){return x-~~x;}

//vector3 

var _v0=vnew(),_v1=vnew(),_v2=vnew();//local to file vector work space
//copy content from s into d and return d ref
function vcpy(d,s){d[0]=s[0];d[1]=s[1];d[2]=s[2]; return d;}
//set d to xyz and return d
function vset(v,x,y,z){v[0]=x;v[1]=y;v[2]=z;return v;}
//create NEW vector object
function vnew(X,Y,Z){return [X?X:0,Y?Y:0,Z?Z:0];}
//multiply with f
function vpmulf(a,f){return a[0]*=f,a[1]*=f,a[2]*=f,a;}
function vmulf(d,a,f){return vset(d,a[0]*f,a[1]*f,a[2]*f);} 
// function vmul(r,a,b){return r[0]=a[0]*b[0],r[1]=a[1]*b[1],r[2]=a[2]*b[2],r;}
//divide with f
function vpdivf(a,f){return a[0]/=f,a[1]/=f,a[2]/=f,a;}
//multiply with vector
// function vpmul(a,b){a[0]*=b[0];a[1]*=b[1];a[2]*=b[2];return a;}
//add vectors

function vadd(d,a,b){d[0]=a[0]+b[0];d[1]=a[1]+b[1];d[2]=a[2]+b[2];return d;}
function vpadd(a,b){a[0]+=b[0];a[1]+=b[1];a[2]+=b[2];return a;}
function vsub(d,a,b){d[0]=a[0]-b[0]; d[1]=a[1]-b[1];d[2]=a[2]-b[2];return d;}

//make u32 color
function vmc(v){
	var c=255<<24;
	c|=clamp(v[0],0,1)*255;
	c|=clamp(v[1],0,1)*255<<8;
	c|=clamp(v[2],0,1)*255<<16; 
	return c;
}
//interpolate s and t by f
function vplerp(s,t,f){s[0]+=(t[0]-s[0])*f;s[1]+=(t[1]-s[1])*f;s[2]+=(t[2]-s[2])*f;}
function vlerp(d,a,b,f){
	d[0]=a[0]+(b[0]-a[0])*f;
	d[1]=a[1]+(b[1]-a[1])*f;
	d[2]=a[2]+(b[2]-a[2])*f;
	return d;
}

//de de dot
function vdot(a,b){return a[0]*b[0]+a[1]*b[1]+a[2]*b[2];}
//length
function vlen(v){return Math.sqrt(vdot(v,v));} 
//normalize, make a unit length
function vnormalize(d,a){
	var L=vlen(a);
	//DEBUG DEBUG DEBUG DEBUG
	if(L==0.0)alert("vnormalize ZERO DIVISION");
	//DEBUG DEBUG DEBUG DEBUG
	d[0]=a[0]/L;d[1]=a[1]/L;d[2]=a[2]/L;
	return d;
}
function vpnormalize(a){
	var L=vlen(a);
	//DEBUG DEBUG DEBUG DEBUG
	if(L==0.0)alert("vpnormalize ZERO DIVISION");
	//DEBUG DEBUG DEBUG DEBUG
	a[0]/=L;a[1]/=L;a[2]/=L;
	return a;
}

//cross product, calc. and store in d
function vcross(d,a,b){
	d[0]=a[1]*b[2]-a[2]*b[1];
	d[1]=a[2]*b[0]-a[0]*b[2];
	d[2]=a[0]*b[1]-a[1]*b[0];
	return d;
}

//rotate AA, store in vp
function vrotate(d,v,n,a){
	var s=Math.sin(a),c=Math.cos(a),xsa,ndc;
	d[0]=v[0]*c;d[1]=v[1]*c;d[2]=v[2]*c;
    xsa=vpmulf(vcross(_v0,n,v),s);
    ndc=vpmulf(vcpy(_v1,n),(vdot(v,n)*(1-c))); 
    vpadd(d,ndc);
    vpadd(d,xsa);
    return d;
}

//cross product, calc. and store in d
function vreflect(d,e,N){
	var dp2=vdot(e,N)*2;
	return vsub(d,e,vmulf(_v0,N,dp2)); 
}

//matrix4 column major

//object recycling bunch

(function(i){
	MS=[],VS=[];
	while(i--){
		MS[i]=[1.,0.,0.,0., 0.,1.,0.,0., 0.,0.,1.,0., 0.,0.,0.,1.];
		VS[i]=[0.,0.,0.];
	}
})(8);
	
//id amtrix 
function mset(D,a,b,c,d,e,f,g,h,i,j,k,l, m,n,o,p){
	D[0]=a;D[1]=b;D[2]=c;D[3]=d;
	D[4]=e;D[5]=f;D[6]=g;D[7]=h;
	D[8]=i;D[9]=j;D[10]=k;D[11]=l;
	D[12]=m;D[13]=n;D[14]=o;D[15]=p;
	return D;
}
function mcpy(d,s){for(var i=16;i--;)d[i]=s[i];return d;}
 
//mat4 * vec3.5
function mmulv(d,m,v,w){
	d[0]=m[0]*v[0]+m[4]*v[1]+m[8]*v[2]+w*m[12];
	d[1]=m[1]*v[0]+m[5]*v[1]+m[9]*v[2]+w*m[13];
	d[2]=m[2]*v[0]+m[6]*v[1]+m[10]*v[2]+w*m[14];
	return d;
}
//transfromation matrix from position and direction
function mdir(M,P,D,U,L){
	L=L?L:vcross(_v2,D,U);
	return mset(M,
		L[0],L[1],L[2],0,
		U[0],U[1],U[2],0,
		-D[0],-D[1],-D[2],0,
		P[0],P[1],P[2],1); 
}
//look in this direction from this place
function mlook(M,P,D,U){
	var L=vcross(_v0,D,U);
	return mset(M,
		L[0],U[0],-D[0],0,	//LUD! :I
		L[1],U[1],-D[1],0, 
		L[2],U[2],-D[2],0,	
		-vdot(L,P),-vdot(U,P),vdot(D,P),1);	 
}
//matrix set translation
function msett(m,v){m[12]=v[0];m[13]=v[1];m[14]=v[2];return m;};

/*
	matrix multiply
*/
function mmul(dst,m,n){
	/*
	for(var i=16,j,k;i--;){
		j=(0|(i/4))*4;
		k=i%4;
		dst[i]=m[k]*n[j] + m[k+4]*n[j+1] + m[k+8]*n[j+2] + m[k+12]*n[j+3];
	}
	return dst;
	*/ 
    dst[0]=m[0]*n[0]  + m[4]*n[1]  + m[8]*n[2]  + m[12]*n[3];
	dst[1]=m[1]*n[0]  + m[5]*n[1]  + m[9]*n[2]  + m[13]*n[3];
	dst[2]=m[2]*n[0]  + m[6]*n[1]  + m[10]*n[2]  + m[14]*n[3];
	dst[3]=m[3]*n[0]  + m[7]*n[1]  + m[11]*n[2]  + m[15]*n[3];

    dst[4]=m[0]*n[4]  + m[4]*n[5]  + m[8]*n[6]  + m[12]*n[7];
	dst[5]=m[1]*n[4]  + m[5]*n[5]  + m[9]*n[6]  + m[13]*n[7];
	dst[6]=m[2]*n[4]  + m[6]*n[5]  + m[10]*n[6]  + m[14]*n[7];
	dst[7]=m[3]*n[4]  + m[7]*n[5]  + m[11]*n[6]  + m[15]*n[7];

    dst[8]=m[0]*n[8]  + m[4]*n[9]  + m[8]*n[10] + m[12]*n[11];
	dst[9]=m[1]*n[8]  + m[5]*n[9]  + m[9]*n[10] + m[13]*n[11];
	dst[10]=m[2]*n[8]  + m[6]*n[9]  + m[10]*n[10] + m[14]*n[11];
	dst[11]=m[3]*n[8]  + m[7]*n[9]  + m[11]*n[10] + m[15]*n[11];

    dst[12]=m[0]*n[12] + m[4]*n[13] + m[8]*n[14] + m[12]*n[15];
	dst[13]=m[1]*n[12] + m[5]*n[13] + m[9]*n[14] + m[13]*n[15];
	dst[14]=m[2]*n[12] + m[6]*n[13] + m[10]*n[14] + m[14]*n[15];
	dst[15]=m[3]*n[12] + m[7]*n[13] + m[11]*n[14] + m[15]*n[15];
	return dst;
	
}
