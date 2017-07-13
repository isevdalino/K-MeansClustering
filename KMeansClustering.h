#ifndef KMEANSCLUSTERING_H
#define KMEANSCLUSTERING_H
#include <vector>
#include <ctime>
#include <iostream>
#include <cstdlib>
#include<utility>
#include <functional>
#include <queue>
#include<string>
#include <unordered_map>
#include <fstream>
#include <ostream>

//A structure that represents point in given dimension.
//In this structure implementation we count on the hope that all potential users will be
//smart enough to only compare points of the same dimension...big mistake if we go by the book!But anyway.

struct Point{
    std::vector<double> coordinates;
    int dimension;
  Point(std::vector<double> coordinates){
    this->coordinates=coordinates;
    dimension=coordinates.size();
  }
  bool operator<(const Point& other)const{
    return coordinates<other.coordinates;
  }
bool operator==(const Point& other)const{
    return coordinates==other.coordinates;
  }
  friend std::ostream& operator<<(std::ostream& out,Point point);
};
std::ostream& operator<<(std::ostream& out,Point point){
  for(int i=0;i<point.dimension;i++){
    out<<point.coordinates[i]<<" ";
  }
  out<<std::endl;
}

double findDistBtwPoints(const Point& p1,const Point& p2){
  double distSum=0;
  for(int i=0;i<p1.dimension;i++){
    distSum+=(p1.coordinates[i]-p2.coordinates[i])*(p1.coordinates[i]-p2.coordinates[i]);
  }
  return distSum;
}

//I injected a hash treatment in std for type Point so it can be stored in unordered_map container,
//Strange thing is i found that using standard map for storing the clusters for some reason
//makes the algorithm produce slightly more accurate results but i used unordered_map anyway.

namespace std
{
    template<> struct hash<Point>
    {

        std::size_t operator()(Point const& p) const
        {
            size_t hashSum=0;
            for(int i=0;i<p.dimension;i++){
                std::size_t const h ( std::hash<double>{}(p.coordinates[i]) );
                hashSum+=h;
            }
            return hashSum;
        }
    };
}

//Some self-documenting code here

void loadPointsFromFileIntoVr(const std::string& filename,std::vector<Point>& elements)
{

    std::ifstream infile(filename);
    std::string line;
    while(std::getline(infile, line))
    {
        int currIndex=0;
        std::vector<double> currLineEls;
        for(int i=0; i<line.length(); i++)
        {
            if(line[i]==32||line[i]==10)
            {
                double coordinate = atof(line.substr(currIndex,i-currIndex).c_str());
                currLineEls.push_back(coordinate);
                currIndex=i+1;
            }
             if(i+1==line.length()){
               double coordinate = atof(line.substr(currIndex,i+1-currIndex).c_str());
                currLineEls.push_back(coordinate);
             }
        }

        elements.push_back(Point(currLineEls));
        currLineEls.clear();

    }
    infile.close();
}

//A template which implements the k-means clustering logic.
//Note that it only works on date types which have properly defined strict weak ordering
//and properly defined hash structure in std

template<typename VT>
class KMeansClustering
{
public:
    KMeansClustering(std::vector<VT> elements,int k,double (*calcDistFN)(const VT& ,const VT&));
    void printClustersToConsole();
    void printClustersToFile(std::string filename);
private:
    std::vector<VT> elements;
    std::unordered_map<VT,std::vector<VT>> clusters;
    double (*calcDistFN)(const VT& ,const VT&);
    int k;
    void clusterize();
    void setInitialCenters();
    void alocateElsInClusters(std::unordered_map<VT,std::vector<VT>>& clusters);
    VT findClosestCenter(const VT& element,std::unordered_map<VT,std::vector<VT>>& newClusters);
    void resetCenters(std::unordered_map<VT,std::vector<VT>>&);
    VT calcNewCenter(std::vector<VT>& elements);
    bool repeatedClustering();

};

//Some self-documenting code again

template<typename VT>
KMeansClustering<VT>::KMeansClustering(std::vector<VT> elements,int k,double (*calcDistFN)(const VT& ,const VT&))
{
    this->elements=elements;
    this->k=k;
    this->calcDistFN=calcDistFN;
    clusterize();
}

