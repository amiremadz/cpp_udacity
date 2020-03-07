#include "graphedge.h"
#include "graphnode.h"

#include <iostream>

GraphNode::GraphNode(int id)
{
    _id = id;
}

//std::unique_ptr<ChatBot> _chatBot(new ChatBot());

GraphNode::~GraphNode()
{
    //// STUDENT CODE
    ////

    //delete _chatBot; 

    ////
    //// EOF STUDENT CODE
}

void GraphNode::AddToken(std::string token)
{
    _answers.push_back(token);
}

void GraphNode::AddEdgeToParentNode(GraphEdge *edge)
{
    _parentEdges.push_back(edge);
}

void GraphNode::AddEdgeToChildNode(std::unique_ptr<GraphEdge> edge)     //(std::unique_ptr<GraphEdge> edge
{

    _childEdges.push_back(std::move(edge));
}

//// STUDENT CODE
////
void GraphNode::MoveChatbotHere(ChatBot chatbot)
{
    //std::cout << "MoveCBHere.get() " << chatbot << "\n";

    //Use move semantics from task 2 and not std::move() with unique_ptr

    _chatBot = std::move(chatbot);                     
    _chatBot.SetCurrentNode(this);
}

void GraphNode::MoveChatbotToNewNode(GraphNode *newNode)
{

    //Use move semantics from task 2 and not std::move() with unique pointer

    //std::cout << "ChatbotMoveNew: " << _chatBot << "\n";
    newNode->MoveChatbotHere(std::move(_chatBot));          //std::move(_chatBot)
    //_chatBot = nullptr; // invalidate pointer at source - not needed any more since we are moving chatbot around
}
////
//// EOF STUDENT CODE

GraphEdge *GraphNode::GetChildEdgeAtIndex(int index)
{
    //// STUDENT CODE
    //// added .get() to return address of unique pointer

    return _childEdges[index].get();

    ////
    //// EOF STUDENT CODE
}