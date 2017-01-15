/* ------------------------------------------------
 * Program: Trie Harder
 * Using a trie to find rhyming words.
 *
 * Class: CS 251 Data Structures
 * Author: Oliver Hui
 *
 * -------------------------------------------------
 */

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <cassert>    // for assertions
#include <stdlib.h>
#include <iostream>

#define MAX_WORD_LENGTH 100

using namespace std;

struct Node {
    char charLetter;
    bool isWord;
    int numID;
    Node* leftChild;    //Used to point to children
    Node* rightChild;   //Used to point to siblings
};

struct NodeTracker{
    Node* node;         //used to track node in the list
    NodeTracker* pPrev;
};

struct letterStruct{
    //As we traverse the tree, we need to save each letter and we use it
    //to show our words solutions that match our search criteria

    char letter;
    letterStruct* pPrev;
};

void letterListPush(letterStruct* &pHead, char letter){
    //This function pushes a letter that's part of our solution word that's
    //part of our search criteria.

    letterStruct *pTemp = new letterStruct;
    pTemp ->letter = letter;
    pTemp ->pPrev= pHead;
    if (pHead==NULL) {
        pHead = pTemp;
    } else {
        pHead= pTemp;
    }
}//end letterListPush

void letterListPop(letterStruct* &pHead){
    //This function pops off a letter from our link list. It usually happens
    //when found a word, displayed it, and we can pop off that word, letter
    //by letter.

    if (pHead==NULL) {
        cout<<"Empty Letter List"<<endl;
        return;
    }
    letterStruct *pTemp = pHead;
    pHead= pHead->pPrev;
    delete pTemp;
}//end letterListPop

void letterListDisplayWord(letterStruct* &pHead, int &index){
    //This function is what displays each solution word, letter by letter.
    index++;
    cout<<index<<") ";

    letterStruct *pTemp=pHead;
    while (pTemp !=NULL) {
        cout<<pTemp->letter;
        pTemp=pTemp->pPrev;
    }
    cout<<endl;
}//end letterListDisplayWord

void displayMenu(){
    //This display the menu

    cout<< "Options:"<<endl;
    cout<< "f str  Find str"<<endl;
    cout<< "p n    Print next n"<<endl;
    cout<< "a str  Add str"<<endl;
    cout<< "d str  Delete str"<<endl;
    cout<< "? Help"<<endl;
    cout<< "x Exit"<<endl;
    cout<<endl<<"What are your instructions commander?: ";
}//displayMenu

Node* createNewNode(char letter, bool isWord, int &numID, Node* left, Node* right){
    //This creates a new node which is returned.

    Node* pTemp = new Node;
    pTemp->charLetter= letter;
    pTemp->isWord = isWord;
    pTemp->numID=numID;
    pTemp->leftChild= left;
    pTemp->rightChild = right;
    //cout<<"New Node Created-> letter: "<< letter <<" isWord: "<<isWord<<" numID: "<<numID<<endl;
    numID++;
    return pTemp;
}//end createNewNode

Node* createBlankNode(Node* &pParent, int &id){
    //This creates a blank node that points back to the parent

    Node* pTemp = createNewNode(0, false, id , pParent, NULL);
    return pTemp;
}//end createBlankNode

Node* getLatestChildLetterNode(Node* &pParent, char letter, int &id){
    //This gets the latest Child node of a parent

    Node* pTemp = pParent->leftChild;
    Node* pPrev = pTemp;
    bool letterFound = false;

    if (pTemp->rightChild ==NULL) {
        return pTemp;
    }

    while (pTemp->rightChild!=NULL) {
        if (pTemp->charLetter == letter) {
            letterFound = true;
            pPrev = pTemp;
            break;
        }
        pPrev = pTemp;
        pTemp= pTemp->rightChild;
    }//end while

    if (!letterFound) {
        pTemp = createNewNode(letter, false, id, NULL, pPrev->rightChild);
        Node* pNewBlankNode = createBlankNode(pTemp, id);
        pTemp->leftChild = pNewBlankNode;
        pPrev->rightChild = pTemp;
        pPrev = pTemp;
    }

    return pPrev;
}

Node* initializeRoot(int &id){
    Node* pTemp = new Node;
    pTemp->numID = id;
    pTemp->isWord= false;
    pTemp->charLetter =0;
    id++;
    pTemp->leftChild = createBlankNode(pTemp, id);
    pTemp->rightChild= NULL;
    return pTemp;
}

