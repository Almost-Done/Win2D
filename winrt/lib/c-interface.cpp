#include "pch.h"
#include <brushes/CanvasLinearGradientBrush.h>
#include <geometry/CanvasPathBuilder.h>
#include <geometry/CanvasGeometry.h>
#include <text/CanvasTextLayout.h>

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

STDAPI createCanvasBitmapFromBytes(void* rendererUnknown,
                                   unsigned int byteCount,
                                   unsigned char* bytes,
                                   int width,
                                   int height,
                                   ABI::Windows::Graphics::DirectX::DirectXPixelFormat pixelFormat,
                                   void** canvasBitmapUnknown)
{
    auto renderer = reinterpret_cast<ABI::Microsoft::Graphics::Canvas::CanvasRenderTarget*>(rendererUnknown);

    auto canvasFactory = Make<ABI::Microsoft::Graphics::Canvas::CanvasBitmapFactory>();
    if (!canvasFactory) {
        return E_FAIL;
    }

    ABI::Microsoft::Graphics::Canvas::ICanvasBitmap* canvasBitmapPtr = nullptr;
    const auto result =
        canvasFactory->CreateFromBytes(renderer, byteCount, bytes, width, height, pixelFormat, &canvasBitmapPtr);

    *canvasBitmapUnknown = canvasBitmapPtr;

    return result;
}

STDAPI getCanvasPathBuilder(void* sessionUnknown, void** canvasPathBuilderUnknown)
{
    auto session = reinterpret_cast<ABI::Microsoft::Graphics::Canvas::CanvasDrawingSession*>(sessionUnknown);

    auto canvasPathBuilderFactory = Make<ABI::Microsoft::Graphics::Canvas::CanvasPathBuilderFactory>();
    if (!canvasPathBuilderFactory) {
        return E_FAIL;
    }

    ABI::Microsoft::Graphics::Canvas::ICanvasPathBuilder* canvasPathBuilder;
    if (FAILED(canvasPathBuilderFactory->Create(session, &canvasPathBuilder))) {
        return E_FAIL;
    }

    *canvasPathBuilderUnknown = canvasPathBuilder;
    return S_OK;
}

STDAPI getCanvasTextLayout(void* sessionUnknown,
	const wchar_t* text,
	void* canvasTextFormatUnknown,
	float width,
	float height,
	void** canvasPathBuilderUnknown)
{
	auto session = reinterpret_cast<ABI::Microsoft::Graphics::Canvas::CanvasDrawingSession*>(sessionUnknown);
	auto canvasTextFormat = reinterpret_cast<ABI::Microsoft::Graphics::Canvas::CanvasTextFormat*>(canvasTextFormatUnknown);

	auto result = ABI::Microsoft::Graphics::Canvas::Text::CanvasTextLayout::CreateNew(session, HStringReference(text).Get(), canvasTextFormat, width, height);

	*canvasPathBuilderUnknown = result.Detach();
	
	return S_OK;
}

STDAPI getCanvasStrokeStyle(void** canvasStrokeStyleUnknown)
{
	auto canvasStrokeStyle = Make<ABI::Microsoft::Graphics::Canvas::CanvasStrokeStyle>();
    if (!canvasStrokeStyle) {
        return E_FAIL;
    }

    *canvasStrokeStyleUnknown = canvasStrokeStyle.Detach();
    return S_OK;
}

STDAPI canvasGeometryCreatePath(void* pathUnknown, void** canvasGeometryUnknown)
{
	auto canvasGeometryFactory = Make<ABI::Microsoft::Graphics::Canvas::Geometry::CanvasGeometryFactory>();
    if (!canvasGeometryFactory) {
        return E_FAIL;
    }

	auto path = reinterpret_cast<ABI::Microsoft::Graphics::Canvas::ICanvasPathBuilder*>(pathUnknown);

	ABI::Microsoft::Graphics::Canvas::ICanvasGeometry* canvasGeometry;
	canvasGeometryFactory->CreatePath(path, &canvasGeometry);

    *canvasGeometryUnknown = canvasGeometry;
    return S_OK;
}