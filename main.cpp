#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include <QMessageBox>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Create main window
    QWidget window;
    window.setWindowTitle("Temperature Converter");

    // Widgets
    QLabel *inputLabel = new QLabel("Enter Temperature:");
    QLineEdit *inputEdit = new QLineEdit();

    QLabel *fromLabel = new QLabel("From:");
    QComboBox *fromCombo = new QComboBox();
    fromCombo->addItems({"Celsius", "Fahrenheit", "Kelvin"});

    QLabel *toLabel = new QLabel("To:");
    QComboBox *toCombo = new QComboBox();
    toCombo->addItems({"Celsius", "Fahrenheit", "Kelvin"});

    QPushButton *convertButton = new QPushButton("Convert");
    QLabel *resultLabel = new QLabel("Result: ");

    // Layout
    QVBoxLayout *mainLayout = new QVBoxLayout();
    QHBoxLayout *inputLayout = new QHBoxLayout();
    QHBoxLayout *fromLayout = new QHBoxLayout();
    QHBoxLayout *toLayout = new QHBoxLayout();

    inputLayout->addWidget(inputLabel);
    inputLayout->addWidget(inputEdit);

    fromLayout->addWidget(fromLabel);
    fromLayout->addWidget(fromCombo);

    toLayout->addWidget(toLabel);
    toLayout->addWidget(toCombo);

    mainLayout->addLayout(inputLayout);
    mainLayout->addLayout(fromLayout);
    mainLayout->addLayout(toLayout);
    mainLayout->addWidget(convertButton);
    mainLayout->addWidget(resultLabel);

    window.setLayout(mainLayout);
    window.resize(300, 200);

    // Lambda function for conversion
    QObject::connect(convertButton, &QPushButton::clicked, [&]() {
        bool ok;
        double temp = inputEdit->text().toDouble(&ok);
        if (!ok) {
            QMessageBox::warning(&window, "Invalid Input", "Please enter a valid number!");
            return;
        }

        QString fromUnit = fromCombo->currentText();
        QString toUnit = toCombo->currentText();
        double result = temp;

        // Convert input to Celsius first
        if (fromUnit == "Fahrenheit") result = (temp - 32) * 5 / 9;
        if (fromUnit == "Kelvin") result = temp - 273.15;

        // Convert from Celsius to target unit
        if (toUnit == "Fahrenheit") result = result * 9 / 5 + 32;
        if (toUnit == "Kelvin") result = result + 273.15;

        resultLabel->setText("Result: " + QString::number(result, 'f', 2) + " " + toUnit);
    });

    window.show();
    return app.exec();
}
