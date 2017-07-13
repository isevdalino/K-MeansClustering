#include <iostream>
#include <math.h>
#include "KMeansClustering.h"

using namespace std;

//A rather large unit test where i test all the main functionality of the algorithm

void testMainKMeansClusteringFunctionality()
{
    vector<Point> a;
    vector<double> coordinates;
    coordinates.push_back(70);
    coordinates.push_back(75);
    a.push_back(Point(coordinates));
    coordinates.clear();
    coordinates.push_back(137);
    coordinates.push_back(79);
    a.push_back(Point(coordinates));
    coordinates.clear();
    coordinates.push_back(162);
    coordinates.push_back(77);
    a.push_back(Point(coordinates));
    coordinates.clear();
    coordinates.push_back(140);
    coordinates.push_back(44);
    a.push_back(Point(coordinates));
    coordinates.clear();
    coordinates.push_back(118);
    coordinates.push_back(58);
    a.push_back(Point(coordinates));
    coordinates.clear();
    coordinates.push_back(130);
    coordinates.push_back(120);
    a.push_back(Point(coordinates));
    coordinates.clear();
    coordinates.push_back(189);
    coordinates.push_back(57);
    a.push_back(Point(coordinates));
    coordinates.clear();
    coordinates.push_back(88);
    coordinates.push_back(95);
    a.push_back(Point(coordinates));
    coordinates.clear();

    coordinates.push_back(146);
    coordinates.push_back(285);
    a.push_back(Point(coordinates));
    coordinates.clear();
   coordinates.push_back(150);
    coordinates.push_back(300);
    a.push_back(Point(coordinates));
    coordinates.clear();
    coordinates.push_back(116);
    coordinates.push_back(273);
    a.push_back(Point(coordinates));
    coordinates.clear();
    coordinates.push_back(137);
    coordinates.push_back(311);
    a.push_back(Point(coordinates));
    coordinates.clear();
    coordinates.push_back(106);
    coordinates.push_back(252);
    a.push_back(Point(coordinates));
    coordinates.clear();

    coordinates.push_back(343);
    coordinates.push_back(80);
    a.push_back(Point(coordinates));
    coordinates.clear();
    coordinates.push_back(300);
    coordinates.push_back(79);
    a.push_back(Point(coordinates));
    coordinates.clear();
    coordinates.push_back(332);
    coordinates.push_back(100);
    a.push_back(Point(coordinates));
    coordinates.clear();
    coordinates.push_back(326);
    coordinates.push_back(129);
    a.push_back(Point(coordinates));
    coordinates.clear();
    coordinates.push_back(322);
    coordinates.push_back(82);
    a.push_back(Point(coordinates));
    coordinates.clear();
    coordinates.push_back(346);
    coordinates.push_back(116);
    a.push_back(Point(coordinates));
    coordinates.clear();
    coordinates.push_back(308);
    coordinates.push_back(101);
    a.push_back(Point(coordinates));
    coordinates.clear();
    coordinates.push_back(317);
    coordinates.push_back(110);
    a.push_back(Point(coordinates));
    coordinates.clear();

    coordinates.push_back(243);
    coordinates.push_back(241);
    a.push_back(Point(coordinates));
    coordinates.clear();
    coordinates.push_back(232);
    coordinates.push_back(292);
    a.push_back(Point(coordinates));
    coordinates.clear();
    coordinates.push_back(282);
    coordinates.push_back(270);
    a.push_back(Point(coordinates));
    coordinates.clear();
    coordinates.push_back(225);
    coordinates.push_back(258);
    a.push_back(Point(coordinates));
    coordinates.clear();
    coordinates.push_back(295);
    coordinates.push_back(251);
    a.push_back(Point(coordinates));
    coordinates.clear();
    coordinates.push_back(248);
    coordinates.push_back(265);
    a.push_back(Point(coordinates));
    coordinates.clear();
    coordinates.push_back(265);
    coordinates.push_back(283);
    a.push_back(Point(coordinates));
    coordinates.clear();
    coordinates.push_back(234);
    coordinates.push_back(277);
    a.push_back(Point(coordinates));
    coordinates.clear();
    coordinates.push_back(265);
    coordinates.push_back(254);
    a.push_back(Point(coordinates));
    coordinates.clear();
    vector<Point> vr;
    loadPointsFromFileIntoVr("inPoints.txt",vr);
    /*for(int i=0;i<vr.size();i++){
        cout<<vr[i]<<endl;
    }*/
    KMeansClustering<Point> clusters(a,4,findDistBtwPoints);
    clusters.printClustersToConsole();
    clusters.printClustersToFile("outPoints.txt");
}

int main(){
    testMainKMeansClusteringFunctionality();
    return 0;
}
