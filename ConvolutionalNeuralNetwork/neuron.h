#pragma once
#include "matrix.h"
#include <vector>

namespace Convolutional {

class Neuron {
public:
	auto ExtractFeature(Matrix::Position position, const Matrix& matrix) const -> Matrix;
	auto GetBias() const { return bias; }
	auto GetWeights() const { return weights; }

private:
	static auto sigmoid(Matrix::elementType n) -> double;
	double bias = 0;
	std::vector<double> weights;
	Matrix::Size receptiveField;
};

}