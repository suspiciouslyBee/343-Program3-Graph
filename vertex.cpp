#include "vertex.h"

#include <climits>
#include <functional>
#include <map>
#include <string>

#include "edge.h"

////////////////////////////////////////////////////////////////////////////////
// This is 80 characters - Keep all lines under 80 characters                 //
////////////////////////////////////////////////////////////////////////////////

/** Creates an unvisited vertex, gives it a label, and clears its
    adjacency list.
    NOTE: A vertex must have a unique label that cannot be changed. */
Vertex::Vertex(std::string label) {
  visited = false;
  vertexLabel = label;
}

//Vertex::Vertex(std::)

/** @return  The label of this vertex. */
std::string Vertex::getLabel() const { return vertexLabel; }

/** Marks this vertex as visited. */
void Vertex::visit() { visited = true; }

/** Marks this vertex as not visited. */
void Vertex::unvisit() { visited = false; }

/** Returns the visited status of this vertex.
 @return  True if the vertex has been visited, otherwise
    returns false/ */
bool Vertex::isVisited() const { return visited; }

/** Adds an edge between this vertex and the given vertex.
    Cannot have multiple connections to the same endVertex
    Cannot connect back to itself
 @return  True if the connection is successful. */
bool Vertex::connect(const std::string& endVertex, const int edgeWeight) {

  if (endVertex == vertexLabel) {
    return false;
  }

  Edge hopper(endVertex, edgeWeight);

  //emplace() only allows one entry per key
  //Get state via returned pair's bool
  return adjacencyList.emplace(endVertex, hopper).second;
}

/** Removes the edge between this vertex and the given one.
@return  True if the removal is successful. */
bool Vertex::disconnect(const std::string& endVertex) {
  // I could use at() and catch the exception,
  //  but that feels too jank and unclear.
  // same complexity anyhow

  return adjacencyList.erase(endVertex) > 0;
}

/** Gets the weight of the edge between this vertex and the given vertex.
 @return  The edge weight. This value is zero for an unweighted graph and
    is negative if the .edge does not exist */
int Vertex::getEdgeWeight(const std::string& endVertex) const {
  // finds the vert, test if not found

  // using auto because listing the whole template will be unreadable
  // this is an stl iterator
  auto it = adjacencyList.find(endVertex);

  if (it == adjacencyList.end()) {
    return -1;
  }

  return it->second.getWeight();
}

/** Calculates how many neighbors this vertex has.
 @return  The number of the vertex's neighbors. */
int Vertex::getNumberOfNeighbors() const {
  // going to assume that a vertex can be a neighbor to itself

  return adjacencyList.size();
}

/** Sets current neighbor to first in adjacency list. */
void Vertex::resetNeighbor() { currentNeighbor = adjacencyList.begin(); }

/** Gets this vertex's next neighbor in the adjacency list.
    Neighbors are automatically sorted alphabetically via map
    Returns the vertex label if there are no more neighbors
 @return  The label of the vertex's next neighbor. */
std::string Vertex::getNextNeighbor() { 
  if (currentNeighbor == adjacencyList.end()) {
    return vertexLabel;
  }
  

  return (currentNeighbor++)->first;
}

/** Sees whether this vertex is equal to another one.
    Two vertices are equal if they have the same label. */
bool Vertex::operator==(const Vertex& rightHandItem) const {
  return rightHandItem.vertexLabel == vertexLabel;
}

/** Sees whether this vertex is < another one.
    Compares vertexLabel. */
bool Vertex::operator<(const Vertex& rightHandItem) const {
  return vertexLabel < rightHandItem.vertexLabel;
}

