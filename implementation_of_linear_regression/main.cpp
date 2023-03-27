#include <iostream>
#include <vector>
//#include <tuple> // causes an error
#include <numeric>
#include <cmath>
#include <limits>

using namespace std;

#define pb push_back

class LinearRegression{

private:
    vector<double> m_x_vals;
    vector<double> m_y_vals;
    double m_num_elems;
    double m_a;
    double m_b;
    double m_old_err;

    bool isCorverged(double a, double b){

        double error=0;
        double tresh = 0.001;
        for(int i=0; i<m_num_elems; i++){
            error += ((m_a * m_x_vals[i] + m_b) - m_y_vals[i]) * ((m_a * m_x_vals[i] + m_b) - m_y_vals[i]);
        }
        error /= m_num_elems;
        cout<<"Error "<<error<<"\r\n";
        bool res = (abs(error) > m_old_err - tresh && abs(error) < m_old_err + tresh) ? true : false;
        m_old_err = abs(error);
        return res;
    }

public:
    LinearRegression(vector<double> & m_x_vals, vector<double> & m_y_vals): m_x_vals(m_x_vals),
    m_y_vals(m_y_vals), m_num_elems(m_y_vals.size()), m_old_err(std::numeric_limits<double>::max()) {}
    ~LinearRegression(){}

    void trainAlgorithm(int num_iters_, double a_init, double b_init){

        int iter=0;
        m_a = a_init;
        m_b = b_init;

        while(!isCorverged(m_a, m_b) && iter<num_iters_){
            //update the gradient;
            double step = 2 / double(iter+2);
            double a_grad = 0;
            double b_grad = 0;

            // compute the gradient of error wrt to a

            for(int i=0; i<m_num_elems; i++){
                a_grad += m_x_vals[i] * ((m_a * m_x_vals[i] + m_b) - m_y_vals[i]);
            }
            a_grad = (2*a_grad) / m_num_elems;

            // compute the gradient of error wrt to b

            for(int i=0; i<m_num_elems; i++){
                b_grad += ((m_a * m_x_vals[i] + m_b) - m_y_vals[i]);
            }
            b_grad = (2 * b_grad) / m_num_elems;

            // take a step
            m_a = m_a - (step * a_grad);
            m_b = m_b - (step * b_grad);
            cout<< "a:\t" << m_a << ",b:\t" << m_b << "\r\n";
            cout<< "grad_a:\t" << a_grad << ", grad_b:\t" << b_grad << "\r\n";
            iter++;
        }

    }

    double regress(double x_){
        double res = m_a * x_ + m_b;
        return res;
    }
};

int main()
{
    vector<double> x; x.pb(1); x.pb(2); x.pb(3); x.pb(4); x.pb(5);
    vector<double> y; y.pb(2); y.pb(8); y.pb(2); y.pb(9); y.pb(7); y.pb(6); y.pb(9); y.pb(8); y.pb(6);

    LinearRegression lr(x,y);

    lr.trainAlgorithm(10000, 3, -10);

    cout<<lr.regress(3) << endl;

    return 0;
}
