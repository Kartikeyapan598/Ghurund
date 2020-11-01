#pragma once

#include "core/ScopedPointer.h"
#include "ui/Style.h"
#include "ui/control/Control.h"
#include "ui/widget/SeparatorStyle.h"
#include "ui/widget/ProgressBar.h"
#include "ui/control/TextBlockStyle.h"
#include "ui/widget/ProgressBar.h"
#include "ui/widget/menu/ToolbarStyle.h"
#include "ui/widget/menu/MenuBarStyle.h"
#include "ui/widget/tab/TabContainerStyle.h"

namespace Ghurund::UI {
    class Theme {
    private:
        static const inline float emphasis_high = 0.87f;
        static const inline float emphasis_medium = 0.6f;
        static const inline float emphasis_disabled = 0.38f;

        static const inline float state_normal = 0.12f;
        static const inline float state_activated = 0.4f;
        static const inline float state_disabled = 0.08f;

        constexpr unsigned int colorWithAlpha(float alpha, unsigned int color) const {
            unsigned int a = (unsigned int)(alpha * 0xff);
            return ((a & 0xff) << 24) | (color & 0xffffff);
        }

    protected:
        Map<String, StateHandler> stateHandlers;
        Ghurund::ScopedPointer<Ghurund::UI::Font> buttonFont, listHeaderFont, primaryTextFont, secondaryTextFont;
        Ghurund::ScopedPointer<Ghurund::UI::GdiImage> checkBoxChecked, checkBoxUnchecked;
        Ghurund::ScopedPointer<Ghurund::UI::GdiImage> radioButtonChecked, radioButtonUnchecked;

    public:
        Style<Separator>* separatorStyle = ghnew HorizontalSeparatorStyle(*this);
        Style<ProgressBar>* progressBarStyle = ghnew ProgressBarStyle(*this);

        Style<TextBlock>* textViewPrimaryStyle = ghnew TextBlockPrimaryStyle(*this);
        Style<TextBlock>* textViewSecondaryStyle = ghnew TextBlockSecondaryStyle(*this);
        Style<TextBlock>* textViewHeaderStyle = ghnew TextBlockHeaderStyle(*this);

        StyleWithLayout<Toolbar, ToolbarLayout>* toolbarStyle = ghnew ToolbarStyle(*this);
        StyleWithLayout<MenuBar, MenuBarLayout>* menuBarStyle = ghnew MenuBarStyle(*this);
        StyleWithLayout<TabContainer, TabContainerLayout>* tabContainerStyle = ghnew TabContainerStyle(*this);

        virtual ~Theme() {
            separatorStyle->release();
            progressBarStyle->release();

            textViewPrimaryStyle->release();
            textViewSecondaryStyle->release();
            textViewHeaderStyle->release();

            toolbarStyle->release();
            menuBarStyle->release();
            tabContainerStyle->release();
        }

        inline Map<String, StateHandler>& getStateHandlers() {
            return stateHandlers;
        }

        __declspec(property(get = getStateHandlers)) Map<String, StateHandler>& StateHandlers;

        virtual unsigned int getColorError() const = 0;
        virtual unsigned int getColorBackground() const = 0;
        virtual unsigned int getColorControl() const = 0;
        virtual unsigned int getColorAccent() const = 0;
        virtual unsigned int getColorAccentDark() const = 0;

        virtual unsigned int getColorOnError() const = 0;
        virtual unsigned int getColorOnBackground() const = 0;
        virtual unsigned int getColorOnAccent() const = 0;

        inline Ghurund::UI::Font* getButtonFont() {
            return buttonFont;
        }

        inline Ghurund::UI::Font* getPrimaryTextFont() {
            return primaryTextFont;
        }

        inline Ghurund::UI::Font* getSecondaryTextFont() {
            return secondaryTextFont;
        }

        inline GdiImage* getCheckBoxChecked() {
            return checkBoxChecked;
        }

        inline GdiImage* getCheckBoxUnchecked() {
            return checkBoxUnchecked;
        }

        inline GdiImage* getRadioButtonChecked() {
            return radioButtonChecked;
        }

        inline GdiImage* getRadioButtonUnchecked() {
            return radioButtonUnchecked;
        }

        unsigned int getColorControlNormal() const {
            return colorWithAlpha(state_normal, getColorControl());
        }
        unsigned int getColorControlDisabled() const {
            return colorWithAlpha(state_disabled, getColorControl());
        }
        unsigned int getColorControlActivated() const {
            return colorWithAlpha(state_activated, getColorControl());
        }

        unsigned int getColorForegroundPrimaryOnError() const {
            return colorWithAlpha(emphasis_high, getColorOnError());
        }
        unsigned int getColorForegroundPrimaryOnBackground() const {
            return colorWithAlpha(emphasis_high, getColorOnBackground());
        }
        unsigned int getColorForegroundPrimaryOnAccent() const {
            return colorWithAlpha(emphasis_high, getColorOnAccent());
        }

        unsigned int getColorForegroundSecondaryOnError() const {
            return colorWithAlpha(emphasis_medium, getColorOnError());
        }
        unsigned int getColorForegroundSecondaryOnBackground() const {
            return colorWithAlpha(emphasis_medium, getColorOnBackground());
        }
        unsigned int getColorForegroundSecondaryOnAccent() const {
            return colorWithAlpha(emphasis_medium, getColorOnAccent());
        }

        unsigned int getColorForegroundDisabledOnError() const {
            return colorWithAlpha(emphasis_disabled, getColorOnError());
        }
        unsigned int getColorForegroundDisabledOnBackground() const {
            return colorWithAlpha(emphasis_disabled, getColorOnBackground());
        }
        unsigned int getColorForegroundDisabledOnAccent() const {
            return colorWithAlpha(emphasis_disabled, getColorOnAccent());
        }

    };
}