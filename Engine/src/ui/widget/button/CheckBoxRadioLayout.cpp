#include "CheckBoxRadioLayout.h"
#include "ui/style/Theme.h"
#include "ui/drawable/BitmapImageDrawable.h"

namespace Ghurund::UI {
    void CheckBoxRadioLayout::onStateChanged(Control& control) {
        Ghurund::UI::Theme* theme = control.Theme;
        if (!theme || !imageView->Image)
            return;
        if (!control.Enabled) {
            imageView->Image->Tint = theme->getColorForegroundDisabledOnBackground();
        } else if (selectableView->Pressed) {
            if (selectableView->Selected) {
                //imageView->Image->Tint = theme->getColorAccentDark();
            } else {
                imageView->Image->Tint = theme->getColorForegroundPrimaryOnBackground();
            }
        } else if (selectableView->Hovered || selectableView->Focused) {
            if (selectableView->Selected) {
                imageView->Image->Tint = theme->Colors[Theme::COLOR_ACCENT];
            } else {
                imageView->Image->Tint = theme->getColorForegroundSecondaryOnBackground();
            }
        } else {
            if (selectableView->Selected) {
                imageView->Image->Tint = theme->Colors[Theme::COLOR_ACCENT];
            } else {
                imageView->Image->Tint = theme->getColorForegroundSecondaryOnBackground();
            }
        }
    }

    void CheckBoxLayout::onStateChanged(Control& control) {
        Ghurund::UI::Theme* theme = control.Theme;
        if (!theme)
            return;
        if (selectableView->Selected) {
            imageView->Image = makeShared<BitmapImageDrawable>(theme->Images[Theme::IMAGE_CHECKBOX_CHECKED]);
        } else {
            imageView->Image = makeShared<BitmapImageDrawable>(theme->Images[Theme::IMAGE_CHECKBOX_UNCHECKED]);
        }
        __super::onStateChanged(control);
    }

    void RadioButtonLayout::onStateChanged(Control& control) {
        Ghurund::UI::Theme* theme = control.Theme;
        if (!theme)
            return;
        if (selectableView->Selected) {
            imageView->Image = makeShared<BitmapImageDrawable>(theme->Images[Theme::IMAGE_RADIOBUTTON_CHECKED]);
        } else {
            imageView->Image = makeShared<BitmapImageDrawable>(theme->Images[Theme::IMAGE_RADIOBUTTON_UNCHECKED]);
        }
        __super::onStateChanged(control);
    }

    void CheckBoxRadioTextLayout::init() {
        selectableView = ghnew Ghurund::UI::SelectableView();
        SharedPointer<HorizontalLayout> row = ghnew HorizontalLayout();
        row->setPreferredSize(PreferredSize::Width::WRAP, PreferredSize::Height::WRAP);
        textView = ghnew Ghurund::UI::TextBlock();
        imageView = ghnew Ghurund::UI::ImageView();
        SharedPointer<Space> space = ghnew Space();
        row->Children = { imageView, space, textView };
        row->Alignment.vertical = Alignment::Vertical::CENTER;
        selectableView->Child = row;
        Root = selectableView;
    }

    void CheckBoxRadioTextLayout::onStateChanged(Control& control) {
        Ghurund::UI::Theme* theme = control.Theme;
        if (!theme)
            return;
        textView->TextStyle = theme->TextStyles[Theme::TEXTSTYLE_BUTTON];
        if (!control.Enabled) {
            imageView->Image->Tint = theme->getColorForegroundDisabledOnBackground();
            textView->TextColor = theme->getColorForegroundDisabledOnBackground();
        } else if (selectableView->Pressed) {
            if (selectableView->Selected) {
                //imageView->Image->Tint = theme->getColorAccentDark();
            } else {
                imageView->Image->Tint = theme->getColorForegroundPrimaryOnBackground();
            }
            textView->TextColor = theme->getColorForegroundPrimaryOnBackground();
        } else if (selectableView->Hovered || selectableView->Focused) {
            if (selectableView->Selected) {
                imageView->Image->Tint = theme->Colors[Theme::COLOR_ACCENT];
            } else {
                imageView->Image->Tint = theme->getColorForegroundSecondaryOnBackground();
            }
            textView->TextColor = theme->getColorForegroundSecondaryOnBackground();
        } else {
            if (selectableView->Selected) {
                imageView->Image->Tint = theme->Colors[Theme::COLOR_ACCENT];
            } else {
                imageView->Image->Tint = theme->getColorForegroundSecondaryOnBackground();
            }
            textView->TextColor = theme->getColorForegroundSecondaryOnBackground();
        }
    }

    void TextCheckBoxLayout::onStateChanged(Control& control) {
        Ghurund::UI::Theme* theme = control.Theme;
        if (!theme)
            return;
        if (selectableView->Selected) {
            imageView->Image = makeShared<BitmapImageDrawable>(theme->Images[Theme::IMAGE_CHECKBOX_CHECKED]);
        } else {
            imageView->Image = makeShared<BitmapImageDrawable>(theme->Images[Theme::IMAGE_CHECKBOX_UNCHECKED]);
        }
        __super::onStateChanged(control);
    }

    void RadioTextButtonLayout::onStateChanged(Control& control) {
        Ghurund::UI::Theme* theme = control.Theme;
        if (!theme)
            return;
        if (selectableView->Selected) {
            imageView->Image = makeShared<BitmapImageDrawable>(theme->Images[Theme::IMAGE_RADIOBUTTON_CHECKED]);
        } else {
            imageView->Image = makeShared<BitmapImageDrawable>(theme->Images[Theme::IMAGE_RADIOBUTTON_UNCHECKED]);
        }
        __super::onStateChanged(control);
    }
}
