#pragma once

#include "LayoutManager.h"
#include "ui/Alignment.h"

#include <algorithm>

namespace Ghurund::UI {
    class StackLayoutManager:public LayoutManager {
    public:
        Alignment alignment;

        virtual FloatSize measure(ControlGroup& group, float parentWidth, float parentHeight) override;

        virtual void layout(ControlGroup& group, float x, float y, float width, float height) override;
    };
}