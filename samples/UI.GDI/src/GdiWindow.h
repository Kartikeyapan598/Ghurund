#pragma once

#include "core/window/SystemWindow.h"
#include "core/input/Input.h"
#include "ui/RootView.h"
#include "ui/gdi/UIContext.h"
#include "ui/gdi/Canvas.h"
#include "ui/gdi/Gdi.h"

namespace Samples {
    using namespace Ghurund::Core;
    using namespace Ghurund::UI;
    using namespace Ghurund::UI::GDI;

    class GdiWindow: public Ghurund::Core::SystemWindow {
#pragma region reflection
    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();
        virtual const Ghurund::Core::Type& getType() const override { return TYPE; }
#pragma endregion

    private:
        RootView* rootView = nullptr;
        UIContext* uiContext = nullptr;
        Canvas* canvas = nullptr;
        ResourceManager* resourceManager = nullptr;
        Gdi gdi;

    protected:
        virtual bool onSizeChangingEvent(const IntSize& size) override {
            __super::onSizeChangingEvent(size);
            return true;
        }

        virtual bool onSizeChangedEvent() override {
            __super::onSizeChangedEvent();
            return true;
        }

        virtual bool onFocusedChangedEvent() override;

    public:
        GdiWindow(Ghurund::Core::Timer& timer);

        ~GdiWindow() {
            uninit();
        }

        virtual void init(WindowManager& windowManager);

        void uninit();

        virtual bool onKeyEvent(const KeyEventArgs& args) override;

        virtual bool onMouseButtonEvent(const MouseButtonEventArgs& args) override;

        virtual bool onMouseMotionEvent(const MouseMotionEventArgs& args) override;

        virtual bool onMouseWheelEvent(const MouseWheelEventArgs& args) override;

        virtual void update(const uint64_t time) override;

        virtual Status paint() override;
    };
}