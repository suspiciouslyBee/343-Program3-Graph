#include <queue>
#include <climits>
#include <set>
#include <iostream>
#include <fstream>
#include <map>
#include <unordered_map>
#include <sstream>
#include <string>
#include <utility>

#include "graph.h"
#include "edge.h"

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
void Graph::readFile(std::string filename) {

  //open file, if cant then bail
  std::ifstream file(filename);

  if (file.fail()) {
    std::cerr << "ERROR: File not Found!" << std::endl;
    return;
  }

  int weight = 0;
  //assume file is properly formatted

  //std::stringstream parser;
  std::string start;
  std::string end;

  file >> weight;

  //TODO: this is basic, may need to account for random bullshit and unweighteds
  while (!file.eof()) {
    file >> start;
    file >> end;
    file >> weight;

    add(start, end, weight);
  }
}

/** depth-first traversal starting from startLabel
    call the function visit on each vertex label */
void Graph::depthFirstTraversal(std::string startLabel,
                                void visit(const std::string&)) 
{
  //this is a map iterator
  auto search = vertices.find(startLabel);
  if(search == vertices.end()) { return; }
  unvisitVertices();

  depthFirstTraversalHelper(search, visit);
}

/** breadth-first traversal starting from startLabel
    call the function visit on each vertex label */
void Graph::breadthFirstTraversal(std::string startLabel,
                                  void visit(const std::string&)) 
{
  //assume vertex
  auto node = vertices.find(startLabel);
  if(node == vertices.end()) { return; }

  unvisitVertices();
  std::queue<std::map<std::string, 
              Vertex, std::less<std::string>>::iterator> nodeQueue;
  nodeQueue.push(node);

  while(nodeQueue.size() > 0) {
    //Read neighbors into queue


    //pop the head node, use as basis
    node = nodeQueue.front();
    nodeQueue.pop();
    node->second.resetNeighbor();

    //visit() this node
    visit(node->second.getLabel());

    //read adj list into queue
    for(auto it = vertices.find(node->second.getNextNeighbor()); it != node; 
      it = vertices.find(node->second.getNextNeighbor()))
    {
      
      //only lets unvisited neighbors into the queue
      if(!it->second.isVisited()){
        it->second.visit();
        nodeQueue.push(it);
      }
    }
    //queue is updated, can now pop the next one.
  }


}

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
    std::map<std::string, std::string>& previous)
{

  //I'm going to ignore the premise try to do something different

  //Guards
  auto node = vertices.find(startLabel);
  if(node == vertices.end()) { return; }


  //TODO: consider if converting the adjList to a PQ based on int is more
  //efficient

  //setup for recursion
  //hash map pair for vert

  //Copy the vertex map

  //string id, then the key is a pair with vert in question
  //TODO: make this not use string

  //vertex id maps to a pair containing weight and a path

  //goal is to be able to access the graph data with this
  static std::unordered_map<std::string, std::pair<int, std::deque<Vertex*>>>
     pathWeightTable;

  std::pair<int, std::deque<Vertex*>> pathPair;

  //-2 for unassigned weight
  pathPair.first = -2;
  //copy the map into this new format
  for(auto it = vertices.begin(); it != vertices.begin(); it++) {
    pathWeightTable.emplace(it->first, pathPair);
  }
  //Table is set up
  unvisitVertices();

  //Begin the recursion
  dijkstraHelper(node, pathWeightTable);


  //construct pq of starting node
  //std::priority_queue<int, Edge, std::less<int>> nodePQ;

  //read pathweighttable to stdout

  
}

//recursion, expects static
void Graph::dijkstraHelper(
  std::map<std::string, Vertex, std::less<std::string>>::iterator vertex,
  std::unordered_map<std::string, std::pair<int, std::deque<Vertex*>>> &table) 
{

  //Base case: visited node
  if(vertex->second.isVisited()) { return; }
  vertex->second.visit();


  //TODO: this might break if vector doesnt like not having assign
  //make min  pq of paths for selected node
  std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> queue;
  
  //pop the map into the pq
 
  vertex->second.resetNeighbor();
  std::string endVertex = vertex->second.getNextNeighbor();
  std::string vertexName = vertex->second.getLabel(); //do once 

  
  //Wow this is sloppy
  //TODO: may need to handle invalid weights
  while(endVertex != vertexName) {
    queue.push(Edge(endVertex, vertex->second.getEdgeWeight(endVertex)));
    endVertex = vertex->second.getNextNeighbor();
  }

  

  //PQ is built: read the lowest, compare with path
  //go to table, save the weight of our current vert
  
  //bookmark the smallest vertex before clearing queue
  auto smallestVertex = vertices.find(queue.top().getEndVertex());
  int baseWeight = table.at(vertexName).first;
  int weightAdded = 0;
  int targetWeight = 0;
  int combinedWeight = 0;

  //TODO: might be able to do pointer manips here
  std::map<std::string, Vertex, std::less<std::string>>::iterator iterator;

  //TODO make this block better, meant to block childless nodes
  if(queue.size() < 1) { return; }

  while(queue.size() > 0) {
    iterator = vertices.find(queue.top().getEndVertex());
    
    //read weight of the node
    weightAdded = queue.top().getWeight();

    //readcurrent total weight from table
    targetWeight = table.at(queue.top().getEndVertex()).first;

    combinedWeight = baseWeight + weightAdded;

    //PLACEHOLDER: pop pq, iterate vert iterator

    //if the node has just been discovered or the combo is less than base
    if(targetWeight == -2 || combinedWeight < targetWeight) {
      //Copy basePath
      table.at(iterator->first).second = table.at(vertexName).second;
      
      //push mem address of the top of pq's vertex
      table.at(iterator->first).second.push_back(&(iterator->second));
      table.at(iterator->first).first = combinedWeight;
    }

    queue.pop();
  }

  
  dijkstraHelper(smallestVertex, table);
  
  return;
  
}

/** helper for depthFirstTraversal */
void Graph::depthFirstTraversalHelper(
  std::map<std::string, Vertex, std::less<std::string>>::iterator startVertex,
                                      void visit(const std::string&)) 
{
  startVertex->second.visit();
  startVertex->second.resetNeighbor();  //This may screw it up
  visit(startVertex->second.getLabel());

  //this feels jank
  //std::string node;
  //node = startVertex->second.getNextNeighbor();

  //janky... find once, work with this. dont spawn more strings than absolutely
  //neccisary
  auto test = vertices.find(startVertex->second.getNextNeighbor());
  
  while(test != startVertex) {
    //for now, assume list is valid
    if(!test->second.isVisited()) {
      depthFirstTraversalHelper(test, visit);
    }
    test = vertices.find(startVertex->second.getNextNeighbor());
  }

  return;
}

/** helper for breadthFirstTraversal */
void Graph::breadthFirstTraversalHelper(Vertex*startVertex,
                                        void visit(const std::string&)) {}

/** mark all verticies as unvisited */
void Graph::unvisitVertices() {}

/** find a vertex, if it does not exist return nullptr */
/*
Vertex* Graph::findVertex(const std::string& vertexLabel) {

  std::map<std::string, Vertex, std::less<std::string>>::iterator vertex = vertices.find(vertexLabel);

  if (vertex != vertices.end()) {
    
  }

  return result;
}
*/

/** find a vertex, if it does not exist create it and return it */
Vertex* Graph::findOrCreateVertex(const std::string& vertexLabel) { return nullptr; }
