#include "ImageButton.h"
#include "ImageButtonLayout.h"
#include "ui/style/Theme.h"

namespace Ghurund::UI {
    void ImageButtonLayout::init() {
        __super::init();
        stack = ghnew StackLayout();
        paddingContainer->Child = imageView;
        paddingContainer->Padding.All = 4;
        stack->PreferredSize.width = PreferredSize::Width::WRAP;
        stack->PreferredSize.height = PreferredSize::Height::WRAP;
        clickResponseView = makeShared<ClickResponseView>();
        stack->Children = { backgroundView, clickResponseView, border, paddingContainer };
        ClickableView->Child = stack;
        root = ClickableView;
    }

    void ImageButtonLayout::onThemeChanged(Control& control) {
        Ghurund::UI::Theme* theme = control.Theme;
        if (!theme)
            return;
        clickResponseView->Color = theme->ColorHighlightOnBackground;
    }

    void ImageButtonLayout::onStateChanged(Control& control) {
        Ghurund::UI::Theme* theme = control.Theme;
        if (!theme)
            return;
        if (!control.Enabled) {
            if (imageView->Image)
                imageView->Image->Tint = theme->getColorForegroundDisabledOnBackground();
            border->Color = theme->getColorForegroundDisabledOnBackground();
            backgroundView->Color = theme->getColorControlDisabled();
        } else if (ClickableView->Pressed || ClickableView->Hovered || control.Focused) {
            if (imageView->Image)
                imageView->Image->Tint = theme->getColorForegroundSecondaryOnBackground();
            border->Color = theme->getColorAccent();
            backgroundView->Color = theme->getColorControlNormal();
        } else {
            if (imageView->Image)
                imageView->Image->Tint = theme->getColorForegroundSecondaryOnBackground();
            border->Color = theme->getColorForegroundPrimaryOnBackground();
            backgroundView->Color = theme->getColorControlNormal();
        }
        clickResponseView->Pressed = ClickableView->Pressed;
    }

    void ImageButtonFlatLayout::onStateChanged(Control& control) {
        Ghurund::UI::Theme* theme = control.Theme;
        if (!theme)
            return;
        backgroundView->Color = 0;
        if (!control.Enabled) {
            if (imageView->Image)
                imageView->Image->Tint = theme->getColorForegroundDisabledOnBackground();
            border->Color = 0;
        } else if (ClickableView->Pressed || ClickableView->Hovered || control.Focused) {
            if (imageView->Image)
                imageView->Image->Tint = theme->getColorForegroundSecondaryOnBackground();
            border->Color = theme->getColorAccent();
        } else {
            if (imageView->Image)
                imageView->Image->Tint = theme->getColorForegroundSecondaryOnBackground();
            border->Color = 0;
        }
        clickResponseView->Pressed = ClickableView->Pressed;
    }

}
