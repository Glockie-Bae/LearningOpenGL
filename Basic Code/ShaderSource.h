#pragma once
#include<string>

class ShaderSource {
public:
    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

public:
    ShaderSource(const std::string& vs, const std::string& fs)
        : VertexSource(vs), FragmentSource(fs) {}
    ShaderSource() {

    }
private:
    std::string VertexSource;
    std::string FragmentSource;
};

