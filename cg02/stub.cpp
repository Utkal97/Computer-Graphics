//
//		          Programming Assignment #1
//
//					Daljit Singh Dhillon
//
//
/***************************************************************************/
/* Include needed files */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/***************************************************************************/
// Forward declarations
void drawPixel(int x, int y);

// Main tasks for 4050
void drawCircle(int centerX, int centerY, int pointOnCricleX, int pointOnCricleY);
void drawParabola(int vertexX, int vertexY, int pointOnParabolaX, int pointOnParabolaY);
void drawCubicBezier(int* ptX, int* ptY);
/***************************************************************************/
//Main tasks for 6050
void drawArc(int ptX1, int ptY1, int ptX2, int ptY2, int ptX3, int ptY3);
void drawEllipse(int centerX, int centerY, int ptX1, int ptY1, int ptX2, int ptY2); //Bonus for 4050
void drawPoly(int ptX1, int ptY1, int ptX2, int ptY2);
void drawQuinticBezier(int* ptX, int* ptY);
/***************************************************************************/
//Few Bonus tasks
void drawCardinalSpline(int* ptX, int* ptY, int controlPointCount);
void drawCubicBSpline(int* ptX, int* ptY, int controlPointCount); //Not for 4050
void drawMidpointParabola(int vertexX, int vertexY, int pointOnParabolaX, int pointOnParabolaY);
/***************************************************************************/



// Main tasks for 4050
/***************************************************************************/
void drawCircle(int centerX, int centerY, int pointOnCricleX, int pointOnCricleY)
{
	drawPixel(centerX, centerY);
	drawPixel(pointOnCricleX, pointOnCricleY);
	//replace above two lines with your code
}

// Draw Parabola y-squared equals 'a' times x
// vertex is the tip of the parabola
void drawParabola(int vertexX, int vertexY, int pointOnParabolaX, int pointOnParabolaY)
{
	drawPixel(vertexX, vertexY);
	drawPixel(pointOnParabolaX, pointOnParabolaY);
	//replace above two lines with your code
}

void drawCubicBezier(int* ptX, int* ptY) {

	drawPixel(ptX[0], ptY[0]);
	//replace above line with your code
}

// Main tasks for 6050
/***************************************************************************/

struct Point {
	float X, Y;
};

struct Point findCenterWithPerpendicularBisectors(struct Point P1, struct Point P2, struct Point P3) {

	struct Point C;
	C.X = 0;
	C.Y = 0;

	float midPtX12 = (P1.X + P2.X) / 2, midPtY12 = (P1.Y + P2.Y) / 2,	//Mid Point of 1st chord: pt1-pt2
		slope12 = (P1.X!=P2.X) ? (P2.Y - P1.Y) / (P2.X - P1.X) : 0;						//Slope of 1st chord
	
	float midPtX23 = (P2.X + P3.X) / 2, midPtY23 = (P2.Y + P3.Y) / 2,	//Mid Point of 2nd chord: pt2-pt3
 		slope23 = (P2.X!=P3.X) ? (P3.Y - P2.Y) / (P3.X - P2.X) : 0;						//Slope of 2nd chord

	float a1 = (P1.X != P2.X) ? 1/slope12 : 0, 
		  b1 = 1, 
		  c1 = (P1.X != P2.X) ? (-1 * (midPtY12 + (midPtX12/slope12))) : (-1 * midPtY12),
		  a2 = (P2.X != P3.X) ? 1/slope23 : 0, 
		  b2 = 1,
		  c2 = (P2.X != P3.X) ? (-1 * (midPtY23 + (midPtX23/slope23))) : (-1 * midPtY23);

	if((a1*b2 - a2*b1)==0) {
		printf("Finding Circle center is impossible\n");
		return C;
	}

	// printf("Line equation 1: %fx + %fy + %f = 0\n",a1,b1,c1);
	// printf("Line equation 2: %fx + %fy + %f = 0\n",a2,b2,c2);

	C.X = (((b1 * c2) - (b2 * c1)) / ((a1 * b2) - (a2 * b1)));
	C.Y = (((c1 * a2) - (c2 * a1)) / ((a1 * b2) - (a2 * b1)));

	return C;
}

struct Point findCenterWithSubstitution(struct Point P1, struct Point P2, struct Point P3) {
 

    float sx13 = pow(P1.X, 2) - pow(P3.X, 2);
    float sx21 = pow(P2.X, 2) - pow(P1.X, 2);
 
