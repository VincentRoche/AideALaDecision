#ifndef B1_Variable_hpp
#define B1_Variable_hpp

#include <stdio.h>
#include <vector>

using namespace std;

class Variable {
    int numero;
    vector<int> domaine; // Valeurs que la variable peut prendre
    
public:
    Variable(int numero, vector<int> domaine);
};

#endif /* B1_Variable_hpp */
