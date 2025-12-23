#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <string>

struct WAVHeader
{
    char riff[4];             // "RIFF"
    uint32_t chunkSize;
    char wave[4];             // "WAVE"
    char fmt[4];              // "fmt "
    uint32_t subchunk1Size;   // 16 for PCM
    uint16_t audioFormat;     // 1 = PCM, 3 = float
    uint16_t numChannels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
    char data[4];             // "data"
    uint32_t dataSize;
};

bool wavInfo(const std::string &wavFile)
{
    std::ifstream in(wavFile, std::ios::binary);
    if (!in) {
        std::cerr << "Cannot open file: " << wavFile << std::endl;
        return false;
    }

    WAVHeader header;
    in.read(reinterpret_cast<char*>(&header), sizeof(WAVHeader));

    std::cout << "WAV File: " << wavFile << std::endl;
    std::cout << "RIFF Chunk ID: " << std::string(header.riff, 4) << std::endl;
    std::cout << "Chunk Size: " << header.chunkSize << std::endl;
    std::cout << "Format: " << std::string(header.wave, 4) << std::endl;
    std::cout << "Subchunk1 ID: " << std::string(header.fmt, 4) << std::endl;
    std::cout << "Subchunk1 Size: " << header.subchunk1Size << std::endl;
    std::cout << "Audio Format: " << header.audioFormat;
    if (header.audioFormat == 1) std::cout << " (PCM)" << std::endl;
    else if (header.audioFormat == 3) std::cout << " (Float)" << std::endl;
    else std::cout << " (Unknown)" << std::endl;
    std::cout << "Channels: " << header.numChannels << std::endl;
    std::cout << "Sample Rate: " << header.sampleRate << std::endl;
    std::cout << "Byte Rate: " << header.byteRate << std::endl;
    std::cout << "Block Align: " << header.blockAlign << std::endl;
    std::cout << "Bits Per Sample: " << header.bitsPerSample << std::endl;
    std::cout << "Data Chunk ID: " << std::string(header.data, 4) << std::endl;
    std::cout << "Data Size: " << header.dataSize << " bytes" << std::endl;

    // 计算时长
    double duration_sec = static_cast<double>(header.dataSize) / header.byteRate;
    std::cout << "Approx Duration: " << duration_sec << " sec" << std::endl;

    return true;
}

int main()
{
    wavInfo("disagree3.wav");
    return 0;
}
