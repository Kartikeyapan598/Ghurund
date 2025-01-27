#pragma once

#include "LayoutBinding.h"
#include "ui/widget/Widget.h"
#include <ui/widget/button/Button.h>
#include <ui/widget/button/CheckBox.h>
#include "ui/layout/StackLayout.h"
#include "ui/style/WindowsTheme.h"

namespace Preview {
    using namespace Ghurund::UI;

    enum class ThemeType {
        Dark, Light
    };

    class PreviewLayout:public Widget {
    private:
        Ghurund::UI::StackLayout* container = nullptr;
        Ghurund::UI::Button* color1 = nullptr;
        Ghurund::UI::Button* color2 = nullptr;
        Ghurund::UI::Button* color3 = nullptr;
        Ghurund::UI::Button* color4 = nullptr;
        Ghurund::UI::Button* colorTheme = nullptr;
        Ghurund::UI::CheckBox* enabledCheckBox = nullptr;
        Ghurund::UI::CheckBox* themeCheckBox = nullptr;

    protected:
        static const Ghurund::Core::Type& GET_TYPE() {
            static const Ghurund::Core::Type TYPE = TypeBuilder<PreviewLayout>(NAMESPACE_NAME, GH_STRINGIFY(PreviewLayout))
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

        virtual void bind() override {
            __super::bind();
            container = (Ghurund::UI::StackLayout*)find("container");
            color1 = (Ghurund::UI::Button*)find("color1");
            color2 = (Ghurund::UI::Button*)find("color2");
            color3 = (Ghurund::UI::Button*)find("color3");
            color4 = (Ghurund::UI::Button*)find("color4");
            colorTheme = (Ghurund::UI::Button*)find("colorTheme");
            enabledCheckBox = (Ghurund::UI::CheckBox*)find("enabledCheckBox");
            themeCheckBox = (Ghurund::UI::CheckBox*)find("themeCheckBox");

            themeCheckBox->checkedChanged += [this](CheckBox& checkBox) {
                themeChanged(checkBox.Checked ? ThemeType::Dark : ThemeType::Light);
                repaint();
                return true;
            };
            enabledCheckBox->checkedChanged += [this](CheckBox& checkBox) {
                container->Enabled = checkBox.Checked;
                container->repaint();
                return true;
            };

            auto colorClickHandler = [this](Button& button, const MouseClickedEventArgs& args) {
                if (args.Button == MouseButton::LEFT) {
                    ColorView* colorView = (ColorView*)button.find(ColorView::TYPE);
                    Theme->Colors.set(Theme::COLOR_ACCENT, colorView->Color.getValue(*colorView));
                    Theme->updateColors();
                    dispatchThemeChanged();
                } else if (args.Button == MouseButton::RIGHT) {

                }
                return true;
            };
            color1->clicked += colorClickHandler;
            color2->clicked += colorClickHandler;
            color3->clicked += colorClickHandler;
            color4->clicked += colorClickHandler;

            ColorView* colorView = (ColorView*)colorTheme->find(ColorView::TYPE);
            WindowsTheme::init();
            colorView->Color = ColorValue(WindowsTheme::getAccentColor());
            colorTheme->clicked += colorClickHandler;
        }

    public:
        Event<PreviewLayout, ThemeType> themeChanged = *this;

        inline StackLayout* getContainer() {
            return container;
        }

        __declspec(property(get = getContainer)) StackLayout* Container;

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }
    };
}