#pragma once
#include <Geode/DefaultInclude.hpp>

#define MEMBERBYOFFSET(type, class, offset) *reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(class) + offset)
#define MBO MEMBERBYOFFSET //lol

using namespace geode::prelude;