template<typename VT>
void KMeansClustering<VT>::printClustersToFile(std::string filename)
{
    std::ofstream onfile(filename);
    int clusterNum=1;
    for(const std::pair<VT,std::vector<VT>>& currPair:clusters)
    {
        onfile<<clusterNum<<std::endl;
        onfile<<"Center:"<<currPair.first;
        for(const VT& currEl:currPair.second)
        {
            onfile<<currEl;
        }
        onfile<<std::endl;
        clusterNum++;
    }
    onfile.close();
}

template<typename VT>
void KMeansClustering<VT>::printClustersToConsole()
{
    int clusterNum=1;
    for(const std::pair<VT,std::vector<VT>>& currPair:clusters)
    {
        std::cout<<clusterNum<<std::endl;
        std::cout<<"Center:"<<currPair.first;
        for(const VT& currEl:currPair.second)
        {
            std::cout<<currEl;
        }
        std::cout<<std::endl;
        clusterNum++;
    }
}

//Here starts the algorithm logic

template<typename VT>
void KMeansClustering<VT>::clusterize()
{
    setInitialCenters();
    alocateElsInClusters(clusters);
    while(repeatedClustering())
    {
    }
}

template<typename VT>
void KMeansClustering<VT>::setInitialCenters()
{
    srand( (unsigned)time( NULL ) );
    for(int i=0; i<k; i++)
    {
        int rn;
        while(clusters.count(elements[rn=rand()%elements.size()])!=0)
        {

        }
        clusters[elements[rn]]=std::vector<VT>();
    }
}

template<typename VT>
void KMeansClustering<VT>:: alocateElsInClusters(std::unordered_map<VT,std::vector<VT>>& clusters)
{
    for(const VT& currEl:elements)
    {
        if(clusters.count(currEl)==0)
        {
            clusters[findClosestCenter(currEl,clusters)].push_back(currEl);
        }
    }
}

template<typename VT>
VT KMeansClustering<VT>:: findClosestCenter(const VT& element,std::unordered_map<VT,std::vector<VT>>& newClusters)
{
    auto cmp=[](std::pair<VT,double> el1, std::pair<VT,double> el2)
    {
        return el1.second>el2.second;
    };;
    std::priority_queue<std::pair<VT,double>, std::vector<std::pair<VT,double>>, decltype(cmp) > pq(cmp);
    for(const std::pair<VT,std::vector<VT>>& currPair:newClusters)
    {
        pq.push(std::pair<VT,double>(currPair.first,calcDistFN(element,currPair.first)));
    }
    return pq.top().first;
}

template<typename VT>
bool KMeansClustering<VT>::repeatedClustering()
{
    std::unordered_map<VT,std::vector<VT>> newClusters;
    resetCenters(newClusters);
    alocateElsInClusters(newClusters);

    if(clusters == newClusters)
    {
        return false;
    }
    else
    {
        clusters=newClusters;
        return true;
    }


}

template<typename VT>
void KMeansClustering<VT>:: resetCenters(std::unordered_map<VT,std::vector<VT>>& newClusters)
{
    for(const std::pair<VT,std::vector<VT>>& currPair:clusters)
    {
        std::vector<VT> currCluster=currPair.second;
        currCluster.push_back(currPair.first);
        newClusters[calcNewCenter(currCluster)]=std::vector<VT>();
    }

}

template<typename VT>
VT KMeansClustering<VT>:: calcNewCenter(std::vector<VT>& elements)
{
    auto cmp=[](std::pair<VT,double> el1, std::pair<VT,double> el2)
    {
        return el1.second>el2.second;
    };;
    std::priority_queue<std::pair<VT,double>, std::vector<std::pair<VT,double>>, decltype(cmp) > pq(cmp);
    for(int i=0; i<elements.size(); i++)
    {
        double currSum=0;
        for(int j=0; j<elements.size(); j++)
        {
            if(i!=j)
            {
                currSum+=calcDistFN(elements[i],elements[j]);
            }
        }

        pq.push(std::pair<VT,double>(elements[i],currSum));

    }
    return pq.top().first;
}

//Here ENDS the whole application!

#endif // KMEANSCLUSTERING_H
