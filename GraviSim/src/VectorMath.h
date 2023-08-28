#pragma once
#include <SFML/Graphics.hpp>

class VectorMath
{
public:
	static float length(sf::Vector2f vec) {
		return sqrt(vec.x * vec.x + vec.y * vec.y);
	}

	static float dot(sf::Vector2f vec1, sf::Vector2f vec2) {
		return vec1.x * vec2.x + vec1.y * vec2.y;
	}

	static void normalize(sf::Vector2f& vec) {
		vec /= length(vec);
	}
};

