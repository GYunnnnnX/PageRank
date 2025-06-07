#pragma once
#include <string>
#include <map>
#include <vector>

std::map<std::string, double> pagerank(const std::string& filename, double damping = 0.85, int max_iter = 100, double tol = 1e-6);
