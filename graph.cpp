#include <queue>
#include <climits>
#include <set>
#include <iostream>
#include <fstream>
#include <map>

#include "graph.h"

/**
 * A graph is made up of vertices and edges
 * A vertex can be connected to other vertices via weighted, directed edge
 */


////////////////////////////////////////////////////////////////////////////////
// This is 80 characters - Keep all lines under 80 characters                 //
////////////////////////////////////////////////////////////////////////////////


/** constructor, empty graph */
Graph::Graph() {
  numberOfEdges = 0;
  numberOfVertices = 0;
}

/** destructor, delete all vertices and edges
    only vertices stored in map
    no pointers to edges created by graph */
Graph::~Graph() {}

/** return number of vertices */
int Graph::getNumVertices() const { return numberOfVertices; }

/** return number of vertices */
int Graph::getNumEdges() const { return numberOfEdges; }

/** add a new edge between start and end vertex
    if the vertices do not exist, create them
    calls Vertex::connect
    a vertex cannot connect to itself
    or have multiple edges to another vertex */
bool Graph::add(std::string start, std::string end, int edgeWeight) {
  // I am assuming that the graph will be directed
  // So an undirected graph would need to essentially duplicate this but reverse
  // the "polarity"

  if (edgeWeight < 0 || start == end) {
    return false;
  }

  auto startVertex = vertices.find(start);
  auto endVertex = vertices.find(end);

  if (startVertex == vertices.end()) {
    startVertex = vertices.emplace(Vertex(start)).first;
  }

  if (endVertex == vertices.end()) {
    endVertex = vertices.emplace(Vertex(end)).first;
  }

  return startVertex->second.connect(end, edgeWeight);

}


/** return weight of the edge between start and end
    returns INT_MAX if not connected or vertices don't exist */
int Graph::getEdgeWeight(std::string start, std::string end) const {
  auto vertexStart = vertices.find(start);
  auto vertexEnd = vertices.find(end);

  if (vertexStart == vertices.end() || vertexEnd == vertices.end()) {
    return false;
  }

  int result = vertexStart->second.getEdgeWeight(end);

  return (result < 0) ? INT_MAX : result;
}

/** read edges from file
    the first line of the file is an integer, indicating number of edges
    each edge line is in the form of "string string int"
    fromVertex  toVertex    edgeWeight */
void Graph::readFile(std::string filename) {}

/** depth-first traversal starting from startLabel
    call the function visit on each vertex label */
void Graph::depthFirstTraversal(std::string startLabel,
                                void visit(const std::string&)) {}

/** breadth-first traversal starting from startLabel
    call the function visit on each vertex label */
void Graph::breadthFirstTraversal(std::string startLabel,
                                  void visit(const std::string&)) {}

/** find the lowest cost from startLabel to all vertices that can be reached
    using Djikstra's shortest-path algorithm
    record costs in the given map weight
    weight["F"] = 10 indicates the cost to get to "F" is 10
    record the shortest path to each vertex using given map previous
    previous["F"] = "C" indicates get to "F" via "C"

    cpplint gives warning to use pointer instead of a non-const map
    which I am ignoring for readability */
void Graph::djikstraCostToAllVertices(
    std::string startLabel,
    std::map<std::string, int>& weight,
    std::map<std::string, std::string>& previous) {}

/** helper for depthFirstTraversal */
void Graph::depthFirstTraversalHelper(Vertex* startVertex,
                                      void visit(const std::string&)) {}

/** helper for breadthFirstTraversal */
void Graph::breadthFirstTraversalHelper(Vertex*startVertex,
                                        void visit(const std::string&)) {}

/** mark all verticies as unvisited */
void Graph::unvisitVertices() {}

/** find a vertex, if it does not exist return nullptr */
Vertex* Graph::findVertex(const std::string& vertexLabel) const { return nullptr; }

/** find a vertex, if it does not exist create it and return it */
Vertex* Graph::findOrCreateVertex(const std::string& vertexLabel) { return nullptr; }
