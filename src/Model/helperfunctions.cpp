int isNumber(char symbol) {
    int result = 0;
    if ('0' <= symbol && symbol <= '9') result = 1;
    return result;
}

int isX(char symbol) {
    return (symbol == 'x' || symbol == 'X') ? 1 : 0;
}

int isLetter(char symbol) {
    int result = 0;
    if (symbol == 'c' || symbol == 's' || symbol == 't' ||
        symbol == 'C' || symbol == 'S' || symbol == 'T' ||
        symbol == 'L' || symbol == 'l'|| symbol == 'q')
            result = 1;
    return result;
}

int isOperation(char symbol) {
    int result = 0;
    if (symbol == '+' || symbol == '-' || symbol == '*' ||
        symbol == '/' || symbol == '^' || symbol == 'm')
            result = 1;
    return result;
}

double letterToDouble(std::string str, const int *position) {
    double result;
    switch (str[*position]) {
        case 'c': result = -9; break;
        case 's': result = -10; break;
        case 't': result = -11; break;
        case 'C': result = -12; break;
        case 'S': result = -13; break;
        case 'T': result = -14; break;
        case 'l': result = -15; break;
        case 'L': result = -16; break;
        case 'q': result = -17; break;
    }
    return result;
}

double operationToDouble(std::string str, const int *position) {
    double result;
    switch (str[*position]) {
        case '+': result = -3; break;
        case '-': result = -4; break;
        case '*': result = -5; break;
        case '/': result = -6; break;
        case '^': result = -7; break;
        case 'm': result = -8; break;
    }
    return result;
}

double numberToDouble(std::string str, int *position) {
    double result = 0.0;
    int i = *position;
    std::string strWithNumber = "";
    while (isNumber(str[i])) {
        strWithNumber += str[i];
        i++;
    }
    if (strWithNumber.size() > 16) {
        result = ERROR;
    } else {
        if (str[i] == '.' || str[i] == ',') {
            strWithNumber += ".";
            ++i;
            while (isNumber(str[i])) {
                strWithNumber += str[i];
                ++i;
            }
            if (str[i] == 'e' || str[i] == 'E') {
                strWithNumber += "e";
                ++i;
                if (((str[i] == '+' || str[i] == '-') && isNumber(str[i + 1])) || isNumber(str[i])) {
                    strWithNumber += str[i];
                    ++i;
                    while (isNumber(str[i])) {
                        strWithNumber += str[i];
                        ++i;
                    }
                } else {
                    result = ERROR;
                }
            }
        }
        if (result != ERROR) result = atof(strWithNumber.c_str());
    }
    *position = i - 1;
    return result;
}

bool priorityOfSecondItem(double first, double second) {
    bool result = true;
        if (first == -3 || first == -4) {
            result = (second <= -3) ? true : false;
        } else if (first == -5 || first == -6) {
            result = (second <= -5) ? true : false;
        } else if (first <= - 7) {
            result = (second <= -7) ? true : false;
        }
    return result;
}

double calculateOfPair(double a, double b, double operation) {
    int oper = operation;
    double result = 0;
    switch (oper) {
        case -3: result = a + b; break;
        case -4: result = a - b; break;
        case -5: result = a * b; break;
        case -6: result = a / b; break;
        case -7: result = pow(a, b); break;
        case -8: result = fmod(a, b); break;
    }
    return result;
}

double calculateOfOne(double a, double operation) {
    int oper = operation;
    double result = 0;
    switch (oper) {
        case -9: result = cos(a); break;
        case -10: result = sin(a); break;
        case -11: result = tan(a); break;
        case -12: result = acos(a); break;
        case -13: result = asin(a); break;
        case -14: result = atan(a); break;
        case -15: result = log10(a); break;
        case -16: result = log(a); break;
        case -17: result = sqrt(a); break;
    }
    return result;
}

std::string deleteZeros(std::string str) {
    std::string result = str;
    size_t len = str.size();
    if (str[len - 1] == '0') {
        while (str[len - 1] == '0')
            --len;
        }
    if (str[len - 1] == '.' || str[len - 1] == ',') --len;
    if (len != str.size()) result = str.substr(0, len);
    return result;
}
