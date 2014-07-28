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

#pragma once

#include "ofMain.h"



class ofxTFIDF {
protected:

    map <string,int> allDocWords; //single map of all words + frequency of appearance in all docs (1 per doc)
    vector <map < string, int> > docMapList; //vector of maps of all words and frequency of words
    
    
    int totalDocs; //total number of docs loaded.
    bool printWordScores;
    
    float termFreq(string word, map <string,int> wordMap); //term frequency
    int numDocContain(string word); //count number of docs containing a word
    float inverseDocFreq(string word);
    float tfidfScore(string word, map <string,int> wordMap);
    
public:
	ofxTFIDF();
	
	void loadDocsToMap(string filePath,string fileExt,string splitChar); //store each txt doc as a word map object
    void scoreWords(); //look at words in map object and score the words via id-tf
    void printAllScores(bool toggle) { printWordScores = toggle; }
    
    vector <vector<pair<string,float> > > docScoreList; //final idtf scores for each document.
    
	
};

