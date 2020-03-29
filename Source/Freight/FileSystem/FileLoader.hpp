#pragma once
#include "Freight/pch.hpp"

namespace fr
{
    void LoadFileAsString(const fr::Filepath &fp, String &output);
    void LoadFileAsBytes(const fr::Filepath fp, std::vector<fr::u8> &output);
}