#include <fstream>
#include <iomanip>
#include <iostream>
#include <eigen3/Eigen/Eigen>
#include <vector>

Eigen::Matrix3d transform_mat(double q, double l)
{
    Eigen::Matrix3d transform_matrix;
    double t_x = l*cos(q);
    double t_y = l*sin(q);
    transform_matrix << cos(q), -sin(q), t_x,
                 sin(q), cos(q), t_y,
                 0,0, 1;
    return transform_matrix; 
}

int main(int argc, char* argv[])
{
    std::string input_filename{"joint_angles.txt"};
    if (argc >= 2) {
        input_filename = argv[1];
    }
    std::ifstream ifs(input_filename);

    if (!ifs.good()) {
        std::cerr << "Failed to open file " << input_filename << std::endl;
        return 0;
    }

    double l1{1.0};
    double l2{0.5};
    double l3{0.25};

    while (ifs.peek() != -1)
    {
        double q1, q2, q3;
        ifs >> q1 >> q2 >> q3;

        std:: vector<double> angles;
        angles.push_back(q1);
        angles.push_back(q2);
        angles.push_back(q3);

        std:: vector<double> l_s;
        l_s.push_back(l1);
        l_s.push_back(l2);
        l_s.push_back(l3);

        Eigen::Matrix3d ans = Eigen::Matrix3d::Identity();
        for (int i = 0; i < l_s.size(); i++){
            double angle = angles[i];
            double len = l_s[i];
            ans = ans*transform_mat(angle, len);
            

        }
        std::cout<<std::setprecision(3)<<ans(0,2)<<std::endl;
        std::cout<<std::setprecision(3)<<ans(1,2)<<std::endl;

    }

}
