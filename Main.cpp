#include "Main.h"
#include "JackieEngineLayer/MathSupport.h"
#include "JackieEngineLayer/RasterizingSupport.h"

#include <algorithm>
using std::min;
using std::max;

#include <cmath>

void Setup (CS_FrameBuffer& fb, CS_Keyboard& kb, CS_Mouse& mouse, i32 deltaTime) {
	;
}

float a = 320.0f;
float b = 320.0f;
float r = 100.0f;

float lineYForControl = 520.0f;
float lineY = 520.0f;
float disLineCir = 50.0f;

void Update(CS_FrameBuffer& fb, CS_Keyboard& kb, CS_Mouse& mouse, i32 deltaTime) {

	if (kb.IsKeyPressed('W')) {
		lineYForControl -= 0.1f;
	}
	else if (kb.IsKeyPressed('S')) {
		lineYForControl += 0.1f;
	}

	lineY = (int)lineYForControl;

	for (int y = 0; y < fb.height; y++) {

		if (y == lineY) {
			for (int x = 0; x < fb.width; x++) {
				fb.PutPixel(x, y, 255, 255, 255);
			}
		}

		for (int x = 0; x < fb.width; x++) {

			float x_a = x - a;
			float y_b = y - b;

			float d = x_a * x_a + y_b * y_b;
			float rsq = r * r;
			float determiner = abs(d - rsq);

			if ( determiner < 100.0f ) {
				// Inside the circle
				fb.PutPixel(x, y, 255, 255, 255);

				float newDeterminer = abs(y - lineY);

				if (
					newDeterminer < disLineCir + 1.0f &&
					newDeterminer > disLineCir - 1.0f
				) {

					int yStart = min(y, (int)lineY);
					int yEnd   = max(y, (int)lineY);

					for (int yPrime = yStart; yPrime < yEnd; yPrime++) {
						fb.PutPixel(x, yPrime, 255, 0, 0);
					}
				}
			}
		}
	}
}
