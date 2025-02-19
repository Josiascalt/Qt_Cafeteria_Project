#include <iostream>
#include <fstream>

#include "json.cpp"
#include "json_builder.cpp"

using namespace std;

int main() {
    auto doc = json::Document(
               json::Builder{}.StartDict().Key("DATABASE_TAC"s).Value(1)
                                          .Key("DATABASE_TAIS"s).Value(2)
                                          .Key("DATABASE_TAA"s).Value(3)
                              .EndDict().Build());
    
    std::ofstream fout("database.json");
    json::Print(doc, cout);
    cout << "\nSuccess!";
    return 0;
}
