#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

class TrieNode
{
    friend class ACSearch;
    friend class WildcardSearch; 

    std::map<char, TrieNode*> children;
    TrieNode *parent;
    char toParent;
    bool bEnd;
    std::string _str;
    
    TrieNode(TrieNode* parent = nullptr, char toParent = 0):
        parent(parent), toParent(toParent), bEnd(0)
    {};

public:
    bool end() const
    {
        return bEnd;
    }

    const std::string& getString() const
    {
        return _str;
    }
};


class TrieNode;

class WildcardSearch
{
    // default aho-corasick part
    TrieNode *root;
    std::map<TrieNode*, TrieNode*> suffix;

    // wildcards addition
    // key - substring of pattern
    // value - vector of positions, where we can find this substring
    size_t pattern_size;
    std::map<std::string, std::vector<size_t>> subP_map;
    size_t subP_count;


    // encapasulated default aho-corasick funcitons
    void calcSuffixLink(TrieNode* node);
    void turnIntoMachine();
    void insert(const std::string& key);

public:
    WildcardSearch();

    bool empty() const;

    void setPattern(const std::string& key, char joker);    

    // returns empty vector, if trie is empty
    std::vector<TrieNode*> getAllNodes();    

    void print();

    std::vector<size_t> search(const std::string& text);
};


WildcardSearch::WildcardSearch():
    root(nullptr)
{}


void WildcardSearch::calcSuffixLink(TrieNode* node)
{

    // suffix link of root is root itself
    if(node == root)
    {
        suffix[node] = root;
        return;
    }

    // suffix links of root children are root
    if(node->parent == root)
    {
        suffix[node] =  root;
        return;
    }

    // for computate the suffix link
    // we need the suffix link of node parent
    TrieNode *pCurrBetterNode;
    try
    {
        pCurrBetterNode = suffix.at(node->parent);
    }
    catch (std::out_of_range)
    {
        // trying to calculate prefix, before parent
        throw std::out_of_range("can't take first parent suffix, "
                                "check <calcSuffixLink>, "
                                "it's actually broken");
    }

    // and the character, which that moves us to node
    char cParentChar = node->toParent;

    
    while(true)
    {
        // try to find the children of parent suffix
        // with the same key as to current node
        if(pCurrBetterNode->children.find(cParentChar) != pCurrBetterNode->children.end())
        {
            suffix[node] = pCurrBetterNode->children[cParentChar];
            break;
        }

        // otherwise jump through suffix links
        // until reach root
        if(pCurrBetterNode == root)
        {
            suffix[node] = root;
            break;
        }

        try
        {
            pCurrBetterNode = suffix.at(pCurrBetterNode);
        }
        catch(std::out_of_range)
        {
            // trying to calculate prefix of node, which doesn't
            // have full prefix path
            throw std::out_of_range("can't take next parent suffix, "
                                    "check <calcSuffixLink>, "
                                    "it's actually broken");
        }
    }
}


void WildcardSearch::turnIntoMachine()
{
    if(!root) return;

    // find suffix links using breadth first search
    // which needs queue
    std::queue<TrieNode*> q;

    q.push(root);
    while(!q.empty())
    {
        auto pCurrNode = q.front();
        q.pop();

        calcSuffixLink(pCurrNode);

        for(auto child: pCurrNode->children){
            q.push(child.second);
        }
    }
}


void WildcardSearch::insert(const std::string& key)
{
    if(empty())
        root = new TrieNode();

    auto pCrawl = root;
    for(auto c: key)
    {
        if(pCrawl->children.count(c) == 0)
        {
            pCrawl->children[c] = new TrieNode(pCrawl, c);
        }
        pCrawl = pCrawl->children[c];
    }
    pCrawl->bEnd = 1;
    pCrawl->_str = key;
}


bool WildcardSearch::empty() const
{
    return !root;
}


