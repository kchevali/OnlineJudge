using l = long long;
// #include <iostream>

#include <algorithm>

// Binary Search
namespace BinarySearch{
  // STL implementation
  // std::binary_search(nums, nums + n, x) -> bool
  // std::lower_bound(nums, nums + n, x) -> poler
  // std::upper_bound(nums, nums + n, x) -> poler

  l* lowerbound(l* a, l* b, l t) {
    while (a < b) {
      l* m = a + (b - a) / 2;
      if (t <= *m)
        b = m;
      else
        a = m + 1;
    }
    return a;
  }

  l* upperbound(l* a, l* b, l t) {
    while (a < b) {
      l* m = a + (b - a) / 2;
      if (t < *m)
        b = m;
      else
        a = m + 1;
    }
    return a;
  }
}

/*
OUTPUT:
NUMS:
1 2 3 3 3 5 5 7 8
0 1 2 3 4 5 6 7 8

x = 3
Contains: True
Lower index: 2 Value: 3
Upper index: 5 Value: 5

x = -1
Contains: False
Lower index: 0 Value: 1
Upper index: 0 Value: 1

x = 9
Contains: False
Lower index: 9 Value: 0
Upper index: 9 Value: 0

x = 4
Contains: False
Lower index: 5 Value: 5
Upper index: 5 Value: 5

x = 8
Contains: True
Lower index: 8 Value: 8
Upper index: 9 Value: 0
*/
// #include <iostream>
// l main() {
//     const l n = 9;

//     l nums[]{5, 3, 3, 2, 7, 5, 3, 8, 1};
//     std::sort(nums, nums + n);

//     l x = 5;

//     std::cout << "x = " << x << "\n";
//     std::cout << "Contains: " << (std::binary_search(nums, nums + n, x) ? "True" : "False") << "\n";

//     auto lower = std::lower_bound(nums, nums + n, x), upper = std::upper_bound(nums, nums + n, x);
//     l lowerIndex = lower - nums, upperIndex = upper - nums;
//     std::cout << "Lower index: " << lowerIndex << " Value: " << nums[lowerIndex] << " Sanity Check Index: " << *BinarySearch::lowerbound(nums, nums + n, x) << "\n";
//     std::cout << "Upper index: " << upperIndex << " Value: " << nums[upperIndex] << " Sanity Check Index: " << *BinarySearch::upperbound(nums, nums + n, x) << "\n\n";
// }

// Substring search

#include <string>

// Knuth–Morris–Pratt Substring search algorithm
// preprocess pattern O(m) - length of pattern
// matching O(n) - length of text
// space complexity O(m)
namespace KMPSubstringSearch {
  using StringIterator = std::string::iterator;

  // Fills lps[] for given pattern
  // lps length must be equal (or greater) to pattern.length 
  void preprocess(const StringIterator& patA, const StringIterator& patB, l* lps){
    // length of the previous longest prefix suffix
    l len = 0, m = patB - patA;
    lps[0] = 0; // lps[0] is always 0

    for (l i = 1; i < m;) {
      if (patA[i] == patA[len]) {
        len++;
        lps[i] = len;
        i++;
      } else {
        if (len != 0) {
          len = lps[len - 1];
        } else {
          lps[i] = 0;
          i++;
        }
      }
    }
  }
  
  // Prints occurrences of txt[] in pattern[]
  const StringIterator search(const StringIterator& strA, const StringIterator& strB, const StringIterator& patA, const StringIterator& patB, const l* lps){
    l n = strB - strA, m = patB - patA;
    if (m == 0) return strA;
    l i = 0, j = 0; // (text idx, pattern idx)

    while ((n - i) >= (m - j) && i < n && j < m) {
      // std::cout << "i: " << i << " j: " << j << "\n";
      if (patA[j] == strA[i]) {
          j++, i++;
      }

      if (j == m) {
        return strA + i - j; // remove this line to find all substrings
        j = lps[j - 1];
      }else if (i < n && patA[j] != strA[i]) {
        if (j != 0){
          j = lps[j - 1];
        }else{
          i = i + 1;
        }
      }
    }
    return strB; // substring not found
  }
}

