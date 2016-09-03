#ifndef PARSER_H
#define PARSER_H

#include "QWidget"

class parser {
 public:
  parser();
  QString convertToRPN(QString input);
  QString evaluateRPN(QString expression);

 private:
  bool comparePrecedence(QChar a, QChar b);
  double evaluate(double left, double right, QChar op);
};
#endif // PARSER_H
