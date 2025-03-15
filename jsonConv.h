//
// Final project. Sairch Engine.
// JSON Converter Class
// Created by RoliMoon on 09.02.2025.
//

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "nlohmann/json.hpp"

using std::string;
using std::vector;

class JsonConv {

public:
    static JsonConv* getProgInstance();
    string requPath = "requests.json";
    string answPath = "answers.json";
    void readConfig(string confPath = "config.json");
    vector<string> getTextDocuments();
    int getResponseLimit();
    vector<string> getRequests();
    void putAnswers(vector<vector<std::pair<int, float>>> answers);

private:
    JsonConv() = default;
    static JsonConv* progInstance;
    string appName;
    string appVersion;
    int maxResponses = { 5 };
    vector<string> resPaths;
    vector<string> textDocs;
    vector<string> requestVec;
};