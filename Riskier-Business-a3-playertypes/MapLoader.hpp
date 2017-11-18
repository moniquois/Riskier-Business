//
//  MapLoader.hpp
//  Tester101
//
//  Created by Monique Richard on 2017-10-21.
//  Copyright © 2017 Monique Richard. All rights reserved.
//

#ifndef MapLoader_hpp
#define MapLoader_hpp
#include <iostream>
#include <vector>
#include <stdio.h>

class MapLoader {
public:
    MapLoader();
    ~MapLoader();
    bool is_validExt(std::string fn);//can probably make this private
    bool is_valid(std::string fn);//can probably make this private
    bool createMap(std::string fn);
    void printall();
    std::vector<std::string> returnCountries(){return countries;};
    std::vector<std::string> returncontinentnames(){return continentnames;};
    std::vector<std::string> returncontinentlist(){return continentlist;};
    std::vector<std::vector<std::string>> returnadj_countries(){return adj_countries;};
    std::vector<int> returnBonus(){return bonus;};
private:
    std::vector<std::string> countries;
    std::vector<std::string> continentnames;
    std::vector<std::string> continentlist;//list of continents that belong to
    std::vector< std::vector<std::string>> adj_countries;
    std::vector<int> bonus;
};
#endif /* MapLoader_hpp */
