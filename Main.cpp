#include "Main.h"
#include "JackieEngineLayer/MathSupport.h"

const float dt = 1.0f / 60.0f;
static constexpr float dTheta = PI;
float offset_z = 2.0f;
float theta_x = 0.0f;
float theta_y = 0.0f;
float theta_z = 0.0f;
Cube cube(1.0f);
PubeScreenTransformer pst;

void Setup (CS_FrameBuffer& fb, CS_Keyboard& kb, CS_Mouse& mouse, i32 deltaTime) {
	pst.SetWidthHeight(fb.width, fb.height);
}

void Update(CS_FrameBuffer& fb, CS_Keyboard& kb, CS_Mouse& mouse, i32 deltaTime) {
	
	//// Keyboard Control

	//if (kb.IsKeyPressed('Q'))
	//{
	//	theta_x = theta_x + dTheta * dt;
	//}
	//if (kb.IsKeyPressed('W'))
	//{
	//	theta_y = theta_y + dTheta * dt;
	//}
	//if (kb.IsKeyPressed('E'))
	//{
	//	theta_z = theta_z + dTheta * dt;
	//}
	//if (kb.IsKeyPressed('A'))
	//{
	//	theta_x = theta_x - dTheta * dt;
	//}
	//if (kb.IsKeyPressed('S'))
	//{
	//	theta_y = theta_y - dTheta * dt;
	//}
	//if (kb.IsKeyPressed('D'))
	//{
	//	theta_z = theta_z - dTheta * dt;
	//}
	//if (kb.IsKeyPressed('R'))
	//{
	//	offset_z += 2.0f * dt;
	//}
	//if (kb.IsKeyPressed('F'))
	//{
	//	offset_z -= 2.0f * dt;
	//}

	//// 3D Transform

	//auto lines = cube.GetLines();

	//Mat3 rotation =
	//	Mat3::RotationX(theta_x) *
	//	Mat3::RotationY(theta_y) *
	//	Mat3::RotationZ(theta_z);

	//for (auto& v : lines.vertices) {
	//	v *= rotation;
	//	v += Vec3(0.0f, 0.0f, offset_z);
	//	pst.Transform(v);

	//	fb.PutPixel((int)v.x, (int)v.y, 255, 255, 255);
	//}

	Vertex v1;
	Vertex v2(Vec3(1.0f, 2.0f, 3.0f), Vec2(4.0f, 5.0f));

	Vertex v3(v2);
	Vertex v4;
	v4 = v2;

	int a = 0;
}
