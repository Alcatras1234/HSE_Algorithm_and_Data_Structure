#include <iostream>
#include <vector>
#include <random>

class Point {
public:
    Point() : Ax(0), Ay(0) {

    }
    Point(double x, double y) {
        Ax = x;
        Ay = y;
    }
    double X() {
        return Ax;
    }
    double Y() {
        return Ay;
    }
private:
    double Ax;
    double Ay;
};

double get_Random (double x) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1.0, 1.0);
    x = dis(gen);
    return x;
}

int get_Random_int (int x) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(1000, 100000);
    x = dis(gen);
    return x;
}

double point_gen(int R, int N) {
    int M = 0;
    for (int i = 0; i < N; ++i) {
        Point m;
        double x = get_Random(x);
        double y = get_Random(y);
        m = *new Point (x, y);
        if (m.X() * m.X() + m.Y() * m.Y() <= (R*R) ) {
            M++;
        }

    }

    return (static_cast<double>(4 * M) )/ N;;
}

int main() {



    int N = get_Random_int(N);
    int R = 1;

    double pi = point_gen(R, N);
    std::cout<<'N'<<" "<<N<<" "<<"pi"<<" "<<pi;
    //experiment
    //double pi_new = 0;
    //for (int i = 100; i <= 5000; i += 100) {
       // pi_new = point_gen(R, i);
        //std::cout<<pi_new<<std::endl;
   // }
    return 0;
}
