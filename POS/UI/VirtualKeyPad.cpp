#include <POS/UI/VirtualKeyPad.hpp>


VirtualKeyPad::VirtualKeyPad(QWidget& window,ProductContainer& products,
    int visibleXPos, int visibleYPos, int unvisibleXPos, int unvisibleYPos, int xSize, int ySize
) noexcept
    : m_products{ products }
    , m_window{ window }
    , m_visibleXPos{ visibleXPos }
    , m_visibleYPos{ visibleYPos }
    , m_unvisibleXPos{ unvisibleXPos }
    , m_unvisibleYPos{ unvisibleYPos }
    , m_buttonSize{ (xSize / 4), (ySize) / 5 }
    , m_validateCallback{ std::nullopt }
    , m_textBox{
        window,
        unvisibleXPos + m_buttonSize.width() * 0,
        unvisibleYPos + m_buttonSize.height() * 0,
        xSize,
        (m_buttonSize.height())
    } , m_buttons{
        CustomText{
            window,
            "clear",
            unvisibleXPos + m_buttonSize.width() * 0,
            unvisibleYPos + m_buttonSize.height() * 4,
            (m_buttonSize.width()),
            (m_buttonSize.height()),
            [this](){ m_textBox.clearLine(); m_textBox.addLine(""); m_textBox.print(); }
        }, CustomText{
            window,
            "0",
            unvisibleXPos + m_buttonSize.width() * 1,
            unvisibleYPos + m_buttonSize.height() * 4,
            (m_buttonSize.width()),
            (m_buttonSize.height()),
            [this](){ m_textBox.addText("0"); m_textBox.print(); }
        }, CustomText{
            window,
            "validate",
            unvisibleXPos + m_buttonSize.width() * 2,
            unvisibleYPos + m_buttonSize.height() * 4,
            (m_buttonSize.width()),
            (m_buttonSize.height()),
            [this, &window](){
                this->validate();
            }
        }, CustomText{
            window,
            "close",
            unvisibleXPos + m_buttonSize.width() * 3,
            unvisibleYPos + m_buttonSize.height() * 4,
            (m_buttonSize.width()),
            (m_buttonSize.height()),
            [this](){ this->conceal(); }
        }, CustomText{
            window,
            "1",
            unvisibleXPos + m_buttonSize.width() * 0,
            unvisibleYPos + m_buttonSize.height() * 3,
            (m_buttonSize.width()),
            (m_buttonSize.height()),
            [this](){ m_textBox.addText("1"); m_textBox.print(); }
        }, CustomText{
            window,
            "2",
            unvisibleXPos + m_buttonSize.width() * 1,
            unvisibleYPos + m_buttonSize.height() * 3,
            (m_buttonSize.width()),
            (m_buttonSize.height()),
            [this](){ m_textBox.addText("2"); m_textBox.print(); }
        }, CustomText{
            window,
            "3",
            unvisibleXPos + m_buttonSize.width() * 2,
            unvisibleYPos + m_buttonSize.height() * 3,
            (m_buttonSize.width()),
            (m_buttonSize.height()),
            [this](){ m_textBox.addText("3"); m_textBox.print(); }
        }, CustomText{
            window,
            ".00",
            unvisibleXPos + m_buttonSize.width() * 3,
            unvisibleYPos + m_buttonSize.height() * 3,
            (m_buttonSize.width()),
            (m_buttonSize.height()),
            [this](){ m_textBox.addText(".00"); m_textBox.print(); }
        }, CustomText{
            window,
            "4",
            unvisibleXPos + m_buttonSize.width() * 0,
            unvisibleYPos + m_buttonSize.height() * 2,
            (m_buttonSize.width()),
            (m_buttonSize.height()),
            [this](){ m_textBox.addText("4"); m_textBox.print(); }
        }, CustomText{
            window,
            "5",
            unvisibleXPos + m_buttonSize.width() * 1,
            unvisibleYPos + m_buttonSize.height() * 2,
            (m_buttonSize.width()),
            (m_buttonSize.height()),
            [this](){ m_textBox.addText("5"); m_textBox.print(); }
        }, CustomText{
            window,
            "6",
            unvisibleXPos + m_buttonSize.width() * 2,
            unvisibleYPos + m_buttonSize.height() * 2,
            (m_buttonSize.width()),
            (m_buttonSize.height()),
            [this](){ m_textBox.addText("6"); m_textBox.print(); }
        }, CustomText{
            window,
            ".0",
            unvisibleXPos + m_buttonSize.width() * 3,
            unvisibleYPos + m_buttonSize.height() * 2,
            (m_buttonSize.width()),
            (m_buttonSize.height()),
            [this](){ m_textBox.addText(".0"); m_textBox.print(); }
        }, CustomText{
            window,
            "7",
            unvisibleXPos + m_buttonSize.width() * 0,
            unvisibleYPos + m_buttonSize.height() * 1,
            (m_buttonSize.width()),
            (m_buttonSize.height()),
            [this](){ m_textBox.addText("7"); m_textBox.print(); }
        }, CustomText{
            window,
            "8",
            unvisibleXPos + m_buttonSize.width() * 1,
            unvisibleYPos + m_buttonSize.height() * 1,
            (m_buttonSize.width()),
            (m_buttonSize.height()),
            [this](){ m_textBox.addText("8"); m_textBox.print(); }
        }, CustomText{
            window,
            "9",
            unvisibleXPos + m_buttonSize.width() * 2,
            unvisibleYPos + m_buttonSize.height() * 1,
            (m_buttonSize.width()),
            (m_buttonSize.height()),
            [this](){ m_textBox.addText("9"); m_textBox.print(); }
        }, CustomText{
            window,
            ".",
            unvisibleXPos + m_buttonSize.width() * 3,
            unvisibleYPos + m_buttonSize.height() * 1,
            (m_buttonSize.width()),
            (m_buttonSize.height()),
            [this](){ m_textBox.addText("."); m_textBox.print(); }
        }
    }, m_textBoxAnimation {
        ::QPropertyAnimation{ &m_textBox, "pos" },
    }, m_buttonAnimations {
        ::QPropertyAnimation{ &m_buttons[0], "pos" },
        ::QPropertyAnimation{ &m_buttons[1], "pos" },
        ::QPropertyAnimation{ &m_buttons[2], "pos" },
        ::QPropertyAnimation{ &m_buttons[3], "pos" },
        ::QPropertyAnimation{ &m_buttons[4], "pos" },
        ::QPropertyAnimation{ &m_buttons[5], "pos" },
        ::QPropertyAnimation{ &m_buttons[6], "pos" },
        ::QPropertyAnimation{ &m_buttons[7], "pos" },
        ::QPropertyAnimation{ &m_buttons[8], "pos" },
        ::QPropertyAnimation{ &m_buttons[9], "pos" },
        ::QPropertyAnimation{ &m_buttons[10], "pos" },
        ::QPropertyAnimation{ &m_buttons[11], "pos" },
        ::QPropertyAnimation{ &m_buttons[12], "pos" },
        ::QPropertyAnimation{ &m_buttons[13], "pos" },
        ::QPropertyAnimation{ &m_buttons[14], "pos" },
        ::QPropertyAnimation{ &m_buttons[15], "pos" }
    }
{
    m_textBox.setFontPointSize(25);
    m_textBox.addLine("");
}


