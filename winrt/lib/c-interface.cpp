#include "pch.h"

STDAPI getSharedDevice(void** deviceUnknown)
{
    auto canvasDeviceFactory = Make<ABI::Microsoft::Graphics::Canvas::CanvasDeviceFactory>();
    if (!canvasDeviceFactory) {
        return E_FAIL;
    }

    ABI::Microsoft::Graphics::Canvas::ICanvasDevice* devicePtr;
    if (FAILED(canvasDeviceFactory->GetSharedDevice(&devicePtr))) {
        return E_FAIL;
    }

    *deviceUnknown = devicePtr;
    return S_OK;
}

STDAPI getRenderTarget(void* deviceUnknown,
                       float width,
                       float height,
                       float dpi,
                       ABI::Windows::Graphics::DirectX::DirectXPixelFormat pixelFormat,
                       ABI::Microsoft::Graphics::Canvas::CanvasAlphaMode alphaMode,
                       void** renderTargetUnknown)
{
    auto device = reinterpret_cast<ABI::Microsoft::Graphics::Canvas::ICanvasDevice*>(deviceUnknown);

    auto renderTarget =
        ABI::Microsoft::Graphics::Canvas::CanvasRenderTarget::CreateNew(device, width, height, dpi, pixelFormat, alphaMode);

    if (!renderTarget) {
        return E_FAIL;
    }

    *renderTargetUnknown = renderTarget.Detach();
    return S_OK;
}