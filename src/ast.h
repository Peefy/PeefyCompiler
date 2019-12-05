
#ifndef __AST_H_
#define __AST_H_

#include <vector>

using namespace std;

class AstTreeNode
{
private:
    
public:
    AstTreeNode() = default;
    virtual ~AstTreeNode() = default;
};


class AstTree
{
private:
    
public:
    AstTree() = default;
    AstTree(AstTree& ohther) = default;
    AstTree& operator=(AstTree& ohther) = default;
    virtual ~AstTree() = default;
private:
    bool _isAbstract;
public:
    AstTreeNode* root;
    vector<AstTreeNode*> nodes;
    void inOrder() {
        
    }
};




#endif
