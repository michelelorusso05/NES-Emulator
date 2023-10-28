#pragma once

#include <cstdint>
#include <string>
#include <fstream>
#include <vector>

#include "mappers/mapper000.hpp"
#include "mappers/mapper001.hpp"
#include "mappers/mapper002.hpp"
#include "mappers/mapper003.hpp"
#include "mappers/mapper004.hpp"
#include "mappers/mapper007.hpp"
#include "mappers/mapper009.hpp"
#include "mappers/mapper011.hpp"
#include "mappers/mapper028.hpp"
#include "mappers/mapper066.hpp"
#include "mappers/mapper105.hpp"

const static uint16_t supportedMappers[] = 
{
        0,   1,   2,   3,   4,   7,   9,  11,
       28,  66, 105
};

class Cartridge 
{
public:
    struct iNesHeader 
    {
        char headerSignature[4];
        uint8_t prgRomBanks;
        uint8_t chrRomBanks;
        uint8_t mapperLoAndFlags6;
        uint8_t mapperHiAndFlags7;
        uint8_t prgRamSize;
        uint8_t tvSystem;
        uint8_t tvSystemUnofficial;

        char unused[5];
    };


    static bool IsMapperImplemented(uint16_t mapper)
    {
        for (uint16_t i = 0; i < sizeof(supportedMappers) >> 1; i++)
        {
            if (supportedMappers[i] == mapper)
                return true;
        }
        return false;
    }

    bool IsMapperSupported()
    {
        return isMapperSupported;
    }

    Cartridge(std::string filepath)
    {
        int pos;
        for (pos = filepath.size() - 1; pos >= 0; pos--)
        {
            if (filepath.at(pos) == '/' || filepath.at(pos) == '\\')
                break;
        }

        filename = filepath.substr(pos + 1, filepath.size() - pos - 5);
        if (filename.size() > 20)
            filename = filename.substr(0, 18).append("...");

        std::ifstream inputStream;
        inputStream.open(filepath, std::ifstream::binary);

        if (!inputStream.is_open())
        {
            inputStream.close();
            isRomValid = false;
            return;
        }

        inputStream.read((char*) &header, 16);

        // NES followed by EOF 0x1A
        isRomValid = header.headerSignature[0] == 0x4E &&
                     header.headerSignature[1] == 0x45 &&
                     header.headerSignature[2] == 0x53 &&
                     header.headerSignature[3] == 0x1A;

        if (!isRomValid)
        {
            inputStream.close();
            return;
        }

        // Skip trainer data, if present
        if (header.mapperHiAndFlags7 & 0b00000100)
            inputStream.seekg(512, std::ios_base::cur);

        prgRom.resize(header.prgRomBanks * 16 * 1024);
        inputStream.read((char*) prgRom.data(), prgRom.size());

        if (header.chrRomBanks == 0)
        {
            // Treat as RAM
            chrRom.resize(8 * 1024);
        }
        else
        {
            chrRom.resize(header.chrRomBanks * 8 * 1024);
            inputStream.read((char*) chrRom.data(), chrRom.size());
        }

        inputStream.close();

        mapperID = (header.mapperLoAndFlags6 >> 4) | (header.mapperHiAndFlags7 & 0b11110000);
        Mapper::Arrangement arr = header.mapperLoAndFlags6 & 0x01 ? Mapper::Arrangement::HORIZONTAL : Mapper::Arrangement::VERTICAL;

        switch (mapperID)
        {
            case 0:
                mapper = new Mapper000(header.prgRomBanks, header.chrRomBanks, arr, &prgRam);
                break;
            case 1:
                mapper = new Mapper001(header.prgRomBanks, header.chrRomBanks, arr, &prgRam);
                break;
            case 2:
                mapper = new Mapper002(header.prgRomBanks, header.chrRomBanks, arr);
                break;
            case 3:
                mapper = new Mapper003(header.prgRomBanks, header.chrRomBanks, arr);
                break;
            case 4:
                mapper = new Mapper004(header.prgRomBanks, header.chrRomBanks, arr, &prgRam);
                break;
            case 7:
                mapper = new Mapper007(header.prgRomBanks, header.chrRomBanks, arr);
                break;
            case 9:
                mapper = new Mapper009(header.prgRomBanks, header.chrRomBanks, arr, &prgRam);
                break;
            case 11:
                mapper = new Mapper011(header.prgRomBanks, header.chrRomBanks, arr);
                break;
            case 28:
                mapper = new Mapper028(header.prgRomBanks, header.chrRomBanks, arr);
                break;
            case 34:
                mapper = new Mapper028(header.prgRomBanks, header.chrRomBanks, arr);
                break;
            case 66:
                mapper = new Mapper066(header.prgRomBanks, header.chrRomBanks, arr);
                break;
            case 105:
                mapper = new Mapper105(header.prgRomBanks, header.chrRomBanks, arr, &prgRam);
                break;
            default:
                mapper = new Mapper000(header.prgRomBanks, header.chrRomBanks, arr, &prgRam);
                break;
        }

        isVsGame = header.mapperHiAndFlags7 & 0x01;
        hasSave = header.mapperLoAndFlags6 & 0x02;
        isMapperSupported = IsMapperImplemented(mapperID);

        prgRam.resize(32 * 1024);
        
        if (hasSave)
        {
            std::ifstream saveDataStream;
            saveDataStream.open(filepath.append(".sav", std::ifstream::binary));
            if (saveDataStream.is_open())
                saveDataStream.read((char*) prgRam.data(), prgRam.size());

            saveDataStream.close();

            savefilePath = filepath;
        }
    }
    ~Cartridge()
    {
        delete mapper;

        if (savefilePath.length() > 0)
        {
            std::ofstream saveDataStream;
            saveDataStream.open(savefilePath, std::ofstream::binary);

            if (saveDataStream.is_open())
                saveDataStream.write((char *)prgRam.data(), prgRam.size());

            saveDataStream.close();
        }
    }

