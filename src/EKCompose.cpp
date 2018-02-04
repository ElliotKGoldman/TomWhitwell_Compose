//
//  EKCompose.cpp
//  TomWhitwell_compose
//
//  Created by Elliot Goldman on 1/30/18.
//

#include "EKCompose.hpp"

//The main compose function

bool EKCompose::initializedEK = false;
ofXml EKCompose::xml;
vector<string> EKCompose::vowels;
vector<string> EKCompose::consonants;
vector<string> EKCompose::shapeVowels;
vector<string> EKCompose::shapeConsonants;
vector<string> EKCompose::moods;
vector<string> EKCompose::sources;
vector<string> EKCompose::filters;
vector<string> EKCompose::modulations;
vector<string> EKCompose::slopes;
vector<string> EKCompose::resonances;
vector<string> EKCompose::chords;
vector<string> EKCompose::sequences;

string EKCompose::compose(){
    if(!initializedEK){
        EKCompose::initializeEK();
    }
    
    string albumTitle = randomName(8);
    
    ofBuffer score;
    
    score.append(albumTitle);
    score.append("\r");
    
    for(int i= 0; i <= albumTitle.length(); i++){
        score.append("-");
    }
    score.append("\r");
    score.append("\r");
    
    int numberOfTracks = ofRandom(5, 12);
    //Create each track
    for(int i = 0; i < numberOfTracks; i++){
        score.append("Track " + ofToString(i) + ": " + randomName(ofRandom(5,12)));
        score.append("\r");
        score.append("Mood: ");
        score.append(choose(moods));
        score.append(", ");
        score.append(choose(moods));
        score.append(".\r");
        score.append("Source: ");
        score.append(choose(sources));
        score.append(".\r");
        score.append("Filter: ");
        score.append(choose(filters));
        score.append(".\r");
        score.append("Modulation: ");
        score.append(choose(modulations));
        score.append(".\r");
        score.append("Slope: ");
        score.append(choose(slopes));
        score.append(".\r");
        score.append("Resonance: ");
        score.append(choose(resonances));
        score.append(".\r");
        score.append("Chords: ");
        score.append(choose(chords));
        score.append(".\r");
        score.append("Sequence: ");
        score.append(choose(sequences));
        score.append(".\r\r\r");
        
        int width = ofRandom(8, 64);
        int height = ofRandom(1, 12);
        for(int i = 0; i < height; i++){
            score.append(randomShape(width) + '\r');
        }
        score.append("\r\r");
        
    }
    saveScore(albumTitle, score);
    return "Album: " + albumTitle + " has been saved";
}

//Helper Functions

void EKCompose::saveScore(string albumTitle, ofBuffer score){
    
    ofFileDialogResult saveFileResult = ofSystemSaveDialog(albumTitle+ "." + "txt", "Save your score");
     if (saveFileResult.bSuccess){
         //If the file doesn't save, warn the user
         if(!ofBufferToFile(saveFileResult.filePath, score)){
             cout << "File didn't save!\n";
         }
     }else{
         cout << "Save Canceled\n";
     }
    
    
    
}

void EKCompose::initializeEK(){
    if( xml.load("composeWords.xml") ){
        xml.setTo("COMPOSEWORDS");
        loadVectorFromXML("VOWEL", &vowels);
        loadVectorFromXML("CONSONANT", &consonants);
        loadVectorFromXML("SHAPEVOWEL", &shapeVowels);
        loadVectorFromXML("SHAPECONSONANT", &shapeConsonants);
        loadVectorFromXML("MOOD", &moods);
        loadVectorFromXML("SOURCE", &sources);
        loadVectorFromXML("FILTER", &filters);
        loadVectorFromXML("MODULATION", &modulations);
        loadVectorFromXML("SLOPE", &slopes);
        loadVectorFromXML("RESONANCE", &resonances);
        loadVectorFromXML("CHORD", &chords);
        loadVectorFromXML("SEQUENCE", &sequences);
    }else{
        cout << "Where's compose words? What'd you do with it?!?!";
        abort();
    }
}

void EKCompose::loadVectorFromXML(string name, vector<string> *theVector){
    //Load in different lists of compose words
    if(xml.exists(name + "S")){
        xml.setTo(name + "S");
        if(xml.exists(name + "[0]")){
            xml.setTo(name + "[0]");
            do{
                string value = xml.getValue();
                theVector->push_back(value);
            }while(xml.setToSibling()); // go the next name
        }
    }else{
        cout << name << "S doesn't exist! Check your XML!\n";
    }
    //Reset to top
    xml.setTo("//COMPOSEWORDS");
}

string EKCompose::randomName(int length){
    return randomBlank(7, vowels, consonants);
}

string EKCompose::randomShape(int length){
    return randomBlank(length, shapeVowels, shapeConsonants);
}

string EKCompose::randomBlank(int length, vector<string> vowelsVector, vector<string> consonantsVector ){
    string name = "";
    int randomNum = 0;
    
    for(int i = 0 ; i < (length/2); i++){
        //Capitalize first letter
        if(i == 0){
            name += ofToUpper(choose(consonantsVector));
        }else{
            name += choose(consonantsVector);
        }
    }

    for(int i = 1; i < length; i+=2){
        name.insert(i, choose(vowelsVector));
        
    }
    return name;
}


string EKCompose::choose(vector<string> theVector){
    int randomElement = ofRandom(0, theVector.size() - 1);
    return theVector[randomElement];
}
