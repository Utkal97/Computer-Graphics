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

struct point {
	int X, Y;
}

struct point findCenter(int x1, int y1, int x2, int y2, int x3, int y3) {

	struct point C;
	float midPtX12 = (x1 + x2) / 2, midPtY12 = (y1 + y2) / 2,	//Mid point of 1st chord: pt1-pt2
		slope12 = (x1!=x2) ? (y2 - y1) / (x2 - x1) : 0;						//Slope of 1st chord
	
	float midPtX23 = (x2 + x3) / 2, midPtY23 = (y2 + y3) / 2,	//Mid point of 2nd chord: pt2-pt3
 		slope23 = (x2!=x3) ? (y3 - y2) / (x3 - x2) : 0;						//Slope of 2nd chord

	float a1 = (x1 != x2) ? (1/slope12) : 0, 
		  b1 = 1, 
		  c1 = (x1 != x2) ? (-1 * (midPtY12 + (midPtX12/slope12))) : (-1 * midPtY12),
		  a2 = (x2 != x3) ? (1/slope23) : 0, 
		  b2 = 1,
		  c2 = (x2 != x3) ? (-1 * (midPtY23 + (midPtX23/slope23))) : (-1 * midPtY23);

	if((a1*b2 - a2*b1)==0) {
		printf("Circle drawing is impossible\n");
		return;
	}

	C.X = (int)(((b1 * c2) - (b2 * c1)) / ((a1 * b2) - (a2 * b1)));
	C.Y = (int)(((c1 * a2) - (c2 * a1)) / ((a1 * b2) - (a2 * b1)));

	return C;
}

/*
	Checks whether given point "currentPt" lies on the arc from pt1 to pt2, where testPt is a point on arc
*/
boolean pointLiesOnArc(struct pt1, struct pt2, struct comparePt, struct currentPt) {
	
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
		printf("Cannot draw circle, since the third point is lieing on the chord\n");
		return false;
	} else if(comparePointWithLineEquation * currentPointWithLineEquation > 0) {	//If both are on same side
		return true;
	} else {
		return false;
	}
}

void drawArc(int ptX1, int ptY1, int ptX2, int ptY2, int ptX3, int ptY3) {
	
	struct point C = findCenter( ptX1, ptY1, ptX2, ptY2, ptX3,  ptY3);
	printf("Center of circle: %d %d", C.X, C.Y);

	struct pt1; 
	struct pt2;
	struct testPt;
	struct currentPt;

	pt1.X = ptX1;
	pt1.Y = ptY1;
	pt2.X = ptX3;
	pt2.Y = ptY3;
	testPt.X = ptX2;
	testPt.Y = ptY2;

	int radius = (int)(sqrt( pow((pt1.X-C.X),2) + pow((pt1.Y - C.Y),2) ));
	
	currentPt.X = C.X + 0;
	currentPt.Y = C.Y + radius;

	if(pointLiesOnArc(pt1, pt2, testPt, currentPt)) {
		drawPixel(currentPt.X, currentPt.Y);
	}

	float decisionParameter	= (5/4) - radius;

	while(currentPt.X <= currentPt.Y) {
		
		currentPt.X += 1;
		
		if(decisionParameter < 0) {
			decisionParameter += 2*(currentPt.X) + 1;
		} else {
			currentPt.Y -= 1;
			decisionParameter += 2*(currentPt.X) + 1 - 2*(currentPt.Y);
		}

		if(pointLiesOnArc(pt1, pt2, testPt, currentPt)) {
			drawPixel(currentPt.X, currentPt.Y);
		}

		struct currentPt2;
		struct currentPt3;
		struct currentPt4;
		struct currentPt5;
		struct currentPt6;
		struct currentPt7;
		struct currentPt8;

		currentPt2.X = currentPt.Y;
		currentPt2.Y = currentPt.X;

		currentPt3.X = -1*currentPt.Y;
		currentPt3.Y = currentPt.X;

		currentPt4.X = -1*currentPt.X;
		currentPt4.Y = currentPt.Y;

		currentPt5.X = -1*currentPt.X;
		currentPt5.Y = -1*currentPt.Y;

		currentPt6.X = -1*currentPt.Y;
		currentPt6.Y = -1*currentPt.X;

		currentPt7.X = currentPt.Y;
		currentPt7.Y = -1*currentPt.X;

		currentPt8.X = currentPt.X;
		currentPt8.Y = -1*currentPt.y;


		if(pointLiesOnArc(pt1, pt2, testPt, currentPt2)) {
			drawPixel(currentPt2.X, currentPt2.Y);
		}
		if(pointLiesOnArc(pt1, pt2, testPt, currentPt3)) {
			drawPixel(currentPt3.X, currentPt3.Y);
		}
		if(pointLiesOnArc(pt1, pt2, testPt, currentPt4)) {
			drawPixel(currentPt4.X, currentPt4.Y);
		}
		if(pointLiesOnArc(pt1, pt2, testPt, currentPt5)) {
			drawPixel(currentPt5.X, currentPt5.Y);
		}
		if(pointLiesOnArc(pt1, pt2, testPt, currentPt6)) {
			drawPixel(currentPt6.X, currentPt6.Y);
		}
		if(pointLiesOnArc(pt1, pt2, testPt, currentPt7)) {
			drawPixel(currentPt7.X, currentPt7.Y);
		}
		if(pointLiesOnArc(pt1, pt2, testPt, currentPt8)) {
			drawPixel(currentPt8.X, currentPt8.Y);
		}
	}

	return;
}

void drawEllipse(int centerX, int centerY, int ptX1, int ptY1, int ptX2, int ptY2)
{
	drawPixel(ptX1, ptY1);
	drawPixel(ptX2, ptY2);
	drawPixel(centerX, centerY);
	//replace above three lines with your code
}

void drawPoly(int ptX1, int ptY1, int ptX2, int ptY2)
{	
	drawPixel(ptX1, ptY1);
	drawPixel(ptX2, ptY2);
	//replace above two lines with your code
}

void drawQuinticBezier(int* ptX, int* ptY) {

	drawPixel(ptX[0], ptY[0]);
	//replace above line with your code
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

