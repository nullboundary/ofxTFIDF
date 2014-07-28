#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    cout << "tf-idf Example App" << endl;
    
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

}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
