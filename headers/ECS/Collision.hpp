#pragma once

#include "raylib.h"

inline bool IsEnter(Rectangle actual_body, Rectangle target_body) {
	bool isXcol = actual_body.x < target_body.x + target_body.width && actual_body.x + actual_body.width > target_body.x;
	bool isYcol = actual_body.y < target_body.y + target_body.height && actual_body.y + actual_body.height > target_body.y;

	return isXcol && isYcol;
}
