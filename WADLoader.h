#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <iostream>

#include "DataTypes.h"
#include "WADReader.h"

class WADLoader
{
public:
    WADLoader(std::string WADFilePath);
    bool LoadWAD();

    ~WADLoader();

protected:
    bool OpenAndLoad();
    bool ReadDirectories();

    std::string m_WADFilePath;
    std::ifstream m_WADFile;
    uint8_t* m_WADData;
    std::vector<Directory> m_WADDirectories;
};