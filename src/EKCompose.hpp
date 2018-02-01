//
//  EKCompose.hpp
//  TomWhitwell_compose
//
//  Created by Elliot Goldman on 1/30/18.
//
#include "ofApp.h"
using namespace std;

class EKCompose{
public:
    
    static bool compose();
    
private:
    static bool initializedEK;
    
    //Initialized from XML
    static ofXml xml;
    static vector<string> vowels;
    static vector<string> consonants;
    static vector<string> shapeVowels;
    static vector<string> shapeConsonants;
    static vector<string> moods;
    static vector<string> sources;
    static vector<string> filters;
    static vector<string> modulations;
    static vector<string> slopes;
    static vector<string> resonances;
    static vector<string> chords;
    static vector<string> sequences;
    
    static void initializeEK();
    static void loadVectorFromXML(string name, vector<string> *theVector);
    static string randomName(int length = 6);
    static string randomShape(int length = 6);
    static string randomBlank(int length, vector<string> vowels, vector<string> consonants);
    static string choose(vector<string> theVector);
};
