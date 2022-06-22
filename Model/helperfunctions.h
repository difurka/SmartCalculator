#ifndef SRC_MODEL_HELPERFUNCTIONS_H_
#define SRC_MODEL_HELPERFUNCTIONS_H_


#include <stack>
#include <queue>
#include <iostream>
#include <cmath>

#define ERROR -18

inline double numberToDouble(std::string str, int *position);
inline int isNumber(char symbol);
inline int isLetter(char symbol);
inline int isOperation(char symbol);
inline int isX(char symbol);
inline double letterToDouble(std::string str, const int *position);
inline double operationToDouble(std::string str, const int *position);
inline bool priorityOfSecondItem(double first, double second);
inline double calculateOfOne(double a, double operation);
inline double calculateOfPair(double a, double b, double operation);
inline std::string deleteZeros(std::string str);

#include "helperfunctions.cpp"
#endif  // SRC_MODEL_HELPERFUNCTIONS_H_
