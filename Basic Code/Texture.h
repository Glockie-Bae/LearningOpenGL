#pragma once

#include"Shader.h"

class Texture {
private:
	unsigned int m_Render_ID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
public:
	Texture(const std::string& file_path);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void UnBind() const;

	void SetParameteri(unsigned int target, unsigned int pname, int param);
	
	inline int GetWidth() const { return m_Width; };
	inline int GetHeight() const { return m_Height; };
	inline unsigned int GetTextureID() const { return m_Render_ID; };
};