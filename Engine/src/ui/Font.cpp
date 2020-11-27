#include "Font.h"
#include "ui/Canvas.h"
#include "application/log/Logger.h"
#include "ui/Graphics2D.h"

#include <commdlg.h>

namespace Ghurund::UI {
    Font::Font(const String& file, const String& family, float size, unsigned int weight, bool italic) {
        this->size = size;
        this->familyName = family;
        this->weight = weight;
        this->italic = italic;
    }

    Status Font::init(Graphics2D& graphics2d) {
        this->graphics2d = &graphics2d;
        if (FAILED(graphics2d.DWriteFactory->CreateTextFormat(
            UnicodeString(familyName),
            nullptr,
            (DWRITE_FONT_WEIGHT)weight,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            size,
            L"en-us",
            &textFormat)))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, "CreateTextFormat failed\n");

        if (FAILED(textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING)))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, "SetTextAlignment failed\n");

        if (FAILED(textFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR)))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, "SetParagraphAlignment failed\n");

        return Status::OK;
    }

    IDWriteTextLayout* Font::makeLayout(UnicodeString& text, float width, float height) {
        IDWriteTextLayout* textLayout;
        graphics2d->DWriteFactory->CreateTextLayout(
            text.getData(),      // The string to be laid out and formatted.
            (UINT32)text.Size,  // The length of the string.
            textFormat.Get(),  // The text format to apply to the string (contains font information, etc).
            width,         // The width of the layout box.
            height,        // The height of the layout box.
            &textLayout  // The IDWriteTextLayout interface pointer.
        );
        return textLayout;
    }
}