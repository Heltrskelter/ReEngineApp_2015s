#define _USE_MATH_DEFINES
#include "MyPrimitive.h"
#include <cmath>

MyPrimitive::MyPrimitive() { }
MyPrimitive::MyPrimitive(const MyPrimitive& other) { }
MyPrimitive& MyPrimitive::operator=(const MyPrimitive& other) { return *this; }
MyPrimitive::~MyPrimitive(void) { super::Release(); }
void MyPrimitive::CompileObject(vector3 a_v3Color)
{
	m_uVertexCount = static_cast<int> (m_lVertexPos.size());
	for (uint i = 0; i < m_uVertexCount; i++)
	{
		AddVertexColor(a_v3Color);
	}
	
	CompleteTriangleInfo(true);
	CompileOpenGL3X();

}
//C--D
//|\ |
//| \|
//A--B
//This will make the triang A->B->C and then the triang C->B->D
void MyPrimitive::AddQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight)
{
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);

	AddVertexPosition(a_vTopLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopRight);
}
void MyPrimitive::GeneratePlane(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = 0.5f * a_fSize;

	vector3 pointA(-fValue, -fValue, 0.0f); //0
	vector3 pointB(fValue, -fValue, 0.0f); //1
	vector3 pointC(fValue, fValue, 0.0f); //2
	vector3 pointD(-fValue, fValue, 0.0f); //3

	vector3 pointE(fValue, -fValue, -0.001f); //1
	vector3 pointF(-fValue, -fValue, -0.001f); //0
	vector3 pointG(fValue, fValue, -0.001f); //2
	vector3 pointH(-fValue, fValue, -0.001f); //3

											  //F
	AddQuad(pointA, pointB, pointD, pointC);
	//Double sided
	AddQuad(pointE, pointF, pointG, pointH);

	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCube(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = 0.5f * a_fSize;
	//3--2
	//|  |
	//0--1
	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	vector3 point4(-fValue, -fValue, -fValue); //4
	vector3 point5(fValue, -fValue, -fValue); //5
	vector3 point6(fValue, fValue, -fValue); //6
	vector3 point7(-fValue, fValue, -fValue); //7

											  //F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;


	Release();
	Init();

	//Your code starts here
	//AddVertexPosition(a_vBottomLeft);
	//AddVertexPosition(a_vBottomRight);
	//AddVertexPosition(a_vTopLeft);

	//setting up the points array
	vector3 vTop(0.0f, a_fHeight / 2, 0.0f);
	vector3 vBottom(0.0f, -a_fHeight / 2, 0.0f);
	vector3* points = new vector3[a_nSubdivisions];
	

	//for loop to create shape using trig
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		//getting the angle
		float theta = 360.0f / a_nSubdivisions * i;
		float angle = theta * M_PI / 180;
		float x = cos(angle)* a_fRadius;
		float z = sin(angle)*a_fRadius;
		points[i] = vector3(x, -a_fHeight / 2, z);
	}
	
	//add Verticies
	for (int j = 0; j < a_nSubdivisions; j++)
	{	//top of cone
		AddVertexPosition(vTop);
		AddVertexPosition(points[(j+1) % a_nSubdivisions]);
		AddVertexPosition(points[j]);
	
		//base of cone
		AddVertexPosition(vBottom);
		AddVertexPosition(points[j]);
		AddVertexPosition(points[(j + 1) % a_nSubdivisions]);
	}

	//deallocate
	delete points;
	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	//have top triangles     ___
	//have center squares   | | |
	//have bottom triangles |_|_|

	vector3 vTop(0.0f, a_fHeight / 2, 0.0f);
	vector3 vBottom(0.0f, -a_fHeight / 2, 0.0f);
	vector3* pointsTop = new vector3[a_nSubdivisions];
	vector3* pointsBottom = new vector3[a_nSubdivisions];
	//for loop to create top and bottom 'base'
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		//getting the angle
		float theta = 360.0f / a_nSubdivisions * i;
		float angle = theta * M_PI / 180;
		float x = cos(angle)* a_fRadius;
		float z = sin(angle)*a_fRadius;
		pointsTop[i] = vector3(x, a_fHeight / 2, z);
		pointsBottom[i] = vector3(x, -a_fHeight / 2, z);
	}
	
	//create forloop to Addvertex for top and bottom, then add quads using those points
	for (int j = 0; j < a_nSubdivisions; j++)
	{	//top of cylinder
		AddVertexPosition(vTop);
		AddVertexPosition(pointsTop[(j + 1) % a_nSubdivisions]);
		AddVertexPosition(pointsTop[j]);

		//quads of cylinder
		//AddQuad(point0, point1, point3, point2);
		AddQuad(pointsTop[j], pointsTop[(j + 1) % a_nSubdivisions], pointsBottom[j], pointsBottom[(j + 1) % a_nSubdivisions]);

		//base of cylinder
		AddVertexPosition(vBottom);
		AddVertexPosition(pointsBottom[j]);
		AddVertexPosition(pointsBottom[(j + 1) % a_nSubdivisions]);
	}

	//deallocate
	delete pointsTop;
	delete pointsBottom;

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	//Have top squares
	//have middle squares
	//have bottom squares

	//arrays, split up into outter and inner radius
	
	vector3* upperIn = new vector3[a_nSubdivisions];
	vector3* upperOut = new vector3[a_nSubdivisions];
	vector3* lowerIn = new vector3[a_nSubdivisions];
	vector3* lowerOut = new vector3[a_nSubdivisions];

	//fill arrays
	for (int i = 0; i < a_nSubdivisions ; i++) {
		//getting the angle
		float theta = 360.0f / a_nSubdivisions * i;
		float angle = theta * M_PI / 180;
		float xIn = cos(angle)* a_fInnerRadius;
		float zIn = sin(angle)*a_fInnerRadius;
		float xOut = cos(angle)* a_fOuterRadius;
		float zOut = sin(angle)*a_fOuterRadius;

		upperIn[i] = vector3(xIn, a_fHeight / 2, zIn);
		upperOut[i] = vector3(xOut, a_fHeight / 2, zOut);
		lowerIn[i] = vector3(xIn, -a_fHeight / 2, zIn);
		lowerOut[i] = vector3(xOut, -a_fHeight / 2, zOut);
	}

	//adding verticies
	for (int j = 0; j < a_nSubdivisions; j++) {
		//AddQuad(point0, point1, point3, point2);

		//upper quads
		AddQuad(upperOut[j], upperIn[j], upperOut[(j + 1) % a_nSubdivisions], upperIn[(j + 1) % a_nSubdivisions]);
		//middle quad Inner
		AddQuad(upperIn[(j + 1) % a_nSubdivisions], upperIn[j], lowerIn[(j + 1) % a_nSubdivisions], lowerIn[j]);
		//middle quad outer
		AddQuad(upperOut[j], upperOut[(j + 1) % a_nSubdivisions], lowerOut[j], lowerOut[(j + 1) % a_nSubdivisions]);
		//lower quads
		AddQuad(lowerOut[(j + 1) % a_nSubdivisions], lowerIn[(j + 1) % a_nSubdivisions], lowerOut[j], lowerIn[j]);
	}

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionsA, int a_nSubdivisionsB, vector3 a_v3Color)
{
	if (a_fOuterRadius <= a_fInnerRadius + 0.1f)
		return;

	if (a_nSubdivisionsA < 3)
		a_nSubdivisionsA = 3;
	if (a_nSubdivisionsA > 25)
		a_nSubdivisionsA = 25;

	if (a_nSubdivisionsB < 3)
		a_nSubdivisionsB = 3;
	if (a_nSubdivisionsB > 25)
		a_nSubdivisionsB = 25;

	Release();
	Init();

	//Your code starts here
	float fValue = 0.5f;
	//3--2
	//|  |
	//0--1
	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	AddQuad(point0, point1, point3, point2);

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color)
{
	//Sets minimum and maximum of subdivisions
	if (a_nSubdivisions < 1)
	{
		GenerateCube(a_fRadius * 2, a_v3Color);
		return;
	}
	if (a_nSubdivisions > 6)
		a_nSubdivisions = 6;

	Release();
	Init();

	//Your code starts here
	//points top and bottom 
	vector3 vCTop = vector3(0.0f, a_fRadius / 2, 0.0f);
	vector3 vCBottom = vector3(0.0f, -a_fRadius / 2, 0.0f);
	float subLength = a_fRadius / a_nSubdivisions;
	//array for cone on top and bottom
	vector3* coneTop = new vector3[10];
	vector3* coneBottom = new vector3[10];
	//array for quad center
	vector3* quadCenter = new vector3[10];

	//add points + verticies to top and bottom
	for (int p = 0; p < 10; p++) {
		//getting the angle
		float theta = 360.0f / 10 * p;
		float angle = theta * M_PI / 180;
		float x = cos(angle)* a_fRadius;
		float z = sin(angle)*a_fRadius;
		coneTop[p] = vector3(x, subLength, z);
		coneBottom[p] = vector3(x, subLength * a_nSubdivisions, z);

		AddVertexPosition(vCTop);
		AddVertexPosition(coneTop[(p + 1) % a_nSubdivisions]);
		AddVertexPosition(coneTop[p]);

		AddVertexPosition(vCBottom);
		AddVertexPosition(coneBottom[(p + 1) % a_nSubdivisions]);
		AddVertexPosition(coneBottom[p]);
	}
	
	//add points + verticies to center
	for (int i = 0; i < a_nSubdivisions; i++) {
		for (int j = 0; j < 10; j++) {
		
		}

	}
	
	//Your code ends here
	CompileObject(a_v3Color);
}