#include "WADReader.h"

WADReader::WADReader()
{

}

WADReader::~WADReader()
{

}

uint16_t WADReader::Read2Bytes(const uint8_t* WADData, int offset)
{
    uint16_t ReadValue;
    std::memcpy(&ReadValue, WADData + offset, sizeof(uint16_t));
    return ReadValue;
}

uint32_t WADReader::Read4Bytes(const uint8_t* WADData, int offset)
{
    uint32_t ReadValue;
    std::memcpy(&ReadValue, WADData + offset, sizeof(uint32_t));
    return ReadValue;
}

void WADReader::ReadHeaderData(const uint8_t* WADData, int offset, Header& header)
{
    for (int i = 0; i < 4; i++)
    {
        header.WADType[i] = WADData[offset + i];
    }
    header.WADType[4] = '\n';

    header.DirectoryCount = Read4Bytes(WADData, offset + 4);
    header.DirectoryOffset = Read4Bytes(WADData, offset + 8);
}

void WADReader::ReadDirectoryData(const uint8_t* WADData, int offset, Directory& directory)
{
    directory.LumpOffset = Read4Bytes(WADData, offset);
    directory.LumpSize = Read4Bytes(WADData, offset + 4);

    for (int i = 0; i < 8; i++)
    {
        directory.LumpName[i] = WADData[WADData, offset + 8 + i];
    }
    directory.LumpName[8] = '\n';
}