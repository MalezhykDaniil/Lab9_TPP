#include"PointsSystem.h"

#include<stdexcept>

int PointsSystem::pointsForPosition(int position) const {
	if (position < 1) {
		throw std::invalid_argument("Position must be a positive integer");
	}
	
	if (position > 3) {
		return 0;
	}
	else {
		return POINTS[position - 1];
	}
}