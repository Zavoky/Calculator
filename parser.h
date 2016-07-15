#ifndef PARSER_H
#define PARSER_H

#include "QWidget"

class parser {
 public:
  parser();
  QString convertToRPN(QString input);
  QString evaluateRPN(QString expression);

 private:
  bool compare(QChar a, QChar b);
  int evaluate(int left, int right, QChar op);
};
#endif // PARSER_H
