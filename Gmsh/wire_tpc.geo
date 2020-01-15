lc_0 = 1.0;
lc_05 = 1.0;
lc_1 = 1.0;

vw = 28; 
vh = 12;

//wire radius
wr = 0.01;
//sqrt(2)
//R = 1.41421356;

// cage width
cw = 15; 

//cageout
Point(  1) = {vw/2+0.2, vw/2+0.2, -0.2, lc_1};
Point(  2) = {-vw/2-0.2, vw/2+0.2, -0.2, lc_1};
Point(  3) = {-vw/2-0.2, -vw/2-0.2, -0.2, lc_1};
Point(  4) = {vw/2+0.2, -vw/2-0.2, -0.2, lc_1};
Point(  5) = {vw/2+0.2, vw/2+0.2, vh+0.2, lc_1};
Point(  6) = {-vw/2-0.2, vw/2+0.2, vh+0.2, lc_1};
Point(  7) = {-vw/2-0.2, -vw/2-0.2, vh+0.2, lc_1};
Point(  8) = {vw/2+0.2, -vw/2-0.2, vh+0.2, lc_1};

//cagein
Point(  9) = {vw/2, vw/2, 0, lc_1};
Point(  10) = {-vw/2, vw/2, 0, lc_1};
Point(  11) = {-vw/2, -vw/2, 0, lc_1};
Point(  12) = {vw/2, -vw/2, 0, lc_1};
Point(  13) = {vw/2, vw/2, vh, lc_1};
Point(  14) = {-vw/2, vw/2, vh, lc_1};
Point(  15) = {-vw/2, -vw/2, vh, lc_1};
Point(  16) = {vw/2, -vw/2, vh,lc_1};

//GEM TOP
Point( 17) = {cw/2, cw/2, 0.1, lc_05};
Point( 18) = {-cw/2, cw/2, 0.1, lc_05};
Point( 19) = {-cw/2, -cw/2, 0.1, lc_05};
Point( 20) = {cw/2, -cw/2, 0.1, lc_05};
Point( 21) = {cw/2, cw/2, 0.2, lc_05};
Point( 22) = {-cw/2, cw/2, 0.2, lc_05};
Point( 23) = {-cw/2, -cw/2, 0.2, lc_05};
Point( 24) = {cw/2, -cw/2, 0.2, lc_05};

//Mesh
Point( 25) = {cw/2, cw/2, 10.2, lc_05};
Point( 26) = {-cw/2, cw/2, 10.2, lc_05};
Point( 27) = {-cw/2, -cw/2, 10.2, lc_05};
Point( 28) = {cw/2, -cw/2, 10.2, lc_05};
Point( 29) = {cw/2, cw/2, 10.3, lc_05};
Point( 30) = {-cw/2, cw/2, 10.3, lc_05};
Point( 31) = {-cw/2, -cw/2, 10.3, lc_05};
Point( 32) = {cw/2, -cw/2, 10.3, lc_05};

//cagedefine
Line( 1) = { 1, 2}; Line( 2) = { 2, 3};
Line( 3) = { 3, 4}; Line( 4) = { 4, 1};

Line( 5) = { 5, 6}; Line( 6) = { 6, 7};
Line( 7) = { 7, 8}; Line( 8) = { 8, 5};

Line( 9) = { 1, 5};
Line( 10) = { 2, 6};
Line( 11) = { 3, 7};
Line( 12) = { 4, 8};

//Physical Line(1) = {1,2,3,4,5,6,7,8,9,10,11,12};

Line Loop( 1) = {1, 2, 3, 4};
Line Loop( 2) = {5, 6, 7, 8};
Line Loop( 3) = {1, 10, -5, -9};
Line Loop( 4) = {2, 11, -6, -10};
Line Loop( 5) = {3, 12, -7, -11};
Line Loop( 6) = {4, 9, -8, -12};

