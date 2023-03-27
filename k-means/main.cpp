#include <utility>
#include <cmath>
#include <iostream>
#include <valarray>
#include <vector>
#include <algorithm>

using namespace std;

class KMeans{
public:
    KMeans() {}
    ~KMeans() {}
    KMeans(int k_, vector<pair<double, double> > & data_) : m_k(k_), m_means(k_), m_data(k_) {
    }

    void clusterData(valarray <pair<double,double> > & init_means_, int num_iters_) {
        m_means = init_means_;
        this->assignLabels();

        int i=0;
        while(i < num_iters_ && !this->computeMeans()){
            cout << "Running iteration: " << i << "\r\n";
            //this->computeMeans();
            this->assignLabels();
            i++;
        }
    }

    void printClusters() const {
        for (int k=0; k<m_k; k++) {
            for(pair<double, double> const & it : m_data[k]) {
                cout << " [" << it.first << " , " << it.second;
            }
            cout << "\r\n";
        }
    }

private:

    bool computeMeans() {
        //return true if means are same as previous iteration;
        bool res = true;
        for(int k=0; k<m_k; k++){
            pair<double, double> mean(0,0);
            int num_features_of_k = m_data[k].size();
            for(pair<double, double> const & it : m_data[k]) {
                mean.first += it.first;
                mean.second += it.second;
            }
            mean.first /= num_features_of_k;
            mean.second /= num_features_of_k;
            res = (m_means[k] == mean && res == true) ? true : false;
            m_means[k] = mean;
            cout << "Cluster centroid << " << k << " :\tx " << mean.first << " , y " << mean.second << "\t";
        }
        cout << "\r\n";
        return res;
    }

    void assignLabels() {
        valarray<vector<pair<double, double> > > new_data(m_k);
        for (auto const & clust : m_data) {
            for (const pair<double, double> & feature : clust) {
                int closest_mean = this->computeClosestCentroid(feature);
                new_data[closest_mean].push_back(feature);
            }
        }
        m_data = new_data;
    }

    int computeClosestCentroid(const pair<double, double> & point_) {
        valarray<double> distances(m_k);
        for (int k=0; k<m_k; k++) {
            double del_x = point_.first - m_means[k].first;
            double del_y = point_.second - m_means[k].second;
            double dist = sqrt((del_x * del_x) + (del_y * del_y));
            distances[k] = dist;
        }
        double * first = & distances[0];
        double *last = & distances[m_k-1];
        int closest_mean = distance(first, min_element(first, last));
        return closest_mean;
    }

    //private data members
    int m_k;
    int m_features;
    valarray<pair<double, double> > m_means; //container to hold the current means;
    valarray<vector<pair<double, double> > > m_data; //array of vectors containing the data
};

int main()
{
    vector<pair<double, double> > data;

    data[0].first=1.1; data[0].second=1.0;
    data[1].first=1.4; data[1].second=2.0;
    data[2].first=3.8; data[2].second=7.0;
    data[3].first=5.0; data[3].second=8.0;
    data[4].first=4.3; data[4].second=6.0;
    data[5].first=8.0; data[5].second=5.0;
    data[6].first=6.0; data[6].second=8.5;
    data[7].first=3.0; data[7].second=2.0;
    data[8].first=9.0; data[8].second=6.0;
    data[9].first=9.1; data[9].second=4.0;

    KMeans km(2, data);
    valarray<pair<double, double> > init_means_;
    init_means_[0].first=1.0; init_means_[0].second=1.0;
    init_means_[1].first=3.0; init_means_[1].second=4.0;

    km.clusterData(init_means_, 10);
    km.printClusters();

    return 0;
}