    float sy13 = pow(P1.Y, 2) - pow(P3.Y, 2);
    float sy21 = pow(P2.Y, 2) - pow(P1.Y, 2);
 
    float f = ((sx13) * (P1.X - P2.X)
             + (sy13) * (P1.X - P2.X)
             + (sx21) * (P1.X - P3.X)
             + (sy21) * (P1.X - P3.X))
            / (2 * ((P3.Y - P1.Y) * (P1.X - P2.X) - (P2.Y - P1.Y) * (P1.X -P3.X)));

    float g = ((sx13) * (P1.Y - P2.Y)
             + (sy13) * (P1.Y - P2.Y)
             + (sx21) * (P1.Y - P3.Y)
             + (sy21) * (P1.Y - P3.Y))
            / (2 * ((P3.X - P1.X) * (P1.Y - P2.Y) - (P2.X - P1.X) * (P1.Y - P3.Y)));
 
    // int c = -pow(P1.X, 2) - pow(P1.Y, 2) - 2 * g * P1.X - 2 * f * P1.Y;
 
    // eqn of circle be x^2 + y^2 + 2*g*x + 2*f*y + c = 0
    // where centre is (h = -g, k = -f) and radius r
    // as r^2 = h^2 + k^2 - c
	struct Point C;
    C.X = -g;
    C.Y = -f;
	return C; 
}

/*
	Checks whether given point "currentPt" lies on the arc from pt1 to pt2, where testPt is a point on arc
*/
bool pointLiesOnArc(struct Point pt1, struct Point pt2, struct Point comparePt, struct Point currentPt) {
	//If X1, X2 are same, slope will be infinite, here we need to check X cordinates
	if(pt1.X == pt2.X) {
		return ((comparePt.X - pt1.X) * (currentPt.X - pt1.X)) >= 0;
	}

	//Equation of line passing through points pt1, pt2 is given by
	//y = (slope)*x + (y2 - (slope*x2))
	float slope = (pt2.Y - pt1.Y) / (pt2.X - pt1.X);	//If X1==X2, slope value is infinity
	float yIntercept = pt2.Y - (slope*pt2.X);

	//If the same line is written as ax + by + c = 0, then
	//a = -1*slope13, b = 1, c= -1*yIntercept
	float a = -1*slope, b = 1, c = -1*yIntercept;

	//A point on the circle lies on the arc if it lies on the same side as that of any other point on arc
	//We have a third point (ptX2, ptY2) for testing
	float comparePointWithLineEquation = a*comparePt.X + b*comparePt.Y + c,
		currentPointWithLineEquation = a*currentPt.X + b*currentPt.Y + c;

	if(comparePointWithLineEquation == 0) {
		printf("Cannot draw circle, since the third point is lying on the chord\n");
		return false;
	} else if(comparePointWithLineEquation * currentPointWithLineEquation > 0) {	//If both are on same side
		return true;
	} else {
		return false;
	}
}

