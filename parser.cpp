#include "parser.h"
#include "QtWidgets"

parser::parser() {}

// converts user input to reverse polish notation and returns it
QString parser::convertToRPN(QString input) {
  QStack<QChar> operatorStack;
  QQueue<QChar> outputQueue;
  QChar ops[] = {'+', '-', '*', '/'};
  for (QChar &token : input) {
    // digit check
    if (token > 47 && token < 58 || token == 46) {
      outputQueue.enqueue(token);
    }
    // operator check
    else for (QChar &op : ops) {
      if (token == op) {
        // add a space for easier parsing
        outputQueue.enqueue(32);
        while (!operatorStack.isEmpty() &&
               comparePrecedence(op, operatorStack.top())) {
          outputQueue.enqueue(operatorStack.pop());
          outputQueue.enqueue(32);
        }
        operatorStack.push(token);
        break;
      }
    }
  }
  outputQueue.enqueue(32);
  while (!operatorStack.isEmpty()) {
    outputQueue.enqueue(operatorStack.pop());
  }
  QString expressionRPN;
  while (!outputQueue.isEmpty()) {
    expressionRPN += outputQueue.dequeue();
  }

  return expressionRPN;
}

// evaluates RPN expressions and returns it
QString parser::evaluateRPN(QString expression) {
  QStringList input = expression.split(' ');
  QStack<double> values;
  QChar token;
  double left;
  double right;
  double result;
  for (int i = 0; i < input.length(); i++) {
    token = input[i][0];
    if (token > 47 && token < 58) {
      values.push(input[i].toDouble());
    }
    else {
      // no exceptions for pop() so isEmpty() is used instead
      if (!values.isEmpty()) {
        right = values.pop();
        if (!values.isEmpty()) {
          left = values.pop();
        }
        else {
          return "Invalid Input";
        }
      }
      else {
        return "Invalid Input";
      }
      result = evaluate(left, right, token);
      values.push(result);
    }
  }
  return QString::number(values.pop());
}

// helper function for evaluateRPN
double parser::evaluate(double left, double right, QChar op) {
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

// Returns true if a is less than or equal to b
bool parser::comparePrecedence(QChar a, QChar b) {
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
  return opA <= opB;
}
