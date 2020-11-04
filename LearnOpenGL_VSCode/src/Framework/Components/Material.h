#include "Component.h"
#include "Texture.h"
#include "../Shaders/Shader.h"

#include <vector>
#include <string>

using std::vector;

class Material
{
public:
    Material();
    Material(Shader *shader);
    Material(string vertexPath, string fragPath);

    void AddTexture(string target, Texture *texture);
    void RemoveTexture(unsigned int textureId);
    unsigned int GetTextureCount();
    Texture *GetTexture(int index);
    Shader *GetShader();
    ~Material();

private:
    Shader *shader = nullptr;
    vector<Texture *> textureList;
};