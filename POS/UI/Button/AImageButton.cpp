#include <POS/UI/Button/AImageButton.hpp>

// Constructors

///////////////////////////////////////////////////////////////////////////
AImageButton::AImageButton(
        QWidget& window, const QString& filename,
        int xPos, int yPos, int xSize, int ySize ) noexcept
    : QPushButton{ &window }
{
    this->setIcon(::QIcon{ ("./assets/icon/" + filename).toStdString().c_str() });
    this->setIconSize(QSize{ xSize, ySize });
    this->move(xPos, yPos);
    this->resize(xSize, ySize);
    this->show();
}

///////////////////////////////////////////////////////////////////////////
AImageButton::AImageButton(
        QWidget& window, const QString& filename, const QString& tooltip,
        int xPos, int yPos,int xSize, int ySize) noexcept
    : AImageButton{ window, filename, xPos, yPos, xSize, ySize }
{
    this->setToolTip(tooltip.toStdString().c_str());
}

///////////////////////////////////////////////////////////////////////////
AImageButton::~AImageButton() noexcept = default;
