#include "secondwindow.h"

QStringList g_history;

SecondWindow::SecondWindow(QWidget* parent)
    : QWidget(parent)
{
    initializeSecondWindow();
    connectSecondWindow();
}

void SecondWindow::initializeSecondWindow()
{
    // --- Create widgets ---
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

    // --- Layout ---
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(combobox);
    mainLayout->addWidget(textedit_input);
    mainLayout->addWidget(button_count);

    QHBoxLayout* bottomLayout = new QHBoxLayout;
    bottomLayout->addWidget(checkbox_isWrite);
    bottomLayout->addStretch();
    bottomLayout->addWidget(label_output);
    mainLayout->addLayout(bottomLayout);

    setLayout(mainLayout);
    setWindowTitle(tr("Calculator"));
    qDebug(logInfo()) << "SecondWindow initialized.";
}

void SecondWindow::clear()
{
    label_output->setText(tr("Result will appear here"));
    textedit_input->setText(tr(""));
} 

void SecondWindow::setModified(bool c)
{
    textedit_input->setWindowModified(c);
}

void SecondWindow::connectSecondWindow()
{
    // --- Connections ---
    connect(button_count, &QPushButton::clicked,
            this, &SecondWindow::onButtonPress);
    qDebug(logInfo()) << "SecondWindow connected.";
}

void SecondWindow::calculate()
{
    QString s = textedit_input->toPlainText().trimmed();
    bool ok = false;
    double base = s.toDouble(&ok);
    if (!ok) {
        QMessageBox::warning(this, tr("Input Error"), tr("Please enter a valid number."));
        return;
    }

    QString entry;
    double result = 0.0;

    int idx = combobox->currentIndex();
    if (idx == 0) { // Power
        bool expOk = false;
        int exponent = QInputDialog::getInt( this, tr("Power"), 
            tr("Enter exponent (integer):"), 2, INT_MIN, INT_MAX, 1, &expOk
        );
        if (!expOk) 
        {
            QMessageBox::warning(this, tr("Input Error"), tr("Please enter a valid number."));
            return;
        }
        result = std::pow(base, double(exponent));
        entry = QString("%1^%2 = %3")
                    .arg(base)
                    .arg(exponent)
                    .arg(result);

    } else if (idx == 1) { // Root
        bool expOk = false;
        int degree = QInputDialog::getInt(
            this,
            tr("Root"),
            tr("Enter root degree (positive integer):"),
            2,
            1, INT_MAX,
            1,
            &expOk
        );
        if (!expOk) return;
        if (degree % 2 == 0 && base < 0) {
            QMessageBox::warning(
                this,
                tr("Math Error"),
                tr("Cannot take even root of a negative number.")
            );
            return;
        }
        result = std::pow(base, 1.0 / double(degree));
        entry = QString("%1√%2 = %3")
                    .arg(degree)
                    .arg(base)
                    .arg(result);

    } else if (idx == 2) { // Factorial
        bool intOk = false;
        int n = s.toInt(&intOk);
        if (!intOk || n < 0) {
            QMessageBox::warning(
                this,
                tr("Input Error"),
                tr("Please enter a non-negative integer for factorial.")
            );
            return;
        }
        if (n > 20) {
            QMessageBox::warning(
                this,
                tr("Overflow Risk"),
                tr("Factorial result may overflow for n > 20.")
            );
            return;
        }
        unsigned long long fact = 1;
        for (int i = 2; i <= n; ++i)
            fact *= static_cast<unsigned long long>(i);
        result = double(fact);
        entry = QString("%1! = %2").arg(n).arg(fact);

    } else {
        // Should not happen
        return;
    }

    // Display result
    label_output->setText(entry);

    // Save to history if requested
    if (checkbox_isWrite->isChecked()) {
        g_history.append(entry);
        qDebug(logInfo()) << "Appended to history:" << entry;
    }
}

void SecondWindow::onButtonPress()
{
    qDebug(logInfo()) << "Calculate button pressed.";
    calculate();
    
}

void SecondWindow::write(QTextStream& out)
{
    qDebug(logInfo()) << "Writing history to stream.";
    for (const QString& line : g_history) {
        out << line << "\n";
    }
}

void SecondWindow::read(QTextStream& in)
{
    qDebug(logInfo()) << "Reading history from stream.";
    g_history.clear();
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (!line.isEmpty())
            g_history.append(line);
    }
}

bool SecondWindow::isModified()
{
    return textedit_input->isWindowModified();
}

void SecondWindow::undo()
{
    textedit_input->undo();
}

void SecondWindow::redo()
{
    textedit_input->redo();
}

void SecondWindow::cut()
{
    textedit_input->cut();
}

void SecondWindow::copy()
{
    textedit_input->copy();
}

void SecondWindow::paste()
{
    textedit_input->paste();
}