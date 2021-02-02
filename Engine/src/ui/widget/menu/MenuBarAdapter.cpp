#include "MenuBarAdapter.h"
#include "ui/style/Theme.h"

namespace Ghurund::UI {
    Control* ButtonMenuBarAdapter::makeControl() const {
        return ghnew TextButton(ghnew TextButtonFlatLayout(context, loader));
    }
    
    void ButtonMenuBarAdapter::bind(Control& control, MenuItem* const& item, size_t position) const {
        TextButton& textButton = (TextButton&)control;
        ButtonMenuItem* menuItem = (ButtonMenuItem*)item;
        textButton.Text = menuItem->Text;
        textButton.OnClicked.clear();
        textButton.OnClicked.add([menuItem](Control& sender, const MouseClickedEventArgs& args) {
            menuItem->ClickEventHandler(sender);
            return true;
        });
    }
}