Line( 13) = { 9, 10};Line( 14) = { 10, 11};
Line( 15) = { 11, 12};Line( 16) = { 12, 9};

Line( 17) = { 13, 14};Line( 18) = { 14, 15};
Line( 19) = { 15, 16};Line( 20) = { 16, 13};

Line( 21) = { 9, 13};
Line( 22) = { 10, 14};
Line( 23) = { 11, 15};
Line( 24) = { 12, 16};

//Physical Line( 2) = {13,14,15,16,17,18,19,20,21,22,23,24};

Line Loop( 7) = {13, 14, 15, 16}; 
Line Loop( 8) = {17, 18, 19, 20}; 
Line Loop( 9) = {13, 22, -17, -21}; 
Line Loop( 10) = {14, 23, -18, -22}; 
Line Loop( 11) = {15, 24, -19, -23}; 
Line Loop( 12) = {16, 21, -20, -24};  


//outsurface
Plane Surface( 1) = {1};
Plane Surface( 2) = {2};
Plane Surface( 3) = {3};
Plane Surface( 4) = {4};
Plane Surface( 5) = {5};
Plane Surface( 6) = {6};

//insurface
Plane Surface( 7) = {7};
Plane Surface( 8) = {8};
Plane Surface( 9) = {9};
Plane Surface( 10) = {10};
Plane Surface( 11) = {11};
Plane Surface( 12) = {12};

//physur[0] = newreg;
Physical Surface( 1) = {1,2,3,4,5,6,7,8,9,10,11,12};

//out
Surface Loop( 1) = {1, 2, 3, 4, 5, 6};
//in
Surface Loop( 2) = {7, 8, 9, 10, 11, 12};

//cagevolume
vol[1] = newreg;
Volume(vol[1]) = {1,2};



//GEMdefine
Line(25) = {17, 18}; Line(26) = {18, 19};
Line(27) = {19, 20}; Line(28) = {20, 17};
Line(29) = {21, 22}; Line(30) = {22, 23};
Line(31) = {23, 24}; Line(32) = {24, 21};

Line(33) = {17, 21}; Line(34) = {18, 22};
Line(35) = {19, 23}; Line(36) = {20, 24};

//Physical Line( 3) = {25,26,27,28,29,30,31,32,33,34,35,36};

Line Loop( 13) = {25, 26, 27, 28};
Line Loop( 14) = {29, 30, 31, 32};
Line Loop( 15) = {25, 34, -29, -33};
Line Loop( 16) = {26, 35, -30, -34};
Line Loop( 17) = {27, 36, -31, -35};
Line Loop( 18) = {28, 33, -32, -36};

Plane Surface( 13) = {13}; 
Plane Surface( 14) = {14}; 
Plane Surface( 15) = {15}; 
Plane Surface( 16) = {16}; 
Plane Surface( 17) = {17}; 
Plane Surface( 18) = {18}; 

//physur[1] = newreg;
Physical Surface( 2) = {13,14,15,16,17,18};

surloop[0] = newreg;
Surface Loop(surloop[0]) = {13,14,15,16,17,18};

//GEMvolume
vol[2] = newreg;
Volume(vol[2]) = {surloop[0]};



//Meshdefine
Line(37) = {25, 26}; Line(38) = {26, 27};
Line(39) = {27, 28}; Line(40) = {28, 25};
Line(41) = {29, 30}; Line(42) = {30, 31};
Line(43) = {31, 32}; Line(44) = {32, 29};

Line(45) = {25, 29}; Line(46) = {26, 30};
Line(47) = {27, 31}; Line(48) = {28, 32};

//Physical Line( 4) = {37,38,39,40,41,42,43,44,45,46,47,48};

Line Loop(19) = {37, 38, 39, 40};
Line Loop(20) = {41, 42, 43, 44};
Line Loop(21) = {37, 46, -41, -45};
Line Loop(22) = {38, 47, -42, -46};
Line Loop(23) = {39, 48, -43, -47};
Line Loop(24) = {40, 45, -44, -48};

