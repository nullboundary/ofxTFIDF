/************************************************************************************
 *
 * 	Name    : ofxTFIDF Library
 * 	Author  : Noah Shibley, http://socialhardware.net
 * 	Date    : July 28th, 2014
 * 	Version : 0.1
 * 	Notes   : An openframeworks library to do tf–idf. tf-idf is short for term frequency–inverse document frequency, it is a numerical statistic that is intended to reflect how important a word is to a document in a collection or corpus
 *
 *
 * 	This file is part of ofxTFIDF.
 *
 * 		    ofxTFIDF is free software: you can redistribute it and/or modify
 * 		    it under the terms of the GNU General Public License as published by
 * 		    the Free Software Foundation, either version 3 of the License, or
 * 		    (at your option) any later version.
 *
 * 		    ofxTFIDF is distributed in the hope that it will be useful,
 * 		    but WITHOUT ANY WARRANTY; without even the implied warranty of
 * 		    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * 		    GNU General Public License for more details.
 *
 * 		    You should have received a copy of the GNU General Public License
 * 		    along with ofxTFIDF.  If not, see <http://www.gnu.org/licenses/>.
 *
 ***********************************************************************************/

#include "ofxTFIDF.h"

bool sortFunction(const pair<string,float> firstElem, const pair<string,float> secondElem)
{
    return (firstElem.second > secondElem.second);
}

ofxTFIDF::ofxTFIDF()
{
    printWordScores = false;
}

//--------------------------------------------------------------
void ofxTFIDF::loadDocsToMap(string filePath,string fileExt,string splitChar)
{
    
    map<string,int> singleDoc;
    string path = filePath;
    ofDirectory dir(path);
    dir.allowExt(fileExt);
    //populate the directory object
    dir.listDir();
    totalDocs = dir.numFiles();
    vector <string> wordList; //temporary word list before mapping words.
    
    for(int i = 0; i < dir.numFiles(); i++) //load each doc
    {
        string fileName = dir.getPath(i);
        ofBuffer buffer = ofBufferFromFile(fileName);
        cout << fileName << endl;
        if(buffer.size())
        {
            
            string text = buffer.getText();
            
            wordList = ofSplitString(text, splitChar);
            
            for(int i=0;i<wordList.size();i++) //add all words to a single doc word map
            {
                if(singleDoc.count(wordList[i])>0) //word already in map
                {
                    
                    singleDoc.at(wordList[i]) = singleDoc.at(wordList[i]) + 1;
                }
                else //word not in map, add it.
                {
                    
                    singleDoc.insert ( std::pair<string,int>(wordList[i],1) );
                    
                }
            }
            docMapList.push_back(singleDoc);
            
            //take each single occurance of the word out into the all doc map.
            for (map<string,int>::iterator it=singleDoc.begin(); it!=singleDoc.end(); ++it)
            {
                
                if(allDocWords.count(it->first)>0) //word already in map
                {
                    allDocWords.at(it->first) = allDocWords.at(it->first) + 1;
                }
                else //word not in map, add it.
                {
                    allDocWords.insert ( std::pair<string,int>(it->first,1) );
                    
                }
            }
            
        }
        singleDoc.clear();
        wordList.clear();
    }

}
//--------------------------------------------------------------
void ofxTFIDF::scoreWords()
{
    for(int i=0;i<docMapList.size();i++)
    {
        map <string,int> wordDoc = docMapList.at(i);
        vector < pair<string,float> > wordDocScore; //map for storing scores
        for (map<string,int>::iterator it=wordDoc.begin(); it!=wordDoc.end(); ++it)
        {
            if (printWordScores) {
               cout << it->first << " count:" << wordDoc.at(it->first) << " total:" << wordDoc.size() << " numDoc: " <<  allDocWords.at(it->first) << " score: " << tfidfScore(it->first, wordDoc) << " tf: " << termFreq(it->first, wordDoc) << " idf:" << inverseDocFreq(it->first) << endl;
            }
            
            float wordScore = tfidfScore(it->first, wordDoc); //compute score
            
            if(wordScore > 0)
            {
                wordDocScore.push_back( pair<string,float>(it->first,wordScore) );
            }
        }
        
        
        
        sort(wordDocScore.begin(),wordDocScore.end(),&sortFunction); //sort based on score
        
        docScoreList.push_back(wordDocScore);
        
    }

}

//--------------------------------------------------------------
//TF
float ofxTFIDF::termFreq(string word, map <string,int> wordMap){
    
    int count = wordMap.at(word);
    return (float) count / (float) wordMap.size();
}

//--------------------------------------------------------------
//IDF
float ofxTFIDF::inverseDocFreq(string word)
{
    return log( (float) totalDocs / (1.0 + numDocContain(word)));
}

//--------------------------------------------------------------
float ofxTFIDF::tfidfScore(string word, map <string,int> wordMap)
{
    return termFreq(word, wordMap) * inverseDocFreq(word);
}

//--------------------------------------------------------------

int ofxTFIDF::numDocContain(string word){
    
    return  allDocWords.at(word);
}
