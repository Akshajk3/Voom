#include "WADLoader.h"

WADLoader::WADLoader(std::string WADFilePath)
    : m_WADFilePath(WADFilePath), m_WADData(NULL)
{

}

WADLoader::~WADLoader()
{
    delete[] m_WADData;
    m_WADData = NULL;
}

bool WADLoader::LoadWAD()
{
    if (!OpenAndLoad())
    {
        return false;
    }

    if (!ReadDirectories())
    {
        return false;
    }
    
    return true;
}

bool WADLoader::OpenAndLoad()
{
    std::cout << "Info: Loading WAD File: " << m_WADFilePath << std::endl;

    m_WADFile.open(m_WADFilePath, std::ifstream::binary);
    if (!m_WADFile.is_open())
    {
        std::cout << "Failed to Open WAD File: " << m_WADFilePath << std::endl;
        return false;
    }

    m_WADFile.seekg(0, m_WADFile.end);
    size_t length = m_WADFile.tellg();

    if (m_WADData)
    {
        delete[] m_WADData;
        m_WADData = NULL;
    }

    m_WADData = new uint8_t[length];
    if (m_WADData == NULL)
    {
        std::cout << "Failed to allocate memory for WAD file of size " << length << std::endl;
        return false;
    }

    m_WADFile.seekg(std::ifstream::beg);
    m_WADFile.read((char*)m_WADData, length);


    std::cout << "Info: Loading Complete" << std::endl;
    std::cout << std::endl << std::endl;
    m_WADFile.close();

    return true;
}

bool WADLoader::ReadDirectories()
{
    std::cout << "Info: Loading Directories" <<std::endl;
    std::cout << std::endl;

    WADReader reader;
    Header header;
    reader.ReadHeaderData(m_WADData, 0, header);

    std::cout << header.WADType << std::endl;
    std::cout << header.DirectoryCount << std::endl;
    std::cout << header.DirectoryOffset << std::endl;
    std::cout << std::endl << std::endl;

    Directory directory;

    for (unsigned int i = 0; i < header.DirectoryCount; i++)
    {
        reader.ReadDirectoryData(m_WADData, header.DirectoryOffset, directory);

        std::cout << directory.LumpOffset << std::endl;
        std::cout << directory.LumpSize << std::endl;
        std::cout << directory.LumpName << std::endl;
        std::cout << std::endl;
    }

    std::cout << "Info: Finished Loading Directories" << std::endl;
    return true;
}