void WildcardSearch::setPattern(const std::string& key, char joker)
{
    subP_map.clear();
    subP_count = 0;
    pattern_size = key.size();

    std::string sCurrP; // current pattern

    for(auto it = key.begin(); it != key.end(); it++)
    {
        char c = *it;
        size_t index = it - key.begin();
        if(c != joker)
        {
            sCurrP.push_back(c);
            if(it == key.end()-1)
            {
                // save position of this substring
                size_t sub_index = index + 2;
                sub_index -= sCurrP.size();
                subP_map[sCurrP].push_back(sub_index);
                subP_count++;
            }
        }
        else
        {
            if(!sCurrP.empty())
            {
                // we are on the position beyond string 
                // therefore we don't need to add one
                size_t sub_index = index + 1;
                sub_index -= sCurrP.size();
                subP_map[sCurrP].push_back(sub_index);
                subP_count++;
                sCurrP.clear();
            }
        }
    }

    // put all substrings into aho-corasick machine
    for(auto& item: subP_map)
    {
        insert(item.first);
    }

    // add suffix links into trie
    turnIntoMachine();
}


std::vector<TrieNode*> WildcardSearch::getAllNodes()
{
    std::vector<TrieNode*> nodes;
    if(root == nullptr)
        return nodes;

    // find all graph nodes using breadth first search
    std::queue<TrieNode*> q;
    q.push(root);

    while(!q.empty())
    {
        auto pCurrNode = q.front();
        q.pop();
        nodes.push_back(pCurrNode);

        for(auto child: pCurrNode->children)
        {
            // it is a tree, there can't be cycles,
            // so, there is no need to mark nodes
            q.push(child.second);
        }
    }
    return nodes;
}


void WildcardSearch::print()
{
    auto nodes = getAllNodes();
    for(auto node: nodes){
        std::cout << node->parent << " " << node << " " 
                  << node->toParent << " " << suffix[node] << std::endl;
    }
}


std::vector<size_t> WildcardSearch::search(const std::string& text)
{
    std::vector<size_t> pattern_entries;
    if(!root) return pattern_entries;


    // subP_entries[i] - how many substrings of pattern
    // macthed on position i
    std::map<size_t, size_t> subP_entries;

    auto pCurrentState = root;
    for(auto it = text.begin(); it != text.end(); it++)
    {
        char c = *it;

        // calculate new state
        while(true)
        {
            // if state has child with edge 'c', go in
            if(pCurrentState->children.find(c) != pCurrentState->children.end())
            {
                try
                {
                    pCurrentState = pCurrentState->children.at(c);
                }
                catch(std::out_of_range)
                {
                    // find failed
                    throw std::out_of_range("Wierd thing in <search>, when trying go to the child");
                }
                break;
            }

            // otherwise we gonna go deeper to the root using suffix
            if(pCurrentState == root) break;

            try
            {
                pCurrentState = suffix.at(pCurrentState);
            }
            catch(std::out_of_range)
            {
                throw std::out_of_range("Can't access suffix link of vertex, "
                                        "check <search> function, "
                                        "it's actually broken");
            }
        }
        

        auto pSuffixCrawl = pCurrentState;
        // check all suffixes of current state             
        while(pSuffixCrawl != root)
        {
            // when match
            if(pSuffixCrawl->end())
            {
                size_t index = (it - text.begin()) + 1 - pSuffixCrawl->getString().size();
                index++;

                for(auto l: subP_map[pSuffixCrawl->getString()])
                {
                    if(l <= index)
                        subP_entries[index - l]++;
                }
            }

            try
            {
                pSuffixCrawl = suffix.at(pSuffixCrawl);
            }
            catch(std::out_of_range)
            {
                throw std::out_of_range("Can't access suffix link of vertex, "
                                        "check <search> function, "
                                        "it's actually broken");
            }
        }
    }

    for(auto p: subP_entries)
    {
        if(p.second == subP_count)
        {
            if(p.first + pattern_size <= text.size())
                pattern_entries.push_back(p.first);
        }
    }
    return pattern_entries;
}

int main()
{
    std::string text;
    std::getline(std::cin, text);
    std::string pattern;
    std::cin >> pattern;
    char joker;
    std::cin >> joker;


    WildcardSearch w;
    w.setPattern(pattern, joker);
    auto pos = w.search(text);

    for(auto p: pos){
        std::cout << p+1 << std::endl;
    }

    return 0;
}
