#include "../induco.h"
#include "display.h"
#include "evolve.h"
#include "genetic_core.h"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

namespace genetic {
int populationsize = 100, chromosomelength = 10, genoration = 0;
double mutationrate = 0.05;
std::string goalvalue = "";
std::vector<Chromosome> population;
}

double genetic::RunAlgorithm(std::string gova, int popsize, double mutate,
                             bool display) {
  induco::Timer(true);
  Clean();
  if (popsize != -1) {
    populationsize = popsize;
  }
  chromosomelength = gova.size();
  goalvalue = gova;
  if (mutate != -1) {
    mutationrate = mutate;
  }
  bool running = true;
  if (display == true) {
    display::DrawStr("[" + goalvalue + "]");
    std::cout << "\n";
  }
  evolve::GenorateBasePopulation();
  genoration = 0;
  while (running == true) {
    if (induco::Timer() >= 120 || genoration >= 1000000) {
      running = false;
    }
    evolve::CalculateFitness();
    evolve::SumFitness();
    evolve::Sort();
    evolve::CumulateFitness();
    if (display == true) {
      display::DrawStr(0);
    }
    if (population[0].str == goalvalue) {
      running = false;
      break;
    }
    evolve::Killoff();
    evolve::Reproduce();
    evolve::Mutate();
    genoration++;
  }
  if (display == true) {
    std::cout << "\n";
  }
  double elapsedtime = induco::Timer(false);
  if (population[0].str == goalvalue && display == true) {
    std::cout << "GENORATIONS: " << genoration << "\n";
    std::cout << "TIME: " << induco::DisplayTime(elapsedtime, true) << "\n";
    display::DrawStr(0);
  }
  return (elapsedtime);
}

double genetic::drand() { return (fabs((double)rand() / (RAND_MAX + 1))); }

void genetic::Clean() {

  population.clear();
  goalvalue = "";
  populationsize = 0;
  chromosomelength = 0;
  genoration = 0;
  mutationrate = 0;
  evolve::totalfitness = 0;
  evolve::totalbottemup = 0;
}
