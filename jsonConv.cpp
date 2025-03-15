//
// Final project. Sairch Engine.
// JSON Converter Class
// Created by RoliMoon on 09.02.2025.
//

#include "../include/jsonConv.h"

using std::string;
using std::to_string;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::vector;
using std::ofstream;
using std::ifstream;

JsonConv* JsonConv::progInstance = nullptr;
JsonConv* JsonConv::getProgInstance() {
    if (progInstance == nullptr) progInstance = new JsonConv;
    return progInstance;
}

//*
//Readin config file
//*

void JsonConv::readConfig(string confPath) {
    ifstream configFile(confPath);
    if (configFile.is_open()) {
        nlohmann::json configDict;
        configFile >> configDict;
        appName = configDict["config"]["name"];
        appVersion = configDict["config"]["version"];
        maxResponses = configDict["config"]["maxResponses"];
        resPaths.clear();
        for (auto finds : configDict["files"]) {
            resPaths.push_back(finds);
        }
        cout << appName << ". Version: " << appVersion << endl;
        cout << "Max responses per request" << maxResponses << endl;
        cout << "Foondit files: " << resPaths.size();
        configFile.close();
    } else {
        cerr << "Eeror! Config file is empty!\n";
    }
    return;
}

//*
//Gettin the text documents
//*

vector<string> JsonConv::getTextDocuments() {

    textDocs.clear();
    for (auto& docs : resPaths) {
        ifstream readDocumentsStream(docs);
        if (readDocumentsStream.is_open()) {
            string wBuffer;
            while (readDocumentsStream.eof()){
                string rBuffer;
                readDocumentsStream >> rBuffer;
                wBuffer += rBuffer;
                wBuffer += "_";
            }
            textDocs.push_back(wBuffer);
            readDocumentsStream.close();
        } else {
            cerr << "Eeror! Sairch failed!\n";
        }
    }
    return textDocs;
}

//*
//Limit o responses per yin request
//*

int JsonConv::getResponseLimit() {
    return maxResponses;
}

//*
//Acceptin the requests fae the uiser
//*
//A think that would be better tae move it tae main.cpp
//*

string takinUiserReq() {
    string enterin;
    cout << "Enter a request > ";
    std::getline(cin, enterin);
    ofstream ootOProg;
    ootOProg.open("requests.json");
    if (ootOProg.is_open()) {
        ootOProg << enterin << endl;
    }
    ootOProg.close();
    return enterin;
}

//
//Gettin the requests fae "requests.json"

vector<string> JsonConv::getRequests() {
    ifstream inProg("requests.json");
    if (inProg.is_open()) {
        nlohmann::json requestDict;
        inProg >> requestDict;
        requestVec.clear();
        for (auto finds : requestDict["Requests"]) {
            requestVec.push_back(finds);
        }
        inProg.close();
        string requestCounter = requestVec.size() == 1 ? " request is " : " requests are ";
        cout << requestVec.size() << requestCounter << "foond.\n";
    } else {
        cerr << "Eeror! Nae any request nae foond!";
    }
}

void JsonConv::putAnswers(vector<vector<std::pair<int, float>>> answers) {
    nlohmann::json answersDict;
    if (!answers.empty()) {
        //AnswersReg - Answers Register
        ofstream answersFile(answPath, std::ios_base::trunc);
        if (answersFile.is_open()) {
            int requestCount{0};
            nlohmann::json answersReg;
            for (auto request: answers) {
                answersDict["answers"]["request" + to_string(requestCount)]["result"] = !request.empty();
                if (request.size() == 1) {
                    answersDict["answers"]["request" + to_string(requestCount)]["docid"] = request[0].first;
                    answersDict["answers"]["request" + to_string(requestCount)]["rank"] = request[0].second;
                } else {
                    auto relevArray = nlohmann::json::array();
                    int relevanceID{0};
                    for (auto relevance: request) {
                        relevanceID++;
                        if (relevanceID > maxResponses) {
                            break;
                        }
                        auto relevanceObject = nlohmann::json::object();
                        relevanceObject["docid"] = relevance.first;
                        relevanceObject["rank"] = relevance.second;
                        relevArray.push_back(relevanceObject);
                    }
                    answersDict["answers"]["request" + to_string(requestCount)]["relevance"] = relevArray;
                }
                requestCount++;
            }
            answersFile << answersDict;
            answersFile.close();
            cout << "dane\n";
        } else {
            cerr << "Eeror! File nae foond: " << answPath << endl;
        }
    } else {
        cerr << "Nae yin answers foond tae pushin.\n";
    }
}