void pushNewWord(char newWord[], Node* &pRoot, int &numID){
    Node* pParent= pRoot;
    Node* pChild = NULL;
    Node* pNewChild = NULL;
    Node* pNewBlankNode= NULL;
    int i;

    for (i = (int)strlen(newWord)-1; i>=0; i--) {
        pNewBlankNode = NULL;
        pNewChild = NULL;

        pChild=getLatestChildLetterNode(pParent, newWord[i], numID);

        if (pChild->leftChild== pParent) {
            //This means we're at the empty node that points back to parent

            if (i != 0){
                pNewChild= createNewNode(newWord[i], false, numID, NULL, pChild);
            } else {
                pNewChild= createNewNode(newWord[i], true, numID, NULL, pChild);
            }

            //We create a new node for our letter

            pNewBlankNode= createBlankNode(pNewChild, numID);
            //We create the null blank node that points back it

            pNewChild ->leftChild = pNewBlankNode;
            //Set the newly created node's left pointer to point at blank node

            pParent ->leftChild= pNewChild;


            pParent = pNewChild;
            if (i != 0){

            } else {
                pParent->isWord = true;
            }
        }//end if (pChild->leftChild== pParent)
        else {
            //We're at a node that has the letter we need
            pParent = pChild;

            if (i != 0){
                //pParent->isWord = false;
            } else {
                pParent->isWord = true;
            }
        }

    }//end for
}

void displayChildren(Node* &pParent){
    //This takes any parent node and print the childrens
    Node* pTemp = pParent->leftChild;
    cout<<endl<<"at Parent node "<< pParent->charLetter<<" id: "<< pParent->numID<< " isWord "<< pParent->isWord<<endl;
    while (pTemp->rightChild!=NULL) {
        cout<<"Node "<< pTemp->charLetter<<" id: "<< pTemp->numID<< " isWord "<< pTemp->isWord<<endl;
        pTemp= pTemp->rightChild;
    }
}

bool lettersAreAllAlphabets(char word[]){
    //This checks if a word passed in and sees if there are any
    //non alphabets in the word. If there is, then it returns a 0.
    //If there is nothing but alphabets, then it'll return a 1, which is good!
    bool result= true;

    if (strlen(word)==1) {
        return false;
    }
    word[strlen(word)-1]= '\0';
    for (int i =0 ; i< strlen(word); i++) {
        if(isalpha(word[i] )== false ){
            result = false;
            break;
        }
    }//end for (int i =0 ;
    return result;
}//end lettersAreAllAlphabets

void readFileIntroTree(char * fileName, Node* &pRoot, int &numID){
    //This is the file that gets read in and help pushes the word into
    //our tree.
    FILE* fp;
    fp = fopen(fileName, "r");
    char word[MAX_WORD_LENGTH];
    while (fgets(word,MAX_WORD_LENGTH,fp)!=NULL) {
        //We read the file line by line
        if (lettersAreAllAlphabets(word)) {
            pushNewWord(word, pRoot, numID); // we push a word
        }
    }//end  while (fgets(word,M
}//end readFileIntroTree

Node* findString(char string[], Node* &pRoot){
    Node* pReturn=NULL;
    Node* pTemp = pRoot->leftChild;

    for (int i =(int)strlen(string)-1; i>=0; i--) {
        while (pTemp!=NULL) {
            if (pTemp->charLetter== string[i]) {
                break;
            }
            pTemp= pTemp->rightChild;
        }
        pReturn = pTemp;
        pTemp = pTemp->leftChild;
    }
    return pReturn;
}

void nodeTrackerPop(NodeTracker *&pHead){
    //cout<<"POP List is now"<<endl;
    NodeTracker* pTemp;
    pTemp = pHead;
    pHead = pHead->pPrev;
}

void nodeTrackerPush(NodeTracker *&pHead, Node* targetNode){

    NodeTracker* pNew = new NodeTracker;
    pNew->node = targetNode;
    pNew->pPrev = NULL;
    if (pHead == NULL) {
        pHead= pNew;
    } else {
        pNew->pPrev = pHead;
        pHead = pNew;
    }
}

