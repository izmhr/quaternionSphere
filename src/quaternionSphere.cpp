#include "quaternionSphere.h"

QuaternionSphere::QuaternionSphere(){
	radius = 100.0;
	division = 4;
	flagRadiusRandom = false;
	flagColorize = false;
}

QuaternionSphere::QuaternionSphere(float radius, int division) {
	this->radius = radius;
	this->division = division;
		flagRadiusRandom = false;
	flagColorize = false;
}

QuaternionSphere::~QuaternionSphere(){

}

void QuaternionSphere::init(){
	
	resetDivisionQue = false;

	faceNum = 8 * division * division;
	vertexNum = faceNum * 3;
	vectors = new ofVec3f[ vertexNum ];
	radiuses = new float[ faceNum ];
	radiusesFactor = new float[faceNum];
	colors = new ofColor[faceNum]; 
	for( int i=0; i<faceNum; i++){
		radiusesFactor[i] = ofRandom(0, 100.0);
		colors[i] = ofColor(ofRandom(255), ofRandom(125,255), ofRandom(100,255));
		radiuses[i] = 100.0;
	}
	makePolygon();
}

void QuaternionSphere::finalize() {
	delete [] vectors; vectors = NULL;
	delete [] radiuses; radiuses = NULL;
	delete [] radiusesFactor; radiusesFactor = NULL;
	delete [] colors; colors = NULL;
}

void QuaternionSphere::update() {

	if( resetDivisionQue ) resetDivision( divisionQue );
	// noise for radiuses
	if( flagRadiusRandom ){
		for( int i=0; i<faceNum; i++){
			radiusesFactor[i] += 0.005;
			radiuses[i] =  100 + 50.0 * ofNoise(radiusesFactor[i]);
		}
	}

}

void QuaternionSphere::draw() {
	ofSetColor(255,255,255);
	ofNoFill();
	for( int i=0; i<vertexNum/3; i++) {
		if(flagColorize) ofSetColor(colors[i]);
		ofBeginShape();
		for( int j=0; j<3; j++ ){
			ofVertex(vectors[i*3 + j].x * radiuses[i], vectors[i*3 + j].y * radiuses[i], vectors[i*3 + j].z * radiuses[i]);
		}
		ofVertex(vectors[i*3].x * radiuses[i], vectors[i*3].y * radiuses[i], vectors[i*3].z * radiuses[i]);
		ofEndShape();
	}
}

void QuaternionSphere::queResetDivision(int d = 1) {
	resetDivisionQue = true;
	divisionQue = d;
}

void QuaternionSphere::toggleRadiusNoise() {
	flagRadiusRandom = !flagRadiusRandom;
}

void QuaternionSphere::toggleColorize() {
	flagColorize = !flagColorize;
}

/*
* private method
*/

void QuaternionSphere::makePolygon() {
	int n = division;

	ofQuaternion init_vectors[24];
	init_vectors[0]		= ofQuaternion( 1, 0, 0, 0 );
	init_vectors[1]		= ofQuaternion( 0, 1, 0, 0 );
	init_vectors[2]		= ofQuaternion( 0, 0, 1, 0 );
	init_vectors[3]		= ofQuaternion( 0, 1, 0, 0 );
	init_vectors[4]		= ofQuaternion(-1, 0, 0, 0 );
	init_vectors[5]		= ofQuaternion( 0, 0, 1, 0 );
	init_vectors[6]		= ofQuaternion(-1, 0, 0, 0 );
	init_vectors[7]		= ofQuaternion( 0,-1, 0, 0 );
	init_vectors[8]		= ofQuaternion( 0, 0, 1, 0 );
	init_vectors[9]		= ofQuaternion( 0,-1, 0, 0 );
	init_vectors[10]	= ofQuaternion( 1, 0, 0, 0 );
	init_vectors[11]	= ofQuaternion( 0, 0, 1, 0 );
	init_vectors[12]	= ofQuaternion( 0, 1, 0, 0 );
	init_vectors[13]	= ofQuaternion( 1, 0, 0, 0 );
	init_vectors[14]	= ofQuaternion( 0, 0,-1, 0 );
	init_vectors[15]	= ofQuaternion(-1, 0, 0, 0 );
	init_vectors[16]	= ofQuaternion( 0, 1, 0, 0 );
	init_vectors[17]	= ofQuaternion( 0, 0,-1, 0 );
	init_vectors[18]	= ofQuaternion( 0,-1, 0, 0 );
	init_vectors[19]	= ofQuaternion(-1, 0, 0, 0 );
	init_vectors[20]	= ofQuaternion( 0, 0,-1, 0 );
	init_vectors[21]	= ofQuaternion( 1, 0, 0, 0 );
	init_vectors[22]	= ofQuaternion( 0,-1, 0, 0 );
	init_vectors[23]	= ofQuaternion( 0, 0,-1, 0 );

	//n /= 4;	//every edge should be divided into n edges
	int j = 0;	//index on vectors[]

	for(int i=0; i<24; i+=3){
		/*
		*                   c _________d
		*    ^ /\           /\        /
		*   / /  \         /  \      /
		*  p /    \       /    \    /
		*   /      \     /      \  /
		*  /________\   /________\/
		*     q->       a         b
		*/
		for(int p=0; p<n; p++){	//edge index 1
			ofQuaternion edge_p1;	//edge p left
			ofQuaternion edge_p2;	//edge p right
			ofQuaternion edge_p3;	//edge p+1 left
			ofQuaternion edge_p4;	//edge p+1 right
			edge_p1.slerp((float)p/n, init_vectors[i], init_vectors[i+2]);
			edge_p2.slerp((float)p/n, init_vectors[i+1], init_vectors[i+2]);
			edge_p3.slerp((float)(p+1)/n, init_vectors[i], init_vectors[i+2]);
			edge_p4.slerp((float)(p+1)/n, init_vectors[i+1], init_vectors[i+2]);

			for(int q=0; q<(n-p); q++){	//edge index 2
				ofQuaternion a;
				ofQuaternion b;
				ofQuaternion c;
				ofQuaternion d;
				a.slerp((float)q/(n-p), edge_p1, edge_p2);
				b.slerp((float)(q+1)/(n-p), edge_p1, edge_p2);
				if (edge_p3 == edge_p4){
					c = edge_p3;
					d = edge_p3;
				}else{
					c.slerp((float)q/(n-p-1), edge_p3, edge_p4);
					d.slerp((float)(q+1)/(n-p-1), edge_p3, edge_p4);
				}
				vectors[j++] = ofVec3f(a.x(), a.y(), a.z());
				vectors[j++] = ofVec3f(b.x(), b.y(), b.z());
				vectors[j++] = ofVec3f(c.x(), c.y(), c.z());
				if (q < n-p-1){
					vectors[j++] = ofVec3f(c.x(), c.y(), c.z());
					vectors[j++] = ofVec3f(b.x(), b.y(), b.z());
					vectors[j++] = ofVec3f(d.x(), d.y(), d.z());
				}
			}
		}
	}
}

void QuaternionSphere::resetDivision(int d){
	division = d;
	finalize();
	init();
}