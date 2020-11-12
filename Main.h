#ifndef __CROSSBUFFER_H__
#define __CROSSBUFFER_H__
#include "CrossBuffer.h"
#endif

#ifndef __TEXTOUTPUT_H__
#define __TEXTOUTPUT_H__
#include "TextOutput.h"
#endif

#ifndef __INPUT_H__
#define __INPUT_H__
#include "Input.h"
#endif

#ifndef __JACKIE_ENGINE_H__
#define __JACKIE_ENGINE_H__
#include "JackieEngineLibraries/JackieEngine.h"
#endif

#ifndef __STDIO_H__
#define __STDIO_H__
#include <stdio.h>
#endif

#ifndef __FPS_H__
#define __FPS_H__
#include "FPS.h"
#endif


void OnCreate() {
	;
}

int clamp(int min, int input, int max) {
	if (input > min) {
		if (input < max) {
			return input;
		}
		else {
			return max;
		}
	}
	else {
		return min;
	}
}

int min3(int a, int b, int c) {
	int min = a;
	if (b < min) {
		min = b;
	}
	if (c < min) {
		min = c;
	}
	return min;
}

int max3(int a, int b, int c) {
	int max = a;
	if (b > max) {
		max = b;
	}
	if (c > max) {
		max = c;
	}
	return max;
}

void DrawVector4D(FrameBuffer fb, int width, int height, Vector4D* vec, int radius) {
	int CentralX = (int)vec->x;
	int CentralY = (int)vec->y;
	int StartX = clamp(0, CentralX - radius, width);
	int EndX   = clamp(0, CentralX + radius, width);
	int StartY = clamp(0, CentralY - radius, height);
	int EndY   = clamp(0, CentralY + radius, height);

	for (int y = StartY; y < EndY; y++) {
		for (int x = StartX; x < EndX; x++) {
			SetPixel(fb, x, y, CreateColor(255, 255, 255, 255));
		}
	}
}

Vector4D CreateVector4DFromPointToPoint(Vector4D* from, Vector4D* to) {
	Vector4D tmp = Vector4DMinusVector4D(to, from);
	tmp.w = 1;
	return tmp;
}

void DrawFlatMesh4D(FrameBuffer fb, int width, int height,
	Vector4D* v0, Vector4D* v1, Vector4D* v2
)
{
	Color color = CreateColor(255, 255, 255, 255);

	int StartX = min3(v0->x, v1->x, v2->x);
	int StartY = min3(v0->y, v1->y, v2->y);
	int EndX   = max3(v0->x, v1->x, v2->x);
	int EndY   = max3(v0->y, v1->y, v2->y);
	StartX     = clamp(0, StartX, width);
	StartY     = clamp(0, StartY, height);
	EndX       = clamp(0, EndX, width);
	EndY       = clamp(0, EndY, height);

	Vector4D v1v2 = CreateVector4DFromPointToPoint(v1, v2);
	Vector4D v0v1 = CreateVector4DFromPointToPoint(v0, v1);
	Vector4D v2v0 = CreateVector4DFromPointToPoint(v2, v0);

	Vector4D p;
	Vector4D v1p;
	Vector4D v0p;
	Vector4D v2p;

	Vector4D result1;
	Vector4D result2;
	Vector4D result3;

	for (int y = StartY; y < EndY; y++) {
		for (int x = StartX; x < EndX; x++) {
			p.x = x;
			p.y = y;
			p.z = 0;
			p.w = 1;

			v1p = CreateVector4DFromPointToPoint(v1, &p);
			v0p = CreateVector4DFromPointToPoint(v0, &p);
			v2p = CreateVector4DFromPointToPoint(v2, &p);

			result1 = Vector4DCrossVector4D(&v1v2, &v1p);
			result2 = Vector4DCrossVector4D(&v0v1, &v0p);
			result3 = Vector4DCrossVector4D(&v2v0, &v2p);

			if (result1.z > 0 && result2.z > 0 && result3.z > 0) {
				SetPixel(fb, x, y, color);
			}
			else if (result1.z < 0 && result2.z < 0 && result3.z < 0) {
				SetPixel(fb, x, y, color);
			}
		}
	}
}

Camera4D cam;
Vector4D vecs[8];

void Setup(FrameBuffer fb, int width, int height, int deltaTime, Keyboard keyboard, Mouse mouse) {
	
	
	/*
	** Camera
	*/

	cam = CreateCamera4D(
		0.0f, 0.0f, 4.0f, 0.0f, 0.0f, 0.0f,
		-0.1f, -1000.0f, 60.0f, width, height
	);
	CalcCamera4DMatrices(&cam);


	/*
	** Vectors
	*/

	vecs[0] = CreateVector4D(-1.0f, -1.0f,  1.0f, 1.0f);
	vecs[1] = CreateVector4D( 1.0f, -1.0f,  1.0f, 1.0f);
	vecs[2] = CreateVector4D( 1.0f,  1.0f,  1.0f, 1.0f);
	vecs[3] = CreateVector4D(-1.0f,  1.0f,  1.0f, 1.0f);
	vecs[4] = CreateVector4D(-1.0f, -1.0f, -1.0f, 1.0f);
	vecs[5] = CreateVector4D( 1.0f, -1.0f, -1.0f, 1.0f);
	vecs[6] = CreateVector4D( 1.0f,  1.0f, -1.0f, 1.0f);
	vecs[7] = CreateVector4D(-1.0f,  1.0f, -1.0f, 1.0f);
}


