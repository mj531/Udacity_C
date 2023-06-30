#include "graphedge.h"
#include "graphnode.h"

GraphNode::GraphNode(int id)
{
    _id = id;
}

GraphNode::~GraphNode()
{
    //// STUDENT CODE
    ////
    // already deleted in chatlogi.cpp ChatLogic::~ChatLogic()
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

// void GraphNode::AddEdgeToChildNode(GraphEdge *edge)
// {
//     _childEdges.push_back(edge);
//     // _childEdges.emplace_back(edge);
// }

//TASK3
void GraphNode::AddEdgeToChildNode(std::unique_ptr<GraphEdge> edge)
{
    //_childEdges is a vector of std::unique_ptr, shouldn't use get() which returns raw ptr
    _childEdges.push_back(std::move(edge));
}

//// STUDENT CODE
////
//TASK3 remove *
void GraphNode::MoveChatbotHere(ChatBot chatbot)
{
    _chatBot = std::move(chatbot);
    _chatBot->SetCurrentNode(this);
}

void GraphNode::MoveChatbotToNewNode(GraphNode newNode)
{
    newNode->MoveChatbotHere(std::move(_chatBot));
    _chatBot = nullptr; // invalidate pointer at source
}
////
//// EOF STUDENT CODE

GraphEdge *GraphNode::GetChildEdgeAtIndex(int index)
{
    //// STUDENT CODE
    ////
    //TASK3
    return _childEdges[index].get();

    ////
    //// EOF STUDENT CODE
}