#include <algorithm>

// Boyer-Moore Substring search algorithm
// preprocess pattern O(m + k) - length of pattern
// matching O(n) - length of text
// space complexity O(m)
namespace BoyerMooreSubstringSearch{
  const l MAX_CHAR = 'z';
  using StringIterator = std::string::iterator;

  // BAD CHARACTER RULE.
  // delta1 table: delta1[c] contains the distance between the last
  // character of pat and the rightmost occurrence of c in pat.
  //
  // If c does not occur in pat, then delta1[c] = patlen.
  // If c is at string[i] and c != pat[patlen-1], we can safely shift i
  //   over by delta1[c], which is the minimum distance needed to shift
  //   pat forward to get string[i] lined up with some character in pat.
  // c == pat[patlen-1] returning zero is only a concern for BMH, which
  //   does not have delta2. BMH makes the value patlen in such a case.
  //   We follow this choice instead of the original 0 because it skips
  //   more. (correctness?)
  //
  // This algorithm runs in alphabet_len+patlen time.
  void make_delta1(const StringIterator& patA, const StringIterator& patB, l *delta1) {
    l m = patB - patA;
    for (l i = 0; i < MAX_CHAR; i++) {
        delta1[i] = m;
    }
    for (l i = 0; i < m; i++) {
        delta1[patA[i]] = m-1 - i;
    }
  }

  // true if the suffix of word starting from word[pos] is a prefix
  // of word
  bool is_prefix(const StringIterator& patA, const StringIterator& patB, l pos) {
    for (l i = 0, n = patB - patA - pos; i < n; i++) {
        if (patA[i] != patA[pos+i]) {
            return false;
        }
    }
    return true;
  }

  // length of the longest suffix of word ending on word[pos].
  // suffix_length("dddbcabc", 8, 4) = 2
  l suffix_length(const StringIterator& patA, const StringIterator& patB, l pos) {
      l i = 0, n = patA - patB;
      for (i = 0; (patA[pos-i] == patA[n-1-i]) && (i <= pos); i++);
      return i;
  }

  // GOOD SUFFIX RULE.
  // delta2 table: given a mismatch at pat[pos], we want to align
  // with the next possible full match could be based on what we
  // know about pat[pos+1] to pat[patlen-1].
  //
  // In case 1:
  // pat[pos+1] to pat[patlen-1] does not occur elsewhere in pat,
  // the next plausible match starts at or after the mismatch.
  // If, within the substring pat[pos+1 .. patlen-1], lies a prefix
  // of pat, the next plausible match is here (if there are multiple
  // prefixes in the substring, pick the longest). Otherwise, the
  // next plausible match starts past the character aligned with
  // pat[patlen-1].
  //
  // In case 2:
  // pat[pos+1] to pat[patlen-1] does occur elsewhere in pat. The
  // mismatch tells us that we are not looking at the end of a match.
  // We may, however, be looking at the middle of a match.
  //
  // The first loop, which takes care of case 1, is analogous to
  // the KMP table, adapted for a 'backwards' scan order with the
  // additional restriction that the substrings it considers as
  // potential prefixes are all suffixes. In the worst case scenario
  // pat consists of the same letter repeated, so every suffix is
  // a prefix. This loop alone is not sufficient, however:
  // Suppose that pat is "ABYXCDBYX", and text is ".....ABYXCDEYX".
  // We will match X, Y, and find B != E. There is no prefix of pat
  // in the suffix "YX", so the first loop tells us to skip forward
  // by 9 characters.
  // Although superficially similar to the KMP table, the KMP table
  // relies on information about the beginning of the partial match
  // that the BM algorithm does not have.
  //
  // The second loop addresses case 2. Since suffix_length may not be
  // unique, we want to take the minimum value, which will tell us
  // how far away the closest potential match is.
  void make_delta2(const StringIterator& patA, const StringIterator& patB, l *delta2) {
      l last_prefix_index = 1, patlen = patB - patA;

      for (l p=patlen-1; p>=0; p--) {
          if (is_prefix(patA, patB, p+1)) {
              last_prefix_index = p+1;
          }
          delta2[p] = last_prefix_index + (patlen-1 - p);
      }

      for (l p=0; p < patlen-1; p++) {
          l slen = suffix_length(patA, patB, p);
          if (patA[p - slen] != patA[patlen-1 - slen]) {
              delta2[patlen-1 - slen] = patlen-1 - p + slen;
          }
      }
  }

