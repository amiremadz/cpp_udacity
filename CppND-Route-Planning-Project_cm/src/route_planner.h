#ifndef ROUTE_PLANNER_H
#define ROUTE_PLANNER_H

#include <iostream>
#include <vector>
#include <string>
#include "route_model.h"


class RoutePlanner {
  public:
    RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y);
    // Add public variables or methods declarations here.
    float GetDistance() const {return distance;}
    void AStarSearch();
    float ComputeSum(RouteModel::Node *node);
    RouteModel::Node *lower_sum_node;
    RouteModel::Node *swap_node;
    RouteModel::Node *lowest_node_pointer; 
    RouteModel::Node *current_parent;
    RouteModel::Node *next_parent;
    

    // The following methods have been made public so we can test them individually.
    void AddNeighbors(RouteModel::Node *current_node);
    float CalculateHValue(RouteModel::Node const *node);
    std::vector<RouteModel::Node> ConstructFinalPath(RouteModel::Node *current_node);
    RouteModel::Node *NextNode();

  private:
    // Add private variables or methods declarations here.
    std::vector<RouteModel::Node*> open_list;
    RouteModel::Node *start_node;
    RouteModel::Node *end_node;
    RouteModel::Node *next_node;
    



    float distance = 0.0f;
    RouteModel &m_Model;
};

#endif