#include "window.h"
#include "parser.h"

Window::Window(QWidget *parent) : QWidget(parent) {
  QGridLayout *mainLayout = new QGridLayout;
  mainLayout->setSizeConstraint(QLayout::SetFixedSize);
  setLayout(mainLayout);

  QSize buttonSize(50, 50);

  // create buttons
  display = new QLineEdit();
  QPushButton *buttonDivision = createButton(QChar(0x00F7), buttonSize, SLOT(clickedButton()));
  QPushButton *buttonMultiplication = createButton(QChar(0x00D7), buttonSize, SLOT(clickedButton()));
  QPushButton *buttonSubtract = createButton("-", buttonSize, SLOT(clickedButton()));
  QPushButton *buttonAdd = createButton("+", buttonSize, SLOT(clickedButton()));
  QPushButton *buttonEnter = createButton("=", buttonSize, SLOT(clickedEnter()));
  QPushButton *buttonClear = createButton("clear", buttonSize, SLOT(clickedClear()));
  QPushButton *buttonDigits[10];
  for (int i = 0; i < 10; i++) {
    buttonDigits[i] = createButton(QString::number(i), buttonSize, SLOT(clickedButton()));
  }

  // add buttons to layout
  mainLayout->addWidget(display, 0, 0, 1, 6);
  mainLayout->addWidget(buttonDivision, 1, 3);
  mainLayout->addWidget(buttonMultiplication, 2, 3);
  mainLayout->addWidget(buttonSubtract, 3, 3);
  mainLayout->addWidget(buttonAdd, 4, 3);
  mainLayout->addWidget(buttonEnter, 5, 3);
  mainLayout->addWidget(buttonClear, 5, 2);
  mainLayout->addWidget(buttonDigits[0], 4, 1);
  for (int i=1; i < 10; i++) {
    int row = 3 - (i - 1) / 3;
    int col = (i - 1) % 3;
    mainLayout->addWidget(buttonDigits[i], row, col);
  }
}

void Window::clickedButton() {
  QPushButton *obj = qobject_cast<QPushButton *> (sender());
  if (obj->text() == QChar(0x00F7)) {
    display->setText(display->text() + "/");
    return;
  }
  else if (obj->text() == QChar(0x00D7)) {
    display->setText(display->text() + "*");
    return;
  }
  else {
    display->setText(display->text() + obj->text());
  }
}

void Window::clickedEnter() {
  parser expression;
  QString expressionRPN = expression.convertToRPN(display->text());
  QString text = expression.evaluateRPN(expressionRPN);
  display->setText(text);
}

void Window::clickedClear() {
  display->clear();
}

QPushButton *Window::createButton(QString text, QSize size, const char *slot) {
  QPushButton *button = new QPushButton(text);
  button->setFixedSize(size);
  connect(button, SIGNAL(clicked()), this, slot);
  return button;
}

Window::~Window() {}
