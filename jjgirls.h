#ifndef JJGIRLS_H
#define JJGIRLS_H

#include <string>
//using namespace std;

class jjgirl{
public:
    jjgirl();
    jjgirl(const std::string jjgirlName);
    jjgirl(const std::string jjgirlName, const int pageNumber);
    ~jjgirl();
    void SetJJGirlName(const std::string jjgirlName);
    void SetPageNumber(int pageNumber);
    //int GetPageNumber();
    std::string* GetUrls();
    std::string Url(int number);
private:
    std::string jjgirlName;
    int pageNumber;
    int imgNumberOfOnePage = 12;
    std::string* pUrls;

};

jjgirl::jjgirl(){

}
//函数实现
jjgirl::jjgirl(const std::string jjgirlName):jjgirlName(jjgirlName){

}

jjgirl::~jjgirl(){
    delete pUrls;
}

jjgirl::jjgirl(const std::string jjgirlName, const int pageNumber):jjgirlName(jjgirlName),pageNumber(pageNumber){
    this->jjgirlName = jjgirlName;
    this->pageNumber = pageNumber;
    int tempIndex=0;
    std::string urls[pageNumber*12];
    for(int i=0;i<pageNumber;i++){
        for(int j=0;j<imgNumberOfOnePage;j++){
            std::string url = "https://www.jjgirls.com/japanese/" + jjgirlName
                                + "/" + std::to_string(i+1) + "/" + jjgirlName
                                + "-" + std::to_string(j+1) + ".jpg";
            urls[tempIndex] = url;
            tempIndex++;
        }
    }
    pUrls = urls;
}

void jjgirl::SetJJGirlName(const std::string jjgirlName){
    this->jjgirlName = jjgirlName;
}

void jjgirl::SetPageNumber(int pageNumber){
    this->pageNumber = pageNumber;
}

std::string* jjgirl::GetUrls(){
    return this->pUrls;
}

std::string jjgirl::Url(int number){
    return this->pUrls[number];
}



#endif // JJGIRLS_H
