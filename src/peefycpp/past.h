
#ifndef __P_AST_H__
#define __P_AST_H__

// peefy 抽象语法树AST库

#include "util.h"

#include <vector>

using namespace std;

BEGIN_PEEFY_NAMESPACE

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
        return;
    }
};

END_PEEFY_NAMESPACE

#endif
