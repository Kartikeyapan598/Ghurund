#pragma once

#include "ControlGroup.h"
#include "ItemAdapter.h"
#include "ItemSource.h"
#include "ui/layout/LayoutManager.h"
#include "ControlPool.h"
#include "AdapterView.h"

namespace Ghurund::UI {
    template<class T = void*, class ControlType = Control>
    requires IsControl<ControlType>
    class RecyclerView:public AdapterView<T, ControlType> {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(RecyclerView);
        inline static const BaseConstructor& CONSTRUCTOR = NoArgsConstructor<RecyclerView<T, ControlType>>();

    public:
        virtual void onDraw(Canvas& canvas) override {
            if (!layoutManager || !items)
                return;

            canvas.save();
            canvas.clipRect(0, 0, Size.width, Size.height);
            auto& scroll = layoutManager->Scroll;
            canvas.translate(scroll.x, scroll.y);
            for (Control* c : Children)
                c->draw(canvas);
            canvas.restore();
        }

        virtual ControlType* getChild(size_t index) {
            ItemAdapter<T, ControlType>* adapter = findAdapter(index);
            ControlType* control = adapter->getControl();
            adapter->bind(*control, items->get(index), index);
            return control;
        }

        virtual void releaseChild(ControlType* control, size_t index) {
            findAdapter(index)->recycleControl(control);
        }

        virtual bool dispatchMouseButtonEvent(const MouseButtonEventArgs& event) {
            if (!layoutManager)
                return false;

            const XMFLOAT2& scroll = layoutManager->Scroll;
            return __super::dispatchMouseButtonEvent(event.translate(-scroll.x, -scroll.y));
        }

        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event) {
            if (!layoutManager)
                return false;

            const XMFLOAT2& scroll = layoutManager->Scroll;
            return __super::dispatchMouseMotionEvent(event.translate(-scroll.x, -scroll.y));
        }

        virtual bool dispatchMouseWheelEvent(const MouseWheelEventArgs& args) {
            if (layoutManager) {
                if (args.Wheel == MouseWheel::VERTICAL) {
                    layoutManager->scrollBy(*this, 0, (float)args.Delta);
                    repaint();
                } else {
                    layoutManager->scrollBy(*this, (float)args.Delta, 0);
                    repaint();
                }
            }

            return OnMouseWheel(args);
        }

        inline static const Ghurund::Type& TYPE = TypeBuilder<RecyclerView>(NAMESPACE_NAME, CLASS_NAME)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}