#pragma once
#include "species.hpp"
#include "../trained/neural_network.hpp"
#include "../utility/logger.hpp"
#include "species_manager.hpp"
#include "data.hpp"
#include "../body/supervised_learning.hpp"
#include "../trained/classifier.hpp"

#include <vector>
#include <memory>

namespace Hippocrates::Training {

class NeuralNetworkTrainer {
public:
	bool loggingEnabled = false;

private:
	SpeciesManager species;
	Utility::Logger logger;
	size_t generationsPassed = 0;

public:
	auto TrainUnsupervised(SpeciesManager::Bodies& bodies) -> Trained::NeuralNetwork;
	template <typename Classification, std::size_t ClassificationCount>
	auto TrainSupervised(const Data<Classification, ClassificationCount>& data, std::size_t trainingInstances) -> Trained::Classifier<Classification>;
	
	auto GetGenerationsPassed() const { return generationsPassed; }

	auto GetJSON() const -> std::string;


private:
	auto TrainGenerationAndLogUsingBodies(SpeciesManager::Bodies& bodies) -> void;
};

template <typename Classification, std::size_t ClassificationCount>
auto NeuralNetworkTrainer::TrainSupervised(const Data<Classification, ClassificationCount>& data, std::size_t trainingInstances) -> Trained::Classifier<Classification> {
	using supervised_body_t = Body::SupervisedLearning<Classification, ClassificationCount>;
	std::vector<supervised_body_t> bodies;
	bodies.reserve(trainingInstances);
	for (std::size_t i = 0; i < trainingInstances; ++i) {
		supervised_body_t body(data);
		bodies.push_back(std::move(body));
	}
	SpeciesManager::Bodies bodyRefs(bodies.begin(), bodies.end());
	auto champ = TrainUnsupervised(bodyRefs);
	return Trained::Classifier<Classification>(std::move(champ));
}

}