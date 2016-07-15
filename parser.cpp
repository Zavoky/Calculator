#include "parser.h"
#include "QtWidgets"

parser::parser() {}

QString parser::convertToRPN(QString input) {
  QStack<QChar> operators;
  QQueue<QChar> digits;
  QChar ops[] = {'+', '-', '*', '/'};
  for (QChar &token : input) {
    // digit check
    if (token > 47 && token < 58) {
      digits.enqueue(token);
    }
    // operator check
    else for (QChar &op : ops) {
      if (token == op) {
        while (!operators.isEmpty() && compare(operators.top(), op)) {
          digits.enqueue(operators.pop());
        }
        operators.push(token);
        break;
      }
    }
  }
  while (!operators.isEmpty()) {
    digits.enqueue(operators.pop());
  }
  QString expressionRPN;
  while (!digits.isEmpty()) {
    expressionRPN += digits.dequeue();
  }
  return expressionRPN;
}

QString parser::evaluateRPN(QString expression) {
  int left, right, result;
  QChar op;
  QStack<int> digits;
  for (QChar token : expression) {
    if (token > 47 && token < 58) {
      digits.push(token.digitValue());
    }
    else {
      op = token;
      right = digits.pop();
      left = digits.pop();
      result = evaluate(left, right, token);
      digits.push(result);
    }
  }
  return QString::number(digits.pop());
}

// Returns result
int parser::evaluate(int left, int right, QChar op) {
  switch (op.toLatin1()) {
    case '+': {
      return left+right;
    }
    case '-': {
      return left-right;
    }
    case '*': {
      return left*right;
    }
    case '/': {
      return left/right;
    }
    default: {
      return 999;
    }
  }
}

// Returns true if a is greater than b
bool parser::compare(QChar a, QChar b) {
  enum class ops {
    opPlus,
    opSub,
    opMult,
    opDiv
  };

  ops opA, opB;
  switch (a.toLatin1()) {
    case '+': {
      opA = ops::opPlus;
      break;
    }
    case '-': {
      opA = ops::opSub;
      break;
    }
    case '*': {
      opA = ops::opMult;
      break;
    }
    case '/': {
      opA = ops::opDiv;
      break;
    }
    default: {
      break;
    }
  }

  switch (b.toLatin1()) {
    case '+': {
      opB = ops::opPlus;
      break;
    }
    case '-': {
      opB = ops::opSub;
      break;
    }
    case '*': {
      opB = ops::opMult;
      break;
    }
    case '/': {
      opB = ops::opDiv;
      break;
    }
    default: {
      break;
    }
  }
  return opA > opB;
}