void drawArc(int ptX1, int ptY1, int ptX2, int ptY2, int ptX3, int ptY3) {

	struct Point P1, P2, P3;
	P1.X = ptX1;
	P1.Y = ptY1;
	P2.X = ptX2;
	P2.Y = ptY2;
	P3.X = ptX3;
	P3.Y = ptY3;
	
	struct Point C = findCenterWithSubstitution( P1, P2, P3);
	// printf("Center of circle: (%f, %f)\n", C.X, C.Y);
	// drawPixel(C.X, C.Y);
	
	struct Point currentPt;

	float radius = (sqrt( pow( (P1.X - C.X), 2 ) + pow( (P1.Y - C.Y), 2 ) ));

	int X = 0, Y = (int)radius;

	currentPt.X = (int)(C.X + X);
	currentPt.Y = (int)(C.Y + Y);
	if(pointLiesOnArc(P1, P3, P2, currentPt)) {
		drawPixel(currentPt.X, currentPt.Y);
	}

	float decisionParameter	= 1 - radius;

	while(X <= Y) {
		
		X += 1;

		if(decisionParameter < 0) {
			decisionParameter += 2*(X) + 1;
		} else {
			Y -= 1;
			decisionParameter += 2*(X) + 1 - 2*(Y);
		}

		currentPt.X = (int)(C.X + X);
		currentPt.Y = (int)(C.Y + Y);
		if(pointLiesOnArc(P1, P3, P2, currentPt)) {
			drawPixel(currentPt.X, currentPt.Y);
		}

		currentPt.X = (int)(C.X - X);
		currentPt.Y = (int)(C.Y + Y);
		if(pointLiesOnArc(P1, P3, P2, currentPt)) {
			drawPixel(currentPt.X, currentPt.Y);
		}

		currentPt.X = (int)(C.X - Y);
		currentPt.Y = (int)(C.Y + X);
		if(pointLiesOnArc(P1, P3, P2, currentPt)) {
			drawPixel(currentPt.X, currentPt.Y);
		}

		currentPt.X = (int)(C.X - Y);
		currentPt.Y = (int)(C.Y - X);
		if(pointLiesOnArc(P1, P3, P2, currentPt)) {
			drawPixel(currentPt.X, currentPt.Y);
		}

		currentPt.X = (int)(C.X - X);
		currentPt.Y = (int)(C.Y - Y);
		if(pointLiesOnArc(P1, P3, P2, currentPt)) {
			drawPixel(currentPt.X, currentPt.Y);
		}

		currentPt.X = (int)(C.X + X);
		currentPt.Y = (int)(C.Y - Y);
		if(pointLiesOnArc(P1, P3, P2, currentPt)) {
			drawPixel(currentPt.X, currentPt.Y);
		}

		currentPt.X = (int)(C.X + Y);
		currentPt.Y = (int)(C.Y - X);
		if(pointLiesOnArc(P1, P3, P2, currentPt)) {
			drawPixel(currentPt.X, currentPt.Y);
		}

		currentPt.X = (int)(C.X + Y);
		currentPt.Y = (int)(C.Y + X);
		if(pointLiesOnArc(P1, P3, P2, currentPt)) {
			drawPixel(currentPt.X, currentPt.Y);
		}
	}

	return;
}

void drawEllipse(int centerX, int centerY, int ptX1, int ptY1, int ptX2, int ptY2)
{
	drawPixel(ptX1, ptY1);
	drawPixel(ptX2, ptY2);
	drawPixel(centerX, centerY);

	struct Point P1, P2, C;
	
	P1.X = ptX1;
	P1.Y = ptY1;
	P2.X = ptX2;
	P2.Y = ptY2;
	C.X = centerX;
	C.Y = centerY;
	// printf("Center: (%f, %f), Point1: (%f, %f), Point2: (%f, %f)\n", C.X, C.Y, P1.X, P1.Y, P2.X, P2.Y);

	long double rY = pow(P1.X-C.X,2)/(P1.X - P2.X);
		rY *= (P2.Y - P1.Y)/(P1.X + P2.X - 2*C.X);
		rY *= (P2.Y + P1.Y - 2*C.Y);

	if( (P2.X - P1.X==0) || (P1.X+P2.X-2*C.X==0) ) {
		printf("We cannot compute Ry (vertical radius) since ptX1 and ptX2 are very close.\n");
		return;
	}

	rY += pow(P1.Y-C.Y,2);
	rY = sqrt(abs(rY));

	double rX = (P1.X - P2.X)/(P2.Y - P1.Y);
	rX *= (P1.X + P2.X - 2*C.X)/(P2.Y + P1.Y - 2*C.Y);

	if( (P1.Y - P2.Y == 0) || (P2.Y+P1.Y-2*C.Y==0) ) {
		printf("We cannot compute Rx (horizontal radius) since ptY1 and ptY2 are very close.\n");
		return;
	}

	rX = sqrt(abs(rX));
	rX *=  rY;

	int Rx = (int)rX, Ry = (int)rY;

	//Region 1
	struct Point currentPt;
	int X = 0, Y = Ry;
	// printf("rX: %d , rY:%d\n", Rx, Ry);
	
	currentPt.X = C.X + X;
	currentPt.Y = C.Y + Y;
	drawPixel((int)currentPt.X, (int)currentPt.Y);

	float region1DecisionParameter = pow(Ry,2) - (pow(Rx,2)*Ry) + (pow(Rx,2)/4);

	while( (2*pow(Ry,2) * X) < (2*pow(Rx,2) * Y) ) {	//RECHECK THIS CONDITION

		X += 1;
		if(region1DecisionParameter < 0) {
			region1DecisionParameter += 2*pow(Ry,2)*X + pow(Ry,2);
		} else {
			Y -= 1;
			region1DecisionParameter += 2*pow(Ry,2)*X + pow(Ry,2) - 2*pow(Rx,2)*Y;
		}

		currentPt.X = C.X + X;
		currentPt.Y = C.Y + Y;
		drawPixel((int)currentPt.X, (int)currentPt.Y);
		
		currentPt.X = C.X - X;
		currentPt.Y = C.Y + Y;
		drawPixel((int)currentPt.X, (int)currentPt.Y);

		currentPt.X = C.X - X;
		currentPt.Y = C.Y - Y;
		drawPixel((int)currentPt.X, (int)currentPt.Y);

		currentPt.X = C.X + X;
		currentPt.Y = C.Y - Y;
		drawPixel((int)currentPt.X, (int)currentPt.Y);
	}

	//Region 2
	float region2DecisionParameter = pow(Ry,2)*pow(X + 0.5,2) 
									 + pow(Rx,2)*pow(Y-1,2)
									 - pow(Rx,2)*pow(Ry, 2);

	while(Y!=0) {	//RECHECK THE CONDITION

		Y -= 1;
		if(region2DecisionParameter > 0) {
			region2DecisionParameter += pow(Rx,2) - 2*pow(Rx,2)*Y;
 		} else {
			X += 1;
			region2DecisionParameter += pow(Rx,2) - 2*pow(Rx,2)*Y + 2*pow(Ry,2)*X;
		}

		currentPt.X = centerX + X;
		currentPt.Y = centerY + Y;
		drawPixel((int)currentPt.X, (int)currentPt.Y);

		currentPt.X = centerX - X;
		currentPt.Y = centerY + Y;
		drawPixel((int)currentPt.X, (int)currentPt.Y);

		currentPt.X = centerX - X;
		currentPt.Y = centerY - Y;
		drawPixel((int)currentPt.X, (int)currentPt.Y);

		currentPt.X = centerX + X;
		currentPt.Y = centerY - Y;
		drawPixel((int)currentPt.X, (int)currentPt.Y);
	}
	return;
}

