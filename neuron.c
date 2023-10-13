#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double Sigmoid(double x);
double Perceptrone(double *x, double **w, double *b, int perc, int now_perc);
double MSE_loss(double y_true, double y_pred);
double Deriv_Sigmoid(double x);

int main() {
  int out = 1;    // Количество выходных нейронов.
  int input = 2;  // Количество входных нейронов.
  int perceptron = 2;  // Количество нейронов скрытого слоя.
  double *x;           // Массив входных данных.
  double *h;           // Массив скрытых нейронов.
  double **w;  // Массив всех весов.
  double y;    // Выходной нейрон, значение после сигмоиды для применения алгоритма обратного распространения ошибки.
  double *b;   // Порог вхождения.
  x = malloc(input * sizeof(double));
  w = (double **)malloc((input + out) * sizeof(double *));
  for (int i = 0; i < input + out; i++) {
    w[i] = (double *)malloc(perceptron * sizeof(double));
  }
  b = malloc((perceptron + out) * sizeof(double));
  h = malloc(perceptron * sizeof(double));
  for (int i = 0; i < input; i++) {
    printf("x[%d] = ", i + 1);
    scanf("%lf", &x[i]);
  }
  for (int i = 0; i < input + out; i++) {
    for (int j = 0; j < perceptron; j++) {
      if (i == 0) {
        if (j == 0) w[i][j] = 0;
        if (j == 1) w[i][j] = 1;
      }
      if (i == 1) {
        if (j == 0) w[i][j] = 1;
        if (j == 1) w[i][j] = 0;
      }
      if (i == 2) {
        if (j == 0) w[i][j] = 0;
        if (j == 1) w[i][j] = 1;
      }
    }
  }
  for (int i = 0; i < perceptron; i++) {
    h[i] = Perceptrone(x, w, b, input, i);
    printf("h[%d]=%.10lf\n", i + 1, h[i]);
  }
  printf("\n");
  y = Perceptrone(h, w, b, perceptron, input + out - 1);
  free(x);
  free(h);
  free(w);
  free(b);
  printf("out = %.10lf\n", y);
  return 0;
}

double Sigmoid(double x) {
  x = 1 / (1 + exp(-1 * x));
  return x;
}

double Perceptrone(double *x, double **w, double *b, int perc, int now_perc) {
  double q = 0;
  double n[perc];
  for (int i = 0; i < perc; i++) {
    n[perc] = x[i] * w[now_perc][i];
    q = q + n[perc];
  }
  q = b[now_perc];
  return Sigmoid(q);
}

double MSE_loss(double y_true, double y_pred) {
  double g = 0;
  g = pow(y_true - y_pred, 2);
  return g;
}

double Deriv_Sigmoid(double x) {
  double fx = Sigmoid(x);
  return fx * (1 - fx);
}

double Train(double **w, double *x, double *h, double *b, double out) {
  double Learn_rate = 0.01;
  int epoch = 100000;
  for (int i = 0; i < epoch; i++) {
    double sum_out = w[2][0] * h[0] + w[2][1] * h[1] + b[2];
    double output = Sigmoid(sum_out);
    double sum_h1 = w[0][0] * x[0] + w[0][1] * x[1] + b[0];
    double h1 = Sigmoid(sum_h1);
    double sum_h2 = w[1][0] * x[0] + w[1][1] * x[1] + b[1];
    double h2 = Sigmoid(sum_h2);

    double L_yp = -2 * (1 - out);

    double yp_w5 = h[0] * Deriv_Sigmoid(sum_out);
    double yp_w6 = h[1] * Deriv_Sigmoid(sum_out);
    double yp_b3 = Deriv_Sigmoid(sum_out);
    double yp_h1 = w[2][0] * Deriv_Sigmoid(sum_out);
    double yp_h2 = w[2][1] * Deriv_Sigmoid(sum_out);

    double h1_w1 = x[0] * Deriv_Sigmoid(sum_h1);
    double h1_w2 = x[1] * Deriv_Sigmoid(sum_h1);
    double h1_b1 = Deriv_Sigmoid(sum_h1);

    double h2_w3 = x[0] * Deriv_Sigmoid(sum_h2);
    double h2_w4 = x[1] * Deriv_Sigmoid(sum_h2);
    double h2_b2 = Deriv_Sigmoid(sum_h2);

    w[0][0] = w[0][0] - (Learn_rate * L_yp * yp_h1 * h1_w1);
    w[0][1] = w[0][1] - (Learn_rate * L_yp * yp_h1 * h1_w2);
    b[0] = b[0] - (Learn_rate * L_yp * yp_h1 * h1_b1);

    w[1][0] = w[1][0] - (Learn_rate * L_yp * yp_h2 * h2_w3);
    w[1][1] = w[1][1] - (Learn_rate * L_yp * yp_h2 * h2_w4);
    b[1] = b[1] - (Learn_rate * L_yp * yp_h2 * h2_b2);

    w[2][0] = w[2][0] - (Learn_rate * L_yp * yp_w5);
    w[2][1] = w[2][1] - (Learn_rate * L_yp * yp_w6);
    b[2] = b[2] - (Learn_rate * L_yp * yp_b3);
    // if (epoch % 10 == 0) {
    //     double Loss;
    //     Loss = MSE_loss(,out)
    // }
  }
}

// dL/dy_pred = -2 * (1 - y_pred);
// dy_pred/dh1 = w5 * F'(w5 * h1 + w6 * h2 + b3);
// dh1/dw1 = x1 * F'(w1 * x1 + w2 * x2 + b1);
// dL/dw1 = dL/dy_pred * dy_pred/dh1 * dh1/dw1;
