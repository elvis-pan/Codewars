#include <bits/stdc++.h>
using namespace std;

int precedence(char op) {
  if (op == '+' || op == '-')
    return 1;
  if (op == '*' || op == '/')
    return 2;
  if (op == '~')
    return 3;
  return 0;
}

double apply(double a, double b, char op) {
  if (op == '+') return a+b;
  if (op == '-') return a-b;
  if (op == '*') return a*b;
  if (op == '/') return a/b;
  assert(false); // Should not happen
  return 0.0;
}

double calc(string expression) {
  stack<double> nums;
  stack<char> ops;
  int i = 0;
  for (i = 0; i < (int)expression.size(); ++i) {
    char c = expression[i];
    if (c == ' ')
      continue;
    else if (c == '(')
      ops.push(c);
    else if (isdigit(c)) {
      double val = 0.0;
      while (i < (int)expression.size() && isdigit(expression[i])) {
        val = val*10.0 + double(expression[i]-'0');
        ++i;
      }
      if (expression[i] == '.') {
        double d = 0.1;
        while (i < (int)expression.size() && isdigit(expression[i])) {
          val += d*double(expression[i]-'0');
          d /= 10.0;
          ++i;
        }
      }
      nums.push(val);
      --i;
    }
    // Closing brace
    else if (c == ')') {
      while (!ops.empty() && ops.top() != '(') {
        double val2 = nums.top(); nums.pop();
        char op = ops.top(); ops.pop();
        if (op == '~') {
          nums.push(-val2);
          continue;
        }
        double val1 = nums.top(); nums.pop();
        nums.push(apply(val1, val2, op));
      }
      ops.pop(); // opening brace
    }
    // negate
    else {
      if (c == '-') {
        bool neg = false;
        if (i == 0)
          neg = true;
        else {
          for (int j = i-1; j >= 0; --j) {
            if (isdigit(expression[j]) || expression[j] == ')') break;
            else if (expression[j] != ' ') {
              neg = true;
              break;
            }
          }
        }
        if (neg) {
          ops.push('~');
          continue;
        }
      }
      while (!ops.empty() && precedence(ops.top()) >= precedence(expression[i])) {
        double val2 = nums.top(); nums.pop();
        char op = ops.top(); ops.pop();
        if (op == '~') {
          nums.push(-val2);
          continue;
        }
        double val1 = nums.top(); nums.pop();
        nums.push(apply(val1, val2, op));
      }
      ops.push(c);
    }
  }
  while (!ops.empty()) {
    double val2 = nums.top(); nums.pop();
    char op = ops.top(); ops.pop();
    if (op == '~') {
      nums.push(-val2);
      continue;
    }
    double val1 = nums.top(); nums.pop();
    nums.push(apply(val1, val2, op));
  }
  return nums.top();
}
