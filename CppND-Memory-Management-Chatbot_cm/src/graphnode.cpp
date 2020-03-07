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

    delete _chatBot; 

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

void GraphNode::AddEdgeToChildNode(GraphEdge *edge)     //(std::unique_ptr<GraphEdge> edge
{

    _childEdges.push_back(edge);
}

//// STUDENT CODE
////
void GraphNode::MoveChatbotHere(ChatBot *chatbot)
{
    std::cout << "MoveCBHere.get() " << chatbot << "\n";

    _chatBot = chatbot;                     //std::move(chatbot);
    _chatBot->SetCurrentNode(this);
}

void GraphNode::MoveChatbotToNewNode(GraphNode *newNode)
{

    std::cout << "ChatbotMoveNew: " << _chatBot << "\n";
    newNode->MoveChatbotHere(_chatBot);          //std::move(_chatBot)
    _chatBot = nullptr; // invalidate pointer at source
}
////
//// EOF STUDENT CODE

GraphEdge *GraphNode::GetChildEdgeAtIndex(int index)
{
    //// STUDENT CODE
    //// ?? what to do here? should i do something?

    return _childEdges[index];

    ////
    //// EOF STUDENT CODE
}