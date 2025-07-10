#include "contentwindow.h"


ContentWindow::ContentWindow(QWidget* parent)
    : QWidget(parent)
{
    initializeContentWindow();
    connectContentWindow();
}

ContentWindow::~ContentWindow()
{
    delete listView;
}

void ContentWindow::initializeContentWindow()
{
    combobox = new QComboBox(this);
    combobox->addItems({ tr("Power"), tr("Root"), tr("Factorial") });

    checkbox_isWrite = new QCheckBox(tr("Save to history"), this);
    checkbox_isWrite->setChecked(true);

    textedit_input = new QTextEdit(this);
    textedit_input->setPlaceholderText(tr("Enter a number..."));
    textedit_input->setFixedHeight(50);

    label_output = new QLabel(tr("Result will appear here"), this);
    label_output->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    label_output->setAlignment(Qt::AlignCenter);
    label_output->setMinimumHeight(30);

    button_count = new QPushButton(tr("Calculate"), this);
    button_showlist = new QPushButton(tr("Show history"), this);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(combobox);
    mainLayout->addWidget(textedit_input);
    mainLayout->addWidget(button_count);
    mainLayout->addWidget(button_showlist);

    QHBoxLayout* bottomLayout = new QHBoxLayout;    
    bottomLayout->addWidget(checkbox_isWrite);
    bottomLayout->addStretch();
    bottomLayout->addWidget(label_output);
    mainLayout->addLayout(bottomLayout);

    listView = new HistoryWidget();
    listView->hide();

    setLayout(mainLayout);
    is_m = 0;
    this->setWindowTitle(tr("Content window"));
    qDebug(logInfo()) << "ContentWindow initialized.";
}

void ContentWindow::clear()
{
    label_output->setText(tr("Result will appear here"));
    textedit_input->setText(tr(""));
    g_history.clear();
    listView->clear();
    is_m = 0;
} 

void ContentWindow::setModified(bool c)
{
    is_m = c;
}

void ContentWindow::connectContentWindow()
{
    connect(button_count, &QPushButton::clicked,
            this, &ContentWindow::onButtonCalculatePress);
    connect(button_showlist, &QPushButton::clicked,
            this, &ContentWindow::onButtonShowPress);
    qDebug(logInfo()) << "ContentWindow connected.";
}

void ContentWindow::handle()
{
    QString s = textedit_input->toPlainText().trimmed();
    bool ok = false;
    double base = s.toDouble(&ok);
    if (!ok) {
        QMessageBox::warning(this, tr("Input Error"), tr("Please enter a valid number."));
        qDebug(logWarning()) << "User entered " << s << " and that's not a number";
        return;
    }

    QString entry;
    double result = 0.0;


    int idx = combobox->currentIndex();
    if (idx == 0)
        handle_pow(base, entry, result);
    else if (idx == 1)
        handle_root(base, entry, result);
    else if (idx == 2)
        handle_fact(base, entry, result, s);

    if(entry.isEmpty())
    {
        label_output->setText(tr("Result will appear here"));
    }
    else
    {
        if(checkbox_isWrite->isChecked()) {
            is_m = 1;
            label_output->setText(entry);
            listView->addItem(entry);
            g_history.append(entry);
            qDebug(logInfo()) << tr("Appended to history:") << entry;
        }
    }
}


void ContentWindow::handle_root(qreal base, QString& entry, qreal& result, QString s)
{
    qDebug(logInfo()) << "Root handler is called.";
    bool expOk = false;
    int degree = QInputDialog::getInt(this, tr("Root"),
        tr("Enter root degree (positive integer):"), 2,
        1, INT_MAX, 1, &expOk);
    if (!expOk) 
    {
        QMessageBox::warning(this, tr("Input Error"), tr("Invalid number. Please enter a non-negative integer for root."));
        qDebug(logWarning()) << tr("User entered an invalid number");
        return;
    }
    if (degree % 2 == 0 && base < 0) {
        QMessageBox::warning(this, tr("Math Error"), tr("Cannot take even root of a negative number."));
        qDebug(logWarning()) << tr("User entered even root of a negative number.");
        return;
    }
    result = std::pow(base, 1.0 / double(degree));
    entry = QString("%1√%2 = %3").arg(degree).arg(base).arg(result);
}
void ContentWindow::handle_pow(qreal base, QString& entry, qreal& result, QString s)
{
    qDebug(logInfo()) << "Power handler is called.";
    bool expOk = false;
    int exponent = QInputDialog::getInt( this, tr("Power"), 
        tr("Enter exponent (integer):"), 2, INT_MIN, INT_MAX, 1, &expOk
    );
    if (!expOk) 
    {
        QMessageBox::warning(this, tr("Input Error"), tr("Please enter a valid number."));
        qDebug(logWarning()) << tr("User entered an invalid number.");
        return;
    }
    result = std::pow(base, double(exponent));
    entry = QString("%1^%2 = %3").arg(base).arg(exponent).arg(result);
}
void ContentWindow::handle_fact(qreal base, QString& entry, qreal& result, QString s)
{
    qDebug(logInfo()) << "Factorial handler is called.";
    bool intOk = false;
    int n = s.toInt(&intOk);
    if (!intOk || n < 0) {
        QMessageBox::warning(this, tr("Input Error"), tr("Invalid number. Please enter a non-negative integer for factorial."));
        qDebug(logWarning()) << tr("User entered an invalid number.");
        return;
    }
    if (n > 20) {
        QMessageBox::warning(this, tr("Overflow Risk"), tr("Factorial result may overflow for n > 20."));
        qDebug(logWarning()) << tr("With factorial of %1 > 20 exists risk of overflow. Aborting operation...").arg(n);
        return;
    }
    unsigned long long fact = 1;
    for (int i = 2; i <= n; i++)
        fact *= static_cast<unsigned long long>(i);
    result = double(fact);
    entry = QString("%1! = %2").arg(n).arg(fact);
}

void ContentWindow::onButtonCalculatePress()
{
    qDebug(logInfo()) << "Calculate button pressed.";
    handle();
}

void ContentWindow::onButtonShowPress()
{
    qDebug(logInfo()) << "Show history button pressed.";
    showList();
}

void ContentWindow::write(QTextStream& out)
{
    qDebug(logInfo()) << "Writing history to stream.";
    for (const QString& line : g_history) {
        out << line << "\n";
    }
}

void ContentWindow::read(QTextStream& in)
{
    qDebug(logInfo()) << "Reading history from stream.";
    listView->clear();
    g_history.clear();
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (!line.isEmpty()) 
        {
            listView->addItem(line);
            g_history.append(line);
        }
    }
}

void ContentWindow::showList()
{
    listView->show();
}

bool ContentWindow::isModified()
{
    return is_m;
}

void ContentWindow::undo()
{
    textedit_input->undo();
}

void ContentWindow::redo()
{
    textedit_input->redo();
}

void ContentWindow::cut()
{
    textedit_input->cut();
}

void ContentWindow::copy()
{
    textedit_input->copy();
}

void ContentWindow::paste()
{
    textedit_input->paste();
}