  void preprocess(const StringIterator& patA, const StringIterator& patB, l *delta1, l* delta2){
    make_delta1(patA, patB, delta1);
    make_delta2(patA, patB, delta2);
  }

  // Returns pointer to first match.
  // See also glibc memmem() (non-BM) and std::boyer_moore_searcher (first-match).
  const StringIterator search(const StringIterator& a, const StringIterator& b, const StringIterator& patA, const StringIterator& patB, l* delta1, l* delta2) {
        l stringlen = b - a, patlen = patB - patA;
        if (patlen == 0) return a;

        l i = patlen - 1;        // str-idx
        while (i < stringlen) {
            l j = patlen - 1; // pat-idx
            while (j >= 0 && (a[i] == patA[j])) {
                --i;
                --j;
            }
            if (j < 0) {
                return a + i + 1;
            }

            l shift = std::max(delta1[a[i]], delta2[j]);
            i += shift;
        }
        return b;
    }
}

// A C program to implement Ukkonen's Suffix Tree Construction
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

namespace SuffixTree {
  const l MAX_CHAR = 'z';
  
  struct Node {
      Node *children[MAX_CHAR];
  
      //pointer to other node via suffix link
      Node *suffixLink;
  
      /*(start, end) interval specifies the edge, by which the
      node is connected to its parent node. Each edge will
      connect two nodes, one parent and one child, and
      (start, end) interval of a given edge will be stored
      in the child node. Lets say there are two nods A and B
      connected by an edge with indices (5, 8) then this
      indices (5, 8) will be stored in node B. */
      l start;
      l *end;
  
      /*for leaf nodes, it stores the index of suffix for
      the path from root to leaf*/
      l suffixIndex;
  };

  struct Tree {
    
    const std::string text; //Input string
    Node *root = NULL; //Pointer to root node
    
    /*lastNewNode will point to newly created internal node,
    waiting for it's suffix link to be set, which might get
    a new suffix link (other than root) in next extension of
    same phase. lastNewNode will be set to NULL when last
    newly created internal node (if there is any) got it's
    suffix link reset to new internal node created in next
    extension of same phase. */
    Node *lastNewNode = NULL;
    Node *activeNode = NULL;
    l count=0;
    
    /*activeEdge is represented as input string character
    index (not the character itself)*/
    l activeEdge = -1;
    l activeLength = 0;
    
    // remainingSuffixCount tells how many suffixes yet to
    // be added in tree
    l remainingSuffixCount = 0;
    l leafEnd = -1;
    l *rootEnd = NULL;
    l *splitEnd = NULL;
    l size = -1; //Length of input string

    Tree(const std::string& text): text(text), size(text.length()), rootEnd((l*) malloc(sizeof(l))) {
      *rootEnd = - 1;
  
      /*Root is a special node with start and end indices as -1,
      as it has no parent from where an edge comes to root*/
      root = newNode(-1, rootEnd);
  
      activeNode = root; //First activeNode will be root
      for (l i=0; i<size; i++)
          extendSuffixTree(i);
      l labelHeight = 0;
      setSuffixIndexByDFS(root, labelHeight);
  
      //Free the dynamically allocated memory
      freeSuffixTreeByPostOrder(root);
    }
    
