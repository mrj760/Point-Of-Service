#include <POS/UI/ProductContainer.hpp>


///////////////////////////////////////////////////////////////////////////
ProductContainer::ProductContainer( QWidget& window) noexcept : ProductContainer{ window, 0, 0, 0, 0 }
{}

///////////////////////////////////////////////////////////////////////////
ProductContainer::ProductContainer( QWidget& window,
                                    int xPos, int yPos, int xSize, int ySize ) noexcept
    : m_window{ window }
    , m_table{ new QTableWidget{ 0, 3, &window } }
    , m_totalTextBox{ window, xPos, yPos + ySize - (18 * 2 + 2), xSize, 18 }
    , m_fundsTextBox{ window, xPos, yPos + ySize - 18, xSize, 18 }
{
    for (int i { 0 }; true; ++i) {
        if (std::ifstream ifs("database/cart/Cart" + std::to_string(i) + ".csv"); !ifs.good()) {
            m_id = QString::number(i);
            break;
        }
    }

    m_table->move((xPos), (yPos));
    m_table->resize((xSize), (ySize - (20 * 2)));
    m_table->verticalHeader()->hide();
    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table->setSelectionBehavior(QAbstractItemView::SelectRows);

    {
        QStringList headers;
        headers << "Price" << "Quantity" << "Name";
        m_table->setHorizontalHeaderLabels(headers);
    }

    m_table->setColumnWidth(0, 80);
    m_table->setColumnWidth(1, 60);
    m_table->horizontalHeader()->setStretchLastSection(true);

    m_totalTextBox.setVerticalScrollBarPolicy(::Qt::ScrollBarAlwaysOff);
    m_fundsTextBox.setVerticalScrollBarPolicy(::Qt::ScrollBarAlwaysOff);
    this->printTotal();
    this->printFunds();
    m_table->show();
}

///////////////////////////////////////////////////////////////////////////
void ProductContainer::load(const QString& id)
{
    //    if (std::ifstream ifs("database/cart/Cart" + id.toStdString() + ".csv"); !ifs.good()) {
    //        throw std::runtime_error{ "Cart ID does not exist" };
    //    }

    this->clear();
    m_products.clear();

    m_id = id;
    //    auto db{ std::make_shared<::db::Cart>("Cart" + m_id) };
    //    for (auto& product : db->retrieveAll()) {
    //        this->add(product); }
}


///////////////////////////////////////////////////////////////////////////
void ProductContainer::save()
{
    //    std::remove(QString{ "database/cart/Cart" + m_id + ".csv" }.toStdString().c_str());
    //    auto db{ Cart::get("Cart" + m_id) };
    //    for (auto& product : m_products) {
    //        db->insert(product);
    //    }
}

///////////////////////////////////////////////////////////////////////////
int ProductContainer::add(Item *product)
{
    m_products.push_back(product);

    const auto index{ m_products.size() - 1 };

    m_table->insertRow((index));
    m_table->setCurrentIndex(m_table->model()->index((index), 0));

    QString dollarstr = QString::number(m_funds / 100);
    QString centstr = QString::number(m_funds % 100);
    while (centstr.size() < 2)
        centstr = "0" + centstr;

    m_table->setItem((index), 0,
                     new QTableWidgetItem{ "$" + dollarstr + "." + centstr });
    m_table->setItem((index), 1,
                     new QTableWidgetItem{ product->qty });
    m_table->setItem((index), 2,
                     new QTableWidgetItem{ product->name });

    this->printTotal();

    return index;
}

///////////////////////////////////////////////////////////////////////////
int ProductContainer::size()
{
    return m_products.size();
}

///////////////////////////////////////////////////////////////////////////
int ProductContainer::emplaceFromId( const std::vector<QString>& ids)
{
//    return this->addProduct::getFromDataBase(ids[0], m_dbProducts));
    int id = ids[0].toInt();
    Item *item = dbmanager::getItem(id);
    return add(item); //, m_dbProducts));
}

///////////////////////////////////////////////////////////////////////////
int ProductContainer::addFunds(const std::vector<QString>& values)
{
    m_funds += (values[0]).toInt() * 100;
    if (auto it{ values[0].indexOf(".") }; it != -1) {
        //m_funds += (values[0].last(it + 1).toInt());
    }
    this->printFunds();
    return m_funds;
}

///////////////////////////////////////////////////////////////////////////
bool ProductContainer::pay()
{
    int total{ 0 };
    for (const auto& p : m_products) {
        total += p->cents * p->qty;
    }
    if (m_funds >= total) {
        this->clear();
        m_funds -= total;
        this->printFunds();
        std::remove(QString{ "database/cart/Cart" + m_id + ".csv" }.toStdString().c_str());
        return true;
    }
    return false;
}

///////////////////////////////////////////////////////////////////////////
void ProductContainer::remove(int productIndex)
{
    m_table->removeRow((productIndex));
    m_products.erase(m_products.begin() + static_cast<long>(productIndex));
    this->printTotal();
}

///////////////////////////////////////////////////////////////////////////
void ProductContainer::removeSelected()
{
    if (!m_products.empty()) {
        auto productIndex{ m_table->selectionModel()->selectedRows().front().row() };
        m_table->removeRow(productIndex);
        m_products.erase(m_products.begin() + productIndex);
        if (productIndex) {
            m_table->setCurrentIndex(m_table->model()->index(productIndex - 1, 0));
        } else {
            m_table->setCurrentIndex(m_table->model()->index(0, 0));
        }
        this->printTotal();
    } else {
        new ErrorNotification{ m_window, "No remaining item to delete" };
    }
}

///////////////////////////////////////////////////////////////////////////
void ProductContainer::clear()
{
    while (m_table->rowCount()) {
        m_table->removeRow(0);
    }
    m_products.clear();
    this->printTotal();
}

///////////////////////////////////////////////////////////////////////////
void ProductContainer::setReadOnly(bool value)
{
    m_table->setDisabled(value);
}

///////////////////////////////////////////////////////////////////////////
void ProductContainer::printTotal()
{
    int total{ 0 };
    for (const auto& p : m_products) {
        total += p->cents * p->qty;
    }
    m_totalTextBox.clearLine();
//    QString dollarsstr = QString::number(m_funds / 100);
//    QString centsstr = QString::number(m_funds % 100);
    QString dollarsstr = QString::number(total / 100);
    QString centsstr = QString::number(total % 100);
    while (centsstr.size() < 2)
        centsstr = "0" + centsstr;
    m_totalTextBox.addLine("Funds: $" + dollarsstr + "." + centsstr);
    m_totalTextBox.print();
}

///////////////////////////////////////////////////////////////////////////
void ProductContainer::printFunds()
{
    m_fundsTextBox.clearLine();
    QString dollarsstr = QString::number(m_funds / 100);
    QString centsstr = QString::number(m_funds % 100);
    while (centsstr.size() < 2)
        centsstr = "0" + centsstr;
    m_fundsTextBox.addLine("Funds: $" + dollarsstr + "." + centsstr);
    m_fundsTextBox.print();
}
