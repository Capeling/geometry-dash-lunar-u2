#pragma once
#include <Geode/Geode.hpp>

namespace PatchTool {
    void patch(int address, geode::ByteVector const& data) {
        geode::Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + address), data).unwrap();
    }
    void patchCocos(int address, geode::ByteVector const& data) {
        #ifndef GEODE_IS_ANDROID
        geode::Mod::get()->patch(reinterpret_cast<void*>(geode::base::getCocos() + address), data);
        #endif
    }
    std::vector<unsigned char> intToBytes(int value) {
        std::vector<unsigned char> result;
        result.push_back(value & 0x000000ff);
        result.push_back((value & 0x0000ff00) >> 8);
        result.push_back((value & 0x00ff0000) >> 16);
        result.push_back((value & 0xff000000) >> 24);
        return result;
    }
}