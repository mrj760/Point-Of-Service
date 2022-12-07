#include <POS/UI/Screen/Home.hpp>

///////////////////////////////////////////////////////////////////////////
Home::Home( TransactionContainer& window /*, std::shared_ptr<::db::Products> dbProducts*/) noexcept
    :
      m_window{ window },
      //    m_dbProducts{ dbProducts }

      m_products {
          m_window.get(),
          //          m_dbProducts,
          int(m_window.getSize().width() * 0.05),
          int(m_window.getSize().height() * 0.05),
          int(m_window.getSize().width() * 0.50),
          int(m_window.getSize().height() * 0.9)
          },

      m_virtualKeyPad {
          m_window.get(),
          m_products,
          int(m_window.getSize().width() * 0.56),
          int(m_window.getSize().height() * 0.05),
          (m_window.getSize().width()),
          int(m_window.getSize().height() * 0.05),
          int(m_window.getSize().width() * 0.39),
          int(m_window.getSize().height() * 0.9)
          },

      m_addProductButton {
          m_window.get(),
          "add.png",
          "Add a product to cart from its ID",
          int(m_window.getSize().width() * 0.56),
          int(m_window.getSize().height() * 0.05),
          int(m_window.getSize().width() * 0.08),
          int(m_window.getSize().height() * 0.08),
          [this]{
            m_virtualKeyPad.reveal(std::bind(&ProductContainer::emplaceFromId, &m_products, std::placeholders::_1));
          } },

      m_removeProductButton{
          m_window.get(),
          "remove.png",
          "Remove the selected product in the cart",
          int(m_window.getSize().width() * 0.56),
          int(m_window.getSize().height() * 0.15),
          int(m_window.getSize().width() * 0.08),
          int(m_window.getSize().height() * 0.08),
          [this] () {m_products.removeSelected();} },

      m_clearCartButton{
          m_window.get(),
          "clear.png",
          "Remove all products in the cart",
          int(m_window.getSize().width() * 0.56),
          int(m_window.getSize().height() * 0.25),
          int(m_window.getSize().width() * 0.08),
          int(m_window.getSize().height() * 0.08),
          [this] () { m_products.clear();} },

      m_addFundsButton{
          m_window.get(),
          "addFunds.png",
          "Add funds to pay the cart",
          int(m_window.getSize().width() * 0.66),
          int(m_window.getSize().height() * 0.05),
          int(m_window.getSize().width() * 0.08),
          int(m_window.getSize().height() * 0.08),
          //          [this] () { m_virtualKeyPad.reveal(std::bind_front(&ProductContainer::addFunds, &m_products)); }
          []{}},

      m_payButton{
          m_window.get(),
          "pay.png",
          "Pay the cart if enough funds",
          int(m_window.getSize().width() * 0.66),
          int(m_window.getSize().height() * 0.15),
          int(m_window.getSize().width() * 0.08),
          int(m_window.getSize().height() * 0.08),
          [this]() {
    if (!m_products.size()) {
        throw std::runtime_error{ "Nothing is present in the cart" };
    } else if (!m_products.pay()) {
        throw std::runtime_error{ "Not enough funds to pay" };
    }
} },

      m_saveCartButton{
       m_window.get(),
       "save.png",
       "Save the current cart into the data base",
       int(m_window.getSize().width() * 0.76),
       int(m_window.getSize().height() * 0.05),
       int(m_window.getSize().width() * 0.08),
       int(m_window.getSize().height() * 0.08),
       [this](){ m_products.save(); } },

      m_loadCartButton{
       m_window.get(),
       "load.png",
       "Replace current cart with the cart retrieved from the data base with its ID",
       int(m_window.getSize().width() * 0.76),
       int(m_window.getSize().height() * 0.15),
       int(m_window.getSize().width() * 0.08),
       int(m_window.getSize().height() * 0.08),
       [this](){
    m_virtualKeyPad.reveal([this](const std::vector<QString>& ids){
        m_products.load(ids[0]);
    });
} },

      m_exitButton{
       m_window.get(),
       "exit.png",
       "Close the POS application",
       int(m_window.getSize().width() * 0.86),
       int(m_window.getSize().height() * 0.85),
       int(m_window.getSize().width() * 0.08),
       int(m_window.getSize().height() * 0.08),
       [this](){
            m_window.get().close();
        }}

{
//    m_products.emplace(1uz, "article1"s, 10'20ll, 2uz);
//    m_products.emplace(1uz, "article2"s, 22'31ll, 1uz);
}


///////////////////////////////////////////////////////////////////////////
VirtualKeyPad& Home::getVirtualKeyPad()
{
    return m_virtualKeyPad;
}