    Node *newNode(l start, l *end){
        count++;
        Node *node =(Node*) malloc(sizeof(Node));
        for (l i = 0; i < MAX_CHAR; i++)
            node->children[i] = NULL;
    
        /*For root node, suffixLink will be set to NULL
        For internal nodes, suffixLink will be set to root
        by default in current extension and may change in
        next extension*/
        node->suffixLink = root;
        node->start = start;
        node->end = end;
    
        /*suffixIndex will be set to -1 by default and
        actual suffix index will be set later for leaves
        at the end of all phases*/
        node->suffixIndex = -1;
        return node;
    }
    
    l edgeLength(Node *n) {
        return *(n->end) - (n->start) + 1;
    }
    
    l walkDown(Node *currNode){
        /*activePoint change for walk down (APCFWD) using
        Skip/Count Trick (Trick 1). If activeLength is greater
        than current edge length, set next internal node as
        activeNode and adjust activeEdge and activeLength
        accordingly to represent same activePoint*/
        if (activeLength >= edgeLength(currNode)){
            activeEdge =
            (l)text[activeEdge+edgeLength(currNode)]-(l)' ';
            activeLength -= edgeLength(currNode);
            activeNode = currNode;
            return 1;
        }
        return 0;
    }
    
    void extendSuffixTree(l pos){
        /*Extension Rule 1, this takes care of extending all
        leaves created so far in tree*/
        leafEnd = pos;
    
        /*Increment remainingSuffixCount indicating that a
        new suffix added to the list of suffixes yet to be
        added in tree*/
        remainingSuffixCount++;
    
        /*set lastNewNode to NULL while starting a new phase,
        indicating there is no internal node waiting for
        it's suffix link reset in current phase*/
        lastNewNode = NULL;
    
        //Add all suffixes (yet to be added) one by one in tree
        while(remainingSuffixCount > 0) {
    
            if (activeLength == 0) {
                //APCFALZ
                activeEdge = (l)text[pos]-(l)' ';
            }
            // There is no outgoing edge starting with
            // activeEdge from activeNode
            if (activeNode->children[activeEdge] == NULL){
                //Extension Rule 2 (A new leaf edge gets created)
                activeNode->children[activeEdge] =
                                      newNode(pos, &leafEnd);
    
                /*A new leaf edge is created in above line starting
                from an existing node (the current activeNode), and
                if there is any internal node waiting for it's suffix
                link get reset, point the suffix link from that last
                internal node to current activeNode. Then set lastNewNode
                to NULL indicating no more node waiting for suffix link
                reset.*/
                if (lastNewNode != NULL){
                    lastNewNode->suffixLink = activeNode;
                    lastNewNode = NULL;
                }
            }
            // There is an outgoing edge starting with activeEdge
            // from activeNode
            else{
                // Get the next node at the end of edge starting
                // with activeEdge
                Node *next = activeNode->children[activeEdge];
                if (walkDown(next)){
                    //Start from next node (the new activeNode)
                    continue;
                }
                /*Extension Rule 3 (current character being processed
                is already on the edge)*/
                if (text[next->start + activeLength] == text[pos]){
                    //If a newly created node waiting for it's
                    //suffix link to be set, then set suffix link
                    //of that waiting node to current active node
                    if(lastNewNode != NULL && activeNode != root){
                        lastNewNode->suffixLink = activeNode;
                        lastNewNode = NULL;
                    }
    
                    //APCFER3
                    activeLength++;
                    /*STOP all further processing in this phase
                    and move on to next phase*/
                    break;
                }
    
                /*We will be here when activePoint is in middle of
                the edge being traversed and current character
                being processed is not on the edge (we fall off
                the tree). In this case, we add a new internal node
                and a new leaf edge going out of that new node. This
                is Extension Rule 2, where a new leaf edge and a new
                internal node get created*/
                splitEnd = (l*) malloc(sizeof(l));
                *splitEnd = next->start + activeLength - 1;
    
                //New internal node
                Node *split = newNode(next->start, splitEnd);
                activeNode->children[activeEdge] = split;
    
                //New leaf coming out of new internal node
                split->children[(l)text[pos]-(l)' '] =
                                          newNode(pos, &leafEnd);
                next->start += activeLength;
                split->children[activeEdge] = next;
    
                /*We got a new internal node here. If there is any
                internal node created in last extensions of same
                phase which is still waiting for it's suffix link
                reset, do it now.*/
                if (lastNewNode != NULL){
                /*suffixLink of lastNewNode points to current newly
                created internal node*/
                    lastNewNode->suffixLink = split;
                }
    
                /*Make the current newly created internal node waiting
                for it's suffix link reset (which is pointing to root
                at present). If we come across any other internal node
                (existing or newly created) in next extension of same
                phase, when a new leaf edge gets added (i.e. when
                Extension Rule 2 applies is any of the next extension
                of same phase) at that point, suffixLink of this node
                will point to that internal node.*/
                lastNewNode = split;
            }
    
            /* One suffix got added in tree, decrement the count of
            suffixes yet to be added.*/
            remainingSuffixCount--;
            if (activeNode == root && activeLength > 0){
                activeLength--;
                activeEdge = (l)text[pos -
                                remainingSuffixCount + 1]-(l)' ';
            }else if (activeNode != root){
                activeNode = activeNode->suffixLink;
            }
        }
    }
    
