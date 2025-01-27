#pragma once

#include "Control.h"
#include "ui/Alignment.h"
#include "ui/drawable/ImageDrawable.h"
#include "ui/style/ColorAttr.h"

namespace Ghurund::UI {
    enum class ImageScaleMode {
        NONE, STRETCH, FIT, CROP
    };

    class ImageView: public Control {
    private:
        ImageDrawable* image = nullptr;
        ColorAttr* tint = nullptr;
        ImageScaleMode scaleMode = ImageScaleMode::CROP;
        Alignment gravity;

    protected:
        static const Ghurund::Core::Type& GET_TYPE();

        virtual void onMeasure(float parentWidth, float parentHeight) override;

        virtual void onDraw(Ghurund::UI::ICanvas& canvas) override;

    public:
        ImageView(ImageDrawable* image = nullptr) {
            if (image) {
                image->addReference();
                this->image = image;
            }
            gravity.horizontal = Alignment::Horizontal::CENTER;
            gravity.vertical = Alignment::Vertical::CENTER;
        }

        ~ImageView() {
            if (image)
                image->release();
            delete this->tint;
        }

        inline void setImage(ImageDrawable* image) {
            setPointer(this->image, image);
        }

        inline ImageDrawable* getImage() {
            return image;
        }

        __declspec(property(get = getImage, put = setImage)) ImageDrawable* Image;

        inline void setTint(std::unique_ptr<ColorAttr> color) {
            delete this->tint;
            if (color) {
                this->tint = color.release();   // TODO: can this be simplified?
            } else {
                this->tint = nullptr;
            }
        }

        inline const ColorAttr* getTint() const {
            return tint;
        }

        __declspec(property(get = getTint, put = setTint)) const ColorAttr* Tint;

        inline void setScaleMode(ImageScaleMode mode) {
            this->scaleMode = mode;
        }

        inline ImageScaleMode getScaleMode() const {
            return scaleMode;
        }

        __declspec(property(get = getScaleMode, put = setScaleMode)) ImageScaleMode ScaleMode;

        inline const Alignment& getGravity() const {
            return gravity;
        }

        inline void setGravity(const Alignment& gravity) {
            this->gravity = gravity;
        }

        __declspec(property(get = getGravity, put = setGravity)) Alignment& Alignment;

        virtual void load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) override;

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }
    };

    class ImageViewStyle:public Style {
    public:
        virtual void onStateChanged(Control& control) const override;
    };

    class ImageViewOnBackgroundStyle:public Style {
    public:
        virtual void onStateChanged(Control& control) const override;
    };

    class ImageViewOnAccentStyle:public Style {
    public:
        virtual void onStateChanged(Control& control) const override;
    };

    class ImageViewAccentStyle:public Style {
    public:
        virtual void onStateChanged(Control& control) const override;
    };
}