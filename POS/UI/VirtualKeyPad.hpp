#pragma once

#include <POS/UI/Box/ATextBox.hpp>
#include <POS/UI/Button/CustomText.hpp>
#include <POS/UI/ProductContainer.hpp>
#include <POS/UI/ErrorNotification.hpp>

//Enable number typing with virtual key pad
// 9 buttons and a text boxclass VirtualKeyPad
class VirtualKeyPad {

public:

    // Constructors

    explicit VirtualKeyPad( QWidget& window, ProductContainer& products,
                            int visibleXPos, int visibleYPos,
                            int unvisibleXPos, int unvisibleYPos,
                            int xSize, int ySize) noexcept;

    // Animation

    void reveal(std::function<void(const std::vector<QString>&)> validateCallback, int numValues = 1);

    void conceal();

    void write(const QString& str);

    void validate();

private:

    QWidget& m_window;

    bool m_isVisible{ false };
    int m_visibleXPos;
    int m_visibleYPos;
    int m_unvisibleXPos;
    int m_unvisibleYPos;

    QSize m_buttonSize;

    std::optional<std::function<void(const std::vector<QString>&)>> m_validateCallback;

    ATextBox m_textBox;
    std::array<CustomText, 16> m_buttons;

    ProductContainer& m_products;

    QPropertyAnimation m_textBoxAnimation;
    std::array<QPropertyAnimation, 16> m_buttonAnimations;

    static inline constexpr const int animationDuration{ 200 };

    int m_remainingValues{ 0 };
    std::vector<QString> m_values;

};
