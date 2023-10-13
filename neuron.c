#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double Sigmoid(double x);
double dSigmoid(double x);
double Perceptrone(double x1, double w1, double x2, double w2, double b);
double Ypred_h(double x, double y);

int main() {
  double x1, x2, h1, h2, out, w1 = 0.5, w2 = 1, w3 = 2, w4 = -1.5, w5 = 0.5,
                              w6 = 5, b1 = 10, b2 = -4, b3 = 5, Ytrue;
  double L_Ypred, Ypred_h1, Ypred_h2, Ypred_w5, Ypred_w6, Ypred_b3;
  double h1_w1, h1_w2, h1_b1, h2_w3, h2_w4, h2_b2;
  double sig_h1, sig_h2, sig_out, Lr;
  int Epoch = 10000000;
  char c = ' ';
  Lr = 0.001;
  for (int i = 0; i <= Epoch; i++) {
    for (int j = 0; j < 4; j++) {
      if (j == 0) {
        x1 = 80 - 72;
        x2 = 174 - 165;
        Ytrue = 1;
      }
      if (j == 1) {
        x1 = 75 - 72;
        x2 = 183 - 165;
        Ytrue = 0;
      }
      if (j == 0) {
        x1 = 80 - 72;
        x2 = 177 - 165;
        Ytrue = 0; 
      }
      if (j == 1) {
        x1 = 72 - 72;
        x2 = 165 - 165;
        Ytrue = 1;
      }
      h1 = Perceptrone(x1, w1, x2, w2, b1);
      sig_h1 = Sigmoid(h1);
      h2 = Perceptrone(x1, w3, x2, w4, b2);
      sig_h2 = Sigmoid(h2);
      out = Perceptrone(sig_h1, w5, sig_h2, w6, b3);
      sig_out = Sigmoid(out);
      if (i % 1000000 == 0) {
        printf("Ep=%d #%d: %lf\n", i, j + 1, out);
      }
      L_Ypred = -2 * (Ytrue - out);
      Ypred_h1 = Ypred_h(w5, dSigmoid(sig_out));
      Ypred_h2 = Ypred_h(w6, dSigmoid(sig_out));
      Ypred_w5 = Ypred_h(sig_h1, dSigmoid(sig_out));
      Ypred_w6 = Ypred_h(sig_h2, dSigmoid(sig_out));
      Ypred_b3 = dSigmoid(sig_out);
      h1_w1 = Ypred_h(x1, dSigmoid(sig_h1));
      h1_w2 = Ypred_h(x2, dSigmoid(sig_h1));
      h1_b1 = dSigmoid(sig_h1);
      h2_w3 = Ypred_h(x1, dSigmoid(sig_h2));
      h2_w4 = Ypred_h(x2, dSigmoid(sig_h2));
      h2_b2 = dSigmoid(sig_h2);
      w1 = w1 - (Lr * L_Ypred * Ypred_h1 * h1_w1);
      w2 = w2 - (Lr * L_Ypred * Ypred_h1 * h1_w2);
      b1 = b1 - (Lr * L_Ypred * Ypred_h1 * h1_b1);
      w3 = w3 - (Lr * L_Ypred * Ypred_h2 * h2_w3);
      w4 = w4 - (Lr * L_Ypred * Ypred_h2 * h2_w4);
      b2 = b2 - (Lr * L_Ypred * Ypred_h2 * h2_b2);
      w5 = w5 - (Lr * L_Ypred * Ypred_w5);
      w6 = w6 - (Lr * L_Ypred * Ypred_w6);
      b3 = b3 - (Lr * L_Ypred * Ypred_b3);
    }
  }
  printf("w1:%lf\nw2:%lf\t\tw5:%lf\nw3:%lf\t\tw6:%lf\nw4:%lf\n", w1, w2, w5, w3,
         w6, w4);
  printf("b1=%lf; b2=%lf; b3=%lf\n", b1, b2, b3);
  while (c != 'q') {
    printf("x1= ");
    scanf("%lf", &x1);
    printf("x2= ");
    scanf("%lf", &x2);
    x1 = x1 - 72;
    x2 = x2 - 165;
    h1 = Perceptrone(x1, w1, x2, w2, b1);
    sig_h1 = Sigmoid(h1);
    h2 = Perceptrone(x1, w3, x2, w4, b2);
    sig_h2 = Sigmoid(h2);
    out = Perceptrone(sig_h1, w5, sig_h2, w6, b3);
    sig_out = Sigmoid(out);
    if (sig_out >= 0.5) {
      printf("Woman\n");
    } else {
      printf("Man\n");
    }
    printf("press Enter for repeat, or 'q' for exit\n");
    scanf("%c", &c);
  }
  return 0;
}

double Sigmoid(double x) { return 1 / (1 + exp(-x)); }
double dSigmoid(double x) { return x * (1 - x); }
double Perceptrone(double x1, double w1, double x2, double w2, double b) {
  return w1 * x1 + w2 * x2 + b;
}
double Ypred_h(double x, double y) { return x * y; }
// dL/dy_pred = -2 * (1 - y_pred);
// dy_pred/dh1 = w5 * F'(w5 * h1 + w6 * h2 + b3);
// dh1/dw1 = x1 * F'(w1 * x1 + w2 * x2 + b1);
// dL/dw1 = dL/dy_pred * dy_pred/dh1 * dh1/dw1;
