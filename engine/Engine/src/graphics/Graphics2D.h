#pragma once

#include "core/Pointer.h"
#include "ui/font/FontCollectionLoader.h"

#include <dxgi1_6.h>
#include <d2d1_3.h>
#include <dwrite_3.h>
#include <d3d11on12.h>
#include <wrl.h>

namespace Ghurund {
    class Graphics;
    class RenderTarget;

    using Microsoft::WRL::ComPtr;
    using namespace Ghurund::UI;

    enum class UIState {
        RECORDING, IDLE
    };

    class Graphics2D {
    private:
        ComPtr<ID2D1DeviceContext5> deviceContext;
        ComPtr<ID3D11DeviceContext> m_d3d11DeviceContext;
        ComPtr<ID3D11On12Device> m_d3d11On12Device;
        ComPtr<IDWriteFactory5> m_dwriteFactory;
        ComPtr<ID2D1Factory6> m_d2dFactory;
        ComPtr<ID2D1Device5> m_d2dDevice;
        UIState state = UIState::IDLE;

    public:
        ~Graphics2D() {
            uninit();
        }

        inline ID2D1Device5* getDevice() {
            return m_d2dDevice.Get();
        };

        __declspec(property(get = getDevice)) ID2D1Device5* Device;

        inline ID2D1DeviceContext5& getDeviceContext() {
            return *deviceContext.Get();
        };

        __declspec(property(get = getDeviceContext)) ID2D1DeviceContext5& DeviceContext;

        inline ID3D11On12Device* getDevice11() {
            return m_d3d11On12Device.Get();
        };

        __declspec(property(get = getDevice11)) ID3D11On12Device* Device11;

        inline ID2D1Factory6* getFactory() {
            return m_d2dFactory.Get();
        };

        __declspec(property(get = getFactory)) ID2D1Factory6* Factory;

        inline IDWriteFactory5* getDWriteFactory() {
            return m_dwriteFactory.Get();
        };

        __declspec(property(get = getDWriteFactory)) IDWriteFactory5* DWriteFactory;

        inline UIState getState() const {
            return state;
        }

        __declspec(property(get = getState)) UIState State;

        Status init(Graphics& graphics);

        void uninit();

        Status beginPaint(RenderTarget& target);

        Status endPaint(RenderTarget& target);

        void flush() {
            m_d3d11DeviceContext->Flush();
        }
    };
}

namespace Ghurund::Core {
    template<>
    const Type& getType<Graphics2D>();
}