void startDeletingNodesUpTheTree(char string[], Node* &pRoot, int id){
    NodeTracker* pHead= NULL;
    Node* pTemp = pRoot->leftChild;

    nodeTrackerPush(pHead, pRoot);
    for (int i =(int)strlen(string)-1; i>=0; i--) {
        while (pTemp!=NULL) {
            if (pTemp->charLetter== string[i]) {
                nodeTrackerPush(pHead, pTemp);
                break;
            }
            pTemp= pTemp->rightChild;
        }
        pTemp = pTemp->leftChild;
    }

    int i;

    Node* pParent = NULL;
    Node* pChild = NULL;
    Node* pPrev = NULL;

    for (i =0; i<= strlen(string)-1; i++) {

        if (pHead->node->isWord == 1 && i !=0) {
            break;
        }

        pParent = pHead->pPrev->node;
        pChild = pParent->leftChild;
        pPrev = pChild;
        while (pChild!=NULL) {
            if (pChild->charLetter == pHead->node->charLetter) {
                break;
            }
            pPrev = pChild;
            pChild = pChild->rightChild;
        }

        if (pPrev == pChild){
            pParent->leftChild = pChild->rightChild;
        } else {
            pPrev->rightChild = pChild->rightChild;
        }
        nodeTrackerPop(pHead);
    }
}

void deleteStringFromTree(char string[], Node* &pRoot, int id){
    Node* pCursor = findString(string, pRoot);

    if (pCursor->leftChild->leftChild== pCursor ) {
        startDeletingNodesUpTheTree(string, pRoot, id);
    } else {
        pCursor->isWord=0;
    }
}

bool checkIfLegitString(char string[], Node* &pRoot){
    //This function quickly checks if our string does exist in the tree
    //It returns a 1/true that yes, the search term does exist
    //It returns false if the search term does not exist

    bool result= true;
    Node* pReturn=NULL;
    Node* pTemp = pRoot->leftChild;
    int i;
    for (i =(int)strlen(string)-1; i>=0; i--) {

        while (pTemp!=NULL) {
            if (pTemp->charLetter== string[i]) {
                break;
            }
            pTemp= pTemp->rightChild;
        }
        if (pTemp!=NULL) {
        } else {
            result = false;
            break;
        }
        pReturn = pTemp;
        pTemp = pTemp->leftChild;
    }
    return result;
}

void searchSuffix(char suffix[], Node* &pRoot, int numResults, NodeTracker* &pHead, letterStruct* &lHead, int &reachedEnd){

    int i =(int)strlen(suffix)-1;

    for (; i>=1 ; i--) {
        letterListPush(lHead, suffix[i]);
    }

    i=0;

    if (pRoot->leftChild->leftChild == pRoot) {
        return;
    }


    nodeTrackerPush(pHead, pRoot);
    letterListPush(lHead, pRoot->charLetter);

    while (pHead!=NULL) {

        if (pHead->node->isWord== 1) {
            if (numResults==i) {
                break;
            }
            letterListDisplayWord(lHead, i);
        }

        if (pHead->node->leftChild->leftChild!= pHead->node && pHead->node->charLetter!=0) {
            nodeTrackerPush(pHead, pHead->node->leftChild);
            letterListPush(lHead, pHead->node->charLetter);
        } else {
            if (pHead->node->charLetter == 0) {
                nodeTrackerPop(pHead);
                letterListPop(lHead);
            }
            if (pHead== NULL) {
                break;
            }

            if (pHead->node==pRoot) {
                //cout<<"Reached pRoot"<<endl;
                if (numResults > i) {
                    cout<<"End of list. could not find more."<<endl;
                    reachedEnd= 1;
                }
                break;
            }
            pHead->node = pHead->node->rightChild;
            lHead->letter = pHead->node->charLetter;
        }
    }//end while (pHead!=NULL)
}//end searchSuffix

void searchTheRest(NodeTracker* &pHead, int numResults, letterStruct* &lHead, Node* &pRoot, int &reachedEnd){
    int i =0;

    if (reachedEnd==1) {
        cout<<"Cannot print anymore. Sorry"<<endl;
        return;
    }

    while (pHead!=NULL) {

        if (pHead->node->isWord== 1) {
            if (numResults==i) {
                break;
            }
            letterListDisplayWord(lHead, i);
        }

        if (pHead->node->leftChild->leftChild!= pHead->node && pHead->node->charLetter!=0) {
            nodeTrackerPush(pHead, pHead->node->leftChild);
            letterListPush(lHead, pHead->node->charLetter);
        } else {
            if (pHead->node->charLetter == 0) {
                nodeTrackerPop(pHead);
                letterListPop(lHead);
            }
            if (pHead== NULL) {
                break;
            }

            if (pHead->node==pRoot) {
                if (numResults > i) {
                    cout<<"End of list. could not find more"<<endl;
                }
                break;
            }
            pHead->node = pHead->node->rightChild;
            lHead->letter = pHead->node->charLetter;
        }
    }//end while (pHead
}//end searchTheRest

