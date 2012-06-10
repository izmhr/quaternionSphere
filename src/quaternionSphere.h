#include "ofMain.h"
#include <iostream>

class QuaternionSphere{
public:
	QuaternionSphere();
	QuaternionSphere(float radius, int division);
	~QuaternionSphere();

	void init();
	void update();
	void draw();
	void finalize();

	void queResetDivision(int d);
	void toggleRadiusNoise();
	void toggleColorize();


private:
	int		division;	// division = 1 のとき、正8面体となる。正八面体の各面の各辺の分割数を表す。
	ofVec3f	*vectors;
	float	radius;
	int		vertexNum;
	int		faceNum;
	float	*radiuses;
	float	*radiusesFactor;
	ofColor	*colors;

	bool resetDivisionQue;
	int divisionQue;

	// flags for modes
	bool flagRadiusRandom;
	bool flagColorize;

	void	makePolygon();
	void	resetDivision(int d);
};