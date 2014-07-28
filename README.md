```
Name    : ofxTFIDF Library                         
Author  : Noah Shibley, http://socialhardware.net                       
Date    : July 28th, 2014                                 
Version : 0.1                                               
Notes   : An addon for openframeworks to do TF-IDF
Dependencies:	openframeworks
```
An openframeworks library to do tf–idf. Tf-idf is short for term frequency–inverse document frequency, it is a numerical statistic that is intended to reflect how important a word is to a document in a collection or corpus

------------------------------------------------------

Function list:
```cpp
    void loadDocsToMap(string filePath,string fileExt,string splitChar); //store each txt doc as a word map object
    void scoreWords(); //look at words in map object and score the words via id-tf
    void printAllScores(bool toggle) //Print detailed scoring for every word.
    docScoreList //A vector of vectors containing a final idtf scores for each document.
```
------------------------------------------------------

 Example:

Step 1. in the testApp.h: 
```cpp	
#include "ofxTFIDF.h"	
ofxTFIDF wordFreq;
```

Step 2. in the testApp.cpp:

```cpp
wordFreq.printAllScores(false); //set to true to see detailed scoring per word.
wordFreq.loadDocsToMap("articles","txt"," "); //articles path, txt extension, split words by space.
wordFreq.scoreWords();

//Print the top 5 highest scores per document.
for(int i=0;i<wordFreq.docScoreList.size();i++)
{
    vector < pair<string,float> > wordDocScore; //map for storing scores of individual document
    wordDocScore = wordFreq.docScoreList.at(i);
        
    //print only 5 top scores
    for(int j=0;j<5;j++)
    {
        cout << j+1 << ". " << wordDocScore.at(j).first << " " << wordDocScore.at(j).second << endl;
    }
    cout << "--------------------" << endl;
        
}
```
