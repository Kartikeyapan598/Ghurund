#pragma once

#include "Status.h"
#include "MouseEvents.h"
#include "core/resource/Resource.h"
#include "core/Event.h"
#include "core/math/Matrix3x2.h"
#include "core/math/Size.h"
#include "core/input/EventConsumer.h"
#include "ui/Cursor.h"
#include "ui/PreferredSize.h"
#include "ui/UIContext.h"
#include "ui/style/Style.h"

namespace tinyxml2 {
    class XMLElement;
}

namespace Ghurund::UI {
    class Control;
    class ControlParent;
    class Theme;
    class LayoutLoader;
    class ICanvas;
}

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class Control: public Resource, public EventConsumer {
#pragma region reflection
    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();
        virtual const Ghurund::Core::Type& getType() const override { return TYPE; }
#pragma endregion

    private:
        ControlParent* parent = nullptr;
        const Cursor* cursor = nullptr;

        Ghurund::Core::FloatSize size = { 0, 0 };  // what was finally mediated

        bool visible = true;
        bool enabled = true;
        bool focusable = false;
        bool roundToPixels = true;

        Ghurund::Core::AString* name = nullptr;

    protected:
        FloatPoint position = { 0,0 }, scale = { 1,1 };
        float rotation = 0;
        Ghurund::Core::Matrix3x2 transformation;

        Ghurund::Core::FloatSize minSize = { 0,0 };
        PreferredSize preferredSize;   // what the user wants
        Ghurund::Core::FloatSize measuredSize;  // what the view wants
        bool needsLayout = true;

        Theme* localTheme = nullptr;
        const Style* style = nullptr;

        virtual void onStateChanged() {
            stateChanged();
            if (style)
                style->onStateChanged(*this);
        }

        virtual void onThemeChanged() {
            themeChanged();
            if (style)
                style->onThemeChanged(*this);
        }

        virtual void onContextChanged() {
            contextChanged();
        }

        virtual void onMeasure(float parentWidth, float parentHeight);

        virtual void onLayout(float x, float y, float width, float height) {}

        virtual void onDraw(ICanvas& canvas) {}

        virtual bool onMouseButtonEvent(const MouseButtonEventArgs& event) override;

        virtual ~Control() = 0;

    public:
        Event<Control> sizeChanged = Event<Control>(*this);
        Event<Control> stateChanged = Event<Control>(*this);
        Event<Control> themeChanged = Event<Control>(*this);
        Event<Control> contextChanged = Event<Control>(*this);

        inline const Ghurund::Core::AString* getName() const {
            return name;
        }

        void setName(const Ghurund::Core::AString* name);

        void setName(const Ghurund::Core::AString& name);

        __declspec(property(get = getName, put = setName)) const Ghurund::Core::AString* Name;

        inline bool isVisible() const {
            return visible;
        }

        inline void setVisible(bool visible) {
            this->visible = visible;
            if (!visible && Focused) {
                clearFocus();
            } else {
                onStateChanged();
            }
        }

        __declspec(property(get = isVisible, put = setVisible)) bool Visible;

        bool isEnabled() const;

        inline void setEnabled(bool enabled) {
            if (this->enabled == enabled)
                return;
            this->enabled = enabled;
            if (!enabled && Focused)
                clearFocus();
            dispatchStateChanged();
        }

        __declspec(property(get = isEnabled, put = setEnabled)) bool Enabled;

        inline bool isFocusable() const {
            return enabled && visible && focusable;
        }

        inline void setFocusable(bool focusable) {
            this->focusable = focusable;
            if (!Focusable)
                clearFocus();
        }

        __declspec(property(get = isFocusable, put = setFocusable)) bool Focusable;

        virtual Control* getFocus() {
            return nullptr;
        }

        __declspec(property(get = getFocus)) Control* Focus;

        inline Control* findFocus() {
            Control* focus = Focus;
            if (focus) {
                while (focus->Focus)
                    focus = focus->Focus;
            }
            return focus;
        }

        void requestFocus();

        void clearFocus();

        virtual bool isFocused() const;

        __declspec(property(get = isFocused)) bool Focused;

        virtual bool focusNext();

        virtual bool focusPrevious();

        virtual bool focusUp();

        virtual bool focusDown();

        virtual bool focusLeft();

        virtual bool focusRight();

        inline bool isRoundToPixelsEnabled() const {
            return roundToPixels;
        }

        inline void setRoundToPixelsEnabled(bool roundToPixels) {
            this->roundToPixels = roundToPixels;
        }

        __declspec(property(get = isRoundToPixelsEnabled, put = setRoundToPixelsEnabled)) bool RoundToPixelsEnabled;

        inline const FloatPoint& getPosition() const {
            return position;
        }

        inline void setPosition(const FloatPoint& position) {
            this->position = position;
        }

        inline void setPosition(float x, float y) {
            position.x = x;
            position.y = y;
        }

        __declspec(property(get = getPosition, put = setPosition)) const FloatPoint& Position;

        inline float getRotation() const {
            return rotation;
        }

        inline void setRotation(float rotation) {
            this->rotation = rotation;
        }

        __declspec(property(get = getRotation, put = setRotation)) float Rotation;

        inline const FloatPoint& getScale() const {
            return scale;
        }

        inline void setScale(const FloatPoint& scale) {
            this->scale = scale;
        }

        inline void setScale(float x, float y) {
            position.x = x;
            position.y = y;
        }

        __declspec(property(get = getScale, put = setScale)) const FloatPoint& Scale;

        inline const Ghurund::Core::Matrix3x2& getTransformation() const {
            return transformation;
        }

        __declspec(property(get = getTransformation)) const Ghurund::Core::Matrix3x2& Transformation;

        inline const Ghurund::Core::FloatSize& getMinSize() const {
            return minSize;
        }

        inline Ghurund::Core::FloatSize& getMinSize() {
            return minSize;
        }

        inline void setMinSize(const Ghurund::Core::FloatSize& size) {
            this->minSize = size;
        }

        virtual void setMinSize(float width, float height) {
            minSize.width = abs(width);
            minSize.height = abs(height);
        }

        __declspec(property(get = getMinSize, put = setMinSize)) const Ghurund::Core::FloatSize& MinSize;

        inline const Ghurund::Core::FloatSize& getSize() const {
            return size;
        }

        __declspec(property(get = getSize)) Ghurund::Core::FloatSize& Size;

        inline const PreferredSize& getPreferredSize() const {
            return preferredSize;
        }

        inline PreferredSize& getPreferredSize() {
            return preferredSize;
        }

        inline void setPreferredSize(const PreferredSize& size) {
            this->preferredSize = size;
        }

        virtual void setPreferredSize(const PreferredSize::Width& width, const PreferredSize::Height& height) {
            preferredSize.width = width;
            preferredSize.height = height;
        }

        __declspec(property(get = getPreferredSize, put = setPreferredSize)) const Ghurund::UI::PreferredSize& PreferredSize;

        inline const Ghurund::Core::FloatSize& getMeasuredSize() const {
            return measuredSize;
        }

        __declspec(property(get = getMeasuredSize)) Ghurund::Core::FloatSize& MeasuredSize;

        inline bool canReceiveEvent(const MouseEventArgs& event) {
            return Visible && Enabled && hitTest((float)event.Position.x, (float)event.Position.y);
        }

        // TODO: support matrix transformation
        inline bool hitTest(float x, float y) {
            return x >= position.x && x < position.x + size.width && y >= position.y && y < position.y + size.height;
        }

        void setParent(ControlParent* parent);

        inline ControlParent* getParent() const {
            return parent;
        }

        __declspec(property(get = getParent, put = setParent)) ControlParent* Parent;

        inline const Cursor* getCursor() {
            return cursor;
        }

        inline void setCursor(const Cursor* cursor) {
            this->cursor = cursor;
        }

        __declspec(property(get = getCursor, put = setCursor)) const Ghurund::UI::Cursor* Cursor;

        void setTheme(Theme* theme);

        Theme* getTheme() const;

        __declspec(property(get = getTheme, put = setTheme)) Ghurund::UI::Theme* Theme;

        virtual IUIContext* getContext();

        __declspec(property(get = getContext)) IUIContext* Context;

        inline void setStyle(const Style* style) {
            this->style = style;
            if (style) {
                style->onThemeChanged(*this);
                style->onStateChanged(*this);
            }
        }

        inline const Style* getStyle() {
            return style;
        }

        __declspec(property(get = getStyle, put = setStyle)) const Ghurund::UI::Style* Style;

        virtual void dispatchStateChanged();

        virtual void dispatchThemeChanged();

        virtual void dispatchContextChanged();

        virtual void repaint();

        virtual void invalidate();

        inline void measure(float parentWidth, float parentHeight) {
            if (needsLayout || preferredSize.width.Type != PreferredSize::Type::PIXELS || preferredSize.height.Type != PreferredSize::Type::PIXELS)
                onMeasure(parentWidth, parentHeight);
        }

        void layout(float x, float y, float width, float height);

        virtual void onUpdate(const uint64_t time) {}

        void draw(ICanvas& canvas);

        virtual Control* find(const Ghurund::Core::AString& name);

        template<class T>
        inline T* find() {
            return (T*)find(T::TYPE);
        }

        virtual Control* find(const Ghurund::Core::Type& type);

        virtual FloatPoint getPositionInWindow();

        __declspec(property(get = getPositionInWindow)) FloatPoint PositionInWindow;

        FloatPoint getPositionOnScreen();

        __declspec(property(get = getPositionOnScreen)) FloatPoint PositionOnScreen;

        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event) override;

        virtual void load(Ghurund::UI::LayoutLoader& loader, const tinyxml2::XMLElement& xml);

        static const inline Ghurund::Core::ResourceFormat FORMAT_XML = Ghurund::Core::ResourceFormat(L"xml", true, true);

        inline static const Ghurund::Core::Array<Ghurund::Core::ResourceFormat>& FORMATS = { FORMAT_XML };

        virtual const Ghurund::Core::Array<Ghurund::Core::ResourceFormat>& getFormats() const override {
            return FORMATS;
        }

#ifdef _DEBUG
        virtual void validate();
#endif
    };

    template<class T>
    concept IsControl = std::is_base_of<Control, T>::value;
}