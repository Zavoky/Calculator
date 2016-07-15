#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QtWidgets>

QT_BEGIN_NAMESPACE
class QLineEdit;
QT_END_NAMESPACE

class Window : public QWidget {
 Q_OBJECT

 public:
  explicit Window(QWidget *parent = 0);
  ~Window();

 private slots:
  void clickedButton();
  void clickedEnter();
  void clickedClear();

 private:
  QPushButton *createButton(QString text, QSize size, const char *slot);
  QLineEdit *display;
};

#endif // WINDOW_H