    void print(l i, l j){
        for (l k=i; k<=j; k++){
            printf("%c", text[k]);
        }
    }
    
    //Print the suffix tree as well along with setting suffix index
    //So tree will be printed in DFS manner
    //Each edge along with it's suffix index will be printed
    void setSuffixIndexByDFS(Node *n, l labelHeight){
        if (n == NULL) return;
    
        if (n->start != -1){ //A non-root node
            //Print the label on edge from parent to current node
            print(n->start, *(n->end));
        }
        l leaf = 1;
        for (l i = 0; i < MAX_CHAR; i++){
            if (n->children[i] != NULL){
                if (leaf == 1 && n->start != -1)
                    printf(" [%lld]\n", n->suffixIndex);
    
                //Current node is not a leaf as it has outgoing
                //edges from it.
                leaf = 0;
                setSuffixIndexByDFS(n->children[i],
                      labelHeight + edgeLength(n->children[i]));
            }
        }
        if (leaf == 1){
            n->suffixIndex = size - labelHeight;
            printf(" [%lld]\n", n->suffixIndex);
        }
    }
    
    void freeSuffixTreeByPostOrder(Node *n){
        if (n == NULL)
            return;
        for (l i = 0; i < MAX_CHAR; i++){
            if (n->children[i] != NULL){
                freeSuffixTreeByPostOrder(n->children[i]);
            }
        }
        if (n->suffixIndex == -1)
            free(n->end);
        free(n);
    }
  };
}
 
// int doTraversal(Node *n, int labelHeight, int* maxHeight, int* substringStartIndex)
// {
//     if(n == NULL)
//     {
//         return 0;
//     }
//     int i=0;
//     int ret = -1;
//     if(n->suffixIndex < 0) //If it is internal node
//     {
//         for (i = 0; i < MAX_CHAR; i++)
//         {
//             if(n->children[i] != NULL)
//             {
//                 ret = doTraversal(n->children[i], labelHeight +
//                     edgeLength(n->children[i]),
//                     maxHeight, substringStartIndex);
                 
//                 if(n->suffixIndex == -1)
//                     n->suffixIndex = ret;
//                 else if((n->suffixIndex == -2 && ret == -3) ||
//                     (n->suffixIndex == -3 && ret == -2) ||
//                     n->suffixIndex == -4)
//                 {
//                     n->suffixIndex = -4;//Mark node as XY
//                     //Keep track of deepest node
//                     if(*maxHeight < labelHeight)
//                     {
//                         *maxHeight = labelHeight;
//                         *substringStartIndex = *(n->end) -
//                             labelHeight + 1;
//                     }
//                 }
//             }
//         }
//     }
//     else if(n->suffixIndex > -1 && n->suffixIndex < l){ //suffix of X
//         return -2; //Mark node as X
//     }else if(n->suffixIndex >= l){//suffix of Y
//         return -3; //Mark node as Y
//     }
//     return n->suffixIndex;
// }
 
