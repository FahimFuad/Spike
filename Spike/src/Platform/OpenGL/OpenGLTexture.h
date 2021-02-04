/*
                               SPIKE ENGINE
               This file is licensed under the SPIKE LICENSE
                          --Spike Source Code--

         Copyright 2021 - SpikeTechnologies - All Rights Reserved

File Name      : OpenGLTexture
File Type      : h
File created on: 2021/01/09
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

3. THIS NOTICE MAY NOT BE REMOVED OR ALTERED FROM ANY SOURCE DISTRIBUTION.
*/
#pragma once
#include "Spike/Renderer/Texture.h"
#include "Spike/Core/Buffer.h"
#include <glad/glad.h>

namespace Spike
{
    class OpenGLTexture2D : public Texture2D
    {
    public:
        OpenGLTexture2D(uint32_t width, uint32_t height);
        OpenGLTexture2D(const String& path);
        OpenGLTexture2D(const String& path, bool flipVertically, bool srgb);
        virtual ~OpenGLTexture2D();
        virtual String GetName() const override { return m_Name; }
        virtual uint32_t GetWidth() const override { return m_Width; }
        virtual uint32_t GetHeight() const override { return m_Height; }
        virtual uint32_t GetRendererID() const override { return m_RendererID; };
        virtual String GetFilepath() const override { return m_Path; }
        void SetData(void* data, uint32_t size) override;
        virtual void ActivateSlot(uint32_t slot) override;
        virtual void Bind(uint32_t slot = 0) const override;
        virtual void Unbind() const override;
        virtual bool Loaded() override { return m_Loaded; }
        bool operator==(const Texture& other) const override
        {
            return m_RendererID == ((OpenGLTexture2D&)other).m_RendererID;
        }

    private:
        bool m_Loaded = false;
        String m_Path;
        uint32_t m_Width, m_Height;
        RendererID m_RendererID;
        GLenum m_InternalFormat, m_DataFormat;
        String m_Name;
        TextureFormat m_Format;
        TextureWrap m_Wrap = TextureWrap::Clamp;
        bool m_IsHDR = false;
        bool m_Locked = false;
    };
}