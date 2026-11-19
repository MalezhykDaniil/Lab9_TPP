#pragma once

class IPointsSystem {
public:
	virtual int pointsForPosition(int position) const = 0;
	virtual ~IPointsSystem() = default;
};