char* buffer;
char realbuffer[1000];
float deltaX = 0.0f, deltaY = 0.0f, deltaZ = 0.0f;
float sensitivity = 0.005f;

void Update(FrameBuffer fb, int width, int height, int deltaTime, Keyboard keyboard, Mouse mouse) {
	CalcFPS(fb, width, height, deltaTime);

	/*
	** Position Responder
	*/

	if (keyboard['W'] == TRUE) {
		cam.position.z -= sensitivity * deltaTime;
	}
	if (keyboard['S'] == TRUE) {
		cam.position.z += sensitivity * deltaTime;
	}

	if (keyboard['A'] == TRUE) {
		cam.position.x -= 0.5f * sensitivity * deltaTime;
	}
	if (keyboard['D'] == TRUE) {
		cam.position.x += 0.5f * sensitivity * deltaTime;
	}

	if (keyboard['E'] == TRUE) {
		cam.position.y -= 0.5f * sensitivity * deltaTime;
	}
	if (keyboard['Q'] == TRUE) {
		cam.position.y += 0.5f * sensitivity * deltaTime;
	}


	/*
	** Rotation Responder
	*/

	if (keyboard['I'] == TRUE) {
		cam.rotation.x -= 5.0f * sensitivity * deltaTime;
	}
	if (keyboard['K'] == TRUE) {
		cam.rotation.x += 5.0f * sensitivity * deltaTime;
	}

	if (keyboard['J'] == TRUE) {
		cam.rotation.y -= 5.0f * sensitivity * deltaTime;
	}
	if (keyboard['L'] == TRUE) {
		cam.rotation.y += 5.0f * sensitivity * deltaTime;
	}

	if (keyboard['U'] == TRUE) {
		cam.rotation.z -= 5.0f * sensitivity * deltaTime;
	}
	if (keyboard['O'] == TRUE) {
		cam.rotation.z += 5.0f * sensitivity * deltaTime;
	}


	/*
	** Refresh Camera Matrices
	*/

	RefreshCamera4DMatrices(&cam);


	/*
	** Do Projection
	*/

	for (int i = 0; i < 8; i++) {
		vecs[i] = Vector4DTimesMatrix4D(
			&(vecs[i]), &(cam.Mtransform)
		);
	}

	for (int i = 0; i < 8; i++) {
		Vector4DDevidedByW(&(vecs[i]));
	}


	/*
	** Do Y-Axis Reverse
	*/

	for (int i = 0; i < 8; i++) {
		vecs[i].y = height - vecs[i].y;
	}


	/*
	** Output Things
	*/

	sprintf_s(
		realbuffer, 1000,
		"n:%f\nf:%f\nt:%f\nb:%f\nl:%f\nr:%f\n",
		cam.n, cam.f, cam.t, cam.b, cam.l, cam.r
	);
	DrawShadowString(fb, width, height, 10, 42, realbuffer);

	buffer = OutputMatrix4D(&(cam.Mtransform));
	DrawShadowString(fb, width, height, 10, 314, buffer);
	free(buffer);

	for (int i = 0; i < 8; i++) {
		buffer = OutputVector4D(&(vecs[i]));
		DrawShadowString(fb, width, height, 10, 154 + i * 16, buffer);
		free(buffer);
	}

	for (int i = 0; i < 8; i++) {
		float tmp = (-1.0f * vecs[i].z) - 0.9f;
		DrawVector4D(fb, width, height, &(vecs[i]), (int)((0.1f - tmp) * 100.0f));
	}

	//for (int i = 0; i < 8; i++) {
		DrawFlatMesh4D(fb, width, height, &(vecs[0]), &(vecs[1]), &(vecs[3]));
	//}


	/*
	** Reset Vectors
	*/

	vecs[0] = CreateVector4D(-1.0f, -1.0f,  1.0f, 1.0f);
	vecs[1] = CreateVector4D( 1.0f, -1.0f,  1.0f, 1.0f);
	vecs[2] = CreateVector4D( 1.0f,  1.0f,  1.0f, 1.0f);
	vecs[3] = CreateVector4D(-1.0f,  1.0f,  1.0f, 1.0f);
	vecs[4] = CreateVector4D(-1.0f, -1.0f, -1.0f, 1.0f);
	vecs[5] = CreateVector4D( 1.0f, -1.0f, -1.0f, 1.0f);
	vecs[6] = CreateVector4D( 1.0f,  1.0f, -1.0f, 1.0f);
	vecs[7] = CreateVector4D(-1.0f,  1.0f, -1.0f, 1.0f);
}


void OnDestroy() {
	;
}