Plane Surface(19) = {19};
Plane Surface(20) = {20};
Plane Surface(21) = {21};
Plane Surface(22) = {22};
Plane Surface(23) = {23};
Plane Surface(24) = {24};

//physur[2] = newreg;
Physical Surface( 3) = {19,20,21,22,23,24};

surloop[1] = newreg;
Surface Loop(surloop[1]) = {19,20,21,22,23,24};

//Meshvolume
vol[3] = newreg;
Volume(vol[3]) = {surloop[1]};



//wiredefine
wz = 0.3;

Macro CWire

	//wireout
	p1 = newp; Point(p1) = {cw/2+wr, cw/2+wr, wz+wr, lc_0};
	p2 = newp; Point(p2) = {-cw/2-wr, cw/2+wr, wz+wr, lc_0};
	p3 = newp; Point(p3) = {-cw/2-wr, -cw/2-wr, wz+wr, lc_0};
	p4 = newp; Point(p4) = {cw/2+wr, -cw/2-wr, wz+wr, lc_0};
	p5 = newp; Point(p5) = {cw/2+wr, cw/2+wr, wz-wr, lc_0};
	p6 = newp; Point(p6) = {-cw/2-wr, cw/2+wr, wz-wr, lc_0};
	p7 = newp; Point(p7) = {-cw/2-wr, -cw/2-wr, wz-wr, lc_0};
	p8 = newp; Point(p8) = {cw/2+wr, -cw/2-wr, wz-wr, lc_0};
	//wirein
	p9 = newp; Point(p9) = {cw/2-wr, cw/2-wr, wz+wr, lc_0};
	p10 = newp; Point(p10) = {-cw/2+wr, cw/2-wr, wz+wr, lc_0};
	p11 = newp; Point(p11) = {-cw/2+wr, -cw/2+wr, wz+wr, lc_0};
	p12 = newp; Point(p12) = {cw/2-wr, -cw/2+wr, wz+wr, lc_0};
	p13 = newp; Point(p13) = {cw/2-wr, cw/2-wr, wz-wr, lc_0};
	p14 = newp; Point(p14) = {-cw/2+wr, cw/2-wr, wz-wr, lc_0}; 
	p15 = newp; Point(p15) = {-cw/2+wr, -cw/2+wr, wz-wr, lc_0};
	p16 = newp; Point(p16) = {cw/2-wr, -cw/2+wr, wz-wr, lc_0};  

	//outlineup
	l1 = newc; Line( l1) = { p1, p2}; l2 = newreg; Line( l2) = { p2, p3};
	l3 = newc; Line( l3) = { p3, p4}; l4 = newreg; Line( l4) = { p4, p1};
	//outlinelow
	l5 = newc; Line( l5) = { p5, p6}; l6 = newreg; Line( l6) = { p6, p7};
	l7 = newc; Line( l7) = { p7, p8}; l8 = newreg; Line( l8) = { p8, p5};
	//inlineup
	l9 = newc; Line( l9) = { p9, p10}; l10 = newreg; Line( l10) = { p10, p11};
	l11 = newc; Line( l11) = { p11, p12}; l12 = newreg; Line( l12) = { p12, p9};
	//inlinelow
	l13 = newc; Line( l13) = { p13, p14}; l14 = newreg; Line( l14) = { p14, p15};
	l15 = newc; Line( l15) = { p15, p16}; l16 = newreg; Line( l16) = { p16, p13};
	//upxyline
	l17 = newc; Line( l17) = { p1, p9}; l18 = newreg; Line( l18) = { p2, p10};
	l19 = newc; Line( l19) = { p3, p11}; l20 = newreg; Line( l20) = { p4, p12};
	//lowxyline
	l21 = newc; Line( l21) = { p5, p13}; l22 = newreg; Line( l22) = { p6, p14};
	l23 = newc; Line( l23) = { p7, p15}; l24 = newreg; Line( l24) = { p8, p16};
	//outzline
	l25 = newc; Line( l25) = { p1, p5}; l26 = newreg; Line( l26) = { p2, p6};
	l27 = newc; Line( l27) = { p3, p7}; l28 = newreg; Line( l28) = { p4, p8};
	//inzline
	l29 = newc; Line( l29) = { p9, p13}; l30 = newreg; Line( l30) = { p10, p14};
	l31 = newc; Line( l31) = { p11, p15}; l32 = newreg; Line( l32) = { p12, p16};

	//phyline[t] = newreg;
	//Physical Line( phyline[t]) = {l1,l2,l3,l4,l5,l6,l7,l8,l9,l10,l11,l12,l13,l14,l15,l16,l17,l18,l19,l20,l21,l22,l23,l24};


	//outsurface
	lineloop[(t-1)*16] = newreg;
	Line Loop( lineloop[(t-1)*16]) = {l1,l26,-l5,-l25};
	lineloop[(t-1)*16+1] = newreg;
	Line Loop( lineloop[(t-1)*16+1]) = {l2,l27,-l6,-l26};
	lineloop[(t-1)*16+2] = newreg;
	Line Loop( lineloop[(t-1)*16+2]) = {l3,l28,-l7,-l27};
	lineloop[(t-1)*16+3] = newreg;
	Line Loop( lineloop[(t-1)*16+3]) = {l4,l25,-l8,-l28};
	//insurface
	lineloop[(t-1)*16+4] = newreg;
	Line Loop( lineloop[(t-1)*16+4]) = {l9,l30,-l13,-l29};
	lineloop[(t-1)*16+5] = newreg;
	Line Loop( lineloop[(t-1)*16+5]) = {l10,l31,-l14,-l30};
	lineloop[(t-1)*16+6] = newreg;
	Line Loop( lineloop[(t-1)*16+6]) = {l11,l32,-l15,-l31};
	lineloop[(t-1)*16+7] = newreg;
	Line Loop( lineloop[(t-1)*16+7]) = {l12,l29,-l16,-l32};
	//upsurface
	lineloop[(t-1)*16+8] = newreg;
	Line Loop( lineloop[(t-1)*16+8]) = {l1,l18,-l9,-l17};
	lineloop[(t-1)*16+9] = newreg;
	Line Loop( lineloop[(t-1)*16+9]) = {l2,l19,-l10,-l18};
	lineloop[(t-1)*16+10] = newreg;
	Line Loop( lineloop[(t-1)*16+10]) = {l3,l20,-l11,-l19};
	lineloop[(t-1)*16+11] = newreg;
	Line Loop( lineloop[(t-1)*16+11]) = {l4,l17,-l12,-l20};
	//lowsurface
	lineloop[(t-1)*16+12] = newreg;
	Line Loop( lineloop[(t-1)*16+12]) = {l5,l22,-l13,-l21};
	lineloop[(t-1)*16+13] = newreg;
	Line Loop( lineloop[(t-1)*16+13]) = {l6,l23,-l14,-l22};
	lineloop[(t-1)*16+14] = newreg;
	Line Loop( lineloop[(t-1)*16+14]) = {l7,l24,-l15,-l23};
        lineloop[(t-1)*16+15] = newreg;
	Line Loop( lineloop[(t-1)*16+15]) = {l8,l21,-l16,-l24};
 
 
	plasur[(t-1)*16] = newreg;
	Plane Surface( plasur[(t-1)*16]) = { lineloop[(t-1)*16]};
	plasur[(t-1)*16+1] = newreg;
	Plane Surface( plasur[(t-1)*16+1]) = { lineloop[(t-1)*16+1]};
	plasur[(t-1)*16+2] = newreg;
	Plane Surface( plasur[(t-1)*16+2]) = { lineloop[(t-1)*16+2]};
	plasur[(t-1)*16+3] = newreg;
	Plane Surface( plasur[(t-1)*16+3]) = { lineloop[(t-1)*16+3]};
	plasur[(t-1)*16+4] = newreg;
	Plane Surface( plasur[(t-1)*16+4]) = { lineloop[(t-1)*16+4]};
	plasur[(t-1)*16+5] = newreg;
	Plane Surface( plasur[(t-1)*16+5]) = { lineloop[(t-1)*16+5]};
	plasur[(t-1)*16+6] = newreg;
	Plane Surface( plasur[(t-1)*16+6]) = { lineloop[(t-1)*16+6]};
	plasur[(t-1)*16+7] = newreg;
	Plane Surface( plasur[(t-1)*16+7]) = { lineloop[(t-1)*16+7]};
	plasur[(t-1)*16+8] = newreg;
	Plane Surface( plasur[(t-1)*16+8]) = { lineloop[(t-1)*16+8]};
	plasur[(t-1)*16+9] = newreg;
	Plane Surface( plasur[(t-1)*16+9]) = { lineloop[(t-1)*16+9]};
	plasur[(t-1)*16+10] = newreg;
	Plane Surface( plasur[(t-1)*16+10]) = { lineloop[(t-1)*16+10]};
	plasur[(t-1)*16+11] = newreg;
	Plane Surface( plasur[(t-1)*16+11]) = { lineloop[(t-1)*16+11]};
	plasur[(t-1)*16+12] = newreg;
	Plane Surface( plasur[(t-1)*16+12]) = { lineloop[(t-1)*16+12]};
	plasur[(t-1)*16+13] = newreg;
	Plane Surface( plasur[(t-1)*16+13]) = { lineloop[(t-1)*16+13]};
	plasur[(t-1)*16+14] = newreg;
	Plane Surface( plasur[(t-1)*16+14]) = { lineloop[(t-1)*16+14]};
	plasur[(t-1)*16+15] = newreg;
	Plane Surface( plasur[(t-1)*16+15]) = { lineloop[(t-1)*16+15]};

	physur[t-1] = newreg;
	Physical Surface(physur[t-1]) = {plasur[(t-1)*16],plasur[(t-1)*16+1],plasur[(t-1)*16+2],plasur[(t-1)*16+3],plasur[(t-1)*16+4],plasur[(t-1)*16+5],plasur[(t-1)*16+6],plasur[(t-1)*16+7],plasur[(t-1)*16+8],plasur[(t-1)*16+9],plasur[(t-1)*16+10],plasur[(t-1)*16+11],plasur[(t-1)*16+12],plasur[(t-1)*16+13],plasur[(t-1)*16+14],plasur[(t-1)*16+15]};

	surloop[t+1] = newreg;
	Surface Loop( surloop[t+1]) = {plasur[(t-1)*16],plasur[(t-1)*16+1],plasur[(t-1)*16+2],plasur[(t-1)*16+3],plasur[(t-1)*16+4],plasur[(t-1)*16+5],plasur[(t-1)*16+6],plasur[(t-1)*16+7],plasur[(t-1)*16+8],plasur[(t-1)*16+9],plasur[(t-1)*16+10],plasur[(t-1)*16+11],plasur[(t-1)*16+12],plasur[(t-1)*16+13],plasur[(t-1)*16+14],plasur[(t-1)*16+15]};

	//wirevolume
	vol[t+3] = newreg;
	Volume(vol[t+3]) = {surloop[t+1]};
	phyvol[t] = t+4;
	Physical Volume(phyvol[t]) = {vol[t+3]};

Return

For t In {1:9}
  
	wz = 0.2 + t;
	Call CWire;

EndFor



//Gas
vol[0] = newreg;
Volume(vol[0]) = {2 ,surloop[]};
Physical Volume(1) = {vol[0]};

//Vessel
Physical Volume(2) = {vol[1]};

//GEM
Physical Volume(3) = {vol[2]};

//Mesh
Physical Volume(4) = {vol[3]};