// Animatiton

///////////////////////////////////////////////////////////////////////////
void VirtualKeyPad::reveal(
    std::function<void(const std::vector<QString>&)> validateCallback,
    int numValues
)
{
    m_products.setReadOnly(true);
    m_isVisible = true;
    m_validateCallback = validateCallback;
    m_remainingValues = numValues;
    auto i{ 0uz };
    {
        const auto startPosX{ m_unvisibleXPos + m_buttonSize.width() * 0 };
        const auto startPosY{ m_unvisibleYPos + m_buttonSize.height() * 4 };
        const auto endPosX{ m_visibleXPos + m_buttonSize.width() * 0 };
        const auto endPosY{ m_visibleYPos + m_buttonSize.height() * 4 };
        m_buttonAnimations[i].setDuration(VirtualKeyPad::animationDuration);
        m_buttonAnimations[i].setStartValue(::QPoint{
            (startPosX),
            (startPosY)
        });
        m_buttonAnimations[i].setEndValue(::QPoint{
            (endPosX),
            (endPosY)
        });
        m_buttonAnimations[i].start();
        m_buttons[i].raise();
    }
    ++i;
    {
        const auto startPosX{ m_unvisibleXPos + m_buttonSize.width() * 1 };
        const auto startPosY{ m_unvisibleYPos + m_buttonSize.height() * 4 };
        const auto endPosX{ m_visibleXPos + m_buttonSize.width() * 1 };
        const auto endPosY{ m_visibleYPos + m_buttonSize.height() * 4 };
        m_buttonAnimations[i].setDuration(VirtualKeyPad::animationDuration);
        m_buttonAnimations[i].setStartValue(::QPoint{
            (startPosX),
            (startPosY)
        });
        m_buttonAnimations[i].setEndValue(::QPoint{
            (endPosX),
            (endPosY)
        });
        m_buttonAnimations[i].start();
        m_buttons[i].raise();
    }
    ++i;
    {
        const auto startPosX{ m_unvisibleXPos + m_buttonSize.width() * 2 };
        const auto startPosY{ m_unvisibleYPos + m_buttonSize.height() * 4 };
        const auto endPosX{ m_visibleXPos + m_buttonSize.width() * 2 };
        const auto endPosY{ m_visibleYPos + m_buttonSize.height() * 4 };
        m_buttonAnimations[i].setDuration(VirtualKeyPad::animationDuration);
        m_buttonAnimations[i].setStartValue(::QPoint{
            (startPosX),
            (startPosY)
        });
        m_buttonAnimations[i].setEndValue(::QPoint{
            (endPosX),
            (endPosY)
        });
        m_buttonAnimations[i].start();
        m_buttons[i].raise();
    }
    ++i;
    {
        const auto startPosX{ m_unvisibleXPos + m_buttonSize.width() * 3 };
        const auto startPosY{ m_unvisibleYPos + m_buttonSize.height() * 4 };
        const auto endPosX{ m_visibleXPos + m_buttonSize.width() * 3 };
        const auto endPosY{ m_visibleYPos + m_buttonSize.height() * 4 };
        m_buttonAnimations[i].setDuration(VirtualKeyPad::animationDuration);
        m_buttonAnimations[i].setStartValue(::QPoint{
            (startPosX),
            (startPosY)
        });
        m_buttonAnimations[i].setEndValue(::QPoint{
            (endPosX),
            (endPosY)
        });
        m_buttonAnimations[i].start();
        m_buttons[i].raise();
    }
    ++i;
    {
        const auto startPosX{ m_unvisibleXPos + m_buttonSize.width() * 0 };
        const auto startPosY{ m_unvisibleYPos + m_buttonSize.height() * 3 };
        const auto endPosX{ m_visibleXPos + m_buttonSize.width() * 0 };
        const auto endPosY{ m_visibleYPos + m_buttonSize.height() * 3 };
        m_buttonAnimations[i].setDuration(VirtualKeyPad::animationDuration);
        m_buttonAnimations[i].setStartValue(::QPoint{
            (startPosX),
            (startPosY)
        });
        m_buttonAnimations[i].setEndValue(::QPoint{
            (endPosX),
            (endPosY)
        });
        m_buttonAnimations[i].start();
        m_buttons[i].raise();
    }
    ++i;
    {
        const auto startPosX{ m_unvisibleXPos + m_buttonSize.width() * 1 };
        const auto startPosY{ m_unvisibleYPos + m_buttonSize.height() * 3 };
        const auto endPosX{ m_visibleXPos + m_buttonSize.width() * 1 };
        const auto endPosY{ m_visibleYPos + m_buttonSize.height() * 3 };
        m_buttonAnimations[i].setDuration(VirtualKeyPad::animationDuration);
        m_buttonAnimations[i].setStartValue(::QPoint{
            (startPosX),
            (startPosY)
        });
        m_buttonAnimations[i].setEndValue(::QPoint{
            (endPosX),
            (endPosY)
        });
        m_buttonAnimations[i].start();
        m_buttons[i].raise();
    }
    ++i;
    {
        const auto startPosX{ m_unvisibleXPos + m_buttonSize.width() * 2 };
        const auto startPosY{ m_unvisibleYPos + m_buttonSize.height() * 3 };
        const auto endPosX{ m_visibleXPos + m_buttonSize.width() * 2 };
        const auto endPosY{ m_visibleYPos + m_buttonSize.height() * 3 };
        m_buttonAnimations[i].setDuration(VirtualKeyPad::animationDuration);
        m_buttonAnimations[i].setStartValue(::QPoint{
            (startPosX),
            (startPosY)
        });
        m_buttonAnimations[i].setEndValue(::QPoint{
            (endPosX),
            (endPosY)
        });
        m_buttonAnimations[i].start();
        m_buttons[i].raise();
    }
    ++i;
    {
        const auto startPosX{ m_unvisibleXPos + m_buttonSize.width() * 3 };
        const auto startPosY{ m_unvisibleYPos + m_buttonSize.height() * 3 };
        const auto endPosX{ m_visibleXPos + m_buttonSize.width() * 3 };
        const auto endPosY{ m_visibleYPos + m_buttonSize.height() * 3 };
        m_buttonAnimations[i].setDuration(VirtualKeyPad::animationDuration);
        m_buttonAnimations[i].setStartValue(::QPoint{
            (startPosX),
            (startPosY)
        });
        m_buttonAnimations[i].setEndValue(::QPoint{
            (endPosX),
            (endPosY)
        });
        m_buttonAnimations[i].start();
        m_buttons[i].raise();
    }
    ++i;
    {
        const auto startPosX{ m_unvisibleXPos + m_buttonSize.width() * 0 };
        const auto startPosY{ m_unvisibleYPos + m_buttonSize.height() * 2 };
        const auto endPosX{ m_visibleXPos + m_buttonSize.width() * 0 };
        const auto endPosY{ m_visibleYPos + m_buttonSize.height() * 2 };
        m_buttonAnimations[i].setDuration(VirtualKeyPad::animationDuration);
        m_buttonAnimations[i].setStartValue(::QPoint{
            (startPosX),
            (startPosY)
        });
        m_buttonAnimations[i].setEndValue(::QPoint{
            (endPosX),
            (endPosY)
        });
        m_buttonAnimations[i].start();
        m_buttons[i].raise();
    }
    ++i;
    {
        const auto startPosX{ m_unvisibleXPos + m_buttonSize.width() * 1 };
        const auto startPosY{ m_unvisibleYPos + m_buttonSize.height() * 2 };
        const auto endPosX{ m_visibleXPos + m_buttonSize.width() * 1 };
        const auto endPosY{ m_visibleYPos + m_buttonSize.height() * 2 };
        m_buttonAnimations[i].setDuration(VirtualKeyPad::animationDuration);
        m_buttonAnimations[i].setStartValue(::QPoint{
            (startPosX),
            (startPosY)
        });
        m_buttonAnimations[i].setEndValue(::QPoint{
            (endPosX),
            (endPosY)
        });
        m_buttonAnimations[i].start();
        m_buttons[i].raise();
    }
    ++i;
    {
        const auto startPosX{ m_unvisibleXPos + m_buttonSize.width() * 2 };
        const auto startPosY{ m_unvisibleYPos + m_buttonSize.height() * 2 };
        const auto endPosX{ m_visibleXPos + m_buttonSize.width() * 2 };
        const auto endPosY{ m_visibleYPos + m_buttonSize.height() * 2 };
        m_buttonAnimations[i].setDuration(VirtualKeyPad::animationDuration);
        m_buttonAnimations[i].setStartValue(::QPoint{
            (startPosX),
            (startPosY)
        });
        m_buttonAnimations[i].setEndValue(::QPoint{
            (endPosX),
            (endPosY)
        });
        m_buttonAnimations[i].start();
        m_buttons[i].raise();
    }
    ++i;
    {
        const auto startPosX{ m_unvisibleXPos + m_buttonSize.width() * 3 };
        const auto startPosY{ m_unvisibleYPos + m_buttonSize.height() * 2 };
        const auto endPosX{ m_visibleXPos + m_buttonSize.width() * 3 };
        const auto endPosY{ m_visibleYPos + m_buttonSize.height() * 2 };
        m_buttonAnimations[i].setDuration(VirtualKeyPad::animationDuration);
        m_buttonAnimations[i].setStartValue(::QPoint{
            (startPosX),
            (startPosY)
        });
        m_buttonAnimations[i].setEndValue(::QPoint{
            (endPosX),
            (endPosY)
        });
        m_buttonAnimations[i].start();
        m_buttons[i].raise();
    }
    ++i;
    {
        const auto startPosX{ m_unvisibleXPos + m_buttonSize.width() * 0 };
        const auto startPosY{ m_unvisibleYPos + m_buttonSize.height() * 1 };
        const auto endPosX{ m_visibleXPos + m_buttonSize.width() * 0 };
        const auto endPosY{ m_visibleYPos + m_buttonSize.height() * 1 };
        m_buttonAnimations[i].setDuration(VirtualKeyPad::animationDuration);
        m_buttonAnimations[i].setStartValue(::QPoint{
            (startPosX),
            (startPosY)
        });
        m_buttonAnimations[i].setEndValue(::QPoint{
            (endPosX),
            (endPosY)
        });
        m_buttonAnimations[i].start();
        m_buttons[i].raise();
    }
    ++i;
    {
        const auto startPosX{ m_unvisibleXPos + m_buttonSize.width() * 1 };
        const auto startPosY{ m_unvisibleYPos + m_buttonSize.height() * 1 };
        const auto endPosX{ m_visibleXPos + m_buttonSize.width() * 1 };
        const auto endPosY{ m_visibleYPos + m_buttonSize.height() * 1 };
        m_buttonAnimations[i].setDuration(VirtualKeyPad::animationDuration);
        m_buttonAnimations[i].setStartValue(::QPoint{
            (startPosX),
            (startPosY)
        });
        m_buttonAnimations[i].setEndValue(::QPoint{
            (endPosX),
            (endPosY)
        });
        m_buttonAnimations[i].start();
        m_buttons[i].raise();
    }
    ++i;
    {
        const auto startPosX{ m_unvisibleXPos + m_buttonSize.width() * 2 };
        const auto startPosY{ m_unvisibleYPos + m_buttonSize.height() * 1 };
        const auto endPosX{ m_visibleXPos + m_buttonSize.width() * 2 };
        const auto endPosY{ m_visibleYPos + m_buttonSize.height() * 1 };
        m_buttonAnimations[i].setDuration(VirtualKeyPad::animationDuration);
        m_buttonAnimations[i].setStartValue(::QPoint{
            (startPosX),
            (startPosY)
        });
        m_buttonAnimations[i].setEndValue(::QPoint{
            (endPosX),
            (endPosY)
        });
        m_buttonAnimations[i].start();
        m_buttons[i].raise();
    }
    ++i;
    {
        const auto startPosX{ m_unvisibleXPos + m_buttonSize.width() * 3 };
        const auto startPosY{ m_unvisibleYPos + m_buttonSize.height() * 1 };
        const auto endPosX{ m_visibleXPos + m_buttonSize.width() * 3 };
        const auto endPosY{ m_visibleYPos + m_buttonSize.height() * 1 };
        m_buttonAnimations[i].setDuration(VirtualKeyPad::animationDuration);
        m_buttonAnimations[i].setStartValue(::QPoint{
            (startPosX),
            (startPosY)
        });
        m_buttonAnimations[i].setEndValue(::QPoint{
            (endPosX),
            (endPosY)
        });
        m_buttonAnimations[i].start();
        m_buttons[i].raise();
    }
    {
        const auto startPosX{ m_unvisibleXPos + m_buttonSize.width() * 0 };
        const auto startPosY{ m_unvisibleYPos + m_buttonSize.height() * 0 };
        const auto endPosX{ m_visibleXPos + m_buttonSize.width() * 0 };
        const auto endPosY{ m_visibleYPos + m_buttonSize.height() * 0 };
        m_textBoxAnimation.setDuration(VirtualKeyPad::animationDuration);
        m_textBoxAnimation.setStartValue(::QPoint{
            (startPosX),
            (startPosY)
        });
        m_textBoxAnimation.setEndValue(::QPoint{
            (endPosX),
            (endPosY)
        });
        m_textBoxAnimation.start();
        m_textBox.raise();
    }
}

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////
void VirtualKeyPad::conceal()
{
    m_products.setReadOnly(false);
    m_isVisible = false;
    m_textBox.clearLine();
    m_textBox.addLine("");
    m_textBox.print();
    m_values.clear();
    auto i{ 0uz };
    {
        const auto startPosX{ m_visibleXPos + m_buttonSize.width() * 0 };
        const auto startPosY{ m_visibleYPos + m_buttonSize.height() * 4 };
        const auto endPosX{ m_unvisibleXPos + m_buttonSize.width() * 0 };
        const auto endPosY{ m_unvisibleYPos + m_buttonSize.height() * 4 };
        m_buttonAnimations[i].setDuration(VirtualKeyPad::animationDuration);
        m_buttonAnimations[i].setStartValue(::QPoint{
            (startPosX),
            (startPosY)
        });
        m_buttonAnimations[i].setEndValue(::QPoint{
            (endPosX),
            (endPosY)
        });
        m_buttonAnimations[i].start();
    }
    ++i;
    {
        const auto startPosX{ m_visibleXPos + m_buttonSize.width() * 1 };
        const auto startPosY{ m_visibleYPos + m_buttonSize.height() * 4 };
        const auto endPosX{ m_unvisibleXPos + m_buttonSize.width() * 1 };
        const auto endPosY{ m_unvisibleYPos + m_buttonSize.height() * 4 };
        m_buttonAnimations[i].setDuration(VirtualKeyPad::animationDuration);
        m_buttonAnimations[i].setStartValue(::QPoint{
            (startPosX),
            (startPosY)
        });
        m_buttonAnimations[i].setEndValue(::QPoint{
            (endPosX),
            (endPosY)
        });
        m_buttonAnimations[i].start();
    }
    ++i;
    {
        const auto startPosX{ m_visibleXPos + m_buttonSize.width() * 2 };
        const auto startPosY{ m_visibleYPos + m_buttonSize.height() * 4 };
        const auto endPosX{ m_unvisibleXPos + m_buttonSize.width() * 2 };
        const auto endPosY{ m_unvisibleYPos + m_buttonSize.height() * 4 };
        m_buttonAnimations[i].setDuration(VirtualKeyPad::animationDuration);
        m_buttonAnimations[i].setStartValue(::QPoint{
            (startPosX),
            (startPosY)
        });
        m_buttonAnimations[i].setEndValue(::QPoint{
            (endPosX),
            (endPosY)
        });
        m_buttonAnimations[i].start();
    }
    ++i;
    {
        const auto startPosX{ m_visibleXPos + m_buttonSize.width() * 3 };
        const auto startPosY{ m_visibleYPos + m_buttonSize.height() * 4 };
        const auto endPosX{ m_unvisibleXPos + m_buttonSize.width() * 3 };
        const auto endPosY{ m_unvisibleYPos + m_buttonSize.height() * 4 };
        m_buttonAnimations[i].setDuration(VirtualKeyPad::animationDuration);
        m_buttonAnimations[i].setStartValue(::QPoint{
            (startPosX),
            (startPosY)
        });
        m_buttonAnimations[i].setEndValue(::QPoint{
            (endPosX),
            (endPosY)
        });
        m_buttonAnimations[i].start();
    }
    ++i;
    {
        const auto startPosX{ m_visibleXPos + m_buttonSize.width() * 0 };
        const auto startPosY{ m_visibleYPos + m_buttonSize.height() * 3 };
        const auto endPosX{ m_unvisibleXPos + m_buttonSize.width() * 0 };
        const auto endPosY{ m_unvisibleYPos + m_buttonSize.height() * 3 };
        m_buttonAnimations[i].setDuration(VirtualKeyPad::animationDuration);
        m_buttonAnimations[i].setStartValue(::QPoint{
            (startPosX),
            (startPosY)
        });
        m_buttonAnimations[i].setEndValue(::QPoint{
            (endPosX),
            (endPosY)
        });
        m_buttonAnimations[i].start();
    }
    ++i;
    {
        const auto startPosX{ m_visibleXPos + m_buttonSize.width() * 1 };
        const auto startPosY{ m_visibleYPos + m_buttonSize.height() * 3 };
        const auto endPosX{ m_unvisibleXPos + m_buttonSize.width() * 1 };
        const auto endPosY{ m_unvisibleYPos + m_buttonSize.height() * 3 };
        m_buttonAnimations[i].setDuration(VirtualKeyPad::animationDuration);
        m_buttonAnimations[i].setStartValue(::QPoint{
            (startPosX),
            (startPosY)
        });
        m_buttonAnimations[i].setEndValue(::QPoint{
            (endPosX),
            (endPosY)
        });
        m_buttonAnimations[i].start();
    }
    ++i;
    {
        const auto startPosX{ m_visibleXPos + m_buttonSize.width() * 2 };
        const auto startPosY{ m_visibleYPos + m_buttonSize.height() * 3 };
        const auto endPosX{ m_unvisibleXPos + m_buttonSize.width() * 2 };
        const auto endPosY{ m_unvisibleYPos + m_buttonSize.height() * 3 };
        m_buttonAnimations[i].setDuration(VirtualKeyPad::animationDuration);
        m_buttonAnimations[i].setStartValue(::QPoint{
            (startPosX),
            (startPosY)
        });
        m_buttonAnimations[i].setEndValue(::QPoint{
            (endPosX),
            (endPosY)
        });
        m_buttonAnimations[i].start();
    }
    ++i;
    {
        const auto startPosX{ m_visibleXPos + m_buttonSize.width() * 3 };
        const auto startPosY{ m_visibleYPos + m_buttonSize.height() * 3 };
        const auto endPosX{ m_unvisibleXPos + m_buttonSize.width() * 3 };
        const auto endPosY{ m_unvisibleYPos + m_buttonSize.height() * 3 };
        m_buttonAnimations[i].setDuration(VirtualKeyPad::animationDuration);
        m_buttonAnimations[i].setStartValue(::QPoint{
            (startPosX),
            (startPosY)
        });
        m_buttonAnimations[i].setEndValue(::QPoint{
            (endPosX),
            (endPosY)
        });
        m_buttonAnimations[i].start();
    }
    ++i;
    {
        const auto startPosX{ m_visibleXPos + m_buttonSize.width() * 0 };
        const auto startPosY{ m_visibleYPos + m_buttonSize.height() * 2 };
        const auto endPosX{ m_unvisibleXPos + m_buttonSize.width() * 0 };
        const auto endPosY{ m_unvisibleYPos + m_buttonSize.height() * 2 };
        m_buttonAnimations[i].setDuration(VirtualKeyPad::animationDuration);
        m_buttonAnimations[i].setStartValue(::QPoint{
            (startPosX),
            (startPosY)
        });
        m_buttonAnimations[i].setEndValue(::QPoint{
            (endPosX),
            (endPosY)
        });
        m_buttonAnimations[i].start();
    }
    ++i;
    {
        const auto startPosX{ m_visibleXPos + m_buttonSize.width() * 1 };
        const auto startPosY{ m_visibleYPos + m_buttonSize.height() * 2 };
        const auto endPosX{ m_unvisibleXPos + m_buttonSize.width() * 1 };
        const auto endPosY{ m_unvisibleYPos + m_buttonSize.height() * 2 };
        m_buttonAnimations[i].setDuration(VirtualKeyPad::animationDuration);
        m_buttonAnimations[i].setStartValue(::QPoint{
            (startPosX),
            (startPosY)
        });
        m_buttonAnimations[i].setEndValue(::QPoint{
            (endPosX),
            (endPosY)
        });
        m_buttonAnimations[i].start();
    }
    ++i;
    {
        const auto startPosX{ m_visibleXPos + m_buttonSize.width() * 2 };
        const auto startPosY{ m_visibleYPos + m_buttonSize.height() * 2 };
        const auto endPosX{ m_unvisibleXPos + m_buttonSize.width() * 2 };
        const auto endPosY{ m_unvisibleYPos + m_buttonSize.height() * 2 };
        m_buttonAnimations[i].setDuration(VirtualKeyPad::animationDuration);
        m_buttonAnimations[i].setStartValue(::QPoint{
            (startPosX),
            (startPosY)
        });
        m_buttonAnimations[i].setEndValue(::QPoint{
            (endPosX),
            (endPosY)
        });
        m_buttonAnimations[i].start();
    }
    ++i;
    {
        const auto startPosX{ m_visibleXPos + m_buttonSize.width() * 3 };
        const auto startPosY{ m_visibleYPos + m_buttonSize.height() * 2 };
        const auto endPosX{ m_unvisibleXPos + m_buttonSize.width() * 3 };
        const auto endPosY{ m_unvisibleYPos + m_buttonSize.height() * 2 };
        m_buttonAnimations[i].setDuration(VirtualKeyPad::animationDuration);
        m_buttonAnimations[i].setStartValue(::QPoint{
            (startPosX),
            (startPosY)
        });
        m_buttonAnimations[i].setEndValue(::QPoint{
            (endPosX),
            (endPosY)
        });
        m_buttonAnimations[i].start();
    }
    ++i;
    {
        const auto startPosX{ m_visibleXPos + m_buttonSize.width() * 0 };
        const auto startPosY{ m_visibleYPos + m_buttonSize.height() * 1 };
        const auto endPosX{ m_unvisibleXPos + m_buttonSize.width() * 0 };
        const auto endPosY{ m_unvisibleYPos + m_buttonSize.height() * 1 };
        m_buttonAnimations[i].setDuration(VirtualKeyPad::animationDuration);
        m_buttonAnimations[i].setStartValue(::QPoint{
            (startPosX),
            (startPosY)
        });
        m_buttonAnimations[i].setEndValue(::QPoint{
            (endPosX),
            (endPosY)
        });
        m_buttonAnimations[i].start();
    }
    ++i;
    {
        const auto startPosX{ m_visibleXPos + m_buttonSize.width() * 1 };
        const auto startPosY{ m_visibleYPos + m_buttonSize.height() * 1 };
        const auto endPosX{ m_unvisibleXPos + m_buttonSize.width() * 1 };
        const auto endPosY{ m_unvisibleYPos + m_buttonSize.height() * 1 };
        m_buttonAnimations[i].setDuration(VirtualKeyPad::animationDuration);
        m_buttonAnimations[i].setStartValue(::QPoint{
            (startPosX),
            (startPosY)
        });
        m_buttonAnimations[i].setEndValue(::QPoint{
            (endPosX),
            (endPosY)
        });
        m_buttonAnimations[i].start();
    }
    ++i;
    {
        const auto startPosX{ m_visibleXPos + m_buttonSize.width() * 2 };
        const auto startPosY{ m_visibleYPos + m_buttonSize.height() * 1 };
        const auto endPosX{ m_unvisibleXPos + m_buttonSize.width() * 2 };
        const auto endPosY{ m_unvisibleYPos + m_buttonSize.height() * 1 };
        m_buttonAnimations[i].setDuration(VirtualKeyPad::animationDuration);
        m_buttonAnimations[i].setStartValue(::QPoint{
            (startPosX),
            (startPosY)
        });
        m_buttonAnimations[i].setEndValue(::QPoint{
            (endPosX),
            (endPosY)
        });
        m_buttonAnimations[i].start();
    }
    ++i;
    {
        const auto startPosX{ m_visibleXPos + m_buttonSize.width() * 3 };
        const auto startPosY{ m_visibleYPos + m_buttonSize.height() * 1 };
        const auto endPosX{ m_unvisibleXPos + m_buttonSize.width() * 3 };
        const auto endPosY{ m_unvisibleYPos + m_buttonSize.height() * 1 };
        m_buttonAnimations[i].setDuration(VirtualKeyPad::animationDuration);
        m_buttonAnimations[i].setStartValue(::QPoint{
            (startPosX),
            (startPosY)
        });
        m_buttonAnimations[i].setEndValue(::QPoint{
            (endPosX),
            (endPosY)
        });
        m_buttonAnimations[i].start();
    }
    {
        const auto startPosX{ m_visibleXPos + m_buttonSize.width() * 0 };
        const auto startPosY{ m_visibleYPos + m_buttonSize.height() * 0 };
        const auto endPosX{ m_unvisibleXPos + m_buttonSize.width() * 0 };
        const auto endPosY{ m_unvisibleYPos + m_buttonSize.height() * 0 };
        m_textBoxAnimation.setDuration(VirtualKeyPad::animationDuration);
        m_textBoxAnimation.setStartValue(::QPoint{
            (startPosX),
            (startPosY)
        });
        m_textBoxAnimation.setEndValue(::QPoint{
            (endPosX),
            (endPosY)
        });
        m_textBoxAnimation.start();
    }
}

///////////////////////////////////////////////////////////////////////////
void VirtualKeyPad::write(
    const QString& str
)
{
    if (m_isVisible) {
        m_textBox.addText(str);
        m_textBox.print();
    }
}

///////////////////////////////////////////////////////////////////////////
void VirtualKeyPad::validate()
{
    try {
        m_values.emplace_back(m_textBox.getText());
        m_textBox.clearLine();
        m_textBox.addLine("");
        m_textBox.print();

        if (!--m_remainingValues && m_validateCallback) {
            m_validateCallback.value()(m_values);
        }
    } catch (const std::exception& e) {
        new ErrorNotification{ m_window, e.what() };
    }

    if (!m_remainingValues) {
        this->conceal();
    }
}