void displayExtendedMenu(){
    cout<<endl;
    cout<<"f <string>    Find the string str in the tree.  This updates the position reference. Give an error message if str is not found and reset the cursor to NULL. Please enter a valid string. I assume perfect input. Don't enter crazy characters. It traverses the tree one by one until it can't find the character or it gets to the end of the string."<<endl<<endl;
    cout<<"p <int>      Print the next n words from the current position reference, one per line. Successive calls to this command should print the next n words each time until there are no more. Note that these words will not be displayed in alphabetical order. From your search suffix, it'll print the first N words. If there are more, you can use the same command again. It'll alert you if it cannot print anymore. It'll apologize."<<endl<<endl;
    cout<<"a <string>    Add word str to the tree. It won't create new nodes if there is already one. Please don't break my tree. This means don't add weird ascii art characters like question marks and dash. It will listen to you letter by letter. This will not change the pCursor."<<endl<<endl;
    cout<<"d <string>   Delete word str from the tree, giving a warning if it doesn’t exist.  Reset the position reference to the root, but only after a successful deletion. It'll give you a warning if it's a word. I assume perfect input so please don't break my tree. Don't enter weird characters." <<endl<<endl;
    cout<<"?       Display on-line help. This is what you're seeing."<<endl<<endl;
    cout<<"x       Exit the program. Goodbye to the program!"<<endl<<endl;
}//end displayExtendedMenu

int main(int argc, const char * argv[]) {
    cout<<"Trie Harder"<<endl;
    cout<<"Using a trie to find rhyming words."<<endl<<endl;
    cout<<"Author: Oliver Hui"<<endl;
    cout<<"Class: Data Structures"<<endl;

    int numID =0;
    Node* pRoot = initializeRoot(numID);
    Node* pFindString= NULL;

    readFileIntroTree("dictionary.txt", pRoot, numID);

    char userCmd;
    char userInputNewWord[MAX_WORD_LENGTH];
    char userInputSearchSuffix[MAX_WORD_LENGTH];
    char userInputDeleteStr[MAX_WORD_LENGTH];
    int userInputMaxPrints;
    int reachedEnd= 0;

    NodeTracker* pHead = NULL;
    letterStruct* lHead = NULL;

    displayMenu();

    while (true) {
        scanf(" %c", &userCmd);

        switch (userCmd) {

            case 'f':
                scanf("%s", userInputSearchSuffix);
                if (checkIfLegitString(userInputSearchSuffix, pRoot)) {
                    pFindString= findString(userInputSearchSuffix, pRoot);
                    cout<<"Great! Word has been found! Cursor points to the letter "<<pFindString->charLetter <<endl;
                    reachedEnd= 0;
                    pHead= NULL;
                    lHead =NULL;

                }
                else{
                    pFindString= NULL;
                    cout<<"Sorry. We could not find that word. Cursor resetted to NULL"<<endl;
                }
                break;

            case 'a':
                scanf("%s", userInputNewWord);
                cout<<"I will assume perfect input and you didn't want to destroy my tree"<<endl;
                pushNewWord(userInputNewWord, pRoot, numID);
                cout<<"I've added \""<< userInputNewWord<<"\" to the tree."<<endl;
                break;

            case 'p':
                scanf("%d", &userInputMaxPrints);

                if (userInputMaxPrints==0){
                    cout<<"Please enter a valid number"<<endl;
                    continue;
                }

                if (pFindString==NULL) {
                    cout<<"Sorry. Cursor is currently null. We need something to point at first."<<endl;
                } else {
                    if (pHead==NULL) {
                        searchSuffix(userInputSearchSuffix, pFindString, userInputMaxPrints, pHead, lHead, reachedEnd);
                    } else{
                        searchTheRest(pHead, userInputMaxPrints, lHead, pFindString, reachedEnd);
                    }
                }
                break;

            case 'd':
                scanf("%s", userInputDeleteStr);
                cout<<"I will assume perfect input and you didn't want to destroy my tree"<<endl;

                if (checkIfLegitString(userInputDeleteStr, pRoot)){
                    deleteStringFromTree(userInputDeleteStr, pRoot, numID);
                    pHead=NULL;
                    lHead = NULL;
                    reachedEnd = 0;
                    cout<<"I've deleted \""<< userInputDeleteStr<<"\" from the tree."<<endl;
                } else {
                    cout<<"String is not valid. Please enter something valid."<<endl;
                }
                break;
            case '?':
                displayExtendedMenu();
                break;

            case 'x':
                return 0;
                break;

            default:
                cout<<"Invalid Command, please try again"<<endl;
                break;
        }
        cout<<endl<<"What are your instructions commander?: ";
    }
    return 0;
}