void drawPoly(int ptX1, int ptY1, int ptX2, int ptY2)
{	
	drawPixel(ptX1, ptY1);
	drawPixel(ptX2, ptY2);
	//replace above two lines with your code
}

void drawQuinticBezier(int* ptX, int* ptY) {

	
	int n = 5;		// We have 6 control points and can plot a polynomial of 5th order
	
	float totalPixels=500;		// Let's plot 500 Bezier Points
	float C[6];		//Array containing Binomial Coefficients

	//Computing Binomial Coefficients
	for(int k=0; k<=n; k++) {
		C[k] = 1.0;
		for(int i=n;i>=k+1;i--) {
			C[k] *= (float)i;
		}
		for(int i=n-k;i>=2; i--) {
			C[k] /= (float)i;
		}
	}

	//Computing and plotting 500 Bezier Points
	for(int i=0; i<=totalPixels; i++) {
		float u = ((float)i) / totalPixels;
		// printf("\n\n\n i:%d, u:%f:-\n",i,u);

		float x = 0.0, y = 0.0, blendFunctionValue;
		for(int k=0; k<=n; k++) {
			blendFunctionValue = C[k] * pow(u,(float)k) * pow(1.0-u,(float)n-(float)k);
			x += (float)ptX[k] * blendFunctionValue;
			y += (float)ptY[k] * blendFunctionValue;
			// printf("k:%d  pow(u,k): %f  pow(1-u,n-k): %f   C[%d]:%f   blendFunctionValue: %f\n", k,pow(u,k), pow(1-u,n-k), k,C[k], blendFunctionValue);
		}
		drawPixel((int)x, (int)y);
	}
	return;
}

// BONUS TASKS
/***************************************************************************/
void drawMidpointParabola(int vertexX, int vertexY, int pointOnParabolaX, int pointOnParabolaY) 
{
	drawPixel(vertexX, vertexY);
	drawPixel(pointOnParabolaX, pointOnParabolaY);
	//replace above two lines with your code
}

void drawCardinalSpline(int* ptX, int* ptY, int controlPointCount) {

	drawPixel(ptX[0], ptY[0]);
	//replace above line with your code
}

void drawCubicBSpline(int* ptX, int* ptY, int controlPointCount) {

	drawPixel(ptX[0], ptY[0]);
	//replace above line with your code
}