    bool cpuRead(uint16_t addr, uint8_t& data) 
    {
        if (mapper->prgBankRead(addr, mapAddr, data))
        {
            if (mapAddr != DATA_UNMAPPED_BUT_SET)
                data = prgRom.at(mapAddr & (prgRom.size() - 1));
            return true;
        }
        return false;
    }
    bool cpuWrite(uint16_t addr, uint8_t data)
    {
        if (mapper->prgBankWrite(addr, mapAddr, data))
        {
            if (mapAddr != DATA_UNMAPPED_BUT_SET)
                prgRom.at(mapAddr & (prgRom.size() - 1)) = data;
            return true;
        }
        return false;
    }
    bool ppuRead(uint16_t addr, uint8_t& data)
    {
        if (mapper->chrBankRead(addr, mapAddr, data))
        {
            if (mapAddr != DATA_UNMAPPED_BUT_SET)
                data = chrRom.at(mapAddr & (chrRom.size() - 1));
            return true;
        }
        return false;
    }
    bool ppuWrite(uint16_t addr, uint8_t data)
    {
        if (mapper->chrBankWrite(addr, mapAddr, data))
        {            
            if (mapAddr != DATA_UNMAPPED_BUT_SET)
                chrRom.at(mapAddr & (chrRom.size() - 1)) = data;
            return true;
        }
        return false;
    }

    void reset()
    {
        mapper->reset();
    }

    bool checkIRQ()
    {
        return mapper->checkIRQ();
    }
    void resetIRQ()
    {
        mapper->resetIRQ();
    }
    void scanlineCallback()
    {
        mapper->scanlineCallback();
    }

    bool IsRomValid()
    {
        return isRomValid;
    }

    Mapper::Arrangement GetArrangement()
    {
        return mapper->getArrangement();
    }
    bool ArrangementUpdateRequired()
    {
        return mapper->ArrangementUpdatedRequired();
    }

    std::string GetFilename()
    {
        return filename;
    }

    std::string GetMapperName()
    {
        return mapper->getMapperName();
    }

    bool IsVsGame()
    {
        return isVsGame;
    }

    bool IsPALGame()
    {
        return isPalGame;
    }

    bool HasSave()
    {
        return hasSave;
    }

    void sendExternalEvent(uint8_t ev)
    {
        mapper->receiveExternalEvent(ev);
    }

    iNesHeader header;
    uint16_t mapperID;
    Mapper* mapper;

private:
    std::string filename;

    bool isRomValid = true;
    bool isMapperSupported;

    std::vector<uint8_t> prgRom;
    std::vector<uint8_t> chrRom;
    std::vector<uint8_t> prgRam;

    uint32_t mapAddr;

    bool isVsGame;
    bool isPalGame;
    bool hasSave;

    std::string savefilePath;
};