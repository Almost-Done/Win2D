#include "pch.h"
#include <brushes/CanvasLinearGradientBrush.h>

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

    auto renderTarget = ABI::Microsoft::Graphics::Canvas::CanvasRenderTarget::CreateNew(
        device, width, height, dpi, pixelFormat, alphaMode);

    if (!renderTarget) {
        return E_FAIL;
    }

    *renderTargetUnknown = renderTarget.Detach();
    return S_OK;
}

STDAPI getCanvasTextFormat(void** canvasTextFormatUnknown)
{
    auto canvasTextFormat = Make<ABI::Microsoft::Graphics::Canvas::CanvasTextFormat>();
    if (!canvasTextFormat) {
        return E_FAIL;
    }

    *canvasTextFormatUnknown = canvasTextFormat.Detach();
    return S_OK;
}

STDAPI getCanvasLinearGradientBrush(void* rendererUnknown,
                                    ABI::Microsoft::Graphics::Canvas::Brushes::CanvasGradientStop* stops,
                                    unsigned int stopCount,
                                    void** canvasLinearGradientBrushUnknown)
{
    auto linearGradientBrushFactory =
        Make<ABI::Microsoft::Graphics::Canvas::Brushes::CanvasLinearGradientBrushFactory>();

    auto renderer = reinterpret_cast<ABI::Microsoft::Graphics::Canvas::CanvasRenderTarget*>(rendererUnknown);

    ComPtr<ICanvasLinearGradientBrush> linearGradientBrush;
    if (FAILED(linearGradientBrushFactory->CreateWithStops(renderer, stopCount, stops, &linearGradientBrush))) {
        return E_FAIL;
    }

    *canvasLinearGradientBrushUnknown = linearGradientBrush.Detach();
    return S_OK;
}