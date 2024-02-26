#include <bits/stdc++.h>
#include <math.h>
#include <cstdlib>
#include <ctime>
#define SERVER_SIZE 1
#define TEST_CNT 4000
using namespace std;

typedef struct {
  double packet_len;
  double interval_time;
  double arrival_time;
  double wait_time;
  double start_time;
} packet;

double exp_result(double x, double lambda)
{
  return log(x) / (-1 * lambda);
}

double pareto_result(double x, double alpha, double k)
{
  if(x == 0)  return k;
  else return k / pow(x, 1.0/alpha);
}

int main(void)
{
  double lambda;//lambda of exponential distribution
  cout << "input lambda for exponential function: ";
  cin >> lambda;
  srand((unsigned int) time(NULL));
  double clock = 0;
  int n = 0;
  int nw = 0;
  double sw = 0;
  double sa = 0;
  double L = 0; // sum of runtime
  packet queue[TEST_CNT];
  bool flag = false; //true -> running
  double sum_interval = 0;
  double sum_service = 0;

  double rand_num = (double)rand() / (double)RAND_MAX;
  clock += exp_result(rand_num, lambda);
  int i = 0, j = 0;
  while(j < TEST_CNT) {
    double rand_num = (double)rand() / (double)RAND_MAX;
    double interval_t = exp_result(rand_num, lambda);
    double packet_len = pareto_result(rand_num, 3, 1);
    if(i < TEST_CNT) {
      queue[i].arrival_time = clock;
      queue[i].interval_time = interval_t;
      queue[i].packet_len = packet_len;
      sum_service += packet_len;
      sum_interval += interval_t;
      i++;
      cout << "packet " << i << " arrived at " << clock << endl;
    }
    if(!flag) {
      cout << "packet " << j << " begins at " << clock << endl;
      flag = true;
      queue[j].start_time = clock;
      queue[j].wait_time = queue[j].arrival_time - queue[j].start_time;
    } else {
      if(clock - queue[j].start_time >= queue[j].packet_len) {
        cout << "packet " << j << " ends at " << clock << endl;
        flag = false;
        j++;
      }
    }
    clock += interval_t;
  }

  double mean_inter_arrival_time = sum_interval / TEST_CNT;
  double arrival_rate = TEST_CNT / sum_interval;
  double mean_service_time = sum_service / TEST_CNT;
  double service_rate = TEST_CNT / sum_service;
  double proportion_busy_time = (sum_service) / (sum_service + sum_interval);
  double throughput = TEST_CNT / (sum_service + sum_interval);
  cout << "Mean inter arrival time: " << mean_inter_arrival_time << endl; // 0.3xxx -> average of exponential distribution
  cout << "Arrival rate: " << arrival_rate << endl;
  cout << "Mean service time: " << mean_service_time << endl; // 1.5xxx -> average of pareto distribution
  cout << "Service rate: " << service_rate << endl;
  cout << "Proportion busy time: " << proportion_busy_time << endl;
  cout << "Throughput: " << throughput << endl;
}