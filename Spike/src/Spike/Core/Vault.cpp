/*
                               SPIKE ENGINE
               This file is licensed under the SPIKE LICENSE
                          --Spike Source Code--

         Copyright 2021 - SpikeTechnologies - All Rights Reserved

File Name      : Vault
File Type      : cpp
File created on: 2021/02/04
File created by: Fahim Fuad
Other editors  : None
Github repository : https://github.com/FahimFuad/Spike
 
0.This software is provided 'AS-IS', without any express or implied warranty.
  In no event will the authors or contributors be held liable for any damages
  arising from the use of this software.

1.The origin of this software must not be misrepresented; you must not claim
  that you wrote the original software.
 
2.You MUST NOT change or alter this file. This excludes the contributions done
  by people. Changing this file is PERFECTLY LEGAL if you are contributing.

3.THIS NOTICE MAY NOT BE REMOVED OR ALTERED FROM ANY SOURCE DISTRIBUTION.
*/
/* [Spike] All the assets are stored in the Vault [Spike] */
#include "spkpch.h"
#include "Vault.h"
#include <filesystem>

namespace Spike
{
    String Vault::s_ProjectPath = "";
    String Vault::s_AssetPath = "";
    std::unordered_map<String, Ref<Shader>>         Vault::s_Shaders;
    std::unordered_map<String, Ref<Texture2D>>      Vault::s_Textures;

    void Vault::Init(const String& projectPath)
    {
        s_ProjectPath = projectPath;
        auto path = s_ProjectPath + "/Spike Vault";
        if (std::filesystem::create_directory(path) || std::filesystem::exists(path))
            s_AssetPath = path;
    }

    Ref<Shader> Vault::CreateAndSubmitShader(const String& path)
    {
        if (s_Shaders.count(path) == 0)
        {
            s_Shaders[path] = Shader::Create(path); /* [Spike] We store the shader in our cache [Spike] */
            return s_Shaders[path];
        }
        return s_Shaders[path]; /* [Spike] Gives access to the second element, which is our cached shader [Spike] */
    }

    Ref<Texture2D> Vault::CreateAndSubmitTexture2D(const String& path)
    {
        if (s_Textures.count(path) == 0)
        {
            s_Textures[path] = Texture2D::Create(path); /* [Spike] We store the texture in our cache [Spike] */
            return s_Textures[path];
        }
        return s_Textures[path]; /* [Spike] Gives access to the second element, which is our cached texture [Spike] */
    }

    Ref<Texture2D> Vault::CreateAndSubmitTexture2D(const char* path, bool flipVertically, bool srgb)
    {
        if (s_Textures.count(String(path)) == 0)
        {
            s_Textures[path] = Texture2D::Create(path, flipVertically, srgb); /* [Spike] We store the texture in our cache [Spike] */
            return s_Textures[path];
        }
        return s_Textures[path]; /* [Spike] Gives access to the second element, which is our cached texture [Spike] */
    }

    Ref<Shader> Vault::SubmitShader(Ref<Shader>& shader)
    {
        auto filepath = shader->GetFilepath();
        for (auto& cacheShader : s_Shaders) /* [Spike] Blocks loading same shader twice [Spike] */
        {
            if (cacheShader.first == filepath)
                return cacheShader.second;
        }
        s_Shaders[filepath] = shader;
        return s_Shaders[filepath];
    }

    Ref<Texture2D> Vault::SubmitTexture2D(Ref<Texture2D>& texture)
    {
        auto filepath = texture->GetFilepath();
        for (auto& cacheTexture : s_Textures) /* [Spike] Blocks loading same texture twice [Spike] */
        {
            if (cacheTexture.first == filepath)
                return cacheTexture.second;
        }
        s_Textures[filepath] = texture;
        return s_Textures[filepath];
    }

    Ref<Shader> Vault::GetShaderFromCache(const String& nameWithExtension)
    {
        for (auto& shader : s_Shaders)
        {
            if (GetNameWithExtension(shader.first) == nameWithExtension)
                return shader.second;
        }
        SPK_CORE_LOG_WARN("[Spike::Vault::GetShader(const char* path)]::Shader not found in cache!");
        return nullptr;
    }

    Ref<Texture> Vault::GetTexture2DFromCache(const String& nameWithExtension)
    {
        for (auto& texture : s_Textures)
        {
            if (GetNameWithExtension(texture.first) == nameWithExtension)
                return texture.second;
        }
        SPK_CORE_LOG_WARN("[Spike::Vault::GetTexture(const char* path)]::Texture not found in cache!");
        return nullptr;
    }

    void Vault::Shutdown()
    {
        s_AssetPath.clear();
        s_ProjectPath.clear();
        s_Textures.clear();
        s_Shaders.clear();
    }

    String Vault::GetNameWithoutExtension(const String& assetFilepath)
    {
        String name;
        auto lastSlash = assetFilepath.find_last_of("/\\");
        lastSlash = lastSlash == String::npos ? 0 : lastSlash + 1;
        auto lastDot = assetFilepath.rfind('.');
        auto count = lastDot == String::npos ? assetFilepath.size() - lastSlash : lastDot - lastSlash;
        name = assetFilepath.substr(lastSlash, count);
        return name;

    }

    bool Vault::Exists(const String& nameWithExtension, ResourceType type)
    {
        switch (type)
        {
            case Spike::ResourceType::_Shader:
                {
                    for (auto& shader : s_Shaders)
                    {
                        if (GetNameWithExtension(shader.first) == nameWithExtension) return true;
                    }
                }
            case Spike::ResourceType::_Texture:
                {
                    for (auto& texture : s_Textures)
                    {
                        if (GetNameWithExtension(texture.first) == nameWithExtension) return true;
                    }
                }
            case Spike::ResourceType::_Text:
                return false; //TODO
        }
        return false;
    }

    bool Vault::Exists(const char* path, ResourceType type)
    {
        switch (type)
        {
            case Spike::ResourceType::_Shader:
                {
                    for (auto& shader : s_Shaders)
                    {
                        if (shader.first == path) return true;
                    }
                }
            case Spike::ResourceType::_Texture:
                {
                    for (auto& texture : s_Textures)
                    {
                        if (texture.first == path) return true;
                    }
                }
            case Spike::ResourceType::_Text:
                return false; //TODO
        }
        return false;

    }
    std::vector<Ref<Shader>> Vault::GetAllShaders()
    {
        std::vector<Ref<Shader>> shaders;
        shaders.resize(s_Shaders.size());
        for (auto& shader : s_Shaders)
        {
            shaders.emplace_back(shader.second);
        }
        return shaders;
    }

    std::vector<Ref<Texture>> Vault::GetAllTextures()
    {
        std::vector<Ref<Texture>> textures;
        textures.resize(textures.size());
        for (auto& texture : s_Textures)
        {
            textures.emplace_back(texture.second);
        }
        return textures;
    }

    String Vault::GetExtension(const String& assetFilepath)
    {
        return std::filesystem::path(assetFilepath).extension().string();
    }

    String Vault::GetNameWithExtension(const String& assetFilepath)
    {
        return std::filesystem::path(assetFilepath).filename().string();
    }
}