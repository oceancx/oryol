//------------------------------------------------------------------------------
//  TextureSetup.cc
//------------------------------------------------------------------------------
#include "Pre.h"
#include "TextureSetup.h"

namespace Oryol {

//------------------------------------------------------------------------------
TextureSetup::TextureSetup() :
IOLane(0),
Width(0),
Height(0),
RelWidth(0.0f),
RelHeight(0.0f),
ColorFormat(PixelFormat::RGBA8),
DepthFormat(PixelFormat::None),
WrapU(TextureWrapMode::Repeat),
WrapV(TextureWrapMode::Repeat),
WrapW(TextureWrapMode::Repeat),
MagFilter(TextureFilterMode::Nearest),
MinFilter(TextureFilterMode::Nearest),
shouldSetupLoadAsync(false),
shouldSetupFromImageFileData(false),
shouldSetupFromPixelData(false),
shouldSetupAsRenderTarget(false),
isRelSizeRenderTarget(false),
hasSharedDepth(false),
hasMipMaps(false),
Locator(Locator::NonShared()) {
    // empty
}

//------------------------------------------------------------------------------
TextureSetup
TextureSetup::FromFileAsync(const class Locator& loc, Id placeholder) {
    TextureSetup setup;
    setup.shouldSetupLoadAsync = true;
    setup.Locator = loc;
    setup.Placeholder = placeholder;
    return setup;
}

//------------------------------------------------------------------------------
TextureSetup
TextureSetup::RenderTarget(int32 w, int32 h) {
    o_assert(w > 0);
    o_assert(h > 0);

    TextureSetup setup;
    setup.shouldSetupAsRenderTarget = true;
    setup.Width = w;
    setup.Height = h;
    setup.WrapU = TextureWrapMode::ClampToEdge;
    setup.WrapV = TextureWrapMode::ClampToEdge;
    setup.WrapW = TextureWrapMode::InvalidTextureWrapMode;
    return setup;
}

//------------------------------------------------------------------------------
TextureSetup
TextureSetup::FromImageFileData(TextureSetup bluePrint) {
    TextureSetup setup(bluePrint);
    setup.shouldSetupFromImageFileData = true;
    return setup;
}

//------------------------------------------------------------------------------
TextureSetup
TextureSetup::FromPixelData(int32 w, int32 h, bool hasMipMaps, PixelFormat::Code fmt) {
    o_assert(w > 0);
    o_assert(h > 0);
    o_assert(PixelFormat::IsValidTextureColorFormat(fmt));
    o_assert(!PixelFormat::IsCompressedFormat(fmt));
    
    TextureSetup setup;
    setup.shouldSetupFromPixelData = true;
    setup.hasMipMaps = hasMipMaps;
    setup.Width = w;
    setup.Height = h;
    setup.ColorFormat = fmt;
    return setup;
}

//------------------------------------------------------------------------------
TextureSetup
TextureSetup::RelSizeRenderTarget(float32 relWidth, float32 relHeight) {
    o_assert(relWidth > 0.0f);
    o_assert(relHeight > 0.0f);

    TextureSetup setup;
    setup.shouldSetupAsRenderTarget = true;
    setup.isRelSizeRenderTarget = true;
    setup.RelWidth = relWidth;
    setup.RelHeight = relHeight;
    setup.WrapU = TextureWrapMode::ClampToEdge;
    setup.WrapV = TextureWrapMode::ClampToEdge;
    setup.WrapW = TextureWrapMode::InvalidTextureWrapMode;
    return setup;
}

//------------------------------------------------------------------------------
TextureSetup
TextureSetup::SharedDepthRenderTarget(const GfxId& depthRenderTarget) {
    o_assert(depthRenderTarget.IsValid() && depthRenderTarget.Id().Type() == ResourceType::Texture);

    TextureSetup setup;
    setup.shouldSetupAsRenderTarget = true;
    setup.hasSharedDepth = true;
    setup.DepthRenderTarget = depthRenderTarget;
    setup.WrapU = TextureWrapMode::ClampToEdge;
    setup.WrapV = TextureWrapMode::ClampToEdge;
    setup.WrapW = TextureWrapMode::InvalidTextureWrapMode;
    return setup;
}

//------------------------------------------------------------------------------
bool
TextureSetup::ShouldSetupFromFileAsync() const {
    return this->shouldSetupLoadAsync;
}

//------------------------------------------------------------------------------
bool
TextureSetup::ShouldSetupFromImageFileData() const {
    return this->shouldSetupFromImageFileData;
}

//------------------------------------------------------------------------------
bool
TextureSetup::ShouldSetupFromPixelData() const {
    return this->shouldSetupFromPixelData;
}

//------------------------------------------------------------------------------
bool
TextureSetup::ShouldSetupAsRenderTarget() const {
    return this->shouldSetupAsRenderTarget;
}

//------------------------------------------------------------------------------
bool
TextureSetup::IsRelSizeRenderTarget() const {
    return this->isRelSizeRenderTarget;
}

//------------------------------------------------------------------------------
bool
TextureSetup::HasDepth() const {
    return this->hasSharedDepth || (this->DepthFormat != PixelFormat::InvalidPixelFormat);
}

//------------------------------------------------------------------------------
bool
TextureSetup::HasSharedDepth() const {
    return this->hasSharedDepth;
}

//------------------------------------------------------------------------------
bool
TextureSetup::HasMipMaps() const {
    return this->hasMipMaps;
}

} // namespace Oryol
