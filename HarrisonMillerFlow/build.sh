#!/bin/bash
g++ -o flow Creature.cpp Population.cpp Point.cpp AdjMatrix.cpp Dijkstra.cpp Pair.cpp Fitness.cpp Checker.cpp ResolveOverlap.cpp Solver.cpp flow.cpp -pthread -std=c++11
