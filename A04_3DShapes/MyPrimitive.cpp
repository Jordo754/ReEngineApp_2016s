#include "MyPrimitive.h"
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

void MyPrimitive::AddTri(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft)
{
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);
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
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;
	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	Release();
	Init();

	//Your code starts here
	float fHeight = 0.5f * a_fHeight;
	//3--2
	//|  |
	//0--1
	std::vector<vector3> point;
	float theta = 0;
	float steps = 2 * PI / static_cast<float>(a_nSubdivisions);

	//start for the base
	point.push_back(vector3(0.0f, 0.0f, -fHeight));

	//populate points for base
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		point.push_back(vector3(a_fRadius * cos(theta), a_fRadius * sin(theta), -fHeight));
		theta += steps;
	}

	//fill in base
	for (int i = 1; i < a_nSubdivisions; i++)
	{
		AddTri(point[0], point[i + 1], point[i]);
	}

	AddTri(point[0], point[1], point[a_nSubdivisions]);

	//point for the top
	point.push_back(vector3(0.0f, 0.0f, fHeight));

	//connect base to top
	for (int i = 1; i < a_nSubdivisions; i++)
	{
		AddTri(point[a_nSubdivisions + 1], point[i], point[i + 1]);
	}

	AddTri(point[a_nSubdivisions + 1], point[a_nSubdivisions], point[1]);

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;
	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	Release();
	Init();

	//Your code starts here
	float fHeight = 0.5f * a_fHeight;
	//3--2
	//|  |
	//0--1
	std::vector<vector3> point;
	std::vector<vector3> point2;
	float theta = 0;
	float steps = 2 * PI / static_cast<float>(a_nSubdivisions);

	//start for lower circle
	point.push_back(vector3(0.0f, 0.0f, -fHeight));

	//pop lower circle
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		point.push_back(vector3(a_fRadius * cos(theta), a_fRadius * sin(theta), -fHeight));
		theta += steps;
	}

	//make tris for lower circle
	for (int i = 1; i < a_nSubdivisions; i++)
	{
		AddTri(point[0], point[i + 1], point[i]);
	}

	//close the circle
	AddTri(point[0], point[1], point[a_nSubdivisions]);

	//repeat for upper circle (maybe make a function for DRY?) 
	point2.push_back(vector3(0.0f, 0.0f, fHeight));

	for (int i = 0; i < a_nSubdivisions; i++)
	{
		point2.push_back(vector3(a_fRadius * cos(theta), a_fRadius * sin(theta), fHeight));
		theta += steps;
	}

	for (int i = 1; i < a_nSubdivisions; i++)
	{
		AddTri(point2[0], point2[i], point2[i + 1]);
	}

	AddTri(point2[0], point2[a_nSubdivisions], point2[1]);

	//fill in the walls
	for (int i = 1; i < a_nSubdivisions; i++)
	{
		AddQuad(point[i], point[i + 1], point2[i], point2[i + 1]);
	}

	//close the wall
	AddQuad(point[a_nSubdivisions], point[1], point2[a_nSubdivisions], point2[1]);

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;
	if (a_fOuterRadius < 0.01f)
		a_fOuterRadius = 0.01f;
	if (a_fInnerRadius < 0.01f)
		a_fInnerRadius = 0.01f;
	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	Release();
	Init();

	//Your code starts here
	float fHeight = 0.5f * a_fHeight;
	int nPointsReference = a_nSubdivisions * 2 - 2;
	//1--3
	//|  |
	//0--2
	std::vector<vector3> point;
	std::vector<vector3> point2;
	float theta = 0;
	float steps = 2 * PI / static_cast<float>(a_nSubdivisions);

	//populate points for lower and upper loops
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		point.push_back(vector3(a_fOuterRadius * cos(theta), a_fOuterRadius * sin(theta), fHeight));
		point.push_back(vector3(a_fInnerRadius * cos(theta), a_fInnerRadius * sin(theta), fHeight));
		point2.push_back(vector3(a_fOuterRadius * cos(theta), a_fOuterRadius * sin(theta), -fHeight));
		point2.push_back(vector3(a_fInnerRadius * cos(theta), a_fInnerRadius * sin(theta), -fHeight));
		theta += steps;
	}

	//fill in loops and sides
	for (int i = 0; i < nPointsReference; i+=2)
	{
		AddQuad(point[i], point[i + 2], point[i + 1], point[i + 3]);
		AddQuad(point2[i], point2[i + 1], point2[i + 2], point2[i + 3]);
		AddQuad(point[i], point2[i], point[i + 2], point2[i + 2]);
		AddQuad(point[i + 3], point2[i + 3], point[i + 1], point2[i + 1]);
	}

	AddQuad(point[nPointsReference], point[0], point[nPointsReference + 1], point[1]);
	AddQuad(point2[nPointsReference + 1], point2[1], point2[nPointsReference], point2[0]);
	AddQuad(point[nPointsReference], point2[nPointsReference], point[0], point2[0]);
	AddQuad(point[1], point2[1], point[nPointsReference + 1], point2[nPointsReference + 1]);

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionsA, int a_nSubdivisionsB, vector3 a_v3Color)
{
	if (a_fInnerRadius < 0.01f)
		a_fInnerRadius = 0.01f;
	if (a_fOuterRadius < 0.01f)
		a_fOuterRadius = 0.01f;

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
	//3--2
	//|  |
	//0--1
	float fTubeRadius = a_fOuterRadius - a_fInnerRadius;
	float fRefRadius = fTubeRadius + a_fInnerRadius;

	//create reference points for loop subdivisions
	//std::vector<vector3> refPoint;
	std::vector<vector3> point;
	float theta = 0;
	float theta2 = 0;
	float steps = 2 * PI / static_cast<float>(a_nSubdivisionsA);
	float steps2 = 2 * PI / static_cast<float>(a_nSubdivisionsB);

	//populate points
	for (int i = 0; i < a_nSubdivisionsA; i++)
	{
		for (int j = 0; j < a_nSubdivisionsB; j++)
		{
			point.push_back(vector3(cos(theta) * (fRefRadius + fTubeRadius * cos(theta2)), sin(theta) * (fRefRadius + fTubeRadius * cos(theta2)), fTubeRadius * sin(theta2)));
			theta2 += steps2; //thank you to http://paulbourke.net/geometry/torus/ for math equation for torus
		}

		theta += steps;
	}

	//connect the rings
	for (int i = 0; i < a_nSubdivisionsA - 1; i++)
	{
		for (int j = 0; j < a_nSubdivisionsB - 1; j++)
		{
			AddQuad(point[(i * a_nSubdivisionsB) + j], point[((i + 1) * a_nSubdivisionsB) + j], point[(i * a_nSubdivisionsB) + j + 1], point[((i + 1) * a_nSubdivisionsB) + j + 1]);
		}

		//fill in gaps
		AddQuad(point[(i * a_nSubdivisionsB) + 5], point[((i + 1) * a_nSubdivisionsB) + 5], point[(i * a_nSubdivisionsB)], point[((i + 1) * a_nSubdivisionsB)]);
	}

	//fill in more gaps
	for (int i = 0; i < a_nSubdivisionsB - 1; i++)
	{
		AddQuad(point[((a_nSubdivisionsA - 1) * a_nSubdivisionsB) + i], point[i], point[((a_nSubdivisionsA - 1) * a_nSubdivisionsB) + i + 1], point[i + 1]);
	}

	AddQuad(point[((a_nSubdivisionsA - 1) * a_nSubdivisionsB) + 5], point[5], point[((a_nSubdivisionsA - 1) * a_nSubdivisionsB)], point[0]);

	/*
	for (int i = 0; i < a_nSubdivisionsA; i++)
	{
		refPoint.push_back(vector3(fRefRadius * cos(theta), 0, fRefRadius * sin(theta)));
		theta += steps;
	}

	for (int j = 0; j < refPoint.size(); j++)
	{
		theta2 = 0;
		for (int i = 0; i < a_nSubdivisionsB; i++)
		{
			point.push_back(vector3(refPoint[j].x, , ));
			theta2 += steps2;
		}
	}
	*/

	//debug

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
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	Release();
	Init();

	//Your code starts here
	int nPointsReference = (a_nSubdivisions - 1) * (a_nSubdivisions - 2) - 1;
	//3--2
	//|  |
	//0--1
	std::vector<vector3> point;
	std::vector<vector3> point2;
	float theta = 0;
	float theta2 = 0;
	float subDivRadius = 0;
	float steps = 2 * PI / static_cast<float>(a_nSubdivisions);
	float steps2 = 2 * PI / static_cast<float>(a_nSubdivisions * 2);
	theta2 = asin(-1) + steps2;


	//bottom point
	point.push_back(vector3(0, -a_fRadius, 0));

	for (int j = 1; j < a_nSubdivisions; j++)
	{
		//center point
		//point.push_back(vector3(0, a_fRadius * sin(theta2), 0));

		for (int i = 0; i < a_nSubdivisions; i++)
		{
			subDivRadius = (a_fRadius * cos(theta2));
			point.push_back(vector3(subDivRadius * cos(theta), a_fRadius * sin(theta2), subDivRadius * sin(theta)));
			theta += steps;
		}
		theta = 0;
		theta2 += steps2;
	}

	//top point
	point.push_back(vector3(0, a_fRadius, 0));

	//fill in the bottom
	for (int i = 1; i < a_nSubdivisions; i++)
	{
		AddTri(point[0], point[i], point[i + 1]);
	}

	//close the circle
	AddTri(point[0], point[a_nSubdivisions], point[1]);

	//fill in the sides
	for (int j = 0; j < a_nSubdivisions - 2; j++)
	{
		for (int i = 0; i < a_nSubdivisions - 1; i++)
		{
			AddQuad(point[i + 1 + (a_nSubdivisions * (j + 1))], point[i + 2 + (a_nSubdivisions * (j + 1))], point[i + 1 + (a_nSubdivisions * j)], point[i + 2 + (a_nSubdivisions * j)]);
		}

		AddQuad(point[((j + 1) * a_nSubdivisions) + a_nSubdivisions], point[1 + (a_nSubdivisions * (j + 1))], point[(j * a_nSubdivisions) + a_nSubdivisions], point[1 + (a_nSubdivisions * j)]);
	}

	nPointsReference += a_nSubdivisions;

	//fill in the top
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		AddTri(point[nPointsReference + a_nSubdivisions], point[nPointsReference + i + 1], point[nPointsReference + i]);
	}

	//close the circle
	AddTri(point[nPointsReference + a_nSubdivisions], point[nPointsReference], point[nPointsReference + a_nSubdivisions - 1]);

	//Your code ends here
	CompileObject(a_v3Color);
}