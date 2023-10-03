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

struct center {
	int X, Y;
}

struct center findCenter(int x1, int y1, int x2, int y2, int x3, int y3) {

	struct center C;
	float midPtX12 = (x1 + x2) / 2, midPtY12 = (y1 + y2) / 2,	//Mid Point of 1st chord: pt1-pt2
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

	C.X = ((b1 * c2) - (b2 * c1)) / ((a1 * b2) - (a2 * b1));
	C.Y = ((c1 * a2) - (c2 * a1)) / ((a1 * b2) - (a2 * b1));

	return C;
}

void drawArc(int ptX1, int ptY1, int ptX2, int ptY2, int ptX3, int ptY3) {
	drawPixel(ptX1, ptY1);
	drawPixel(ptX2, ptY2);
	drawPixel(ptX3, ptY3);
	
	struct center C = findCenter( ptX1, ptY1, ptX2, ptY2, ptX3,  ptY3);
	printf("Center: %d %d", C.X, C.Y);
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

