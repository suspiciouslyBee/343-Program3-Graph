#include <string>

#include "edge.h"

////////////////////////////////////////////////////////////////////////////////
// This is 80 characters - Keep all lines under 80 characters                 //
////////////////////////////////////////////////////////////////////////////////


Edge::Edge() {}

Edge::Edge(const Edge &rhs)
{
  endVertex = rhs.getEndVertex();
  edgeWeight = rhs.getWeight();
}

/** constructor with label and weight */
Edge::Edge(const std::string& end, int weight) { 
  endVertex = end;
  edgeWeight = weight;
}

bool Edge::operator>(const Edge &rhs) const
{
  return getWeight() > rhs.getWeight();
}

bool Edge::operator<(const Edge &rhs) const
{
  return getWeight() < rhs.getWeight();
}
/** return the vertex this edge connects to */
std::string Edge::getEndVertex() const { return endVertex; }

/** return the weight/cost of travlleing via this edge */
int Edge::getWeight() const { return edgeWeight; }


