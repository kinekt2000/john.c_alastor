#include <iostream>
#include <string>
#include <vector>


auto prefix(const std::string& image){
    std::vector<int> pi;
    pi.push_back(0);
    for(size_t i = 1, j = 0; i < image.size(); i++){
        if(image[i] != image[j]){
            if(j == 0){
                pi.push_back(0);
            }
            else{
                j = pi[j-1];
                i--;
            }
        }
        else{
            pi.push_back(j+1);
            j++;
        }
    }
    return pi;
}


auto KMPA(const std::string& haystack, const std::string& needle){
    auto pi = prefix(needle);
    std::vector<int> overlaps;

    for(size_t i = 0, j = 0; i < haystack.size(); i++){
        if(haystack[i] == needle[j]){
            j++;
            if(j == needle.size()){
                overlaps.push_back(i - j + 1);
                j = pi[j-1];
            }
        }
        else{
            if(j != 0){
                j = pi[j-1];
                i--;
            }
        } 
    }
    return overlaps;
}


// moves base, until it becomes shifted
auto cyclicShift(const std::string& base, const std::string& shifted){
    auto pi = prefix(base);
    std::vector<int> overlaps;

    auto size = base.size();
    if(size != shifted.size())
        return overlaps;

    for(size_t i = 0, j = 0; i < size*2-1; i++){
        if(shifted[i%size] == base[j]){
            j++;
            if(j == size){
                overlaps.push_back(i - j + 1);
                return overlaps;
            }
        }
        else{
            if(j != 0){
                j = pi[j-1];
                i--;
            }
        }
    }
    return overlaps;
}


int main(){

    std::string shifted;
    std::string base;

    std::cin >> shifted;
    std::cin >> base;

    auto overlaps = cyclicShift(base, shifted);

    for(auto it = overlaps.begin(); it != overlaps.end(); it++){
        if(it != overlaps.begin())
            std::cout << ",";        
        std::cout << *it; 
    }
    if(overlaps.empty())
        std::cout << -1;
    std::cout << std::endl;

    return 0;
}
