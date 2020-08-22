#pragma once

#include "ControlContainer.h"
#include "ui/layout/LayoutInflater.h"

namespace Ghurund::UI {
    class ScrollView :public ControlContainer {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(ScrollView);
        inline static const BaseConstructor& CONSTRUCTOR = NoArgsConstructor<ScrollView>();

    public:
        float scroll = 0.0f;

        virtual void draw(Canvas& canvas) override {
            canvas.save();
            canvas.clipRect(position.x, position.y, size.x, size.y);
            canvas.translate(0, scroll);
            __super::draw(canvas);
            canvas.restore();
        }

        virtual void onLayout(float x, float y, float width, float height) override {
            if (Child)
                Child->layout(0, 0, width, Child->MeasuredSize.y);
        }

        virtual bool dispatchMouseButtonEvent(const MouseButtonEventArgs& event) {
            return __super::dispatchMouseButtonEvent(event.translate(0, -scroll));
        }

        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event) {
            return __super::dispatchMouseMotionEvent(event.translate(0, -scroll));
        }

        virtual bool dispatchMouseWheelEvent(const MouseWheelEventArgs& event) {
            return onMouseWheelEvent(event);
        }

        virtual bool onMouseWheelEvent(const MouseWheelEventArgs& event) {
            if (event.Wheel == MouseWheel::VERTICAL && Child) {
                scroll = std::max(Size.y - Child->Size.y, std::min(scroll + event.Delta, 0.0f));
                repaint();
            }
            return false;
        }

        inline static const Ghurund::Type& TYPE = TypeBuilder<ScrollView>(NAMESPACE_NAME, CLASS_NAME)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }

        inline static ScrollView* inflate(LayoutInflater& inflater, json& json) {
            ScrollView* scrollView = ghnew ScrollView();
            inflater.loadChild(scrollView, json);
            inflater.loadControl(scrollView, json);
            return scrollView;
        }
    };
}