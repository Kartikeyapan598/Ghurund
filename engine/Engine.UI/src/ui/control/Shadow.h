#pragma once

#include "Control.h"
#include "ui/Shape.h"
#include "ui/style/ColorAttr.h"
//#include "ui/image/Bitmap.h"

namespace Ghurund::UI {
    class Shadow: public Control {
    private:
        ColorAttr* color = nullptr;
        Ghurund::UI::Shape* shape = nullptr;
        float radius = 2.0f;
        //Bitmap* bitmap = nullptr;
        //ID2D1SolidColorBrush* fillBrush = nullptr;

    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        Shadow(const ColorAttr& color = ColorValue(Ghurund::UI::Color(0, 0, 0, 0.6f)));

        ~Shadow();

        inline const ColorAttr& getColor() const {
            return *color;
        }

        inline void setColor(const ColorAttr& color) {
            delete this->color;
            this->color = (ColorAttr*)color.clone();
        }

        __declspec(property(get = getColor, put = setColor)) const ColorAttr& Color;

        inline Ghurund::UI::Shape* getShape() {
            return shape;
        }

        inline void setShape(Ghurund::UI::Shape* shape) {
            delete this->shape;
            this->shape = shape;
        }

        __declspec(property(get = getShape, put = setShape)) Ghurund::UI::Shape* Shape;

        inline float getRadius() const {
            return radius;
        }

        inline void setRadius(float radius) {
            this->radius = radius;
        }

        __declspec(property(get = getRadius, put = setRadius)) float Radius;

        virtual void onLayout(float x, float y, float width, float height) override;

        virtual void onDraw(Ghurund::UI::ICanvas& canvas) override;

        virtual void load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) override;

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }
    };

    class ShadowButtonStyle:public TypedStyle<Shadow> {
    public:
        virtual void onStateChanged(Shadow& control) const override {
            control.Radius = control.Enabled ? 2.0f : 0.0f;
        }
    };
}