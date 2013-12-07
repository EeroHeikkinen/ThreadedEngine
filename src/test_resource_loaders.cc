#include "test_resource_loaders.hh"

#include <fstream>
#include <iostream>
#include <vector>


bool Test::TestResourceLoader::loadFromTXT(const std::string& fileName) {
    std::string line;
    std::ifstream file(fileName);

    if (file.is_open()) {
        while (std::getline(file, line)) { // parse the resource file
            std::vector<std::string> vLine;
            /* index 0: resource type - tells how the resource should be loaded
               index 1: resource identifier - unique string with which it can be found in resloader
               index 2: resource file name */

            for (size_t i = 0; i < line.size(); ++i) {
                if (line.at(i) == '|') { // separator
                    vLine.push_back(line.substr(0, i));
                    line.erase(0, i+1);
                    i = 0;
                }
                else if (line.at(i) == '*') { // comment
                    line.erase(i);
                    break;
                }
            }

            if (vLine.size() == 2) {
                vLine.push_back(line.substr(0, line.find_last_not_of(' ')+1));
            }

            // line parsing is done

            if (vLine.size() == 3) {
                for (auto i : vLine) {
                    std::cout << "[" << i << "] ";
                }
                std::cout << std::endl;
            }
        }
        return true;
    }
    else {
        /* TODO
        exception?
        unable to open the file
        */
    }
    return false;
}
