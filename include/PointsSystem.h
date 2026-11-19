#pragma once

#include <array>

#include "IPointsSystem.h"

class PointsSystem : public IPointsSystem {
public:
	int pointsForPosition(int position) const override;

private:
	const std::array<int, 3> POINTS = { 25, 18, 15 };
};
