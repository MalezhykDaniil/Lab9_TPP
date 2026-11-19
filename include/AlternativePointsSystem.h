#pragma once

#include <array>

#include "IPointsSystem.h"

class AlternativePointsSystem : public IPointsSystem {
public:
	int pointsForPosition(int position) const override;

private:
	const std::array<int, 3> POINTS = { 30, 20, 10 };
};