// void getLongestCommonSubstring()
// {
//     int maxHeight = 0;
//     int substringStartIndex = 0;
//     doTraversal(root, 0, &maxHeight, &substringStartIndex);
     
//     int k;
//     for (k=0; k<maxHeight; k++)
//         printf("%c", text[k + substringStartIndex]);
//     if(k == 0)
//         printf("No common substring");
//     else
//         printf(", of length: %d",maxHeight);
//     printf("\n");
// }

#include <iostream>  
// driver program to test above functions
int main(int argc, char *argv[])
{
  // std::string txt = "";
  // std::string pattern = "";
  // std::cout << "Text Length: " << txt.length() << " Pattern Length: " << pattern.length() << "\n";

  // l lps[pattern.size()];
  // KMPSubstringSearch::preprocess(pattern.begin(), pattern.end(), lps);

  // auto start = txt.begin();
  // while(true){
  //   start = KMPSubstringSearch::search(start, txt.end(), pattern.begin(), pattern.end(), lps);
  //   l idx = start - txt.begin();
  //   if(idx >= txt.size()) break;
  //   std::cout << "KMP Substring Found at: " << idx << " -> " << txt.substr(idx, pattern.size()) << "\n";
    
  //   ++start;
  // }

  // l delta1[BoyerMooreSubstringSearch::MAX_CHAR];
  // l delta2[pattern.length()];
  // BoyerMooreSubstringSearch::preprocess(pattern.begin(), pattern.end(), delta1, delta2);

  // start = txt.begin();
  // while(true){
  //   start = BoyerMooreSubstringSearch::search(start, txt.end(), pattern.begin(), pattern.end(), delta1, delta2);
  //   l idx = start - txt.begin();
  //   if(idx >= txt.size()) break;
    
  //   std::cout << "Boyer Substring Found at: " << idx << " -> " << txt.substr(idx, pattern.size()) << "\n";
  //   ++start;
  // }
  // l = 7;
  // printf("Longest Common Substring in xabxac and abcabxabcd is: ");
  // strcpy(text, "xabxac#abcabxabcd$"); build();
  // getLongestCommonSubstring();
  // //Free the dynamically allocated memory
  // freeSuffixTreeByPostOrder(root);

  // l = 10;
  // printf("Longest Common Substring in xabxaabxa and babxba is: ");
  // strcpy(text, "xabxaabxa#babxba$"); build();
  // getLongestCommonSubstring();
  // //Free the dynamically allocated memory
  // freeSuffixTreeByPostOrder(root);

  // l = 14;
  // printf("Longest Common Substring in GeeksforGeeks and GeeksQuiz is: ");
  // strcpy(text, "GeeksforGeeks#GeeksQuiz$"); build();
  // getLongestCommonSubstring();
  // //Free the dynamically allocated memory
  // freeSuffixTreeByPostOrder(root);

  // l = 26;
  // printf("Longest Common Substring in OldSite:GeeksforGeeks.org");
  // printf(" and NewSite:GeeksQuiz.com is: ");
  // strcpy(text, "OldSite:GeeksforGeeks.org#NewSite:GeeksQuiz.com$");
  // build();
  // getLongestCommonSubstring();
  // //Free the dynamically allocated memory
  // freeSuffixTreeByPostOrder(root);

  // l = 6;
  // printf("Longest Common Substring in abcde and fghie is: ");
  // strcpy(text, "abcde#fghie$"); build();
  // getLongestCommonSubstring();
  // //Free the dynamically allocated memory
  // freeSuffixTreeByPostOrder(root);

  // l = 6;
  // printf("Longest Common Substring in pqrst and uvwxyz is: ");
  // strcpy(text, "pqrst#uvwxyz$"); build();
  // getLongestCommonSubstring();
  // //Free the dynamically allocated memory
  // freeSuffixTreeByPostOrder(root);

  SuffixTree::Tree tree("abbc");
  printf("Number of nodes in suffix tree are %lld\n",tree.count);
  return 0;
}