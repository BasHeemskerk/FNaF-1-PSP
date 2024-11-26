#pragma once

#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>


#include <pspgu.h>
#include <pspgum.h>

#include <pspdisplay.h>
#include <stdint.h>

#include <pspmoduleinfo.h>

#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <functional>

extern "C" {
    #include "graphics.h"
    #include "image.h"
    #include "vram.h"
    #include "include/oslib.h"
}

using namespace std;

template <typename T>
std::string toString(const T& value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}